#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[])
{
  //prints first four bytes since they are static, traverses p3 file to 2nd line
  int c = getc(stdin);
  char rfe = '.'; //this is our "reserved for future expansion" character
  printf("%c%c%c%c", 'P', 'Z', rfe, rfe);
  for (int i = 0; i < 2; i++) {c = getc(stdin);}

  //build int representation of time and print
  time_t t = time(NULL);
  struct tm c_time = *localtime(&t);
  int c_hour = c_time.tm_hour * 100;
  int c_min = c_time.tm_min;
  int output_time = c_hour + c_min;
  char ot1 = ((output_time >> 8) & 255);
  char ot2 = (output_time & 255);
  putc(ot1, stdout);
  putc(ot2, stdout);

  //build int representation of date and print
  int c_year = (c_time.tm_year + 1900) * 10000;
  int c_month = (c_time.tm_mon + 1) * 100;
  int c_day = c_time.tm_mday;
  int output_date = c_year + c_month + c_day;
  char od1 = ((output_date >> 24) & 255);
  char od2 = ((output_date >> 16) & 255);
  char od3 = ((output_date >> 8) & 255);
  char od4 = (output_date & 255);
  putc(od1, stdout);
  putc(od2, stdout);
  putc(od3, stdout);
  putc(od4, stdout);

  //get width and putc the resulting int
  unsigned char width_arr[6];
  for (int i = 0; i < 6; i++)
  {
    if (c == ' ') {break;}
    width_arr[i] = c;
    c = getc(stdin);
  }
  unsigned int width = atoi(width_arr);
  char w1 = ((width >> 8) & 255);
  char w2 = (width & 255);
  putc(w1, stdout);
  putc(w2, stdout);

  //repeat for height
  c = getc(stdin);
  unsigned char height_arr[6];
  char debug_char;
  for (int i = 0; i < 6; i++)
  {
    if (c == 10) {break;}
    height_arr[i] = c;
    debug_char = c;
    c = getc(stdin);
  }
  unsigned int height = atoi(height_arr);
  char h1 = ((height >> 8) & 255);
  char h2 = (height & 255);
  putc(h1, stdout);
  putc(h2, stdout);

  //print RFE bytes until byte 18
  for (int i = 0; i < 4; i++) {putc(rfe, stdout);}
  for (int i = 0; i < 4; i++) {c = getc(stdin);}
  //debug check
  fprintf(stderr, "after wxh, current char: %c\n", c);

  //build rgb array for use later
  struct rgb rgbs[width * height];
  for (int i = 0; i < width * height; i++)
  {
      scanf("%d", &rgbs[i].r);
      scanf("%d", &rgbs[i].g);
      scanf("%d", &rgbs[i].b);
  }

  //build image from this
  struct image p3_img = {width, height, rgbs};

  //We can now write byte 18:
  int gray = 3;
  int not_gray = 1;
  int is_grayscale = img_grayscale(&p3_img);
  if (is_grayscale != 0) {putc(gray, stdout);}
  else {putc(not_gray, stdout);}

  //print RFE bytes until byte 22
  for (int i = 0; i < 3; i++) {putc(rfe, stdout);}

  //cases for string
  if (argc > 1) 
  {
    printf("%s", argv[1]);
    putc('\0', stdout);
  }
  else 
  {
    putc('\0', stdout);
  }

  //calculate and print the number of runs
  int num_of_runs = 0;
  for (int i = 0; i < (width * height) - 1; i++)
  {
      if (rgb_eq(rgbs[i], rgbs[i+1]) == 0) {num_of_runs++;}
  }
  char nor1 = ((num_of_runs >> 24) & 255);
  char nor2 = ((num_of_runs >> 16) & 255);
  char nor3 = ((num_of_runs >> 8) & 255);
  char nor4 = (num_of_runs & 255);
  putc(nor1, stdout);
  putc(nor2, stdout);
  putc(nor3, stdout);
  putc(nor4, stdout);
  
  //traverse rgbs, when we find a change in pixel value we print
  //the current run_length, then begin again
  int run_length = 1;
  for (int i = 0; i < (width * height) -1; i++)
  {
      if (rgb_eq(rgbs[i], rgbs[i+1]) != 0) {run_length++;}
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

  //we begin cases for if image is greyscale
  if (is_grayscale != 0)
  {
      //first value is always printed
      putc(rgbs[0].r, stdout);
      for (int i = 0; i < (width * height) - 1; i++)
      {
        if (rgb_eq(rgbs[i], rgbs[i+1]) == 0)
        {
            putc(rgbs[i+1].r, stdout);
        }
      }
  }
  
  else
  {
    //first rgb alwyas printed
    putc(rgbs[0].r, stdout);
    putc(rgbs[0].g, stdout);
    putc(rgbs[0].b, stdout);
    for (int i = 0; i < (width * height) - 1; i++)
    {
        if (rgb_eq(rgbs[i], rgbs[i+1]) == 0)
        {
            putc(rgbs[i+1].r, stdout);
            putc(rgbs[i+1].g, stdout);
            putc(rgbs[i+1].b, stdout);
        }
    }
  }
 return 0;
}
