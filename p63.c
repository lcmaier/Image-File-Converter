#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project1.h"

int main(int argc, char *argv[])
{
  //scans first line, changes magic number to target
  char mag_num[2];
  scanf("%s", mag_num);
  mag_num[1] = '3';
  printf("%s\n", mag_num);

  //scans second line, prints as is
  char width[6];
  char height[6];
  scanf("%s", width);
  scanf("%s", height);
  printf("%s %s\n", width, height);

  //since max color is always 255, we just print 255
  char max_color[3];
  scanf("%s", max_color);
  printf("%s\n", max_color);


  int c = getc(stdin);
  c = getc(stdin);  
  //we move character by character and extract the int, then print to stdout
  while (c != EOF)
  {
    printf("%d ", c);
    c = getc(stdin);
  }
  return 0;
}
