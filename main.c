#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0 //LKR per liter

void addCities(int maxCities, char cityNames[][30], int *cityCount);
void displayCities(char cityNames[][30], int cityCount);
void renameCity(char cityNames[][30], int cityCount);
void removeCity(char cityNames[][30], int *cityCount);
void inputDistance(int distance[][30], char cityNames[][30], int cityCount);
void displayDistanceTable(int distance[][30], char cityNames[][30], int cityCount);
void displayVehicles(char vehicleType[][10], int capacity[], float rate[], float speed[], float efficiency[], int count);
void calculateShortestPaths(int distance[][MAX_CITIES], int shortestDistance[][MAX_CITIES], int cityCount);
void handleDelivery(int *deliveryCount, int distance[][MAX_CITIES], char cityNames[][30], int cityCount,char vehicleType[][10],int capacity[], float rate[], float speed[],
        float efficiency[],int srcCity[], int destCity[], int vehicleUsed[], float distanceList[],float chargeList[], float timeList[], float weightList[], float profitList[]);
void showDeliveries(int *deliveryCount, char cityNames[][30], char vehicleType[][10],int srcCity[], int destCity[], int vehicleUsed[],float distanceList[], float chargeList[],
                     float timeList[],float weightList[], float profitList[]);
void generateReports(int deliveryCount,char cityNames[][30],int srcCity[],int destCity[],float distanceList[],float chargeList[],float profitList[],float timeList[]);


