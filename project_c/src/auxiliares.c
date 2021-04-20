#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

int isFloat (const char *s){
  char *str = NULL;
  double flt = strtod (s, &str);
  if (!str  ||  *str)
      return 0;  // has non-floating digits after number, if any
  return 1;
}

int isInteger (const char *s){
  while(*s){
    if(!isDigit(*s)) return 0;   
    s++;
  }
  return 1;
}