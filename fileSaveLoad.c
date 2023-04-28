#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct userDat_struct{
	char username[32];
	char password[64];
	double money;
} userDat;

userDat *accessableUsers;
int userCount = -1;

int initializeAccounts(char *filename);
int saveData(char *filename);

int main(int argc, int argv) {
	printf("%ld\n", sizeof(userDat));
	
	if(initializeAccounts("badData.txt")) {
		return -1;
	}
	
	printf("%lf\n", accessableUsers[0].money);
	printf("%lf\n", (accessableUsers+1)->money);
	printf("%lf\n", (accessableUsers+2)->money);
	
	saveData("loginOutfo.txt");
	
	return 0;
}

/**
	Function that deallocates the memory for the accessableUsers
	Additionally, sets userCount to -1
 */
void deallocAccountMem() {
	//free memory for array
	free(accessableUsers);
	//Set accessableUsers to NULL
	accessableUsers = NULL;
	//Set userCount to -1
	userCount = -1;
}


/** 
	Initializes the array of accounts.
	Reads data from the file at filename.
	data file in the format:
	
	<userCount>
	<username> <password> <balance>
	<username> <password> <balance>
	...
	
	where username has a maximum length of 32 including null-terminator
	where password has a maximum length of 64 including null-terminator
	
	sets global accessableUsers to point to the first index of the allocated array
	sets global userCount to the number of users allocated.
	
	prints to stdout on error.
	
	if fileOpen fails, errors.
	
	if calloc fails, errors.
	
	if file is shorter than userCount, errors and frees accessableUsers
	
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
	
	//Attempt to read number of accounts in data file
	readCount = fscanf(dataFile, " %d", &userCount);
	
	//Check if fscanf call read less than 1 thing from the file
	if(readCount < 1) {
		//Handle error
		fprintf(stdout, "Error reading number of accounts in file\n");
		//Attempt to close file
		if(fclose(dataFile) == EOF) {
			//If not, output failure to stdout and return -1
			fprintf(stdout, "Error closing file.\n");
		}
		return -1;
	}
	
	//Attempt to allocate memory for the array of account info.
	accessableUsers = (userDat *) calloc((size_t) userCount, sizeof(userDat)); 
	
	//Check if calloc failed
	if(accessableUsers == NULL) {
		//Handle error
		fprintf(stdout, "Error allocating memory for userData\n");
		//Attempt to close file
		if(fclose(dataFile) == EOF) {
			//If not, output failure to stdout and return -1
			fprintf(stdout, "Error closing file.\n");
		}
		return -1;
	}
	
	//Read the number of users in the file
	//Now read that many entries form the file.
	for(i = 0; i < userCount; i++) {
		
		//Check if reached end of file while still supposed to be reading
		//If so, error
		if(feof(dataFile)) {
			if(fclose(dataFile) == EOF) {
				//If not, output failure to stdout and return -1
				fprintf(stdout, "Error closing file.\n");
			}
			//If not, output failure to stdout and return -1
			fprintf(stdout, "Error, not enough user accounts in file.\n");
			deallocAccountMem();
			return -1;
		}
		
		readCount = fscanf_s(dataFile, " %s %s",
				&accessableUsers[i].username, 32,
				&accessableUsers[i].password, 64 );
		readCount += fscanf(dataFile, " %lf", &accessableUsers[i].money);
		
		//Needs to read 3 things per line.
		//If doesn't free memory and throw error
		if(readCount < 3) {
			//Try to close file
			if(fclose(dataFile) == EOF) {
				//If not, output failure to stdout and return -1
				fprintf(stdout, "Error closing file.\n");
			}
			//If not, output failure to stdout and return -1
			fprintf(stdout, "Error: malformed data file file.\n");
			deallocAccountMem();
			return -1;
		}
	}
	
	if(fclose(dataFile) == EOF) {
		//If not, output failure to stdout and return -1
		fprintf(stdout, "Error closing file.\n");
		deallocAccountMem();
		return -1;
	}
	
	return 0;
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