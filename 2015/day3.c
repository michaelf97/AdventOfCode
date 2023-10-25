#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct coords {
	int x;
	int y;
};

struct coords *parse_move(struct coords *coords, char move)
{
	switch (move) {
		case '^':
			coords->y++;
			break;
		case 'v':
			coords->y--;
			break;
		case '>':
			coords->x++;
			break;
		case '<':
			coords->x--;
			break;
	}

	return coords;
}

FILE* read_input(char *filename)
{
	FILE *fp;
	
	fp = fopen(filename, "rb");
	
	if (fp == NULL) {
		perror("Error opening file file");
		exit(1);
	}
	
	return fp;
	
}

int get_filesize(FILE *fp)
{
	int saved_position = ftell(fp);
	(void)fseek(fp, 0, SEEK_END);
	int filesize = ftell(fp);
	(void)fseek(fp, saved_position, SEEK_SET);
	
	return filesize;
}

void part1(FILE *fp)
{
	char c;
	int unique_house_count = 1, filesize = get_filesize(fp);
	
	struct coords *coords_array = calloc(filesize + 1, sizeof(struct coords));
	struct coords coords = {.x = 0, .y = 0};
	coords_array[0] = coords;
	
	while ((c = fgetc(fp)) != EOF) {
		coords = *parse_move(&coords, c);
		
		int is_present_flag = 0;
		for (int index = 0; index <= unique_house_count; index++) {
			if (coords_array[index].x == coords.x && coords_array[index].y == coords.y) {
				is_present_flag = 1;
				break;
			}
		}
		
		if (is_present_flag == 0)
			coords_array[++unique_house_count] = coords;
	}
	
	(void)free(coords_array);
	(void)printf("Part 1: Unique House Count: %d\n", unique_house_count);
}

void part2(FILE* fp)
{
	char c[2];
	int unique_house_count = 1, filesize = get_filesize(fp);
	
	struct coords *santa_coords_array = calloc(filesize + 1, sizeof(struct coords));
	struct coords *robot_coords_array = calloc(filesize + 1, sizeof(struct coords));
	struct coords *coords_array = calloc(filesize + 1, sizeof(struct coords));
	
	// Coordinates for santa and robot.
	struct coords santa = {.x = 0, .y = 0};
	struct coords robot = {.x = 0, .y = 0};
	
	santa_coords_array[0] = santa;
	robot_coords_array[1] = robot;
	
	while (fread(c, sizeof(char), 2, fp) == 2) {
		santa = *parse_move(&santa, c[0]);
		robot = *parse_move(&robot, c[1]);
		
		int santa_is_present_flag = 0, robot_is_present_flag = 0, same_house_flag = 0;
		for (int index = 0; index <= unique_house_count; index++) {
			if (santa.x == robot.x && santa.y == robot.y)
				same_house_flag = 1;

			if (coords_array[index].x == santa.x && coords_array[index].y == santa.y)
				santa_is_present_flag = 1;
				
			if (coords_array[index].x == robot.x && coords_array[index].y == robot.y)
				robot_is_present_flag = 1;
				
			if (santa_is_present_flag == 1 && robot_is_present_flag == 1)
				break;		
		}
		
		if ((santa_is_present_flag == 0 || robot_is_present_flag == 0) && same_house_flag == 1) {
			coords_array[++unique_house_count] = robot;
			continue;
		}
			
		if (robot_is_present_flag == 0)
			coords_array[++unique_house_count] = robot;
		
		if (santa_is_present_flag == 0)
			coords_array[++unique_house_count] = santa;
	}
	
	(void)free(coords_array);
	(void)printf("Part 2: Unique House Count: %d\n", unique_house_count);
}

int main(void)
{
	FILE *fp = read_input("day3_input.txt");
	part1(fp);
	(void)fseek(fp, 0, SEEK_SET);
	part2(fp);
}
