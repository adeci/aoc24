/* Advent of Code Day 1 - part1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/utils.h"

// bubble sort, takes array to sort and size of array
void bubble_sort(int *array, int size)
{
    for(unsigned int i = 0; i < size - 1; i++)
    {
        for(unsigned int j = 0; j < size - i - 1; j++)
        {
            if(array[j] > array[j+1])
            {
                int swap = array[j];
                array[j] = array[j + 1];
                array[j + 1] = swap;
            }
        }
    }
}

int main() {
    printf("Advent of Code Day 1 - part1\n");
    char *file_input = load_input("../input.txt");

    int line_total = 0;
    for(char *ptr = file_input; *ptr != '\0'; ptr++)
    {
        if(*ptr == '\n') line_total++;
    }

    int *left_list = (int *)malloc(line_total * sizeof(int));
    int *right_list = (int *)malloc(line_total * sizeof(int));

    char *line = strtok(file_input, "\n");

    int index = 0;
    while(line != NULL)
    {
        char *delimiter = strstr(line, "   ");
        if(delimiter != NULL)
        {
            // replace '   ' with null terminator to isolate first num string
            *delimiter = '\0';
            // step delimiter pointer up three in mem to isolate second num string
            delimiter += 3;
            left_list[index] = atoi(line);
            right_list[index] = atoi(delimiter);
            index++;
        }
        line = strtok(NULL, "\n");
    }

    bubble_sort(left_list, line_total);
    bubble_sort(right_list, line_total);

    int total_difference = 0;
    for(unsigned int i = 0; i < line_total; i++)
    {
        int difference = abs(left_list[i] - right_list[i]);
        total_difference += difference;
    }

    printf("%i\n", total_difference);

    free(left_list);
    free(right_list);
    return 0;
}
