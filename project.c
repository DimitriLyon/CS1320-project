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
userDat *loggedInUser;

int initializeAccounts(char *filename);
int saveData(char *filename);
int login();

//This is the function for user to see available cruises
int menu(){
    int option;

	printf("\t\t\t-- Cruise Express --\n");
	printf("\t\t-- Below are the avialable options --\n");
    printf("1: Bahamas             (Price per day: 155)\n");
    printf("2: Hawaii              (Price per day: 210)\n");
    printf("3: Bermuda             (Price per day: 225)\n");
    printf("4: Caribbean           (Price per day: 305)\n");
    printf("5: Mexico              (Price per day: 179)\n");
    printf("6: Galapagos           (Price per day: 195)\n");
    printf("7: Alaska              (Price per day: 150)\n");
    printf("8: European            (Price per day: 390)\n");
    printf("9: Exit\n");

    printf("Please enter the number associated with the available options:\n");
    scanf("%d", &option);
    printf("\n");
    return option;
}

//This function is if the user decides to exit
void exits(){

    printf("\t\t-- Thank you for choosing Cruise Express --\n");
    printf("\t\t\t-- Hope to see you again --\n");
}

//This function will ask user the amount of nights they want to stay
int nights(){
    int n;
    do{
        printf("How many nights would you like to stay\n");
        printf("The minimum is 2 nights and maximum is 12 nights:\n");
        scanf("%d", &n);
        printf("\n");
    }while(n < 2 || n > 12);

    return n;
}

//This function will tell what deck the person will stay on
int deck(){
    int n;
    do{
        printf("Which deck would you like to stay on\n");
        printf("The avaialable options are:\n");
        printf("1. Luxury Floor (30%% more), 2. Mid-level Floor (15%% more), 3: Normal suite Floor\n");
        scanf("%d", &n);
        printf("\n");
    }while(n < 1 || n > 3);
}

//This will calculate the total price
float total(float ppd, int nights, int floor){
    int t; //This is the total for the trip
    if(floor == 1){ //Floor 1 will cost 30% more
        t = ppd * nights * 1.3;
    }
    else if(floor == 2){ //Floor 2 will cost 15% more
        t = ppd * nights * 1.15;
    }
    else{ //Floor 3 will not have an additional cost
        t = ppd * nights;
    }
    return t;

}

void printout(float ppd, int nights, int floor, float total){
    printf("\nThe total for the cruise with options:\n");
    printf("Price per Day: %.2f\n", ppd);
    printf("Amount of nights: %d\n", nights);
    printf("Floor staying on: %d\n", floor);
    printf("---------------------------------------\n");
    printf("Total: %.2f", total);

}


void main() {
    int travel; //This will be where they are travelling
    int nightTime; //The amount of nights they would like to stay
    int floor; //This is the floor they will stay on
    float pricePerDay; //This is the price per day
    float price; //This is the total price for trip

    travel = menu();//This will load up the main menu

    switch(travel){
        case 1:
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 2:
            pricePerDay = 210;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 3:
            pricePerDay = 225;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 4:
            pricePerDay = 305;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 5:
            pricePerDay = 179;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 6:
            pricePerDay = 195;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 7:
            pricePerDay = 150;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 8:
            pricePerDay = 390;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 9:
        exits(); //This is if they choose to exit
        break;
    }
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
		
		readCount = fscanf_s(dataFile, " %s %s %lf ",
				&accessableUsers[i].username, 32,
				&accessableUsers[i].password, 64,
				&accessableUsers[i].money);
		
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