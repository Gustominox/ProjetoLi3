#ifndef CARRO
#define CARRO

typedef struct car *Car;

Car init_car(const char *str);
char* get_plate(Car c);
int get_horse_power(Car c);
char* get_car_info(Car c);

#endif
