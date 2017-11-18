/*
 * Josh
 * Mario
 *
 * Serial Implementation of the Gaussian Blur Algorithm written in C++
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "ppmFile.h"

#define max(a, b) ({ \
    __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; \
})
#define min(a, b) ({ \
    __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; \
})

int blur (int x, int y, int r, Image* image, unsigned char* colour);

int main(int argc, char* argv[]){
    Image* inputImage;
    Image* outImage;
    int r, width, height;
    char* infile;
    char* outfile;

    if (argc < 4){
        printf("Error: Not Enough Arguments\n");
        return 1;
    }
    r = atoi(argv[1]);
    infile = argv[2];
    outfile = argv[3];

    inputImage = ImageRead(infile);

    width = ImageWidth(inputImage);
    height = ImageHeight(inputImage);

    outImage = ImageCreate(width,height);

    clock_t start = clock();

    for(int x = 0; x<width;x++){
        for(int y = 0; y<height;y++){
            unsigned char colour[3];
            blur(x,y,r,inputImage, colour);
            ImageSetPixel(outImage,x,y,0,colour[0]);
            ImageSetPixel(outImage,x,y,1,colour[1]);
            ImageSetPixel(outImage,x,y,2,colour[2]);
        }
    }

    clock_t end = clock();
    double timeelapsed = (double) (end-start) / CLOCKS_PER_SEC;

    ImageWrite(outImage,outfile);
    printf("%s blurred in %f sec\n",infile,timeelapsed);
    return 0;
}

int blur (int x, int y, int r, Image* image, unsigned char* colour){
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    int minX = max((x-r),0);
    int maxX = min((x+r),width-1);

    int minY = max((y-r),0);
    int maxY = min((y+r),height-1);

    int red = 0;
    int green = 0;
    int blue = 0;

    int count = 0;
    for (int i = minX; i<=maxX;i++){
        for(int j = minY; j<=maxY;j++){
            red = red + ImageGetPixel(image, i, j, 0);
            green = green + ImageGetPixel(image, i, j, 1);
            blue = blue + ImageGetPixel(image, i, j, 2);
            count++;
        }
    }
    red = red/count;
    green = green/count;
    blue = blue/count;

    colour[0] = (unsigned char)red;
    colour[1] = (unsigned char)green;
    colour[2] = (unsigned char)blue;

    return 1;
}
