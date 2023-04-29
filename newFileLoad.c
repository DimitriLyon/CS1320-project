#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct userDat_struct{
	char username[32];
	char password[64];
	double money;
} userDat;

userDat accessableUsers[5];
int userCount = 5;
userDat *loggedInUser;

int initializeAccounts(char *filename);
int saveData(char *filename);
int login();

int main(int argc, int argv) {
	printf("%ld\n", sizeof(userDat));
	
	if(initializeAccounts("loginInfo.txt")) {
		return -1;
	}
	
	printf("%lf\n", accessableUsers[0].money);
	printf("%lf\n", (accessableUsers+1)->money);
	printf("%lf\n", (accessableUsers+2)->money);
	
	login();
	
	saveData("loginOutfo.txt");
	
	return 0;
}


/** 
	Initializes the array of accounts.
	Reads data from the file at filename.
	data file in the format:
	
	<username> <password> <balance>
	<username> <password> <balance>
	...
	
	where username has a maximum length of 32 including null-terminator
	where password has a maximum length of 64 including null-terminator
	
	sets global accessableUsers to point to the first index of the array
	
	prints to stdout on error.
	
	if fileOpen fails, errors.
	
	if file is shorter than userCount, errors
	
	if file is longer than userCount, only reads the first userCount entries
	
	returns -1 on error.
	returns 0 on success.
	
*/
int initializeAccounts(char *filename) {
	//Initialize local vars
	FILE *dataFile;
	int readCount; // Stores the number of reads the fscanf calls perform
	int i; //Iterator variable for reading data into user array
	
	//Open file at filename in text read mode.
	dataFile = fopen(filename, "r");
	
	//Check if open was successful
	if(dataFile == NULL) {
		//If not, output failure to stdout and return -1
		fprintf(stdout, "Error opening file: %s\n", strerror(errno));
		return -1;
	}
	
	
	//Read the number of users in the file
	//Now read that many entries form the file.
	for(i = 0; i < userCount; i++) {
		
		//Check if reached end of file while still supposed to be reading
		//If so, error
		if(feof(dataFile)) {
			fclose(dataFile);
			//If not, output failure to stdout and return -1
			fprintf(stdout, "Error, not enough user accounts in file.\n");
			return -1;
		}
		
		readCount = fscanf_s(dataFile, " %s %s",
				&accessableUsers[i].username, 32,
				&accessableUsers[i].password, 64 );
		readCount += fscanf(dataFile, " %lf", &accessableUsers[i].money);
		
		//Needs to read 3 things per line.
		//If doesn't free memory and throw error
		if(readCount < 3) {
			fclose(dataFile);
			//If not, output failure to stdout and return -1
			fprintf(stdout, "Error: malformed data file.\n");
			
			fprintf(stdout, "%d objects read\n", readCount);
			return -1;
		}
	}
	
	fclose(dataFile);
	return 0;
}


int login() {
	char username[32]; //Bujffer for username
	char password[64]; //Buffer for password
	int i; //Iterator for linear search
		
	
	//Prompt user for username
	printf("Username: ");
	//Take username from input.  Max 32 char
	scanf_s(" %s", username, 32);
	//Prompt user for password
	printf("Password: ");
	//Take password from input.  Max 64 char
	scanf_s(" %s", password, 64);
	
	//Iterate through list of users
	for(i = 0; i < userCount; i++) {
		//Check if username matches
		if(strcmp(username, accessableUsers[i].username) == 0) {
			//Compare password of user to entered password
			if(strcmp(password, accessableUsers[i].password) == 0) {
				//Set loggedInUser to point to the correct pointer.
				loggedInUser = accessableUsers + i; 
				printf("Logged in as username: %s\n", username);
				return 0;
			} else {
				printf("Incorrect password\n");
				return -1;
			}
		}
	}
	printf("User not found.\n");
	return -1;
}

int saveData(char *filename) {
	FILE *optFile; //Handle for file to be written to
	int i; //Iterator
	
	
	optFile = fopen(filename, "w");
	//If file failed to open, report error and return -1.
	if(optFile == NULL) {
		//Report error.
		fprintf(stdout, "Error opening file: %s\n", strerror(errno));
		return -1;
	}
	
	fprintf(optFile, "%d\n", userCount);
	for(i = 0; i < userCount; i++) {
		fprintf(optFile, "%s %s %lf\n", accessableUsers[i].username, accessableUsers[i].password, accessableUsers[i].money);
		fflush(optFile);
	}
	
	fclose(optFile);
	
	return 0;
}