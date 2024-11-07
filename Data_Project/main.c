
// QusayBdier           ID:1220649                 Se:1
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define SizeOfArrays 50
struct Town {                                                          // To build linked list of linked list we need to create to struct and call the sup struct in the super like this.
    char town_name[SizeOfArrays];
    long population;
    struct Town *next_Town;
    struct Town *prev_Town;
};
struct District {
    char district_name[SizeOfArrays];
    struct Town *Towns;
    struct District *next_Dis;
    struct District *prev_Dis;
};
void Print_List(struct District *);                                     // This function use to print the linked list.
void LoadDataFromFileAndPrint(struct District *, int);
void printMenu();
void addDistrict(struct District *, char[], char[], long,int);           // This function use to add new district to linked list.
void addTown(struct District *, char[], char[], long,int);                // This function use to add new town  to linked list.
int search_District(struct District *,char[]);                         // This function use to search if the district is existed in linked list and return its position
int search_Town(struct District *, char[],char[]);                      // This function use to search if the  town is existed in linked list and return its position
void Radix_Sort_Districts(struct District *, int);
void Radix_Sort_Towns(struct District *Dis_head, int);
long getMaxNumber(struct District *, struct Town *Town_head,int);         // This function use to get the max number of string ( District, town) and integer (population).
long getTheNumberOfDigit(long number);                                    // This function use to get the size of digit of max number.
void DeleteTown(struct District *, int, char[], char[], int);
void DeleteDistrict(struct District *, int, int);
void Calculate_The_Population(struct District *, int);
void Update_population(struct District *);

int main() {
    struct District *Dis_head = (struct District *) malloc(
            sizeof(struct District));  // heir we are build the head node for district_Linked list and initialize the first value  .
    Dis_head->next_Dis = NULL;
    Dis_head->prev_Dis = NULL;
    Dis_head->Towns = NULL;
    printMenu();
    int option;
    scanf("%d", &option);
    do {
        switch (option) {
            case 1:
                LoadDataFromFileAndPrint(Dis_head, option);
                break;
            case 2:
                LoadDataFromFileAndPrint(Dis_head, option);
                break;
            case 3: {
                Radix_Sort_Districts(Dis_head, option);
                printf("The Districts has been sorted \n");
            }
                break;
            case 4: {
                Radix_Sort_Towns(Dis_head, option);
                printf("The Towns has been sorted \n");
            }
                break;
            case 5:
                Print_List(Dis_head);
                break;
            case 6: {
                char nameOfDistrict[50];
                printf("Enter the name of district\n");
                scanf(" %[^\n]s",nameOfDistrict);                                       //  " %[^\n]s" this that use for scan the total line that user write .
                addDistrict(Dis_head, nameOfDistrict, " ", 0, option);
                Radix_Sort_Districts(Dis_head, option);
            }
                break;
            case 7: {
                if (Dis_head->next_Dis != NULL) {
                    long population;
                    char nameOfDistrict[50];
                    char nameOfTown[50];
                    printf("Enter the name of district\n");
                    scanf(" %[^\n]s", nameOfDistrict);
                    if (search_District(Dis_head, nameOfDistrict) !=
                        -1) {                    // this condition use to check if the district is exited.
                        printf("The district exists .\n please inter the name of Town and population \n");
                        scanf(" %[^\n]s", nameOfTown);
                        if (search_Town(Dis_head, nameOfDistrict, nameOfTown) == -1) {
                            scanf("%ld", &population);
                            addDistrict(Dis_head, nameOfDistrict, nameOfTown, population, option);
                            Radix_Sort_Towns(Dis_head, option);
                        } else
                            printf("The town exist\n");
                    } else
                        printf("The district is not exists please add the district and try again \n");
                } else
                    printf("The data base is empty\n");
            }
                break;

            case 8: {
                if (Dis_head->next_Dis ==
                    NULL) {                                   // This line use for check if the linked list is empty before used.
                    printf("The Database empty please load the data\n\n");
                } else {
                    char District_name[50];
                    char Town_name[50];
                    printf("Enter the name of district \n");
                    scanf(" %[^\n]s", District_name);
                    int position = search_District(Dis_head, District_name);
                    if (position == -1)
                        printf("The district is not exists\n");
                    else {
                        DeleteTown(Dis_head, position, District_name, Town_name, option);

                    }
                }
            }
                break;
            case 9: {
                if (Dis_head->next_Dis == NULL) {
                    printf("The Database empty please load the data\n\n");
                } else {
                    char District_name[50];
                    printf("Enter the name of district \n");
                    scanf(" %[^\n]s", District_name);
                    int position = search_District(Dis_head, District_name);
                    if (position == -1)
                        printf("The district is not exists\n");
                    else {
                        DeleteDistrict(Dis_head, position, option);
                        printf("The District deleted successful\n");
                    }
                }
            }
                break;
            case 10:
                Calculate_The_Population(Dis_head, option);
                break;
            case 11:
                Calculate_The_Population(Dis_head, option);
                break;
            case 12:
                Update_population(Dis_head);
                break;
            case 13:
                LoadDataFromFileAndPrint(Dis_head, option);
                break;
            case 14:
                exit(0);
            default:
                printf("The option is not valid.\n");
        }
        printMenu();
        scanf("%d", &option);
    } while (option != 14);

    return 0;
}

