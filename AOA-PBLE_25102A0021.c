#include <stdio.h>

#define MAX 100

int id[MAX];
float value[MAX];
float weight[MAX];
float ratio[MAX];
float quantity[MAX];

int n = 0;
float capacity = 0;
int entered = 0;

void enterDetails()
{
    int i;

    printf("\n========== ENTER PACKAGE DETAILS ==========\n");

    printf("Enter number of packages: ");
    scanf("%d", &n);

    printf("Enter vehicle capacity: ");
    scanf("%f", &capacity);

    for (i = 0; i < n; i++)
    {
        id[i] = i + 1;

        printf("\nPackage %d\n", i + 1);

        printf("Enter value/profit: ");
        scanf("%f", &value[i]);

        printf("Enter weight: ");
        scanf("%f", &weight[i]);

        ratio[i] = 0;
        quantity[i] = 0;
    }

    entered = 1;

    printf("\nPackage details entered successfully!\n");
}

void calculateRatio()
{
    int i;

    if (!entered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (weight[i] != 0)
            ratio[i] = value[i] / weight[i];
        else
            ratio[i] = 0;
    }
}

void displayDetails()
{
    int i;

    if (!entered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\n================ PACKAGE DETAILS ================\n");
    printf("Package\tValue\tWeight\tRatio\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               id[i],
               value[i],
               weight[i],
               ratio[i]);
    }

    printf("--------------------------------------------------\n");
    printf("Vehicle Capacity = %.2f\n", capacity);
}

void sortPackages()
{
    int i, j;
    int tempInt;
    float temp;

    if (!entered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    calculateRatio();

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (ratio[j] < ratio[j + 1])
            {
                tempInt = id[j];
                id[j] = id[j + 1];
                id[j + 1] = tempInt;

                temp = value[j];
                value[j] = value[j + 1];
                value[j + 1] = temp;

                temp = weight[j];
                weight[j] = weight[j + 1];
                weight[j + 1] = temp;

                temp = ratio[j];
                ratio[j] = ratio[j + 1];
                ratio[j + 1] = temp;
            }
        }
    }
}

void findMaximumValue()
{
    int i;
    float remaining;
    float totalValue = 0;
    float totalWeight = 0;

    if (!entered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    calculateRatio();
    sortPackages();

    remaining = capacity;

    for (i = 0; i < n; i++)
    {
        quantity[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        if (remaining <= 0)
            break;

        if (weight[i] <= remaining)
        {
            quantity[i] = 1;

            remaining = remaining - weight[i];

            totalWeight = totalWeight + weight[i];
            totalValue = totalValue + value[i];
        }
        else
        {
            quantity[i] = remaining / weight[i];

            totalWeight = totalWeight + remaining;

            totalValue = totalValue +
                         (value[i] * quantity[i]);

            remaining = 0;
        }
    }

    printf("\n================ FINAL RESULT ================\n");
    printf("Total weight used = %.2f\n", totalWeight);
    printf("Maximum value     = %.2f\n", totalValue);
    printf("================================================\n");
}

void displaySelectedPackages()
{
    int i;
    int found = 0;

    if (!entered)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\n============= SELECTED PACKAGES =============\n");
    printf("Package\tQuantity\tValue Obtained\n");
    printf("----------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (quantity[i] > 0)
        {
            printf("%d\t%.2f\t\t%.2f\n",
                   id[i],
                   quantity[i],
                   value[i] * quantity[i]);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No packages selected yet.\n");
    }

    printf("----------------------------------------------\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n\n============================================\n");
        printf("          FRACTIONAL KNAPSACK\n");
        printf("============================================\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterDetails();
                break;

            case 2:
                displayDetails();
                break;

            case 3:
                calculateRatio();
                printf("\nValue/Weight ratio calculated successfully.\n");
                break;

            case 4:
                sortPackages();
                printf("\nPackages sorted successfully.\n");
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelectedPackages();
                break;

            case 7:
                printf("\nProgram ended successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}