int main()
{
    char cityNames[MAX_CITIES][30];
    int cityCount = 0;
    int distance[MAX_CITIES][30] = {0};
    int choice;
      int shortestDistance[MAX_CITIES][MAX_CITIES] = {0};


    // vehicle data
    char vehicleType[3][10] = {"Van", "Truck", "Lorry"};
    int capacity[3] = {1000, 5000, 10000};
    float rate[3] = {30, 40, 80};
    float speed[3] = {60, 50, 45};
    float efficiency[3] = {12, 6, 4};
    float fuelPrice;

    int selectedVehicle;
    int deliveryCount=0;
    int srcCity[MAX_DELIVERIES];
    int destCity[MAX_DELIVERIES];
    int vehicleUsed[MAX_DELIVERIES];
    float distanceList[MAX_DELIVERIES];
    float chargeList[MAX_DELIVERIES];
    float timeList[MAX_DELIVERIES];
    float weightList[MAX_DELIVERIES];
    float profitList[MAX_DELIVERIES];


    do
    {//Main menu
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
                    calculateShortestPaths(distance, shortestDistance, cityCount);
                   printf("Shortest paths have been calculated and are ready for deliveries.\n");
            break;
            case 6:displayDistanceTable (distance,cityNames, cityCount);
            break;
            case 7:displayVehicles(vehicleType, capacity, rate, speed, efficiency, 3);
            break;

             case 8:handleDelivery(&deliveryCount, distance, cityNames, cityCount, vehicleType, capacity,rate, speed, efficiency, srcCity, destCity, vehicleUsed,
                                    distanceList, chargeList, timeList, weightList, profitList);
            break;
            case 9:showDeliveries(&deliveryCount,cityNames, vehicleType, srcCity, destCity, vehicleUsed,distanceList, chargeList, timeList, weightList, profitList);
            break;
            case 10:generateReports(deliveryCount,cityNames,srcCity,destCity,distanceList,chargeList,profitList,timeList);
            break;
            case 0:printf("Exiting...\n");
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

// VEHICLE MANAGEMENT
void displayVehicles(char vehicleType[][10], int capacity[], float rate[], float speed[], float efficiency[], int count)
{
     int i;
    printf("\nAvailable Vehicles:\n");
    printf("-------------------------------------------------------------\n");
    printf("Type\tCapacity(kg)\tRate/km(LKR)\tSpeed(km/h)\tEfficiency(km/l)\n");
    printf("-------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%s\t%d\t\t%.2f\t\t%.2f\t\t%.2f\n",
               vehicleType[i], capacity[i], rate[i], speed[i], efficiency[i]);
    }
    printf("-------------------------------------------------------------\n");
}

void calculateShortestPaths(int distance[][MAX_CITIES], int shortestDistance[][MAX_CITIES], int cityCount)
{
    // Copy the distance table into shortestDistance
    for (int i = 0; i < cityCount; i++)
    {
        for (int j = 0; j < cityCount; j++)
        {
            shortestDistance[i][j] = distance[i][j];
        }
    }

//  Floyd Warshall Algorithm is used
    for (int k = 0; k < cityCount; k++)
    {
        for (int i = 0; i < cityCount; i++)
        {
            for (int j = 0; j < cityCount; j++)
            {
                if (i == j || i == k || j == k)
                    continue;

                if (shortestDistance[i][k] != 0 && shortestDistance[k][j] != 0)
                {
                    int newDistance = shortestDistance[i][k] + shortestDistance[k][j];
                    if (shortestDistance[i][j] == 0 || newDistance < shortestDistance[i][j])
                    {
                        shortestDistance[i][j] = newDistance;
                        shortestDistance[j][i] = newDistance;// keep symmetry mentioned in the assignment.
                    }
                }
            }
        }
    }



}

// DELIVERY REQUEST HANDLING
void handleDelivery(int *deliveryCount, int distance[][MAX_CITIES], char cityNames[][30], int cityCount,char vehicleType[][10], int capacity[], float rate[], float speed[], float efficiency[],int srcCity[], int destCity[], int vehicleUsed[], float distanceList[],float chargeList[], float timeList[], float weightList[], float profitList[])
{
    if (cityCount < 2)
    {
        printf("You must have at least two cities to make a delivery!\n");
        return;
    }

    int src, dest, vehicle;
    float weight,fuelPrice;


    printf("\nList of Cities:\n");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%d. %s\n", i, cityNames[i]);
    }

    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    if (src < 0 || src >= cityCount || dest < 0 || dest >= cityCount)
    {
        printf("Invalid city index!\n");
        return;
    }

    if (src == dest)
    {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    if (distance[src][dest] == 0)
    {
        printf("No distance recorded between %s and %s.\n", cityNames[src], cityNames[dest]);
        return;
    }

    printf("Enter weight of goods (kg): ");
    scanf("%f", &weight);

    //Vehicle details for the delivery
    printf("\nSelect Vehicle Type:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s (Capacity: %d kg, Rate: %.2f/km, Speed: %.2f km/h, Efficiency: %.2f km/l)\n",i + 1, vehicleType[i], capacity[i], rate[i], speed[i], efficiency[i]);
    }

    printf("Enter vehicle type (1-3): ");
    scanf("%d", &vehicle);
    vehicle--;

    if (vehicle < 0 || vehicle > 2)
    {
        printf("Invalid vehicle type!\n");
        return;
    }

    if (weight > capacity[vehicle])
    {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }



    // CALCULATIONS
    float D = distance[src][dest];
    float W = weight;
    float R = rate[vehicle];
    float S = speed[vehicle];
    float E = efficiency[vehicle];
    float F = FUEL_PRICE;

    float deliveryCost = D * R * (1 + W / 10000.0);
    float fuelUsed = D / E;
    float fuelCost = fuelUsed * F;
    float totalCost = deliveryCost + fuelCost;
    float profit = deliveryCost * 0.25;
    float charge = totalCost + profit;
    float time = D / S;



    // display results
    printf("\n=====================================================\n");
    printf("              *DELIVERY COST ESTIMATION*\n");
    printf("-----------------------------------------------------\n");
    printf("From: %s\n", cityNames[src]);
    printf("To: %s\n", cityNames[dest]);
    printf("Distance: %.2f km\n", D);
    printf("Vehicle: %s\n", vehicleType[vehicle]);
    printf("Weight: %.2f kg\n", W);
    printf("-----------------------------------------------------\n");
    printf("Base Cost: %.2f LKR\n", deliveryCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", charge);
    printf("Estimated Time: %.2f hours\n", time);
    printf("=====================================================\n");

    srcCity[*deliveryCount] = src;
    destCity[*deliveryCount] = dest;
    vehicleUsed[*deliveryCount] = vehicle;
    distanceList[*deliveryCount] = D;
    chargeList[*deliveryCount] = charge;
    timeList[*deliveryCount] = time;
    weightList[*deliveryCount] = weight;
    profitList[*deliveryCount] = profit;

    (*deliveryCount)++;

}

void showDeliveries(int *deliveryCount,char cityNames[][30],char vehicleType[][10],int srcCity[],int destCity[],int vehicleUsed[],float distanceList[],float chargeList[],float timeList[],float weightList[],float profitList[])
{
      if (*deliveryCount == 0)
    {
        printf("\nNo deliveries have been completed yet.\n");
        return;
    }
    printf("\n-*- Completed Delivery Records -*-\n");
    for (int i = 0; i < *deliveryCount; i++)
        {
        printf("\n--- Delivery #%d ---\n", i + 1);
        printf("Route: %s -> %s\n", cityNames[srcCity[i]], cityNames[destCity[i]]);
        printf("Distance: %.2f km\n", distanceList[i]);
        printf("Vehicle: %s\n", vehicleType[vehicleUsed[i]]);
        printf("Weight: %.2f kg\n", weightList[i]);
        printf("Time: %.2f hours\n", timeList[i]);
        printf("Charge: %.2f LKR\n", chargeList[i]);
        printf("Profit: %.2f LKR\n", profitList[i]);
        printf("----------------------\n");
        }
        printf("\nTotal Deliveries: %d\n", *deliveryCount);

}

//PERFORMANCE REPORTS
void generateReports( int deliveryCount,char cityNames[][30],int srcCity[],int destCity[],float distanceList[],float chargeList[],float profitList[],float timeList[])
{
     if (deliveryCount == 0)
        {
        printf("\nNo deliveries have been completed yet.\n");
        return;
        }

    float totalDistance = 0, totalCharge = 0, totalProfit = 0, totalTime = 0;
    float longest = 0.0;
    float shortest = 1e9;
    int longIndex = 0, shortIndex = 0;

    for (int i = 0; i < deliveryCount; i++)
        {
        totalDistance += distanceList[i];
        totalCharge += chargeList[i];
        totalProfit += profitList[i];
        totalTime += timeList[i];

        if (distanceList[i] > longest)
            {
            longest = distanceList[i];
            longIndex = i;
            }
        if (distanceList[i] < shortest &&  distanceList[i]>0)
            {
            shortest = distanceList[i];
            shortIndex = i;
            }
        }

    float avgTime = totalTime / deliveryCount;

    //display the report
    printf("\n================ DELIVERY PERFORMANCE REPORT =================\n");
    printf("Total Deliveries     : %d\n", deliveryCount);
    printf("Total Distance       : %.2f km\n", totalDistance);
    printf("Total Customer Charge: %.2f LKR\n", totalCharge);
    printf("Total Profit         : %.2f LKR\n", totalProfit);
    printf("Average Delivery Time: %.2f hours\n", avgTime);
    printf("-------------------------------------------------------------\n");
    printf("Longest Route  : %.2f km (%s -> %s)\n",
           longest, cityNames[srcCity[longIndex]], cityNames[destCity[longIndex]]);
    printf("Shortest Route : %.2f km (%s -> %s)\n",
           shortest, cityNames[srcCity[shortIndex]], cityNames[destCity[shortIndex]]);
    printf("==============================================================\n");

}



