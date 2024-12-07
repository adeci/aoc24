/* Advent of Code Day 4 - part1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/utils.h"

void cleanup_grids(char** rows, char** cols, char** diags, int row_count, int diag_count)
{
    for(int i = 0; i < strlen(rows[0]); i++)
    {
        free(cols[i]);
    }

    for(int i = 0; i < row_count; i++)
    {
        free(rows[i]);
    }
    for (int i = 0; i < diag_count; i++) {
        free(diags[i]);
    }
    free(diags);
    free(rows);
    free(cols);
}

char** get_rows(char *str_input, int* row_count)
{
    *row_count = 0;
    for(char *ptr = str_input; *ptr != '\0'; ptr++)
    {
        if(*ptr == '\n') (*row_count)++;
    }
    if (str_input[strlen(str_input) - 1] != '\n') (*row_count)++;

    char *line = strtok(str_input, "\n");
    char **rows = (char**)malloc(sizeof(char*) * (*row_count));

    int index = 0;
    while(line != NULL && index < *row_count)
    {
        rows[index] = strdup(line);
        line = strtok(NULL, "\n");
        index++;
    }
    return rows;
}

char** get_cols(char** rows, int row_count)
{
    int col_count = strlen(rows[0]);
    char **cols = (char**)malloc(sizeof(char*) * col_count);
    for (int i = 0; i < strlen(rows[0]); i++)
    {
        char *col = (char*)malloc(sizeof(char) * (row_count + 1));
        cols[i] = col;
    }

    for (int i = 0; i < row_count; i++)
    {
        for(int j = 0; j < col_count; j++)
        {
            cols[j][i] = rows[i][j];
        }
    }

    for (int i = 0; i < col_count; i++)
    {
        cols[i][row_count] = '\0';
    }

    return cols;
}

char** get_diags(char **rows, int row_count, int* diag_count) {
    int col_count = strlen(rows[0]);
    int max_diags = row_count + col_count - 1;
    // * 2 for both dirs
    char** diags = (char**)malloc(sizeof(char*) * max_diags * 2);

    *diag_count = 0;

    // tl->br
    for (int i = 0; i < max_diags; i++) {
        char* diag = (char*)malloc(sizeof(char) * (row_count + col_count));
        int index = 0;
        for (int j = 0; j < row_count; j++) {
            int col_index = i - j;
            if (col_index >= 0 && col_index < col_count) {
                diag[index++] = rows[j][col_index];
            }
        }
        diag[index] = '\0';
        if (index > 0) {
            diags[(*diag_count)++] = diag;
        } else {
            free(diag);
        }
    }

    //tr->bl
    for (int i = 0; i < max_diags; i++) {
        char* diag = (char*)malloc(sizeof(char) * (row_count + col_count));
        int index = 0;
        for (int j = 0; j < row_count; j++) {
            int col_index = j + i - row_count + 1;
            if (col_index >= 0 && col_index < col_count) {
                diag[index++] = rows[j][col_index];
            }
        }
        diag[index] = '\0';
        if (index > 0) {
            diags[(*diag_count)++] = diag;
        } else {
            free(diag);
        }
    }

    return diags;
}

int find_xmas_occurences(char* string)
{
    int total = 0;
    char *ptr = string;
    while (*ptr != '\0') {
        if(strncmp(ptr, "XMAS", 4) == 0) total++;
        if(strncmp(ptr, "SAMX", 4) == 0) total++;
        ptr++;
    }
    return total;
}

int main() {
    printf("Advent of Code Day 4 - part1\n");
    char *file_input = load_input("../input.txt");

    int row_count = 0;
    int diag_count = 0;
    char** rows = get_rows(file_input, &row_count);
    char** cols = get_cols(rows, row_count);
    char** diags = get_diags(rows, row_count, &diag_count);

    int total = 0;
    for(int i = 0; i < row_count; i++)
    {
        total += find_xmas_occurences(rows[i]);
    }

    for(int i = 0; i < strlen(rows[0]); i++)
    {
        total += find_xmas_occurences(cols[i]);
    }

    for(int i = 0; i < diag_count; i++)
    {
        total += find_xmas_occurences(diags[i]);
    }

    printf("%i\n", total);

    cleanup_grids(rows, cols, diags, row_count, diag_count);
    free(file_input);
}
