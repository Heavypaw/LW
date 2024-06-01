#ifndef _PASSENGER_H_
#define _PASSENGER_H_

#define STR_SIZE 24

typedef enum { YES, NO } TransferType;

typedef struct {
    char surname[STR_SIZE];
    char initials[STR_SIZE];
    int baggageCount;
    float totalBaggageWeight; // KG
    char destination[STR_SIZE];
    char departureTime[STR_SIZE]; // Format: HH:MM
    TransferType transfer;
    int childCount;
} Passenger;

#endif