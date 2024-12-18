#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// File names
#define NUMBERS_FILE "numbers.txt"
#define INPUT_TEXT_FILE "input_text.txt"
#define OUTPUT_TEXT_FILE "output_text.txt"

// Function prototypes
void processNumbersFile();
void processTextFile();

int main() {
    int choice;

    while (1) {
        printf("\nSelect an option:\n");
        printf("1. Process numbers file (Task 1)\n");
        printf("2. Process text file (Task 2)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                processNumbersFile();
                break;
            case 2:
                processTextFile();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}

// Task 1: Process Numbers File
void processNumbersFile() {
    FILE *file;
    double number, sum = 0.0;
    int count = 0;

    // Open the file for writing
    file = fopen(NUMBERS_FILE, "w");
    if (file == NULL) {
        perror("Error opening file for writing numbers");
        return;
    }

    // Input numbers
    printf("Enter real numbers (type -999 to stop):\n");
    while (1) {
        scanf("%lf", &number);
        if (number == -999) break;
        fprintf(file, "%.6lf ", number); // Write to file
    }
    fclose(file);

    // Re-open the file for reading
    file = fopen(NUMBERS_FILE, "r");
    if (file == NULL) {
        perror("Error opening file for reading numbers");
        return;
    }

    // Read numbers and calculate the average of positive numbers
    while (fscanf(file, "%lf", &number) == 1) {
        if (number > 0) {
            sum += number;
            count++;
        }
    }
    fclose(file);

    // Print the result
    if (count > 0) {
        printf("Average of positive numbers: %.2lf\n", sum / count);
    } else {
        printf("No positive numbers found in the file.\n");
    }
}

// Task 2: Process Text File
void processTextFile() {
    FILE *inputFile, *outputFile;
    char line[256];
    int i, len;

    // Open the input file for reading
    inputFile = fopen(INPUT_TEXT_FILE, "r");
    if (inputFile == NULL) {
        perror("Error opening input text file");
        return;
    }

    // Open the output file for writing
    outputFile = fopen(OUTPUT_TEXT_FILE, "w");
    if (outputFile == NULL) {
        perror("Error opening output text file");
        fclose(inputFile);
        return;
    }

    // Process each line: add "00" between consecutive letters
    printf("Processing the text file...\n");
    while (fgets(line, sizeof(line), inputFile)) {
        len = strlen(line);
        for (i = 0; i < len; i++) {
            fputc(line[i], outputFile); // Write the current character
            if (isalpha(line[i]) && isalpha(line[i + 1])) {
                fputs("00", outputFile); // Insert "00" between consecutive letters
            }
        }
    }

    printf("Text file processed successfully. Check '%s'.\n", OUTPUT_TEXT_FILE);

    // Close files
    fclose(inputFile);
    fclose(outputFile);
}
