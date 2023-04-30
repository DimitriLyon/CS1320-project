#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//We create a structure for username, password, and balance of money for logged in user
typedef struct userDat_struct{
	char username[32];
	char password[64];
	double money;
} userDat;

//Here we are creating all accessableUsers of 5
//We create a user count of 5 so in login it will iterate through usercount
//We also create loggedInUser so that we can access the data attached with user
userDat accessableUsers[5];
int userCount = 5;
userDat *loggedInUser;

//Here are the prototypes that are used for the file handling
int initializeAccounts(char *filename);
int saveData(char *filename);
int login();

//This is the function for user to see available Resorts and return an option
int menu(){
    int option;

	printf("\t\t\t-- Resort Express --\n");
	printf("\t\t-- Below are the avialable options --\n");
    printf("1: Bahamas             (Price per day: $ 155)\n");
    printf("2: Hawaii              (Price per day: $ 210)\n");
    printf("3: Bermuda             (Price per day: $ 225)\n");
    printf("4: Caribbean           (Price per day: $ 305)\n");
    printf("5: Mexico              (Price per day: $ 179)\n");
    printf("6: Galapagos           (Price per day: $ 195)\n");
    printf("7: Alaska              (Price per day: $ 150)\n");
    printf("8: Italy               (Price per day: $ 390)\n");
    printf("9: Exit\n");

    printf("Please enter the number associated with the available options:\n");
    scanf("%d", &option);
    printf("\n");
    return option;
}

//This function is if the user decides to exit
void exits(){

    printf("\t\t-- Thank you for choosing Resort Express --\n");
    printf("\t\t\t-- Hope to see you again --\n");
}

//This function will ask user the amount of nights they want to stay
int nights(){
    int n;
    do{
        printf("How many nights would you like to stay\n");
        printf("The minimum is 1 nights and maximum is 12 nights:\n");
        scanf("%d", &n);
        printf("\n");
    }while(n < 1 || n > 12);

    return n;
}

//This function will tell what type of room the person will stay on
int typeRoom(){
    int n;
    do{
        printf("Which type of room would you like to stay in\n");
        printf("The avaialable options are:\n");
        printf("1. Luxury Room (30%% more), 2. Mid-level Room (15%% more), 3: Normal suite\n");
        scanf("%d", &n);
        printf("\n");
    }while(n < 1 || n > 3);
}

//This will calculate the total price
float total(float ppd, int nights, int room){
    int t; //This is the total for the stay
    if(room == 1){ //Room type 1 will cost 30% more
        t = ppd * nights * 1.3;
    }
    else if(room == 2){ //Room type 2 will cost 15% more
        t = ppd * nights * 1.15;
    }
    else{ //Room type 3 will not have an additional cost
        t = ppd * nights;
    }
    return t;

}

int printout(float ppd, int nights, int room, float total){
    char choose;
    printf("\nThe total for the Resort is\n");
    printf("Price per Day: $%.2f\n", ppd);
    printf("Amount of nights: %d\n", nights);
    printf("Room type staying on: %d\n", room);
    printf("---------------------------------------\n");
    printf("Total: $%.2f\n", total);
    if(loggedInUser->money >= total){
        return 1; //Returns 1 if they have enough to purchase
    }
    else{
        printf("Insufficent funds");
        return 0; //Returns 0 since they do not have enough available
    }
}