void printMenu() {
    printf("\n1. Load the input file (Palestinian districts and their town with population).\n"
           "2. Print the loaded information before sorting (as in the input file format)\n"
           "3. Sort the districts alphabetically using Radix sort\n"
           "4. Sort the towns for each district based on population in ascending order\n"
           "5. Print the sorted information\n"
           "6. Add a new district to the list of sorted districts (and sort the list)\n"
           "7. Add a new town to a certain district\n"
           "8. Delete a town from a specific district\n"
           "9. Delete a complete district; here, you must delete all towns belonging to that district before deleting it\n"
           "10. Calculate the population of Palestine, the max and min town population\n"
           "11. Print the districts and their total population (without towns details)\n"
           "12. Change the population of a town, after prompting the user to enter the district name\n"
           "13. Save to output file\n"
           "14. Exit\n Please inter your option :\n");
}

void LoadDataFromFileAndPrint(struct District *Dis_head, int option) {
    char InputLine[SizeOfArrays];
    FILE *in, *out;
    in = fopen("districts.txt", "r");
    out = fopen("sorted_districts.txt", "w");
    if (in == NULL) {
        printf("Error! can't open the file\n");
        exit(1);
    }
    if (option == 2) {
        printf("\n");
        while (fgets(InputLine, sizeof(InputLine), in) != NULL) {
            printf("%s", InputLine);
        }
        printf("\n\n");
    }
    if (option == 1) {
        while (fgets(InputLine, sizeof(InputLine), in) !=
               NULL) {          // in this process we are take the data from file line by line .
            char *district_scan = strtok(InputLine, "|");
            char *town_scan = strtok(NULL, "|");
            long population_scan = (long) atoi(strtok(NULL, "|"));
            addDistrict(Dis_head, district_scan, town_scan, population_scan, option);
        }
        printf("The data has been loaded\n");
    }
    fclose(in);
    if (option == 13) {
        if (Dis_head == NULL)
            return;
        else {
            long population = 0;
            struct District *current_District = Dis_head->next_Dis;
            while (current_District != NULL) {
                struct Town *current_Town = current_District->Towns;
                struct Town *Town_Print = current_District->Towns;
                while (current_Town != NULL) {
                    population += current_Town->population;
                    current_Town = current_Town->next_Town;
                }
                fprintf(out, "%s District ,Population = %ld\n", current_District->district_name, population);
                while (Town_Print != NULL) {
                    if (strcmp(Town_Print->town_name, " ") != 0)
                        fprintf(out, "%s,%ld\n", Town_Print->town_name, Town_Print->population);
                    Town_Print = Town_Print->next_Town;
                }
                current_District = current_District->next_Dis;
                population = 0;
            }
        }
        fclose(out);
    }
}

