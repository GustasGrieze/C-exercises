/*
Gustas Griežė Programų sistemos 1 grupė 1 pogrupis
12. Užduotis:
    Parašyti funkciją, kuri randa ir atspausdina visus žodžius, kurie vienodai skaitomi iš pradžios ir iš galo.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define MAX_LINE_LENGTH 255
#define MAX_WORD_LENGTH 255
#define SPACE ' '
#define NEWLINE '\n'
#define CARRIAGE_RETURN '\r'

bool isPalindrome(char *word) {
    int length = strlen(word);
    if (length < 2) {
        return false;
    }
    for (int i = 0; i < length / 2; i++) {
        // Compare each character from the start and end of the word
        if (word[i] != word[length - i - 1]) {
            return false;
        }
    }
    return true;
}

void appendWordIfPalindrome(char *word, char *result) {
    if (isPalindrome(word)) {
        strcat(result, word); // Append the word to the result
        strcat(result, "\n"); // Append a newline character after the word
    }
}

void processText(char *text, char *result) {
    char word[MAX_WORD_LENGTH]; // Array to store the current word
    int position = 0; // Position in the word array
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == SPACE || text[i] == NEWLINE || text[i] == CARRIAGE_RETURN) {
            word[position] = '\0'; // Null-terminate the word
            appendWordIfPalindrome(word, result);
            position = 0; // Reset the position for the next word
        } else {
            // Add the character to the word, checking for buffer overflow
            if (position < MAX_WORD_LENGTH - 1) {
                word[position++] = text[i];
            }
        }
    }
    word[position] = '\0'; // Null-terminate the last word
    appendWordIfPalindrome(word, result); // Check if the last word is a palindrome
}

void readFileInChunks(const char *filename, void (*callback)(char *, char *), char *result) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE]; // Buffer to store file chunks
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        callback(buffer, result); // Process each chunk of text
    }
    fclose(file);
}

// Function to write text to a file
void writeToFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", text); // Write the text to the file
    fclose(file);
}

void getInputFilename(char *filename, int maxLength) {
    while (1) {
        if (fgets(filename, maxLength, stdin) == NULL) {
            fprintf(stderr, "Error reading input. Please try again.\n"); // Print an error if input couldn't be read
            continue;
        }
        filename[strcspn(filename, "\n")] = 0; // Remove the newline character from the input

        FILE *file = fopen(filename, "r"); // Try to open the file
        if (file != NULL) {
            fclose(file);
            break;
        } else {
            perror("Error opening file");
        }
    }
}

int main(int argc, char *argv[]) {
    char inputFilename[MAX_LINE_LENGTH]; // Array to store the input filename
    char *outputFilename = NULL; // Pointer to store the output filename

    if (argc > 1) {
        strncpy(inputFilename, argv[1], MAX_LINE_LENGTH); // Copy the input filename from command-line arguments
        if (argc > 2) {
            outputFilename = argv[2]; // Get the output filename from command-line arguments
        }
    } else {
        getInputFilename(inputFilename, MAX_LINE_LENGTH); // Get the input filename from the user
    }

    char result[MAX_LINE_LENGTH * BUFFER_SIZE] = "";
    readFileInChunks(inputFilename, processText, result); // Read the input file and process it

    if (outputFilename != NULL) {
        writeToFile(outputFilename, result); // Write the result to the output file
    } else {
        printf("Palindromes that have been found in the provided file:\n");
        printf("%s", result);
    }

    return 0;
}
