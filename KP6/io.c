#include <stdio.h>
#include <stdlib.h>

#include "passenger.h"
#include <string.h>

int passenger_read_txt(Passenger *s, FILE *in) {
    char transferStr[4] = {0}; // Initialize to zeros
    fscanf(in, "%s", s->surname);
    fscanf(in, "%s", s->initials);
    fscanf(in, "%d", &(s->baggageCount));
    fscanf(in, "%f", &(s->totalBaggageWeight));
    fscanf(in, "%s", s->destination);
    fscanf(in, "%s", s->departureTime);
    fscanf(in, "%3s", transferStr); // Read at most 3 characters
    s->transfer = (strcmp(transferStr, "YES") == 0) ? YES : NO;
    fscanf(in, "%d", &(s->childCount));

    return !feof(in);
}

int passenger_read_bin(Passenger *s, FILE *in)
{
    fread(s->surname, sizeof(char), STR_SIZE, in);
    fread(s->initials, sizeof(char), STR_SIZE, in);
    fread(&(s->baggageCount), sizeof(int), 1, in);
    fread(&(s->totalBaggageWeight), sizeof(float), 1, in);
    fread(s->destination, sizeof(char), STR_SIZE, in);
    fread(s->departureTime, sizeof(char), STR_SIZE, in);
    fread(&(s->transfer), sizeof(TransferType), 1, in);
    fread(&(s->childCount), sizeof(int), 1, in);

    return !feof(in);
}

void passenger_write_bin(Passenger *s, FILE *out)
{
    fwrite(s->surname, sizeof(char), STR_SIZE, out);
    fwrite(s->initials, sizeof(char), STR_SIZE, out);
    fwrite(&(s->baggageCount), sizeof(int), 1, out);
    fwrite(&(s->totalBaggageWeight), sizeof(float), 1, out);
    fwrite(s->destination, sizeof(char), STR_SIZE, out);
    fwrite(s->departureTime, sizeof(char), STR_SIZE, out);
    fwrite(&(s->transfer), sizeof(TransferType), 1, out);
    fwrite(&(s->childCount), sizeof(int), 1, out);
}

void passenger_print(Passenger *s)
{
    printf("Surname: %s\n", s->surname);
    printf("Initials: %s\n", s->initials);
    printf("Baggage Count: %d\n", s->baggageCount);
    printf("Total Baggage Weight: %.2f KG\n", s->totalBaggageWeight);
    printf("Destination: %s\n", s->destination);
    printf("Departure Time: %s\n", s->departureTime);
    printf("Transfer: %s\n", s->transfer == YES ? "YES" : "NO");
    printf("Child Count: %d\n", s->childCount);
    printf("\n");
}