void addDistrict(struct District *Dis_head, char district_scan[], char town_scan[], long population_scan, int option) {
    struct District *newDistrict = (struct District *) malloc(sizeof(struct District));
    strcpy(newDistrict->district_name, district_scan);
    newDistrict->next_Dis = NULL;
    newDistrict->prev_Dis = NULL;
    newDistrict->Towns = NULL;
    if (Dis_head->next_Dis ==NULL) {                                                             //this condition use to check if the linked list is empty .
        Dis_head->next_Dis = newDistrict;
        newDistrict->prev_Dis = Dis_head->prev_Dis;
        addTown(Dis_head->next_Dis, district_scan, town_scan, population_scan, option);

    } else {
        int positionOfDistrict = search_District(Dis_head, district_scan);
        if (positionOfDistrict != (-1)) {
            if (option == 6)
                printf("The district is exists\n");
            while (positionOfDistrict != 0) {
                Dis_head = Dis_head->next_Dis;
                positionOfDistrict--;
            }
            addTown(Dis_head, district_scan, town_scan, population_scan, option);
        } else {
            while (Dis_head->next_Dis != NULL) {
                Dis_head = Dis_head->next_Dis;
            }
            Dis_head->next_Dis = newDistrict;
            newDistrict->prev_Dis = Dis_head;
            addTown(Dis_head->next_Dis, district_scan, town_scan, population_scan, option);
        }
    }
}

void addTown(struct District *Dis_head, char District_name[], char town_scan[], long population_scan, int option) {

    if (search_Town(Dis_head, District_name, town_scan) == -1) {
        struct Town *newTown = (struct Town *) malloc(sizeof(struct Town));
        strcpy(newTown->town_name, town_scan);                                 // Setting to an empty string
        newTown->population = population_scan;
        newTown->next_Town = NULL;
        newTown->prev_Town = NULL;

        if (Dis_head->Towns == NULL) {
            Dis_head->Towns = newTown;
            newTown->prev_Town = Dis_head->Towns;
        } else {
            struct Town *current_town = Dis_head->Towns;
            while (current_town->next_Town != NULL) {
                current_town = current_town->next_Town;
            }
            current_town->next_Town = newTown;
            newTown->prev_Town = current_town;
        }
    } else {
        if (option == 7)
            printf("The Town is exists\n");
    }

}

void Print_List(struct District *Dis_head) {
    if (Dis_head->next_Dis == NULL) {
        printf("The Database empty please load the data\n\n");
    } else {
        struct District *current_district = Dis_head->next_Dis;
        while (current_district != NULL) {
            printf("\n%s\n", current_district->district_name);

            struct Town *current_town = current_district->Towns;
            while (current_town != NULL) {
                printf("  %s ", current_town->town_name);
                if (current_town->population != 0)
                    printf(":%ld\n", current_town->population);
                current_town = current_town->next_Town;
            }

            current_district = current_district->next_Dis;
        }
    }
}

void Radix_Sort_Districts(struct District *Dis_head, int option) {
    if (Dis_head->next_Dis == NULL) {
        printf("The Database is empty. Please load the data.\n\n");
        return;
    }
    struct District *current_Dis = Dis_head->next_Dis;
    int max = getMaxNumber(current_Dis, NULL, option);
    struct District *ArrayOfDistrict[27] = {
            NULL};                                         //this array use to storage the nodes that sorted and the size its equal the number of char .
    char District_name[max];
    int copy_max = max;
    for (int i = 0; i <=max; i++) {                                                          //this loop using to passing through the string
        current_Dis = Dis_head->next_Dis;
        while (current_Dis != NULL) {
            struct District *First_District = (struct District *) malloc(sizeof(struct District));
            struct District *second_District;

            strcpy(First_District->district_name, current_Dis->district_name);
            First_District->next_Dis = NULL;
            First_District->prev_Dis = NULL;
            First_District->Towns = current_Dis->Towns;

            char temp_name[50];
            strcpy(temp_name, current_Dis->district_name);
            strcpy(District_name, strupr(temp_name));
            int value = (District_name[copy_max] - 'A');
            if (value < 0) {
                value = 26; // Empty string handling
            }
            if (ArrayOfDistrict[value] == NULL) {
                ArrayOfDistrict[value] = First_District;
            } else {
                second_District = ArrayOfDistrict[value];
                while (second_District->next_Dis != NULL) {
                    second_District = second_District->next_Dis;
                }
                second_District->next_Dis = First_District;
                First_District->prev_Dis = second_District;
            }
            current_Dis = current_Dis->next_Dis;
        }
        copy_max--;
        Dis_head->next_Dis = NULL;                                                     // Delete memory for existing districts in Dis_head
        for (int m = 0; m < 27; m++) {
            struct District *tempDistrict = ArrayOfDistrict[m];
            option = 20;
            while (tempDistrict != NULL) {
                struct District *tempNext = tempDistrict->next_Dis;
                while (tempDistrict->Towns != NULL) {            // Save next before deleting
                    addDistrict(Dis_head, tempDistrict->district_name, tempDistrict->Towns->town_name,
                                tempDistrict->Towns->population, option);
                    tempDistrict->Towns = tempDistrict->Towns->next_Town;
                }
                free(tempDistrict);                                          // Free the copied district
                tempDistrict = tempNext;                                             // Move to the next district
            }
            ArrayOfDistrict[m] = NULL;                                               // Reset the array entry after copying
        }
    }
}

