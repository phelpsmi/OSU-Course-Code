#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//Global for the user input. 
//Has variables for all sections of the parsing process.
struct Command{
	char raw[300];
	char** parsed;
	int word_count;
	char* prompt;
	char* in_file;
	char* out_file;
	int has_in_file, has_out_file;
	char** args;
	int arg_count;
	int background;
} input;

//Sets of global for the set of child process.
//Since it's need throughout several parts of the code,
//It is important to have access anywhere.
struct ProcessList{
	int count;
	pid_t pids[100];
	pid_t foreground;
	int last_status;
} children;

pid_t pid = 0;
int shell_status = 0;
const char *blank_argv[1] = { NULL };

void input_loop();
void strip_comment();
void parse_input();
void clear_for_exit();
int run_input();
void get_args();
void get_args();
void free_input();
void check_children();
void ctrl_c_handler(int _);


int main(){
	
	children.count = 0;
	children.last_status = 0;

	//Need to handle CTRL-C signal.
	signal(SIGINT, ctrl_c_handler);

	input_loop();

	return 1;
}

void check_children(){
	int i;
	int status;
	for(i = 0; i < children.count; i++){
		if(waitpid(children.pids[i], &status, WNOHANG) > 0){
			printf("Background process finished: %d\n", children.pids[i]);
			if (WIFEXITED(status))
            	printf("Exited: %d\n", WEXITSTATUS(children.last_status));
        	else if (WIFSIGNALED(status))
            	printf("Stop signal: %d\n", WTERMSIG(status));
        	else if (WIFSTOPPED(status))
        		printf("Termination signal: %d\n", WSTOPSIG(status));
			children.pids[i] = children.pids[--children.count];
		}
	}
}

//hands the sigint instead of exiting the shell.
//First it makes sure the current foreground process
//is still running and kills it if it is.
void ctrl_c_handler(int _){
	int status;
	if(waitpid(children.foreground, &status, WNOHANG) == 0 && pid != 0){
		kill(children.foreground, SIGINT);
	}
}

//Runs through the shell input and execution functions.
void input_loop(){
	int cont = 1;

	while(cont){
		//first check if any children have finished.
		check_children();

		//Then get input from the user.
		printf(": "); fflush( stdout );
		fgets(input.raw, 201, stdin );

		//Run our three parsing functions
		strip_comment();
		parse_input();
		get_args();

		//Run the input and get the return value so we know
		//If it got an exit.
		cont = run_input();

		//Finally we just free the points.
		free_input();
	}

}

//Replaces the '#' character or the new line with a null terminator
void strip_comment(){
	int i;
	for(i = 0; i < strlen(input.raw); i++){
		if(input.raw[i] == '#' || input.raw[i] == '\n'){
			input.raw[i] = '\0';
			return;
		}
	}
}

//Parses the raw input by placing null characters in the spaces between
//arguments. Then it simply has the parsed array point to the starting character
//of each argument.
void parse_input(){
	int cur_word = 0;
	int i = -1;
	int got_first_word = 0;
	input.parsed = malloc(sizeof(char*) * strlen(input.raw));

	if(input.raw[0] == '\0'){
		input.word_count = 0;
		return;
	}

	while(input.raw[++i] != '\0'){
		if(input.raw[i] == ' ' && input.raw[i+1] != ' ' && input.raw[i+1] != '\0'){
			input.raw[i] = '\0';
			input.parsed[cur_word] = &(input.raw[i+1]);
			got_first_word = 1;
			cur_word++;


		
		} else {
			if(!got_first_word){
				input.parsed[cur_word] = &(input.raw[i]);
				cur_word++;
				got_first_word = 1;
			}
		}
	}

	input.word_count = cur_word;
	input.prompt = input.parsed[0];
	
}

