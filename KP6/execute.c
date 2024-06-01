#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "passenger.h"

void print_special(FILE *in) {
    Passenger s;
    Passenger maxPassenger;
    int maxBaggageCount = 0;
    float maxBaggageWeight = 0.0;
    int maxCount = 0;

    while (passenger_read_bin(&s, in)) {
        if (s.baggageCount > maxBaggageCount && s.totalBaggageWeight > maxBaggageWeight) {
            maxBaggageCount = s.baggageCount;
            maxBaggageWeight = s.totalBaggageWeight;
            maxPassenger = s;
            maxCount = 1;
        } else if (s.baggageCount == maxBaggageCount || s.totalBaggageWeight == maxBaggageWeight) {
            maxCount++;
        }
    }

    if (maxCount == 1) {
        printf("Passenger with the most baggage (both in count and weight):\n");
        passenger_print(&maxPassenger);
    } else {
        printf("No single passenger with the most baggage (both in count and weight).\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    print_special(in);

    fclose(in);

    return 0;
}
