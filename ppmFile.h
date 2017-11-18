/****************************************************************
 *
 * ppm.h
 *
 * Read and write PPM files.  Only works for "raw" format.
 *
 * Supplied by the TA
 *
 ****************************************************************/

#ifndef PPM_H
#define PPM_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Image
{
  int width;
  int height;
  unsigned char *data;
} Image;

Image *ImageCreate(int width, int height);
Image *ImageRead(char *filename);
void   ImageWrite(Image *image, char *filename);

int    ImageWidth(Image *image);
int    ImageHeight(Image *image);

void   ImageClear(Image *image, unsigned char red, unsigned char green, unsigned char blue);

void   ImageSetPixel(Image *image, int x, int y, int chan, unsigned char val);
unsigned char ImageGetPixel(Image *image, int x, int y, int chan);

#ifdef __cplusplus
}
#endif

#endif /* PPM_H */