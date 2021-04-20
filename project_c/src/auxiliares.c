#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

int isFloat (char *s){
  char *str = NULL;
  double flt = strtod (s, &str);
  if (!str  ||  *str)
      return 0;
  return 1;
}

int isInteger (char *s){
  while(*s){
    if(!isDigit(*s)) return 0;   
    s++;
  }
  return 1;
}