void Radix_Sort_Towns(struct District *Dis_head, int option) {
    if (Dis_head->next_Dis == NULL) {
        printf("The Database empty please load the data\n\n");
    }
    struct District *current_Dis = Dis_head->next_Dis;
    struct Town *current_Town;
    long number;
    long div;
    long digit;
    int MaxNumber;
    while (current_Dis != NULL) {
        div = 1;
        MaxNumber = getMaxNumber(NULL, current_Dis->Towns, option);
        digit = getTheNumberOfDigit(MaxNumber);
        for (int i = 0; i < digit; i++) {
            current_Town = current_Dis->Towns;
            struct Town *ArrayOfTown[10] = {NULL};
            while (current_Town != NULL) {
                struct Town *First_Town = (struct Town *) malloc(sizeof(struct Town));
                struct Town *second_Town;
                First_Town->population = current_Town->population;
                strcpy(First_Town->town_name, current_Town->town_name);
                First_Town->next_Town = NULL;
                First_Town->prev_Town = NULL;
                number = (current_Town->population / div) %
                         10;                              // Determine the index in the ArrayOfTown based on the population
                if (ArrayOfTown[number] == NULL) {
                    ArrayOfTown[number] = First_Town;                                       // If no town exists at this index, set the new town as the head
                } else {
                    second_Town = ArrayOfTown[number];                                      // If a town exists at this index, append the new town to the end
                    while (second_Town->next_Town != NULL) {
                        second_Town = second_Town->next_Town;
                    }
                    second_Town->next_Town = First_Town;                                    // added the new town to the end of the list
                    First_Town->prev_Town = second_Town;
                }
                current_Town = current_Town->next_Town;
            }
            div *= 10;
            current_Dis->Towns = NULL;                                                    //delete the current data in linked lise
            for (int m = 0;
                 m < 10; m++) {                                                // add the sorted data to linked list
                while (ArrayOfTown[m] != NULL) {
                    addTown(current_Dis, current_Dis->district_name, ArrayOfTown[m]->town_name,
                            ArrayOfTown[m]->population, option);
                    ArrayOfTown[m] = ArrayOfTown[m]->next_Town;
                }
            }
        }
        current_Dis = current_Dis->next_Dis;
    }
}

