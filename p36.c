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
  mag_num[1] = '6';
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

  //we loop scanf and assign r g b values
  unsigned char r;
  unsigned char g;
  unsigned char b;
  while (scanf("%hhu %hhu %hhu", &r, &g, &b) != EOF)
  {
      putc(r, stdout);
      putc(g, stdout);
      putc(b, stdout);
  }
  return 0;
}
