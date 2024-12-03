/* Advent of Code Day 3 - part1 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/utils.h"

int main() {
    printf("Advent of Code Day 3 - part1\n");
    char *file_input = load_input("../input.txt");
    int total = 0;

    char *ptr = file_input;
    while(*ptr != '\0')
    {
        if (strncmp(ptr, "mul(", 4) != 0)
        {
            ptr++;
            continue;
        }
        ptr += 4;
        char *start = ptr;
        int length = 0;
        while(isdigit(*ptr))
        {
            length++;
            ptr++;
        }
        if(*ptr != ',')
        {
            continue;
        }
        ptr++;
        char substring1[length+1];
        strncpy(substring1, start, length);
        substring1[length] = '\0';
        int num1 = atoi(substring1);

        start = ptr;
        length = 0;
        while(isdigit(*ptr))
        {
            length++;
            ptr++;
        }
        if(*ptr != ')')
        {
            continue;
        }
        ptr++;
        char substring2[length+1];
        strncpy(substring2, start, length);
        substring2[length] = '\0';
        int num2 = atoi(substring2);
        total += num1 * num2;
    }

    printf("%i\n", total);
    free(file_input);
    return 0;
}
