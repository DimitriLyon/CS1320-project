#include <stdio.h>

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
