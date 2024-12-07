/* Advent of Code Day 4 - part2 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../utils/utils.h"

struct Coord
{
    char c;
    int x;
    int y;
};

struct HitMap
{
    int x;
    int y;
    int hits;
    int shared;
};

void cleanup_grids(char** rows, struct Coord** diags, int row_count, int diag_count)
{
    for(int i = 0; i < row_count; i++)
    {
        free(rows[i]);
    }
    for (int i = 0; i < diag_count; i++) {
        free(diags[i]);
    }
    free(diags);
    free(rows);
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


struct Coord** get_diags(char **rows, int row_count, int* diag_count) {
    int col_count = strlen(rows[0]);
    int max_diags = row_count + col_count - 1;
    // * 2 for both dirs
    struct Coord** diags = (struct Coord**)malloc(sizeof(struct Coord*) * max_diags * 2);

    *diag_count = 0;

    // tl->br
    for (int i = 0; i < max_diags; i++) {
        struct Coord* diag = (struct Coord*)malloc(sizeof(struct Coord) * (row_count + col_count));
        int index = 0;
        for (int j = 0; j < row_count; j++) {
            int col_index = i - j;
            if (col_index >= 0 && col_index < col_count) {
                diag[index].c = rows[j][col_index];
                diag[index].x = j;
                diag[index].y = col_index;
                index++;
            }
        }
        diag[index].c = '\0';
        if (index > 0) {
            diags[(*diag_count)++] = diag;
        } else {
            free(diag);
        }
    }

    //tr->bl
    for (int i = 0; i < max_diags; i++) {
        struct Coord* diag = (struct Coord*)malloc(sizeof(struct Coord) * (row_count + col_count));
        int index = 0;
        for (int j = 0; j < row_count; j++) {
            int col_index = j + i - row_count + 1;
            if (col_index >= 0 && col_index < col_count) {
                diag[index].c = rows[j][col_index];
                diag[index].x = j;
                diag[index].y = col_index;
                index++;
            }
        }
        diag[index].c = '\0';
        if (index > 0) {
            diags[(*diag_count)++] = diag;
        } else {
            free(diag);
        }
    }

    return diags;
}

int find_mas_crosses(struct Coord **coords, int diag_count) {
    struct HitMap *hit_map_global = NULL;
    int hit_map_global_count = -1;

    for (int i = 0; i < diag_count; i++) {
        struct Coord *diag = coords[i];
        int diag_len = 0;

        while (diag[diag_len].c != '\0') diag_len++;

        struct HitMap *hit_map = (struct HitMap *)malloc(sizeof(struct HitMap) * diag_len);
        int hitmap_count = 0;

        for (int i = 0; i < diag_len; i++) {
            hit_map[i].hits = 0;
            hit_map[i].shared = 0;
        }

        for (int index = 0; index < diag_len - 2; index++) {
            if ((diag[index].c == 'M' && diag[index + 1].c == 'A' && diag[index + 2].c == 'S') ||
                (diag[index].c == 'S' && diag[index + 1].c == 'A' && diag[index + 2].c == 'M')) {
                int hit = 0;

                for (int z = 0; z < hitmap_count; z++) {
                    if (diag[index + 1].x == hit_map[z].x && diag[index + 1].y == hit_map[z].y) {
                        hit_map[z].hits += 1;
                        hit = 1;
                        break;
                    }
                }
                if (!hit) {
                    hit_map[hitmap_count].x = diag[index + 1].x;
                    hit_map[hitmap_count].y = diag[index + 1].y;
                    hit_map[hitmap_count].hits = 1;
                    hitmap_count++;
                }
            }
        }

        if (hit_map_global_count == -1) {
            hit_map_global = hit_map;
            hit_map_global_count = hitmap_count;
        } else {
            int shared_points = 0;

            for (int g = 0; g < hit_map_global_count; g++) {
                for (int l = 0; l < hitmap_count; l++) {
                    if (hit_map[l].x == hit_map_global[g].x && hit_map[l].y == hit_map_global[g].y) {
                        shared_points++;
                        hit_map_global[g].hits += hit_map[l].hits;
                        hit_map[l].shared = 1;
                    }
                }
            }

            int new_points = hitmap_count - shared_points;
            if (new_points > 0) {
                int add_index = hit_map_global_count;
                hit_map_global_count += new_points;
                hit_map_global = realloc(hit_map_global, sizeof(struct HitMap) * hit_map_global_count);
                for (int l = 0; l < hitmap_count; l++) {
                    if (!hit_map[l].shared) {
                        hit_map_global[add_index] = hit_map[l];
                        add_index++;
                    }
                }
            }
        }

        free(hit_map);
    }

    int total = 0;
    for (int i = 0; i < hit_map_global_count; i++) {
        if (hit_map_global[i].hits == 2) total++;
    }

    free(hit_map_global);
    return total;
}

int main() {
    printf("Advent of Code Day 4 - part2\n");
    char *file_input = load_input("../input.txt");

    int row_count = 0;
    int diag_count = 0;
    char** rows = get_rows(file_input, &row_count);
    struct Coord** diags = get_diags(rows, row_count, &diag_count);

    int total = find_mas_crosses(diags, diag_count);

    printf("%i\n", total);

    cleanup_grids(rows, diags, row_count, diag_count);
    free(file_input);
}
