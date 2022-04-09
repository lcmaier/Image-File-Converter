#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[])
{
    //get input
    int c = getc(stdin);

    //print static first four bytes
    fprintf(stderr, "Attempting to print first four bytes...\n");
    printf("PZ..");

    //loop through byte 9
    for (int i = 0; i < 10; i++) {c = getc(stdin);}

    //build int representation of time and print
    //NOTE: This and date are copied from p3z, do function?
    fprintf(stderr, "Building time and date ints...\n");
    time_t t = time(NULL);
    struct tm c_time = *localtime(&t);
    int c_hour = c_time.tm_hour * 100;
    int c_min = c_time.tm_min;
    int output_time = c_hour + c_min;
    fprintf(stderr, "output_time = %d\n", output_time);
    char ot1 = ((output_time >> 8) & 255);
    char ot2 = (output_time & 255);
    putc(ot1, stdout);
    putc(ot2, stdout);

    //build int representation of date and print
    int c_year = (c_time.tm_year + 1900) * 10000;
    int c_month = (c_time.tm_mon + 1) * 100;
    int c_day = c_time.tm_mday;
    int output_date = c_year + c_month + c_day;
    fprintf(stderr, "output_date = %d\n", output_date);
    char od1 = ((output_date >> 24) & 255);
    char od2 = ((output_date >> 16) & 255);
    char od3 = ((output_date >> 8) & 255);
    char od4 = (output_date & 255);
    putc(od1, stdout);
    putc(od2, stdout);
    putc(od3, stdout);
    putc(od4, stdout);

    //get width for later use, and print through the input toward byte 18
    //NOTE: This and height are copied from pz3, do function?
    fprintf(stderr, "Attempting to get width and height...\n");
    unsigned char width_arr[2];
    //c = getc(stdin);
    putc(c, stdout);
    width_arr[0] = c;
    c = getc(stdin);
    putc(c, stdout);
    width_arr[1] = c;
    unsigned int width = (width_arr[0] << 8) | width_arr[1];
    fprintf(stderr, "width = %d\n", width);


    //repeat for height
    unsigned char height_arr[2];
    c = getc(stdin);
    putc(c, stdout);
    height_arr[0] = c;
    c = getc(stdin);
    putc(c, stdout);
    height_arr[1]=c;
    unsigned int height = (height_arr[0] << 8) | height_arr[1];
    fprintf(stderr, "height = %d\n", height);


    c = getc(stdin);
    //print stdin until byte 18
    for (int i = 0; i < 4; i++)
    {
        putc(c, stdout);
        c = getc(stdin);
    }

    //set the grayscale bit to 1 and print to the end of the string
    putc(3, stdout);
    c = getc(stdin);
    while (c != '\0') 
    {
        putc(c, stdout);
        c = getc(stdin);
    }
    putc(c, stdout);

    //put the rest of the file in an image struct with our helper
    fprintf(stderr, "Attempting to build image struct...\n");
    struct image im1 = pz_im(width, height);
    fprintf(stderr, "Done.\n");

    //grayscale all pixels
    for (int i = 0; i < width * height; i++)
    {
        int g_scale = luminance(im1.pixels[i]);
        im1.pixels[i].r = g_scale;
        im1.pixels[i].g = g_scale;
        im1.pixels[i].b = g_scale;
    }

    //calculate and print new number of runs
    //NOTE: code copied from p3z line ~112, make function?
    int num_of_runs = 0;
    fprintf(stderr, "Attempting to get new number of runs...\n");
    for (int i = 0; i < (width * height); i++)
    {
       if (rgb_eq(im1.pixels[i], im1.pixels[i+1]) == 0) {num_of_runs++;}
    }
    fprintf(stderr, "number of runs = %d\n", num_of_runs);
    char nor1 = ((num_of_runs >> 24) & 255);
    char nor2 = ((num_of_runs >> 16) & 255);
    char nor3 = ((num_of_runs >> 8) & 255);
    char nor4 = (num_of_runs & 255);
    putc(nor1, stdout);
    putc(nor2, stdout);
    putc(nor3, stdout);
    putc(nor4, stdout);

    //calculate and print new run lengths
    //NOTE: code copied from p3z line ~126, make function?
    fprintf(stderr, "Attempting to get new run lengths...\n");
    int run_length = 1;
    for (int i = 0; i < (width * height) -1; i++)
    {
      if (rgb_eq(im1.pixels[i], im1.pixels[i+1]) != 0) {run_length++;}
      else
      {
          char rl1 = ((run_length >> 24) & 255);
          char rl2 = ((run_length >> 16) & 255);
          char rl3 = ((run_length >> 8) & 255);
          char rl4 = (run_length & 255);
          putc(rl1, stdout);
          putc(rl2, stdout);
          putc(rl3, stdout);
          putc(rl4, stdout);
          run_length = 1;
      }
  }

    //calculate and print new grey pixels
    //NOTE: code copied form p3z line ~146, make function?
    fprintf(stderr, "Attempting to print new grey pixels to output...\n");
      putc(im1.pixels[0].r, stdout);
      for (int i = 0; i < (width * height) - 1; i++)
      {
        if (rgb_eq(im1.pixels[i], im1.pixels[i+1]) == 0)
        {
            putc(im1.pixels[i+1].r, stdout);
        }
      }
    //free pixels
    free(im1.pixels); 
    return 0;
}
