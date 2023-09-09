/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"
#define MaxNeighbors 8
struct neighbDirection{
	int row;
	int col;
};

void isLive(int statues,Color* DeadOrLive){
	if(statues){
		DeadOrLive->B = 255;
	}
	else{
		DeadOrLive->B = 0;
	}
			
}
//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	int liveCellAdiacent = 0;
	uint32_t getStatues = 1;
	//struct declare need add keyword "struct"
	struct neighbDirection  neighb[MaxNeighbors] = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
	for(int i=0; i<MaxNeighbors; i++){
		int rows, cols;
		rows = row;   cols = col;
		rows += neighb[i].row;
		cols += neighb[i].col;
		if((rows>=0 && rows<(image->rows)) && (cols>=0 && cols<(image->cols))){
			if(image->image[rows][cols].R)
				liveCellAdiacent++;				
		}
	}
	Color* DeadOrLive = malloc(sizeof(Color));
	if(!DeadOrLive){
		exit(-1);
	}
	if(!(image->image[row][col].R)){
		getStatues = getStatues & (rule >> liveCellAdiacent);
		isLive(getStatues,DeadOrLive);
	}
	else{
		getStatues = getStatues & (rule >> (liveCellAdiacent+9));
		isLive(getStatues,DeadOrLive);
	}
	return DeadOrLive;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	for(int r =0; r<(image->rows); r++){
		for(int c =0; c<(image->cols); c++){
			Color* temp = evaluateOneCell(image,r,c,rule);
			image->image[r][c].B = temp->B;
			free(temp);
		}
	}
	//所有位状态确定之前不该更新位状态
	for(int r =0; r<(image->rows); r++){
		for(int c =0; c<(image->cols); c++){
				image->image[r][c].R = image->image[r][c].G = image->image[r][c].B;
		}
	}
	return image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
uint32_t HexStringToInt(char* Hexstring){
	char* temp = NULL;
	uint32_t len = strlen(Hexstring);
	temp = Hexstring+2;
	uint32_t result = 0;
	while(*temp != '\0' ){
		result = result*16 + (*temp-'0');
		temp++;
	}
	return result;
}

void processCLI(int argc, char **argv, char **filename, uint32_t *rule) 
{
	if (argc != 3) {
		printf("usage: %s filename rule\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.");
		exit(-1);
	}
	*filename = argv[1];
	*rule = HexStringToInt(argv[2]);
}

int main(int argc, char **argv)
{
	//YOUR CODE HERE
	Image *image;
	char *filename;
	uint32_t rule;

	processCLI(argc,argv,&filename,&rule);
	image = readData(filename);
	image = life(image,rule);
	writeData(image);
	freeImage(image);
	return 0;
}
