#include "car.h"
#include "workshop.h"
#include <string.h>
#include <stdlib.h>

struct workshop
{
  Car workshop[100];
  int nr_of_cars;
};

Workshop init_workshop() {
  Workshop w = (Workshop) malloc(sizeof(struct workshop));
  w->nr_of_cars = 0;
  return w;
}

Workshop insert_car(Workshop w, Car car) {
  w->workshop[w->nr_of_cars] = car;
  (w->nr_of_cars)++;
  return w;
}

// Esta função tem um problema. Qual será?
Car* get_all_cars(Workshop w) {
  Car *res = (Car*) malloc(((w->nr_of_cars)+1) * sizeof(Car));
  for(int i = 0; i < w->nr_of_cars; i++){
    res[i] = w->workshop[i];
  }
  return res;
}

int get_nr_cars(Workshop w) {
  return w->nr_of_cars;
}
