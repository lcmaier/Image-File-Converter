#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[])
{
    //pull magic number and replace 'Z' with '3'
    fprintf(stderr, "Attempting to pull magic number...\n");
    int c = getc(stdin);
    char mag_num[2];
    mag_num[0] = c;
    c = getc(stdin);
    c = getc(stdin);
    mag_num[1] = '3';
    printf("%c%c\n", mag_num[0], mag_num[1]);
    //debug
    fprintf(stderr, "%c%c\n", mag_num[0], mag_num[1]);


    //traverse irrelevent bytes for P3
    for (int i = 0; i < 8; i++) {c = getc(stdin);}

    //store bytes 10 and 11 as a single integer and print it
    fprintf(stderr, "Attempting to grab width...\n");
    unsigned char width_arr[2];
    width_arr[0] = c;
    c = getc(stdin);
    width_arr[1] = c;
    unsigned int width = (width_arr[0] << 8) | width_arr[1];
    printf("%d ", width);
    //debug
    fprintf(stderr, "%d\n", width);

    c = getc(stdin);
    //store bytes 12 and 13 as a single integer and print it
    fprintf(stderr, "Attempting to grab height...\n");
    unsigned char height_arr[2];
    height_arr[0] = c;
    c = getc(stdin);
    height_arr[1]=c;
    unsigned int height = (height_arr[0] << 8) | height_arr[1];
    printf("%u\n", height);
    //debug
    fprintf(stderr, "%u\n", height);

    //print max color value on next line
    printf("255\n");

    //traverse more irrelevant bytes to byte 18
    for (int i = 0; i < 5; i++) {c = getc(stdin);}

    int gray_q;
    //test the 2nd from the right bit of byte 18 and set gray_q accordingly
    fprintf(stderr, "Attempting to determine grayscale...\n");
    if ((c & 0x2) == 2) {gray_q = 1;}
    else {gray_q = 0;}
    fprintf(stderr, "gray_q=%d\n", gray_q);

    //traverse irrelevant bytes to the string
    for (int i = 0; i < 4; i++) { c = getc(stdin);}
    //traverse the string
    fprintf(stderr, "Attempting to traverse string...\n");
    while (c != '\0') {c = getc(stdin);}
    c = getc(stdin);

    //get the number of runs and assign to the variable num_runs
    fprintf(stderr, "Attempting to save number of runs...\n");
    unsigned char num_runs_arr[4];
    for (int i = 0; i < 4; i++)
    {
        num_runs_arr[i] = c;
        c = getc(stdin);
    }
    unsigned int num_runs = (((num_runs_arr[0] << 24) | (num_runs_arr[1] << 16)) | 
                     (num_runs_arr[2] << 8)) | num_runs_arr[3];
    fprintf(stderr, "%d\n", num_runs);

    //define and fill an array to store the run values
    fprintf(stderr, "Attempting to build run_vals array...\n");
    int run_vals[num_runs];
    for (int i = 0; i < num_runs; i++)
    {
        char arb_run[4];
        for (int i = 0; i < 4; i++)
        {
            arb_run[i] = c;
            c = getc(stdin);
        }
        run_vals[i] = (((arb_run[0] << 24) | (arb_run[1] << 16)) | 
                         (arb_run[2] << 8)) | arb_run[3];
    }
    //debug
    fprintf(stderr, "\n");

    //split into cases for if grayscale or not
    if (gray_q == 1)
    {
        //define an array to track the grayscale intensity values
        fprintf(stderr, "Attempting to get grayscale intensities...\n");
        int g_intensity[num_runs];
        for (int i = 0; i < num_runs; i++)
        {
            g_intensity[i] = c;
            c = getc(stdin);
        }

        //we now finally print to output
        fprintf(stderr, "Attempting to print gray p3 to output...\n");
        for (int i = 0; i < num_runs; i++)
        {
            for (int j = 0; j < run_vals[i]; j++)
            {
                printf("%d %d %d ", g_intensity[i], g_intensity[i], g_intensity[i]);
            }
        }
    }

    else
    {
        //define array of rgb structs to track all triples
        fprintf(stderr, "Attempting to build rgb array...\n");
        struct rgb rgbs[num_runs + 1];
        for (int i = 0; i <= num_runs; i++)
        {
            rgbs[i].r = c;
            c = getc(stdin);
            rgbs[i].g = c;
            c = getc(stdin);
            rgbs[i].b = c;
            c = getc(stdin);
        }

        //we print to output
        fprintf(stderr, "Attempting to print to color p3 output...\n");
        for (int i = 0; i <= num_runs; i++)
        {
            for (int j = 0; j < run_vals[i]; j++)
            {
                printf("%d %d %d ", rgbs[i].r, rgbs[i].g, rgbs[i].b);
            }
        }
    }
  return 0;
}