void DeleteTown(struct District *Dis_head, int position, char District_name[], char Town_name[], int option) {
    struct District *current_Dis = Dis_head;
    if (current_Dis == NULL) {
        printf("The Database empty please load the data\n\n");
    } else {
        while (position > 0 && current_Dis != NULL) {
            current_Dis = current_Dis->next_Dis;
            position--;
        }
        if (option == 8) {
            printf("Enter the name of Town \n");
            scanf(" %[^\n]s", Town_name);
            if (search_Town(Dis_head, District_name, Town_name) == -1) {
                printf("The Town is not exists\n");
                return;
            }
        }
        if (current_Dis->Towns != NULL) {
            int position_Town = search_Town(Dis_head, District_name, Town_name);
            struct Town *town_delete = current_Dis->Towns;
            for (int i = 0; i < position_Town; i++) {
                town_delete = town_delete->next_Town;
            }
            if (town_delete == NULL) {
                free(town_delete);

                return;
            }
            if (town_delete->next_Town ==NULL) {                                                        // this condition  use to delete the district that existing at the end .
                town_delete->prev_Town->next_Town = town_delete->next_Town;
                free(town_delete->next_Town);
            }
            if (position_Town ==0) {                                                                   // this condition  use to delete the district that existing at the first .
                current_Dis->Towns = town_delete->next_Town;
                town_delete->prev_Town = Dis_head->Towns;
                town_delete->next_Town = NULL;
                town_delete->prev_Town = NULL;

                free(town_delete);
            } else if (town_delete->prev_Town != NULL && town_delete->next_Town !=
                                                         NULL) {              // this condition  use to delete the district that existing in the middle .
                town_delete->next_Town->prev_Town = town_delete->prev_Town;
                town_delete->prev_Town->next_Town = town_delete->next_Town;
                free(town_delete);
            }
        }
        if (option == 8)
            printf("The town '%s' deleted.\n", Town_name);
    }
}

void DeleteDistrict(struct District *Dis_head, int position, int option) {
    struct District *current_District = Dis_head;
    int copy_position = position;
    while (position !=
           0) {                                                            // this while use to put the pointer on the required district .
        current_District = current_District->next_Dis;
        position--;
    }

    while (current_District->Towns !=
           NULL) {                                        // this while use to Delete all town before delete district .
        struct Town *current_Town = current_District->Towns;
        DeleteTown(Dis_head, copy_position, current_District->district_name, current_District->Towns->town_name,
                   option);
        current_Town = current_Town->next_Town;
        current_District->Towns = current_Town;
    }
    if (copy_position ==1) {                                                                    // this condition  use to delete the district that existing at the first .
        struct District *Temp_District = Dis_head;
        Temp_District->next_Dis = current_District->next_Dis;
        current_District->prev_Dis = Temp_District;
        free(current_District);
    } else if (current_District->next_Dis != NULL && current_District->prev_Dis !=
                                                     NULL) {           // this condition  use to delete the district that existing in the middle .
        current_District->prev_Dis->next_Dis = current_District->next_Dis;
        current_District->next_Dis->prev_Dis = current_District->prev_Dis;
        free(current_District);
    } else {                                                                                     // this condition  use to delete the district that existing at the end .
        current_District->prev_Dis->next_Dis = current_District->next_Dis;
        free(current_District);
    }
}

int search_District(struct District *Dis_head, char District_name[]) {
    int position = 0;
    struct District *current_district = Dis_head;

    while (current_district != NULL) {
        char Temp_Name[50];
        strcpy(Temp_Name, current_district->district_name);
        char Temp_Name_District[50];
        strcpy(Temp_Name_District, District_name);
        if (strcmp(strlwr(Temp_Name), strlwr(Temp_Name_District)) == 0) {
            return position;
        }
        position++;
        current_district = current_district->next_Dis;
    }
    return -1;
}

int search_Town(struct District *Dis_head, char District_name[], char Town_scan[]) {
    int position_District = search_District(Dis_head, District_name);
    while (position_District != 0) {
        Dis_head = Dis_head->next_Dis;
        position_District--;
    }
    struct Town *Town_head = Dis_head->Towns;
    int position_Town = 0;
    if (Town_head == NULL)
        return -1;
    else {
        while (Town_head !=NULL) {                                                              // in this process we are passing of all town and check if the town
            char Temp_Name[50];                                                              // that user inter is exist
            strcpy(Temp_Name, Town_head->town_name);
            char Temp_Name_Scan[50];
            strcpy(Temp_Name_Scan, Town_scan);
            if (strcmp(strlwr(Temp_Name), strlwr(Temp_Name_Scan)) ==0) {               // we are use strlwr to check the capitals word
                return position_Town;
            }
            position_Town++;
            Town_head = Town_head->next_Town;
        }
        return -1;
    }
}

