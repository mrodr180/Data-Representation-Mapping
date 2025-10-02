#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sub_convert(uint32_t n, int base, char *out);
void oct_to_bin(const char* oct, char* out);
void hex_to_bin(const char* hex, char* out);
void oct_to_hex(const char* oct, char* hex);
void to_sign_magnitude(int n, char *out);
void to_ones_complement(int n, char *out);
void to_twos_compliment(int n, char *out);

int main() {
    //file reading and writing code was used/ modified from previous assignment
    FILE *file = fopen("C:\\Users\\migue\\Downloads\\a2_test.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    FILE *outFile = fopen("outputt.txt", "w");
    if (!outFile) {
        printf("Error\n");
        return 1;
    }

    char line[256], function[32], expected[65], output[65];
    int lineNumber = 0;
    char input1[32]; //changed from unsigned int to char due to oct->hex & oct->bin requiring *char in the (parameter)


    while (fgets(line, sizeof(line), file) != NULL) {
        int parse = sscanf(line,"%31s %31s %64s", function, input1, expected);

        if (parse == 3) {
            if (strcmp(function, "oct_to_bin") == 0)
                oct_to_bin(input1, output);
            else if (strcmp(function, "oct_to_hex") == 0)
                oct_to_hex(input1, output);
            else if (strcmp(function, "hex_to_bin") == 0)
                hex_to_bin(input1, output);
            else if (strcmp(function, "to_sign_magnitude") == 0)
                to_sign_magnitude(atoi(input1), output); //TO BE CLEAR I FOUND ATOI AFTER GOOGLING HOW TO CHANGE FROM CHAR TO INT
            else if (strcmp(function, "to_ones_complement") == 0)
                to_ones_complement(atoi(input1), output);
            else if (strcmp(function, "to_twos_complement") == 0)
                to_twos_compliment(atoi(input1), output);

            sprintf(line, "Test %d: %s(%s) --> expected: %s, got %s  [%s]\n", lineNumber, function, input1, expected, output,
            strcmp(output, expected) == 0 ? "pass" : "fail");
            printf("%s", line);
            fprintf(outFile, "%s", line);
            lineNumber++;

        }
    }
    fclose(file);
    fclose(outFile);
    return 0;
}