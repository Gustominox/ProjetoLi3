#include <stdio.h>
#include "dados.h"


int main(){
	Business b = malloc(sizeof(struct business));
	char bid[5] = "12345";
	b->business_id = bid;
	printf("OLA PESSOAS, %s", b->business_id);
}
