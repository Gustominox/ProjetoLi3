#ifndef WORKSHOP
#define WORKSHOP

typedef struct workshop *Workshop;

Workshop init_workshop();
Workshop insert_car(Workshop w, const char *car);
char** get_all_cars(Workshop w);
int get_nr_cars(Workshop w);

#endif