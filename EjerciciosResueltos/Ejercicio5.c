#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int getValue(int x, int y, char colour, unsigned char * data, int height, int width, int rowWidth, int colorDepth)
{
    if (x<0 || x>=width)
        return 0;
    if (y < 0 || y >= height)
        return 0;
    return data[(height - 1 - y) * rowWidth + colorDepth*x +colour];
}
unsigned char * getValuePos(int x, int y, char colour, unsigned char* data, int height, int width, int rowWidth, int colorDepth)
{
    if (x < 0 || x >= width)
        return 0;
    if (y < 0 || y >= height)
        return 0;
    return data+( (height - 1 - y) * rowWidth + colorDepth * x +colour);
}

int main(int argc, char ** argv){
	unsigned char info[54];
    int size;
    int i, width, height, rowSize, imgSize;
    short colorDepth;
    FILE* f =fopen("imagen.bmp", "rb");


    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    colorDepth = *(short*)&info[28];
    printf("%d\n", colorDepth);
    colorDepth = colorDepth / 8;
    rowSize =  (int)(floor((colorDepth*8 * width + 31.) / 32)) * 4;

    // allocate 3 bytes per pixel
    imgSize = rowSize * height;
    unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * imgSize);
    // read the rest of the data at once
    fread(data, sizeof(unsigned char), imgSize, f);
    fclose(f);

    unsigned char* newData = (unsigned char*)malloc(sizeof(unsigned char) * imgSize);


    char matrix[] = {   -1,  -2,  -1,  
                        0,  1, 0,  
                        1,  2,  -1 };
    /*char matrix[] = { -1,  2,  -1,
                        2,  -4, 2,
                        -1,  2,  -1 };*/
    int minTemp = 10000;
    int maxTemp = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int temp = 0;
            for (char colour = 0; colour < colorDepth; colour++)
            {
                //temp += getValue(x, y, colour, data, height, width, rowSize);
                temp+= (getValue(x - 1, y - 1, colour, data, height, width, rowSize, colorDepth) * matrix[0] +
                    getValue(x, y - 1, colour, data, height, width, rowSize, colorDepth) * matrix[1] +
                    getValue(x + 1, y - 1, colour, data, height, width, rowSize, colorDepth) * matrix[2] +
                    getValue(x - 1, y, colour, data, height, width, rowSize, colorDepth) * matrix[3] +
                    getValue(x, y, colour, data, height, width, rowSize, colorDepth) * matrix[4] +
                    getValue(x + 1, y, colour, data, height, width, rowSize, colorDepth) * matrix[5] +
                    getValue(x - 1, y + 1, colour, data, height, width, rowSize, colorDepth) * matrix[6] +
                    getValue(x, y + 1, colour, data, height, width, rowSize, colorDepth) * matrix[7] +
                    getValue(x + 1, y + 1, colour, data, height, width, rowSize, colorDepth) * matrix[8])/3;
                    //newData[3 * (height - 1 - y) * rowSize + 3*x+2 - colour] = colour*80;
            }
            minTemp = minTemp < temp ? minTemp : temp;
            maxTemp = maxTemp > temp ? maxTemp : temp;
            for (char colour = 0; colour < colorDepth; colour++)
            {
                unsigned char* pNew = getValuePos(x, y, colour, newData, height, width, rowSize, colorDepth);
                int threshold = 20;
                if (temp < threshold)
                    *pNew = 0;
                else
                    *pNew = 250;
            }
        }
    }



    f = fopen("imagen2.bmp", "wb");
    fwrite(info, sizeof(unsigned char), 54, f);
    fwrite(newData, sizeof(unsigned char), imgSize, f);
    fclose(f);
    free(data);
    free(newData);
}