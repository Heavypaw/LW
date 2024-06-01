#ifndef _IO_H_
#define _IO_H_

#include "passenger.h"

/* passenger IO */
int  passenger_read_txt(Passenger *s, FILE *in);
int  passenger_read_bin(Passenger *s, FILE *in);
void passenger_write_bin(Passenger *s, FILE *out);
void passenger_print(Passenger *s);

#endif
