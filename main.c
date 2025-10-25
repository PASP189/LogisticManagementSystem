#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0



int main()
{
    char cityNames[MAX_CITIES][30];
    int cityCount = 0;
    int choice;

        printf("\n---  LOGISTIC MANAGEMENT MENU ---\n");
        printf("1.Add a New City\n");
        printf("2.Display Cities\n");
        printf("3.Rename a City\n");
        printf("4.Remove a city\n");
        printf("5.Enter distances\n");
        printf("6.Display distance table\n");
        printf("7.Display vehicles\n");
        printf("8.Handle delivery request\n");
        printf("9.Show completed deliveries\n");
        printf("10.Reports\n");
        printf("0.Exit\n\n");
        printf("Enter your choice:");
        scanf("%d",&choice);



    return 0;
}
