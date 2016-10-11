#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>



void start_error(const char *msg);
int valid_string(char* s);
void extract_file(char* file_name, char** s);
void send_request(int sockfd, char* message, char* key);
int setup_server(int portno);
int valid_key(char* key, char* message);

//global client_type variable
char client_type = 'e';


int main(int argc, char* argv[]){
	//return error if we don't have the proper argument count
	if(argc < 4)
		start_error("Wrong argument count\n");

	char *key, *message;
	char *message_name = argv[1];
	char *key_name = argv[2];
	int port = atoi(argv[3]);

	//Use our file names to get the actuall message
	//and key strings
	extract_file(message_name, &message);
	extract_file(key_name, &key);

	//Some simple validation on the imputs
	if(!port) start_error("Invalid port or 0 port");
	if(!valid_string(message)) start_error("Invalid message");
	if(!valid_string(key)) start_error("Invalid key");
	if(!valid_key(key, message)) start_error("Key too short");

	//Now that we have the information, we send the request to the server
	//the setup_server call returns the socket file descriptor and passes it in
	send_request(setup_server(port), message, key);

}

//basic send error message and quit
void start_error(const char *msg){
	errno = 1;
	perror(msg);
	exit(1);
}

//validates key length by comparing it to the message length
int valid_key(char* key, char* message){
	if(strlen(key) < strlen(message))
		return 0;
	return 1;
}

//checks if a string only contains the allowed characters
//A-Z or space.
int valid_string(char* s){
	int i;
	for(i = 0; i < strlen(s); i++){
		if(s[i] == '\n'){
			s[i] = '\0';
			return 1;
		}
		if(s[i] < 'A' && s[i] != ' ' || s[i] > 'Z' ){
			return 0;
		}
	}
	return 1;
}

//takes a file name and a pointer to a string
//open a file with the file name and dumps the contents 
//into a new string which the s param is pointed to
void extract_file(char* file_name, char** s){
	FILE *file = fopen(file_name, "rb");
	if(file == NULL) start_error("Invalid file name");

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	*s = malloc(size + 1);
	fread(*s, size, 1, file);
	fclose(file);
	(*s)[size] = '\0';

}

void send_request(int sockfd, char *message, char *key){
	int len = strlen(message);
	int n;
	char *response = malloc(sizeof(char)*len);
	char server_type;

	//tells server if it's a decription or encryption client
	n = write(sockfd, &client_type, sizeof(char));
	if (n < 0) start_error("Error sending client type");

	//reads the server type from the server
	n = read(sockfd, &server_type, sizeof(char));
	if (n < 0) start_error("Error reading server type");

	//We don't want to continue if the types aren't the same
	if(client_type != server_type)
		start_error("Error: cannot use decryption server for encryption");

	//Tell server what the file length will be so it can
	//establish a propper buffer
	n = write(sockfd, &len, sizeof(int));
	if (n < 0) start_error("Error sending file length");

	//Sends message to server for encryption 
	n = write(sockfd, message, len);
	if (n < 0) start_error("Error sending message");

	//Sends the encryption key to the server
	n = write(sockfd, key, len);
	if (n < 0) start_error("Error sending key");

	//Reads back the encrypted message from the server
	n = read(sockfd, response, len);
	if (n < 0) start_error("Error reading response");

	//We can simply print out the message but since it probably
	//won't be null terminated, we want to manually select each
	//character to print instead of using printf on the entire string
	int i;
	for(i = 0; i < len; i++){
		printf("%c", response[i]);
	}
	//print out a new line as instructed by the assignment.
	printf("\n");

	close(sockfd);
	free(response);
	free(message);
	free(key);
}

int setup_server(int portno){
	//Open the socket and send error if it can't open.
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		start_error("Could not open socket");
	}

	//Create socket address struct
	struct sockaddr_in address;
	bzero((char *) &address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(portno);
	address.sin_addr.s_addr = INADDR_ANY;

	if (connect(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0)
		start_error("Failed to bind\n");

	return sockfd;

}