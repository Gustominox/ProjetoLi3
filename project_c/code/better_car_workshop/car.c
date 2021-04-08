#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "car.h"

struct car {
  char *plate;
};

Car init_car(const char *str) {
  Car c = (Car) malloc(sizeof(struct car));
  c->plate = strdup(str);
  return c;
}

char* get_plate(Car c) {
  return strdup(c->plate);
}

char* get_car_info(Car c) {
  return get_plate(c);
}
