#include "workshop.h"
#include <string.h>
#include <stdlib.h>

struct workshop
{
  char* workshop[100];
  int nr_of_cars;
};

Workshop init_workshop() {
  Workshop w = (Workshop) malloc(sizeof(struct workshop));
  w->nr_of_cars = 0;
  return w;
}

Workshop insert_car(Workshop w, const char *car) {
  w->workshop[w->nr_of_cars] = strdup(car);
  (w->nr_of_cars)++;
  return w;
}

char** get_all_cars(Workshop w) {
  char **res = (char**) malloc(((w->nr_of_cars)+1) * sizeof(char*));
  for(int i = 0; i < w->nr_of_cars; i++){
    res[i] = strdup(w->workshop[i]);
  }
  return res;
}

int get_nr_cars(Workshop w) {
  return w->nr_of_cars;
}
