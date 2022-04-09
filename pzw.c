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

    //get current width and calculate final width, 
    //and print through the input toward byte 18
    //NOTE: This and height are copied from pz3, do function?
    fprintf(stderr, "Attempting to get width and height...\n");
    unsigned char width_arr[2];
    width_arr[0] = c;
    c = getc(stdin);
    width_arr[1] = c;
    unsigned int width = (width_arr[0] << 8) | width_arr[1];
    fprintf(stderr, "width = %d\n", width);
    //calc new width
    unsigned int out_width = width * 2;
    //print to stdout
    char w1 = ((out_width >> 8) & 255);
    char w2 = (out_width & 255);
    putc(w1, stdout);
    putc(w2, stdout);

    //get height, DO NOT DOUBLE
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

    //check the greyscale bit and store in a variable
    int gray_q;
    if ((c & 2) != 0) {gray_q=1;}
    else {gray_q=0;}
    
    //print to end of string description
    while (c != '\0')
    {
        putc(c, stdout);
        c = getc(stdin);
    }
    //move past sentinel and to start of image data
    putc(c, stdout);
    c = getc(stdin);

    //navigate to the RGB triples as the
    //number of runs doesn't actually change here
    //following code copied from pz3 line ~70
    fprintf(stderr, "Moving through number of runs...\n");
    unsigned char num_runs_arr[4];
    for (int i = 0; i < 4; i++)
    {
        putc(c, stdout); //we print to stdout as is
        num_runs_arr[i] = c;
        c = getc(stdin);
    }
    unsigned int num_runs = (((num_runs_arr[0] << 24) | (num_runs_arr[1] << 16)) | 
                     (num_runs_arr[2] << 8)) | num_runs_arr[3];

    //build initial run lengths array
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

    //we now double every value in this array
    for (int i = 0; i < num_runs; i++)
    {
        run_vals[i] = run_vals[i] * 2;
    }

    //and print them all to stdout
    for (int i = 0; i < num_runs; i++)
    {
        char rl1 = ((run_vals[i] >> 24) & 255);
        char rl2 = ((run_vals[i] >> 16) & 255);
        char rl3 = ((run_vals[i] >> 8) & 255);
        char rl4 = (run_vals[i] & 255);
        putc(rl1, stdout);
        putc(rl2, stdout);
        putc(rl3, stdout);
        putc(rl4, stdout);
    }

    //since rgb's don't change, we print the rest of the file as is
    while (c != EOF)
    {
        putc(c, stdout);
        c = getc(stdin);
    }
}