//Pulls the args out of the parsed input. This is needed to make sure
//input and output files don't go into the argv of the exec function.
//Also saves the input and output files if they were specified in the input.
void get_args(){
	int i, arg_count = 0;
	input.has_out_file = 0;
	input.has_in_file = 0;
	input.background = 0;
	input.args = malloc(sizeof(char*) * input.word_count + 1);
	for(i = 0; i < input.word_count; i++){
		if(strcmp(input.parsed[i], "<") == 0){
			i++;
			if(i < input.word_count){
				input.in_file = input.parsed[i];
				input.has_in_file = 1;
			}
		} else if(strcmp(input.parsed[i], ">") == 0){
			i++;
			if(i < input.word_count){
				input.out_file = input.parsed[i];
				input.has_out_file = 1;
			}
		} else if (strcmp(input.parsed[i], "&") == 0){
			input.background = 1;
		} else {
			input.args[arg_count] = input.parsed[i];
			arg_count++;
		}
	}
	input.args[arg_count] = NULL;
	input.arg_count = arg_count;
	
}

//Once parsing has been completed, we can run the input.
int run_input(){
	//First check if the prompt is blank then check if the prompt is one of the three built in commands
	if(input.arg_count == 0){ return 1; }
	else if(strcmp(input.prompt, "exit") == 0){
		return 0;
	} else if(strcmp(input.prompt, "cd") == 0){
		if(input.arg_count > 1){
			chdir(input.args[1]);
		} else {
			chdir(getenv("HOME"));
		}
	} else if(strcmp(input.prompt, "status") == 0){
		if (WIFEXITED(children.last_status))
            printf("Exited: %d\n", WEXITSTATUS(children.last_status));
        else if (WIFSIGNALED(children.last_status))
            printf("Stop signal: %d\n", WTERMSIG(children.last_status));
        else if (WIFSTOPPED(children.last_status))
        	printf("Termination signal: %d\n", WSTOPSIG(children.last_status));
    //If the command is not built in we create a child to exec it.
	} else {
		pid = fork();
		if(pid == 0){
			int infile;
        	int outfile;

        	//If an input file was specified then we need to redirect the input.
        	if(input.has_in_file){
		
        		infile = open(input.in_file, O_RDONLY);
        		//if the file id is less than 0 then it couldn't find the file so we print an error and exit
        		if(infile < 0){
        			printf("smallsh: cannot open %s for input\n", input.in_file);
        			free_input();
        			exit(1);
        		} else {
        			dup2(infile, STDIN_FILENO);
        			close(infile);
        		}
        	//If the input is specified to be background, then send the input/output to dev/null
        	//Only if no file was specified.
        	} else if(input.background){
        		infile = open("/dev/null", O_RDONLY);
        		dup2(infile, STDIN_FILENO);
        		close(infile);
        	}

        	//If an output file was specified then we need to redirect the output
        	if(input.has_out_file){

        		outfile = open(input.out_file, O_WRONLY | O_CREAT, 0744);
        		//If the file is is less than 0 then there was an error openning or creating the file.
        		if(outfile < 0){
        			printf("smallsh: cannot open %s for output\n", input.out_file);
        			free_input();
        			exit(1);
        		} else {
        			dup2(outfile, STDOUT_FILENO);
        			close(outfile);
        		}
        	//If the input is specified to be background, then send the input/output to dev/null
        	//Only if no file was specified.
        	} else if(input.background){
        		outfile = open("/dev/null", O_WRONLY | O_CREAT, 0744);
        		dup2(outfile, STDOUT_FILENO);
        		close(outfile);
        	}

        	//execute the input and if the return is negative then we print an error.
			if(execvp(input.prompt, input.args) < 0){
				printf("%s: no such file or directory\n", input.prompt);
			}
			exit(1);
		} else {
			//If this is the parent process then we either wait for the child to finish
			//or add it onto the array of background children.
			if(input.background) {
				children.pids[children.count++] = pid;
				printf(" Background PID:%d\n", pid);
			} else {
				children.foreground = pid;
				waitpid(pid, &children.last_status, 0);
			}
		}
	}

	return 1;
}

void free_input(){
	//We only need to free the array of character pointers.
	//This is because everything else just points to something
	//In the input.raw string which is static.
	free(input.parsed);
	free(input.args);
}

