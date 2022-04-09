#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[])
{
    //print static beginning
    printf("{\n");

    printf("  \"filename\" : ");

    //return error if no filename supplied
    if (argv[1] == NULL)
    {
        fprintf(stderr, "Error: No filename supplied to pzm\n");
        exit(1);
    }

    //open given file
    FILE *fp;
    fp = fopen(argv[1], "r");

    //print the filename
    printf("\"%s\",\n", argv[1]);

    //print beginning of line 2
    printf("  \"date\" : ");

    //move through PZ input to time
    int c = getc(fp);
    for (int i = 0; i < 4; i++) {c = getc(fp);}

    unsigned char t1 = c;
    c = getc(fp); //move to 2nd byte of time
    unsigned char t2 = c;
    int time = (t1 << 8) | t2;

    //read date into an int
    c = getc(fp);
    unsigned char d1 = c;
    c = getc(fp);
    unsigned char d2 = c;
    c = getc(fp);
    unsigned char d3 = c;
    c = getc(fp);
    unsigned char d4 = c;
    int date = (((d1 << 24) | (d2 << 16)) | (d3 << 8)) | d4;

    //print the date
    printf("%d,\n", date);

    //print line 3
    printf("  \"time\" : %d,\n", time);

    printf("  \"width\" : ");

    //get width as int
    c = getc(fp);
    unsigned char w1 = c;
    c = getc(fp);
    unsigned char w2 = c;
    int width = (w1 << 8) | w2;

    printf("%d,\n", width);

    //get height as int
    c = getc(fp);
    unsigned char h1 = c;
    c = getc(fp);
    unsigned char h2 = c;
    int height = (h1 << 8) | h2;
    
    printf("  \"height\" : %d,\n", height);

    //loop to byte 18
    for (int i = 0; i < 5; i++) {c = getc(fp);}

    //check grayscale bit and store in a variable
    int grayscale;
    if ((c & 2) != 0) {grayscale = 1;}
    else {grayscale = 0;}

    //print beginning of line 7
    printf("  \"grayscale\" : ");
    //check grayscale var and write appropriate string
    if (grayscale == 1) {printf("true,\n");}
    else {printf("false,\n");}

    //print beginning of line 8
    printf("  \"rle\" : ");
    //check rle bit and write appropriate string
    if ((c & 1) != 0) {printf("true,\n");}
    else {printf("false,\n");}

    //print beginning of line 9
    printf("  \"description\" : ");
    //move fp to byte 22
    for (int i = 0; i < 4; i++) {c = getc(fp);}

    if (c == '\0')
    {
        printf("[No description provided],\n");
        c = getc(fp);
    }

    else
    {
        //print opening quote for descr
        printf("\"");

        //print the description string as characters
        while (c != '\0')
        {
            printf("%c", c);
            c = getc(fp);
        }

        //end the line and move c past sentinel character
        printf("\",\n");
        c = getc(fp);
    }

    //begin line 10
    printf("  \"runs\" : ");

    //get the number of runs as an int and print it
    //NOTE: Code copied exactly from pz3.c, consider function?
    unsigned char num_runs_arr[4];
    for (int i = 0; i < 4; i++)
    {
        num_runs_arr[i] = c;
        c = getc(fp);
    }
    unsigned int num_runs = (((num_runs_arr[0] << 24) | (num_runs_arr[1] << 16)) | 
                     (num_runs_arr[2] << 8)) | num_runs_arr[3];
    printf("%d,\n", num_runs);

    //since the number of run-bytes is always 4* the number of runs,
    //we can print all of the next line immediately
    printf("  \"run-bytes\" : %d,\n", num_runs * 4);

    //if image is grayscale, pixel-bytes = number of runs. Else,
    //it is 3 * number of runs. Print accordingly
    printf("  \"pixel-bytes\" : ");

    if (grayscale == 1) {printf("%d,\n", num_runs);}
    else {printf("%d\n", num_runs * 3);}

    //print final line
    printf("}\n");
}
