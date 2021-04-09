#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

int isUpper(char let){
    if (let < 'A' && let > 'Z')
      return 0;
    else return 1;
}
int isDigit(char dig){
    if (dig < '0' && dig > '9')
      return 0;
    else return 1;
}
