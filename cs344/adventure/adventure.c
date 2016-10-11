#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

FILE ** create_files();
char ** pick_rooms();
void write_contents(FILE** files, char ** room_names);
void play_game(FILE** files);
void get_room_name(FILE* file, char * name);
void get_connections(FILE** files, int selected, int* connections);
char* get_room_type(FILE* file);

int main(){

	FILE ** rooms;

	int i;
	rooms = create_files();
	play_game(rooms);
	return 0;
}

FILE **create_files(){
	char pid[20];
	const char *file_names[7] = {"/file1.swag", "/file2.swag", "/file3.swag", "/file4.swag", "/file5.swag", "/file6.swag", "/file7.swag"};
	char file_name[50];
	char ** room_names = pick_rooms();
	char file_dir[50];

	snprintf(pid, sizeof(pid), "%d", getpid());

	FILE * files[7];
	int i;
	
	strcpy(file_dir, "./phelpsmi.rooms.");
	strcat(file_dir, pid);
	mkdir(file_dir, S_IRWXU);

	for(i = 0; i < 7; i++){
		strcpy(file_name, file_dir);
		strcat(file_name, file_names[i]);
		files[i] = fopen(file_name, "w+");
	}

	write_contents(files, room_names);

	for(i = 0; i < 7; i++){
		strcpy(file_name, file_dir);
		strcat(file_name, file_names[i]);
		files[i] =fopen(file_name, "r");
	}


	return files;
}

char** pick_rooms(){
	const char *room_names[10] = {"Atrium", "Bedroom", "Dungeon", "Bathroom", "Hallway", "Kitchen", "Roof", "Porch", "DiningRoom", "Garage"};
	char** picked_names = malloc(7*sizeof(char*));
	int i, j, pick, reselect;
	srand(time(NULL));

	for(i = 0; i < 7; i++){
		reselect = 0;
		picked_names[i] = malloc((10 * sizeof(char)));
		pick = rand()%10;
		for(j = 0; j < i; j++){
			if(strcmp(room_names[pick], picked_names[j]) == 0){
				reselect = 1;
			}
		}
		if(reselect){ i--; }
		else{ strcpy(picked_names[i], room_names[pick]); }
	}

	return picked_names;

}

void write_contents(FILE** files, char ** room_names){
	//file 1
	fprintf(files[0], "ROOM NAME: %s\n", room_names[0]);
	fprintf(files[0], "CONNECTION 1: %s\n", room_names[1]);
	fprintf(files[0], "CONNECTION 2: %s\n", room_names[2]);
	fprintf(files[0], "CONNECTION 3: %s\n", room_names[3]);
	fprintf(files[0], "CONNECTION 4: %s\n", room_names[4]);
	fprintf(files[0], "ROOM TYPE: START_ROOM\n");

	fprintf(files[1], "ROOM NAME: %s\n", room_names[1]);
	fprintf(files[1], "CONNECTION 1: %s\n", room_names[0]);
	fprintf(files[1], "CONNECTION 2: %s\n", room_names[2]);
	fprintf(files[1], "CONNECTION 3: %s\n", room_names[3]);
	fprintf(files[1], "CONNECTION 4: %s\n", room_names[4]);
	fprintf(files[1], "ROOM TYPE: MID_ROOM\n");

	fprintf(files[2], "ROOM NAME: %s\n", room_names[2]);
	fprintf(files[2], "CONNECTION 1: %s\n", room_names[0]);
	fprintf(files[2], "CONNECTION 2: %s\n", room_names[1]);
	fprintf(files[2], "CONNECTION 3: %s\n", room_names[3]);
	fprintf(files[2], "CONNECTION 4: %s\n", room_names[4]);
	fprintf(files[2], "ROOM TYPE: MID_ROOM\n");

	fprintf(files[3], "ROOM NAME: %s\n", room_names[3]);
	fprintf(files[3], "CONNECTION 1: %s\n", room_names[0]);
	fprintf(files[3], "CONNECTION 2: %s\n", room_names[1]);
	fprintf(files[3], "CONNECTION 3: %s\n", room_names[2]);
	fprintf(files[3], "CONNECTION 4: %s\n", room_names[5]);
	fprintf(files[3], "ROOM TYPE: MID_ROOM\n");

	fprintf(files[4], "ROOM NAME: %s\n", room_names[4]);
	fprintf(files[4], "CONNECTION 1: %s\n", room_names[0]);
	fprintf(files[4], "CONNECTION 2: %s\n", room_names[1]);
	fprintf(files[4], "CONNECTION 3: %s\n", room_names[2]);
	fprintf(files[4], "CONNECTION 4: %s\n", room_names[6]);
	fprintf(files[4], "ROOM TYPE: MID_ROOM\n");

	fprintf(files[5], "ROOM NAME: %s\n", room_names[5]);
	fprintf(files[5], "CONNECTION 2: %s\n", room_names[3]);
	fprintf(files[5], "CONNECTION 3: %s\n", room_names[6]);
	fprintf(files[5], "ROOM TYPE: MID_ROOM\n");

	fprintf(files[6], "ROOM NAME: %s\n", room_names[6]);
	fprintf(files[6], "CONNECTION 1: %s\n", room_names[4]);
	fprintf(files[6], "CONNECTION 2: %s\n", room_names[5]);
	fprintf(files[6], "ROOM TYPE: END_ROOM\n");

	int i;
	for(i = 0; i < 7; i++){
		fclose(files[i]);
	}
}

