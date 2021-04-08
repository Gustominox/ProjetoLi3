#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char buffer[64];
  char* workshop[100];
  int nr_of_cars = 0;

  FILE* f = fopen("input_files/cars.txt", "r");
  if(f == NULL){ 
    printf("Error opening file\n");
    return 1;
  }

  while(fgets(buffer, 64, f)){
    workshop[nr_of_cars] = strdup(strtok(buffer, "\n"));
    nr_of_cars++;
  }

  for(int i = 0; i < nr_of_cars; i++){
    printf("car info: %s\n", workshop[i]);
  }

  return 0;
}