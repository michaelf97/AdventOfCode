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

int compare(const void *a, const void *b)
{
    const int *x = a, *y = b;

    if (*x > *y) return 1;
    if (*x < *y) return -1;
    return 0;
}

int min(int a, int b) { return ((a <= b)) ? a : b; }

int max(int a, int b) { return ((a <= b)) ? a : b; }

int mid(int a, int b, int c)
{
        int array[3] = {a, b, c};
        qsort(array, 3, sizeof(int), compare);

        return array[1];
}

int calculate_paper_for_present(int length, int width, int height)
{
    int face_one = length * width;
    int face_two = width * height;
    int face_three = height * length;

    int smallest_face = min(face_one, min(face_two, face_three));

    return (2 * (face_one + face_two + face_three)) + smallest_face;
}

int calculate_ribbon_for_present(int length, int width, int height)
{
    int smallest_dimension = min(length, min(width, height));
    int middle_dimension = mid(length, width, height);

    return (2 * (smallest_dimension + middle_dimension)) + (length * width * height);
}

void part_1(FILE *input)
{
    (void)fseek(input, 0, SEEK_SET);
    int length = 0, width = 0, height = 0;
    int paper_requirement = 0;

    while (fscanf(input, "%dx%dx%d\n", &length, &width, &height) != EOF)
        paper_requirement += calculate_paper_for_present(length, width, height);

    (void)printf("The total paper required is %d\n", paper_requirement);
}

void part_2(FILE *input)
{
    (void)fseek(input, 0, SEEK_SET);
    int length = 0, width = 0, height = 0;
    int ribbon_requirement = 0;

    while (fscanf(input, "%dx%dx%d\n", &length, &width, &height) != EOF) {
        ribbon_requirement += calculate_ribbon_for_present(length, width, height);
    }

    (void)printf("The total ribbon required is %d\n", ribbon_requirement);
}

int main(void)
{
    FILE *fp = read_input("day2_input.txt");
    part_1(fp);
    part_2(fp);
    (void)fclose(fp);
}