void main() {
    int travel; //This will be where they are travelling
    int nightTime; //The amount of nights they would like to stay
    int room; //This is the type of room they will stay in
    float pricePerDay; //This is the price per day
    float price; //This is the total price for stay
    int choose; //This is if they have available money to purchase
    char pick;//This is if they choose to purchase with available money
    char multi; //This is if they want to get another ticket

    //Here we take in all usernames, passwords, and balances from txt file
    initializeAccounts("loginInfo.txt");

    //Here we see if login worked as if it does it returns 0
    if(login() == 0){
        
        //Main loop so that user can purchase multiple tickets
        do{
            //we set this to N so this will not automatically stay as yes (Y) if they choose to but another
            pick = 'N';

            travel = menu();//This will load up the main menu

            switch(travel){
                /*
                For cases 1 - 8 the format is as follows:
                
                we set price per day based off chosen option
                
                we call nights function and set to nightTime which will hold the amount of nights staying

                we call type room which will return to room what type of room they stay on

                we call total which with parameters of price per day, night time, and room
                it will calculate total price and set into price

                we then call printout that returns 1 if they have enough to purchase ticket
                and 0 if they do not have enough to purchase ticket set into variable choose

                then with returned variable choose if they have enough to purchase ticket (1)
                they will be asked if they want to purchase and returns pick

                we then check if pick is set to yes (Y) we subtract that from their avaialable balance

                then it prints out available money and if they would like to purchase another ticket
                this choose will go into multi
                we see the condition at the end if multi is true then repeat loop
                the loop will then go through main menu until they either choose exit on main menu
                or if they do not decide to choose another ticket 
                */
                case 1:
                    pricePerDay = 155;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 2:
                    pricePerDay = 210;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 3:
                    pricePerDay = 225;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 4:
                    pricePerDay = 305;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 5:
                    pricePerDay = 179;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 6:
                    pricePerDay = 195;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 7:
                    pricePerDay = 150;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 8:
                    pricePerDay = 390;
                    nightTime = nights();
                    room = typeRoom();
                    price = total(pricePerDay, nightTime, room);
                    choose = printout(pricePerDay, nightTime, room, price);
                    if(choose == 1){
                        printf("Would you like to make the purchase?\n");
                        printf("Y for yes and N for no: ");
                        scanf(" %c", &pick);
                    }
                    if(pick == 'Y'){
                        loggedInUser->money = loggedInUser->money - price;
                    }
                    printf("\nBalance is currenty at: $%.2lf", loggedInUser->money);
                    printf("\nWould you like but another ticket?\n");
                    printf("Enter Y for yes and N for no:");
                    scanf(" %c", &multi);
                break;
                
                case 9:
                exits(); //This is if they choose to exit
                break;

                default:
                printf("did not choose one of the availabels options"); 
                break;
                
                
            }
        }while(multi == 'Y'); //This is our condition to repeat loop if they want to buy more tickets
        
        //This is used for when loop ends to print out exit statement
        //If they choose to exit aleady on main menu (case 9) we dont what it to repeat exit statement
        if(travel != 9){
            exits();
        }

    }

    saveData("logoutInfo.txt");
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
		
		readCount = fscanf(dataFile, " %s %s %lf ",
				&accessableUsers[i].username,
				&accessableUsers[i].password,
				&accessableUsers[i].money);
		
		//Needs to read 3 things per line.
		//If doesn't throw error
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
	char username[32]; //Buffer for username
	char password[64]; //Buffer for password
	int i; //Iterator for linear search
	
	//Prompt user for username
	printf("Username: ");
	//Take username from input.  Max 32 char
	scanf(" %s", username);
	//Prompt user for password
	printf("Password: ");
	//Take password from input.  Max 64 char
	scanf(" %s", password);
	
	//Iterate through list of users
	for(i = 0; i < userCount; i++) {
		//Check if username matches
		if(strcmp(username, accessableUsers[i].username) == 0) {
			//Compare password of user to entered password
			if(strcmp(password, accessableUsers[i].password) == 0) {
				//Set loggedInUser to point to the correct pointer.
				loggedInUser = accessableUsers + i; 
				printf("Logged in as username: %s\n", username);
                printf("Balance = %.2lf\n", accessableUsers[i].money);
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
		fprintf(optFile, " %s %s %lf \n", accessableUsers[i].username, accessableUsers[i].password, accessableUsers[i].money);
		fflush(optFile);
	}
	
	fclose(optFile);
	
	return 0;
}
