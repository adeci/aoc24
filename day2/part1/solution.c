/* Advent of Code Day 2 - part1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/utils.h"


int* line_to_intarray(char* line, int *size_export)
{
    int space_total = 0;
    for(char *ptr = line; *ptr != '\0'; ptr++)
    {
        if(*ptr == ' ') space_total++;
    }
    *size_export = space_total + 1;
    int *intarray = (int *)malloc((*size_export) * sizeof(int));

    char *numstr_ptr = line;
    int index = 0;
    for(char *ptr = line; *ptr != '\0'; ptr++)
    {
        if(*ptr == ' ')
        {
            *ptr = '\0';
            intarray[index] = atoi(numstr_ptr);
            numstr_ptr = ptr + 1;
            index++;

        }
    }
    // final num in the line
    intarray[index] = atoi(numstr_ptr);
    return intarray;
}


int check_arr_validity(int *intarr, int size)
{
    for(unsigned int i = 0; i < size - 1; i++)
    {
        // assuming no negative levels are ever present
        if(!(intarr[i] < intarr[i+1] && abs(intarr[i+1] - intarr[i]) <= 3))
        {
            break;
        }
        if(i == size - 2) return 1;
    }
    for(unsigned int i = 0; i < sizeof(intarr) - 1; i++)
    {
        // assuming no negative levels are ever present
        if(!(intarr[i] > intarr[i+1] && abs(intarr[i] - intarr[i+1]) <= 3))
        {
            break;
        }
        if(i == size - 2) return 1;
    }
    return 0;
}


int main() {
    printf("Advent of Code Day 2 - part1\n");
    char *file_input = load_input("../input.txt");

    char *line = strtok(file_input, "\n");

    int total = 0;
    while(line != NULL)
    {
        int size;
        int *intarr = line_to_intarray(line, &size);
        if(check_arr_validity(intarr, size)) total++;
        free(intarr);
        // advances to next line in file
        line = strtok(NULL, "\n");
    }
    printf("%i\n", total);
    free(file_input);
    return 0;
}
