#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define ARGS_ERROR "Error: argument"
#define FILE_ERROR "Error: Operation file corrupted"
int  w, h, ret;
char c, type;
FILE *file;
char **zone;
float x_start, y_start, r;

void putstr(char *s) {
    while (*s)
        write(1, s++, 1);
    write(1, "\n", 1);
}

int draw(char type, float x_start, float y_start, float r, char c) {
    if ((type != 'c' && type != 'C') || r <= 0)
        return -1;
    if (type == 'c') {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (sqrtf((x - x_start) * (x - x_start) + (y - y_start) * (y - y_start)) <= r
                    && r - sqrtf((x - x_start) * (x - x_start) + (y - y_start) * (y - y_start)) < 1)
                    zone[y][x] = c;
            }
        }
        return 0;
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (sqrtf((x - x_start) * (x - x_start) + (y - y_start) * (y - y_start)) <= r)
                zone[y][x] = c;
        }
    }
    return 0;
}

int main(int ac, char **av) 
{
    if (ac != 2) 
        return (putstr(ARGS_ERROR), 1);
    file = fopen(av[1], "r");
    if (!file)
        return (putstr(FILE_ERROR), 1);
    ret = fscanf(file, "%d %d %c\n", &w, &h, &c);
    if (ret != 3 || w > 300 || h > 300 || w <= 0 || h <= 0)
        return (putstr(FILE_ERROR), 1);
    zone = calloc(h, sizeof(char *));
    for (int i = 0; i < h; i++) {
        zone[i] = calloc(w + 1, 1);
        memset(zone[i], c, w);
    }
    while ((ret = fscanf(file, "%c %f %f %f %c\n", &type, &x_start, &y_start, &r, &c)) != -1) {
        if (ret != 5 || draw(type, x_start, y_start, r, c) == -1)
            return (putstr(FILE_ERROR), 1);
    }
    for (int i = 0; i < h; i++)
        putstr(zone[i]);
    fclose(file);
}