void Calculate_The_Population(struct District *Dis_head, int option) {
    if (Dis_head->next_Dis == NULL) {
        printf("The Database empty please load the data\n\n");
    }
    if (option == 10) {
        struct District *current_Dis = Dis_head->next_Dis;
        if (current_Dis !=
            NULL) {                                                                    //this condition use to check if the linked list is empty .
            struct Town *current_Town = current_Dis->Towns;
            struct Town *Max_Pop = current_Town;
            struct Town *Min_Pop = current_Town;
            long population = 0;
            struct District *current_District = Dis_head;
            while (current_District !=
                   NULL) {                                                        //this loop use to pass of all districts .
                struct Town *current_town = current_District->Towns;
                while (current_town !=
                       NULL) {                                                       //this loop use to pass of all towns   .
                    population += current_town->population;
                    if (Max_Pop->population <= current_town->population) {
                        Max_Pop = current_town;
                    }
                    if (Min_Pop->population >= current_town->population) {
                        if(strcmp(current_town->town_name," ")!=0)
                          Min_Pop = current_town;
                    }
                    current_town = current_town->next_Town;
                }
                current_District = current_District->next_Dis;
            }
            printf("\nThe total population of palestine  %ld \n", population);
            printf("The max population in palestine in town  %s   %ld\n", Max_Pop->town_name, Max_Pop->population);
            printf("The main population in palestine in town %s  %ld\n", Min_Pop->town_name, Min_Pop->population);
        }
    }
    if (option == 11) {
        long population = 0;
        struct District *current_District = Dis_head->next_Dis;
        while (current_District != NULL) {
            struct Town *current_Town = current_District->Towns;
            while (current_Town != NULL) {
                population += current_Town->population;
                current_Town = current_Town->next_Town;
            }
            printf("%s\t,Total population = %ld\n", current_District->district_name, population);
            current_District = current_District->next_Dis;
            population = 0;
        }
    }
}

void Update_population(struct District *Dis_head) {
    if (Dis_head->next_Dis == NULL) {
        printf("The Database empty please load the data\n\n");
        return;
    }
    char District_name[50];
    char Town_name[50];
    long population = 0;
    printf("Enter the name of district \n");
    scanf(" %[^\n]s", District_name);
    int position = search_District(Dis_head, District_name);
    if (position == -1)
        printf("The district is not exists\n");
    else {
        struct District *current_Dis = Dis_head;
        while (position > 0 && current_Dis != NULL) {
            current_Dis = current_Dis->next_Dis;
            position--;
        }
        printf("Enter the name of Town \n");
        scanf(" %[^\n]s", Town_name);
        if (search_Town(current_Dis, District_name, Town_name) == -1) {
            printf("The Town is not exists\n");
        } else {
            printf("Enter the new population \n");
            scanf("%ld", &population);
            printf("The population has been update.\n");
        }
        if (current_Dis != NULL) {
            long position_Town = search_Town(current_Dis, District_name, Town_name);
            struct Town *town_update = current_Dis->Towns;
            for (int i = 0; i < position_Town; i++) {
                town_update = town_update->next_Town;
            }
            town_update->population = population;
        }
    }
}

long getTheNumberOfDigit(long number) {
    long numberOfDigit = 0;
    while (number != 0) {
        numberOfDigit++;
        number /= 10;
    }
    return numberOfDigit;
}

long getMaxNumber(struct District *Dis_head, struct Town *Town_head, int option) {
    if (option == 7 || option == 4) {
        if (Town_head == NULL)
            return 0;
        long max = Town_head->population;
        struct Town *current_town = Town_head->next_Town;
        while (current_town != NULL) {
            if (current_town->population > max)
                max = current_town->population;
            current_town = current_town->next_Town;
        }
        return max;
    }
    if (option == 3 || option == 6) {
        if (Dis_head != NULL) {
            long max = strlen(Dis_head->district_name);
            while (Dis_head != NULL) {
                if (strlen(Dis_head->district_name) >= max) {
                    max = strlen(Dis_head->district_name);
                }
                Dis_head = Dis_head->next_Dis;
            }
            return max;
        }
    }
    return 0;
}

