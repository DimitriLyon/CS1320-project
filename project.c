#include <stdio.h>

int menu(){
    int option;

	printf("\t\t\t-- Cruise Express --\n");
	printf("\t\t-- Below are the avialable options --\n");
    printf("1: Bahamas");
    printf("2: Hawaii");
    printf("3: Bermuda");
    printf("4: Caribbean");
    printf("5: Mexico");
    printf("6: Galapagos");
    printf("7: Alaska");
    printf("8: European");
    printf("9: Exit");

    printf("Please enter the number associated with the available options");
    scanf("%d", &option);
    return option;
}


void main() {
	
    int travel; //This will be where they are travelling
    travel = menu(); //This will load up the main menu

    switch(travel)
}
