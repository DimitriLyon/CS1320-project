#include <stdio.h>

//This is the function for user to see available cruises
int menu(){
    int option;

	printf("\t\t\t-- Cruise Express --\n");
	printf("\t\t-- Below are the avialable options --\n");
    printf("1: Bahamas\n");
    printf("2: Hawaii\n");
    printf("3: Bermuda\n");
    printf("4: Caribbean\n");
    printf("5: Mexico\n");
    printf("6: Galapagos\n");
    printf("7: Alaska\n");
    printf("8: European\n");
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

int nights(){
    int n;
    do{
        printf("How many nights would you like to stay\n");
        printf("The minimum is 2 nights and maximum is 12 nights:\n");
        scanf("%d", &n);
        printf("\n");
    }while(n < 2 && n > 12);

    return n;
}

//This function will tell what deck the person will stay on
int deck(){
    int n;
    do{
        printf("Which deck would you like to stay on\n");
        printf("The avaialable options are:\n");
        printf("1. Luxury Floor, 2. Mid-level Floor, 3: Normal suite Floor\n");
        scanf("%d", &n);
        printf("\n");
    }while(n < 0 && n > 4);
}

//This will calculate the total price
float total(float ppd, int nights, int floor){
    int t; //This is the total for the trip
    if(floor == 3){ //Floor 3 will cost 30% more
        t = ppd * nights * 1.3;
    }
    else if(floor == 2){ //Floor 2 will cost 15% more
        t = ppd * nights * 1.15;
    }
    else{ //Floor 1 will not have an additional cost
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
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 3:
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 4:
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 5:
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 6:
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 7:
            pricePerDay = 155;
            nightTime = nights();
            floor = deck();
            price = total(pricePerDay, nightTime, floor);
            printout(pricePerDay, nightTime, floor, price);
        break;
        
        case 8:
            pricePerDay = 155;
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
