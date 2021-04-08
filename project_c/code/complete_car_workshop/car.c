#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "car.h"

struct car {
  char *plate;
  int horse_power;
};

Car init_car(const char *str) {
  char *aux = strdup(str);
  Car c = (Car) malloc(sizeof(struct car));
  c->plate = strdup(strtok(aux, ":\n"));
  c->horse_power = atoi(strtok(NULL, ":\n"));
  return c;
}

char* get_plate(Car c) {
  return strdup(c->plate);
}

int get_horse_power(Car c){
  return c->horse_power;
}

char* get_car_info(Car c) {
  char *plate_info = "Plate: ";
  char *horse_power_info = "Horse power: ";
  char *splitter = "; ";
  char hp[10];
  sprintf(hp, "%d", c->horse_power);
  char *car_info = (char*) malloc(strlen(plate_info)
                                  + strlen(c->plate)
                                  + strlen(splitter)
                                  + strlen(horse_power_info)
                                  + strlen(hp) + 1);
  strcpy(car_info, plate_info);
  strcat(car_info, c->plate);
  strcat(car_info, splitter);
  strcat(car_info, horse_power_info);
  strcat(car_info, hp);
  return car_info;
}
