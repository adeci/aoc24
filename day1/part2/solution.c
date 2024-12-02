/* Advent of Code Day 1 - part2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/utils.h"


int main() {
    printf("Advent of Code Day 1 - part2\n");
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

    /*
    inefficient solution

    int score = 0;
    for(unsigned int i = 0; i < line_total; i++)
    {
        int occs = 0;
        for(unsigned int j = 0; j < line_total; j++)
        {
            if(right_list[j] == left_list[i]) occs++;
        }
        score += occs * left_list[i];
    }
    */

    // somewhat better solution using frequency table for lookups
    int *unique_num_array = (int *)malloc(line_total * sizeof(int));
    int *frequency_array = (int *)calloc(line_total, sizeof(int));
    int uniq = 0;
    for(unsigned int i = 0; i < line_total; i++)
    {
        int discovered = 0;
        for(unsigned int j = 0; j < uniq; j++)
        {
            if(unique_num_array[j] == right_list[i])
            {
                frequency_array[j]++;
                discovered = 1;
                break;
            }
        }
        if(!discovered)
        {
            unique_num_array[uniq] = right_list[i];
            frequency_array[uniq] = 1;
            uniq++;
        }
    }

    int score = 0;
    for(unsigned int i = 0; i < line_total; i++)
    {
        for(unsigned int j = 0; j < uniq; j++)
        {
            if(unique_num_array[j] == left_list[i])
            {
                score += frequency_array[j] * left_list[i];
                break;
            }
        }
    }

    printf("%i\n", score);

    free(unique_num_array);
    free(frequency_array);
    free(left_list);
    free(right_list);
    free(file_input);
    return 0;
}

