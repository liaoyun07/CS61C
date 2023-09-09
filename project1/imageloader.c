/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename,"r");
	if(!fp){
		exit(-1);
	}
	Image *object = malloc(sizeof(Image));
	if(!object){
			exit(-1);
	}
	char buf[10];
	fscanf(fp,"%s",buf);
	fscanf(fp,"%u %u",&(object->cols),&(object->rows));
	if(!(object->image = malloc(object->rows*sizeof(Color*)))){
		free(object);
		object = NULL;
		exit(-1);
	}
		
	for(int i=0; i<object->rows; i++){
		if(!(object->image[i] = malloc(object->cols*sizeof(Color)))){
			freeImage(object);
			exit(-1);
		}
			
	}
	uint32_t maxRGB;
	fscanf(fp,"%u",&maxRGB);
	for(int i=0; i<object->rows; i++){
		for(int j =0; j<object->cols; j++){
			uint32_t R,G,B;
			fscanf(fp,"%u %u %u",&R,&G,&B);
			object->image[i][j].R = (uint8_t)R;
			object->image[i][j].G = (uint8_t)G;
			object->image[i][j].B = (uint8_t)B;
		}
	}
	fclose(fp);
	return object;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%u %u\n",image->cols,image->rows);
	uint32_t maxRGB = 255;
	printf("%u\n",maxRGB);
	for(int i=0; i<image->rows; i++){
		for(int j =0; j<image->cols; j++){
			if(j<(image->cols-1))
				printf("%3u %3u %3u   ",image->image[i][j].R,image->image[i][j].G,image->image[i][j].B);
			else
				printf("%3u %3u %3u\n",image->image[i][j].R,image->image[i][j].G,image->image[i][j].B);
		}
	}
	fflush(stdout);
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for(int i=0; i<image->rows; i++){
		if(image->image[i]){
			free(image->image[i]);
			image->image[i] = NULL;
		}
	}
	free(image->image);
	free(image);
	image = NULL;
}