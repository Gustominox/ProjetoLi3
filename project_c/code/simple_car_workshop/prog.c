#include <stdio.h>
#include <string.h>
#include "workshop.h"

int main(int argc, char const *argv[]) {
  char buffer[64];
  Workshop ws = init_workshop();

  FILE* f = fopen("input_files/cars.txt", "r");
  if(f == NULL){ 
    printf("Error opening file\n");
    return 1;
  }

  while(fgets(buffer, 64, f)){
    ws = insert_car(ws, strtok(buffer, "\n"));
  }

  char** cars = get_all_cars(ws);
  int nr_of_cars = get_nr_cars(ws);

  for(int i = 0; i < nr_of_cars; i++){
    printf("car info: %s\n", cars[i]);
  }

  return 0;
}