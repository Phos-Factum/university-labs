// main.c

#include "calculations.h"
#include "calculations.c"

int main() {
    int calculation_done = 0;
    int time_80V_calculated = 0;
    int parameter_calculated = 0;
    float t[N], Uvx[N], Uvix[N];
    int n = 0;
    float time_80V = 0; // Variable to store time when Uvx reaches 80V

    print_splash_screen(); // Display splash screen

    while (1) {
        int choice;
        
        // Print top border
        printf("\n\n\n\n*******************************************\n");
        printf("*\033[34m||||||||||||||||||\033[0mMenu\033[34m|||||||||||||||||||\033[0m*\n");
        printf("*******************************************\n");
        printf("* 1 -\033[32m Control calculation for 'n' points  \033[0m*\n");
        printf("* 2 -\033[32m Find time when Uvx reaches 80V      \033[0m*\n");
        printf("* 3 -\033[32m Calculate parameter with precision  \033[0m*\n");
        printf("* 4 -\033[32m Write data to files                 \033[0m*\n");
        printf("* 5 -\033[32m Show initial parameters             \033[0m*\n");
        printf("* 6 -\033[33m Abort program execution             \033[0m*\n");
        printf("*******************************************\n");
        printf("            Enter your choice: ");

        // Prompt user for input
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 6) {
            printf("\033[1;31mInvalid choice. Please enter a valid option (1, 2, 3, 4, 5 or 6): \033[0m");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        printf("\n");

        switch(choice) {
            case 1:
                printf("\n\n    Enter the number of points: ");
                while (1) {
                    if (scanf("%d", &n) == 1 && n > 0) {
                        control_calculation(n, t, Uvx, Uvix, &calculation_done);
                        parameter_calculated = 0; // Reset parameter calculation flag
                        time_80V_calculated = 0; // Reset time 80V calculation flag
                        break; // Break if valid input
                    } else {
                        printf("\033[1;31mInvalid input. Please enter a positive integer for the number of points:\033[0m ");
                        while (getchar() != '\n'); // Clear input buffer
                    }
                }
                break;
            case 2:
                if (calculation_done) {
                    time_80V = find_time_80V(n, t, Uvx);
                    if (time_80V != -1) {
                        printf("  Time when 'Uvx' reaches 80V: %f\n", time_80V);
                        time_80V_calculated = 1; // Mark time 80V calculation as done
                    } else {
                        printf("Uvx never reaches 80V.\n");
                    }
                } else {
                    printf("\033[1;31mNo data available. Please perform a control calculation first.\033[0m\n");
                }
                break;
            case 3:
                if (time_80V_calculated) {
                    calculate_parameter_with_precision(n, t, Uvx, Uvix, time_80V); // Pass time when Uvx reaches 80V
                    parameter_calculated = 1; // Set parameter calculation flag
                } else {
                    printf("\033[1;31mTime when Uvx reaches 80V has not been calculated. Please perform this calculation first.\033[0m\n");
                }
                break;
            case 4:
                if (calculation_done) {
                    write_data_to_files(n, t, Uvx, Uvix);
                } else {
                    printf("\033[1;31mNo data to write. Perform control calculation first.\033[0m\n");
                }
                break;
            case 5:
                show_parameters(); // Display calculation parameters
                break;
            case 6:
                printf("\033[1;33mProgram execution aborted by user.\033[0m\n");
                return 0; // Exit the program
        }

        // Clear input buffer
        while (getchar() != '\n');
    }

    return 0;
}
