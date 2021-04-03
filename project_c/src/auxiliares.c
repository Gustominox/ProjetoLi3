#include <stdio.h>
#include <stdlib.h>
#include "auxiliares.h"

int isUpper(char let){
    return (let == 'A' || let == 'B' || let == 'C' || let == 'D' || let == 'E' || let == 'F' || let == 'G' || let == 'H' || let == 'I' || let == 'J' || let == 'K' || let == 'L' || let == 'M' || let == 'N' || let == 'O' || let == 'P' || let == 'Q' || let == 'R' || let == 'S' || let == 'T' || let == 'U' || let == 'V' || let == 'W' || let == 'X' || let == 'Y' || let == 'Z');
}
int isDigit(char dig){
    return (dig == '0' || dig == '1' || dig == '2' || dig == '3' || dig == '4' || dig == '5' || dig == '6' || dig == '7' || dig == '8' || dig == '9');
}
