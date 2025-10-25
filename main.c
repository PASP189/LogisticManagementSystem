#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0

void addCities(int maxCities, char cityNames[][30], int *cityCount);
void displayCities(char cityNames[][30], int cityCount);
void renameCity(char cityNames[][30], int cityCount);
void removeCity(char cityNames[][30], int *cityCount);
void inputDistance(int distance[][30], char cityNames[][30], int cityCount);
void displayDistanceTable(int distance[][30], char cityNames[][30], int cityCount);

int main()
{
    char cityNames[MAX_CITIES][30];
    int cityCount = 0;
    int distance[MAX_CITIES][30] = {0};
    int choice;

    do
    {
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

        switch (choice)
        {
            case 1:addCities(MAX_CITIES,cityNames,&cityCount);
            break;
            case 2:displayCities(cityNames, cityCount);
            break;
            case 3:renameCity(cityNames, cityCount);
            break;
            case 4:removeCity(cityNames, &cityCount);
            break;
            case 5:inputDistance(distance,cityNames, cityCount);
            break;
            case 6:displayDistanceTable (distance,cityNames, cityCount);
            break;
            case 0:printf("Exiting..\n");
            break;
            default:printf("Invalid choice!\n");
        }
    }
     while(choice!=0);


    return 0;
}
//CITY MANAGEMENT
void addCities(int maxCities, char cityNames[][30], int *cityCount)
{
    int n;
    printf("How many cities do you want to add?");
    scanf("%d",&n);

    if(*cityCount +n > maxCities)
        {
            printf("Error");
            return;
        }
    for(int i=0;i<n;i++)
    {
        printf("Enter city name %d:",*cityCount +1);
        scanf("%s",cityNames[*cityCount]);
        (*cityCount)++;
    }
    printf("\n%d cities added.\n",n);

}

void displayCities(char cityNames[][30], int cityCount)
{
     if (cityCount == 0)
        {
        printf("No cities available!\n");
        return;
        }

    printf("\nList of Cities :\n");
    for (int i = 0; i < cityCount; i++)
        {
        printf("%d. %s\n", i, cityNames[i]);
        }
}

void renameCity(char cityNames[][30], int cityCount)
{
    if (cityCount == 0)
    {
        printf("No cities available to rename!\n");
        return;
    }

    int index;
    printf("\nList of Cities: \n");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%d. %s\n", i, cityNames[i]);
    }

    printf("Enter city index to rename: ");
    scanf("%d", &index);

    if (index < 0 || index >= cityCount)
    {
        printf("Invalid index! Try again.\n");
        return;
    }

    char newName[30];
    printf("Enter new name for city: ");
    scanf("%s", newName);

    int j = 0;
    while (newName[j] != '\0')
    {
        cityNames[index][j] = newName[j];
        j++;
    }
    cityNames[index][j] = '\0';

    printf("City renamed successfully!\n");

}

void removeCity(char cityNames[][30], int *cityCount)
{
    if (*cityCount == 0)
    {
        printf("No cities to remove!!\n");
          return;
    }

    int index;
    printf("\nList of Cities:\n");
    for (int i = 0; i < *cityCount; i++)
    {
        printf("%d. %s\n", i, cityNames[i]);
    }

    printf( "Enter city index to remove: ");
    scanf("%d", &index);

    if (index < 0 || index >= *cityCount)
    {
        printf("Invalid index!\n");
        return;
    }
    for (int i = index; i < *cityCount - 1 ; i++) {
        int j = 0;
        while (cityNames[i + 1][j] != '\0') {
            cityNames[i][j] = cityNames[i + 1][j];
            j++;
        }
        cityNames[i][j] = '\0';
    }

    (*cityCount)--;
    printf("City removed successfully!! \n");

}

// DISTANCE MANAGEMNET
void inputDistance(int distance[][30], char cityNames[][30], int cityCount)
{
    if (cityCount < 2)
    {
        printf("Need at least two cities to enter distances!\n");
        return;
    }

    for(int i=0;i<cityCount;i++)
    {
        for(int j=i+1;j<cityCount;j++)
        {
            printf("Distance between %s and %s in(km):",cityNames[i],cityNames[j]);
            scanf("%d",&distance[i][j]);
            distance [j][i]=distance[i][j];
        }
        distance [i][i]=0;
    }
    printf("Distances entered.\n");
}

void displayDistanceTable(int distance[][30], char cityNames[][30], int cityCount)
{
     if ( cityCount == 0)
    {
        printf("No cities available!\n");
        return;
    }

    printf("%-15s", "");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%-15s\t", cityNames[i]);
    }
    printf("\n");

    for (int i = 0; i < cityCount; i++)
    {
        printf("%-15s\t", cityNames[i]);
        for (int j = 0; j < cityCount; j++)
        {
            printf("%-15d\t", distance[i][j]);
        }
        printf("\n");
    }

}
