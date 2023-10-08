#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

FILE* read_input(char* filename)
{
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL){
        perror("read_input");
        exit(1);
    }

    return fp;
}

void part_1(FILE *input)
{
    (void)fseek(input, 0, SEEK_SET);

    int floor = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        if (c == '(')
            floor++;
        else if (c == ')')
            floor--;
    }

    (void)printf("The floor is %d\n", floor);
}

void part_2(FILE *input)
{
    (void)fseek(input, 0, SEEK_SET);

    int floor = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        if (c == '(')
            floor++;
        else if (c == ')')
            floor--;
        if (floor < 0) break;
    }

    (void)printf("The turn where Santa enters the basement is %ld\n", ftell(input));
}

int main(void)
{
    FILE *fp = read_input("day1_input.txt");
    part_1(fp);
    part_2(fp);
    (void)fclose(fp);
}
