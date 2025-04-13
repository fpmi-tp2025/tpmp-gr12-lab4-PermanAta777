#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "database.h"
#include "country.h"
#include "region.h"

void show_menu() {
    printf("\nCountryApp Menu:\n");
    printf("1. Add Country\n");
    printf("2. Delete Country\n");
    printf("3. Add Region\n");
    printf("4. Delete Region\n");
    printf("5. List Regions for Country\n");
    printf("6. Average Population by Regions\n");
    printf("7. Total Population\n");
    printf("8. Exit\n");
    printf("Choose an option: ");
}

int main() {
    char username[50], password[50];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (!authenticate(username, password)) {
        printf("Authentication failed!\n");
        return 1;
    }

    sqlite3 *db = init_db();
    if (!db) {
        return 1;
    }

    int choice;
    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_country(db);
                break;
            case 2: {
                int id;
                printf("Enter country ID to delete: ");
                scanf("%d", &id);
                delete_country(db, id);
                break;
            }
            case 3:
                add_region(db);
                break;
            case 4: {
                int id;
                printf("Enter region ID to delete: ");
                scanf("%d", &id);
                delete_region(db, id);
                break;
            }
            case 5: {
                int id;
                printf("Enter country ID: ");
                scanf("%d", &id);
                list_regions(db, id);
                break;
            }
            case 6: {
                int id;
                printf("Enter country ID: ");
                scanf("%d", &id);
                avg_population(db, id);
                break;
            }
            case 7:
                total_population(db);
                break;
            case 8:
                close_db(db);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option!\n");
        }
    }

    return 0;
}