void play_game(FILE** files){
	int step_count = 0;
	char steps[100][15];
	int found_end = 0, good_choice = 0;
	int cur_file = 0;
	char choice[100];
	int* connections = malloc(sizeof(int)*10);
	char *room_name = malloc(sizeof(char)*15);
	int i, j;

	while(!found_end){
		get_room_name(files[cur_file], room_name);
		printf("CURRENT LOCATION: %s\n", room_name);
		printf("POSSIBLE CONNECTIONS: ");
		get_connections(files, cur_file, connections);
		for(i = 1; i <= connections[0]; i++){
			if(i == connections[0]){
				get_room_name(files[connections[i]], room_name);
				printf("%s.\n", room_name);
			} else {
				get_room_name(files[connections[i]], room_name);
				printf("%s, ", room_name);
			}
		}

		printf("WHERE TO?>");
		scanf("%s", choice);
		good_choice = 0;
		for(i = 0; i < 7; i++){
			get_room_name(files[i], room_name);
			if(i != cur_file && strcmp(choice, room_name) == 0){
				cur_file = i;
				good_choice = 1;
				i = 7;
			}
		}
		if(!good_choice){
			printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
		} else {
			strcpy(steps[step_count], choice);
			step_count++;
		}
		if(strcmp(get_room_type(files[cur_file]), "END_ROOM") == 0){
			found_end = 1;
			printf("YOU HAVE FOUND THE END ROOM. CONGRAGULATIONS!\n");
			printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", step_count);
			for(i = 0; i < step_count; i++){
				printf("%s\n", steps[i]);
			}
		}
	}

}

void get_room_name(FILE* file, char * name){
	rewind(file);
	char room_name[10];\
	fscanf(file, "ROOM NAME: %s", room_name);
	strcpy(name, room_name);
	rewind(file);
}
void get_connections(FILE** files, int selected, int* connections){
	int i, j = 0;
	int *k = malloc(sizeof(int));
	char buffer[10];
	char room_name[10];
	char line[100];
	rewind(files[selected]);
	fgets(line, 100, files[selected]);
	while(fgets(line, 100, files[selected]) != NULL){
		if(sscanf(line, "CONNECTION %d: %s", k, buffer)){
			for(i = 0; i < 7; i++){
				if(i != selected){
					get_room_name(files[i], room_name);
					if(strcmp(buffer, room_name) == 0){
						j++;
						connections[j] = i;
					}
				}
			}
		}
	}
	connections[0] = j;
	rewind(files[selected]);
}

char* get_room_type(FILE* file){
	char type[10];
	char line[100];

	
	while(fgets(line, 100, file) != NULL){
		if(strstr(line, "START_ROOM")){
			strcpy(type, "START_ROOM");
			return type;
		}
		else if(strstr(line, "MID_ROOM")){
			strcpy(type, "MID_ROOM");
			return type;
		}
		else if(strstr(line, "END_ROOM")){
			strcpy(type, "END_ROOM");
			return type;
		}
	}
	rewind(file);
	return NULL;
}