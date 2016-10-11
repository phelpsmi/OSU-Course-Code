#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


void start_error(const char *msg);
void loop_error(const char *msg);
int setup_server();
void server_loop(int socketfd);
void decrypt(char *message, char *key, int message_len);
void space_to_bracket(char* s, int len);
void bracket_to_space(char* s, int len);
			
char server_type = 'd';


int main(int argc, char *argv[]){

	if (argc < 2) {
    	start_error("No port provided\n");
 	}
 	int newsockfd, clilen, n;

	int portno = atoi(argv[1]);
	int sockfd = setup_server(portno);
	server_loop(sockfd);

}

void start_error(const char *msg){
	perror(msg);
	exit(1);
}

void loop_error(const char *msg){
	perror(msg);
}

int setup_server(int portno){
	

	//Open the socket and send error if it can't open.
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		start_error("Could not open socket\n");
	}

	//Create socket address struct
	struct sockaddr_in address;
	bzero((char *) &address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(portno);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
		start_error("Failed to bind\n");

	listen(sockfd, 5);

	return sockfd;

}

void server_loop(int sockfd){
	int newsockfd, clilen, n;
	struct sockaddr_in cli_addr;
	pid_t pid;

	clilen = sizeof(cli_addr);
	while(1){
		//waits for a connection to come in
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0){
			loop_error("accept() error");
			continue;
		}

		//when we receive a new connection, we want to fork off the process
		//so that we can receive other connections at the same time
		pid = fork();
		if(pid == 0){
			char *message, *key;
			int message_len;
			char client_type;

			//get the client type sent by the client
			n = read(newsockfd, &client_type, sizeof(char));
			if (n < 0){
				loop_error("Error reading client type\n");
				exit(EXIT_FAILURE);
			}

			//Sends back our server type
			n = write(newsockfd, &server_type, sizeof(char));
			if (n < 0){
				loop_error("Error sending server type\n");
				exit(EXIT_FAILURE);
			}

			//stop if the client and server don't match
			if(client_type != server_type){
				exit(EXIT_FAILURE);
			}

			//gets the message length from the client
			n = read(newsockfd, &message_len, sizeof(int));
			if(n < 0){
				loop_error("Error getting message length\n");
				exit(EXIT_FAILURE);
			}

			//give our message and key string the proper amount of memory
			message = malloc(message_len);
			key = malloc(message_len);

			//read in the message
			n = read(newsockfd, message, message_len);
			if (n < 0){
				loop_error("Error reading socket for message\n");
				free(message); free(key); 
				exit(EXIT_FAILURE);
			}

			//read in the key
			n = read(newsockfd, key, message_len);
			if (n < 0){
				loop_error("Error reading socket for key\n");
				free(message); free(key); 
				exit(EXIT_FAILURE);
			}

			//decrypt the message
			decrypt(message, key, message_len);

			//write the message back to client
			n = write(newsockfd, message, message_len);

			if (n < 0){
				loop_error("Error writing response to socket\n");
				free(message); free(key);
				exit(EXIT_FAILURE);
			}

			exit(0);
		}

	}

}

void decrypt(char* message, char* key, int message_len){
	int i;
	char letter;

	space_to_bracket(message, message_len);
	space_to_bracket(key, message_len);

	for(i = 0; i < message_len; i++){
		letter = message[i];
		letter = letter - (key[i] - '@');
		
		if (letter < 'A')
			letter = letter + 27;
		
		message[i] = letter;
	}

	message[message_len] = '\0';
	bracket_to_space(message, message_len);
}

void space_to_bracket(char* s, int len){
	int i;
	for(i = 0; i < len; i++){
		if( s[i] == ' ')
			s[i] = '[';
	}
}

void bracket_to_space(char* s, int len){
	int i;
	for(i = 0; i < len; i++){
		if( s[i] == '[')
			s[i] = ' ';
	}
}