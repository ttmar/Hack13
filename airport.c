/**
Author: Victor Nguyen, Collin Sipple
My NU ID: 02357235
CLASS: 155E
Section 250
Date Started: 11/15/2018
Date Finished: 11/16/2018
 *
 */
/**
 * A program that represents and edit the letter of a given quotes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "airport.h"

Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv){
if(type == NULL || name == NULL || city == NULL || countryAbbrv == NULL){
return NULL;
}
Airport *airport = (Airport *) malloc(sizeof(Airport) * 1);
initAirport(airport, gpsId, type, name, latitude, longitude, elevationFeet, city, countryAbbrv);
return airport;
}

void initAirport(Airport* airport,
                      const char* gpsId,
                      const char* type,
                      const char* name,
                      double latitude,
                      double longitude,
                      int elevationFeet,
                      const char* city,
                      const char* countryAbbrv){
if(type == NULL || name == NULL || city == NULL || countryAbbrv == NULL){
  return;
}
airport->gpsId = (char*) malloc(sizeof(char) * (strlen(gpsId) +1));
strcpy(airport->gpsId, gpsId);
airport->type = (char*) malloc(sizeof(char) * (strlen(type) +1));
strcpy(airport->type, type);
airport->name = (char*) malloc(sizeof(char) * (strlen(name) +1));
strcpy(airport->name, name);
airport->latitude = latitude;
airport->longitude = longitude;
airport->elevationFeet = elevationFeet;
if( latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
return;
}
airport->city = (char*) malloc(sizeof(char) * (strlen(city) +1));
strcpy(airport->city, city);
airport->countryAbbrv = (char*) malloc(sizeof(char) * (strlen(countryAbbrv) +1));
strcpy(airport->countryAbbrv, countryAbbrv);
return;

}

char* airportToString(const Airport* a){
  if (a == NULL) {
  char *result1 = (char *)malloc(sizeof(char) * 7);
  strcpy(result1, "(null)");
  return result1;
  }

  // compute the number of characters we'll need:
  int n = strlen(a->gpsId) + strlen(a->type) + strlen(a->name) + sizeof(double) + sizeof(double) + sizeof(int) + strlen(a->city) + strlen(a->countryAbbrv);

  // create a result string
  char *str = (char *)malloc(sizeof(char) * (n+15));

  // format the student into the temporary string
  sprintf(str, "%s, %s, %s, %f, %f, %d, %s, %s", a->gpsId,
  a->type, a->name, a->latitude,
  a->longitude, a->elevationFeet, a->city, a->countryAbbrv);

  // return the result
  return str;

}


double getAirDistance(const Airport* origin, const Airport* destination){
int R = 6371;
double lat1Rad = ((origin->latitude) / 180) * M_PI;
double long1Rad = ((origin->longitude) / 180) * M_PI;
double lat2Rad = ((destination->latitude) / 180) * M_PI;
double long2Rad = ((destination->longitude) / 180) * M_PI;
double difference = (long2Rad - long1Rad);
double answer = (acos(((sin(lat1Rad)) * sin(lat2Rad)) + (cos(lat1Rad) * cos(lat2Rad) * cos(difference))) * R);
return answer;
}

double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs){
if(stops == NULL){
  return 1;
}
double totalDistance = 0;
for(int i = 1; i < size; i++){
totalDistance += getAirDistance(&stops[i - 1], &stops[i]);
}
double travelTime = totalDistance / aveKmsPerHour;
double totalTime = travelTime + (aveLayoverTimeHrs * (size - 2));

return totalTime;
}

int cmpByGPSId(const void* a, const void* b){
const Airport *x = (const Airport *) a;
const Airport *y = (const Airport *) b;
if((x->gpsId) < (y->gpsId)){
  return -1;
}else if((x->gpsId) > (y->gpsId)){
  return 1;
}else{
  return 0;
  }
}

/**
 * A comparator function that orders the two Airport structures by
 * their type.
 */
int cmpByType(const void* a, const void* b){
  const Airport *x = (const Airport *) a;
  const Airport *y = (const Airport *) b;
  return strcmp(x->type, y->type);
}

/**
 * A comparator function that orders the two Airport structures by
 * their name in lexicographic order.
 */
int cmpByName(const void* a, const void* b){
  const Airport *x = (const Airport *) a;
  const Airport *y = (const Airport *) b;
  return strcmp(x->type, y->type);
}

/**
 * A comparator function that orders the two Airport structures by
 * their name in reverse lexicographic order.
 */
int cmpByNameDesc(const void* a, const void* b){
  const Airport *x = (const Airport *) a;
  const Airport *y = (const Airport *) b;
  return strcmp(y->type, x->type);
}

/**
 * A comparator function that orders the two Airport structures first by
 * country, then by city
 */
int cmpByCountryCity(const void* a, const void* b){
  const Airport *x = (const Airport *) a;
  const Airport *y = (const Airport *) b;
  return -(strcmp(x->city, y->city));
}

/**
 * A comparator function that orders the given Airport structures
 * by their latitudes north to south
 */
int cmpByLatitude(const void* a, const void* b){

  const Airport *x = (const Airport *) a;
  const Airport *y = (const Airport *) b;
  if((x->latitude) < (y->latitude)){
    return -1;
  }else if((x->latitude) > (y->latitude)){
    return 1;
  }else{
    return 0;
    }
}

/**
 * A comparator function that orders the given Airport structures
 * by their longitudes west to east
 */
int cmpByLongitude(const void* a, const void* b){

  const Airport *x = (const Airport *) a;
  const Airport *y = (const Airport *) b;
  if((x->longitude) < (y->longitude)){
    return -1;
  }else if((x->longitude) > (y->longitude)){
    return 1;
  }else{
    return 0;
    }
}

/**
 * A comparator function that orders the two Airport structures by
 * their relative distance from Lincoln Municipal Airport
 * (0R2, 40.846176, -96.75471)
 * in ascending order according (closest to Lincoln would come first)
 */
int cmpByLincolnDistance(const void* a, const void* b){
const Airport *x = (const Airport *) a;
const Airport *y = (const Airport *) b;
Airport* LincolnAir = createAirport("LNK", "sml", "Lincoln Airport", 40.846176, -96.75471, 1219, "Lincoln, Nebraska", "USA");
double port1 = getAirDistance(LincolnAir, x);
double port2 = getAirDistance(LincolnAir, y);
if(port1 < port2){
  return -1;
}else if(port1 > port2){
  return 1;
}else{
  return 0;
  }
return 0;
}

void printAirport(const Airport *airports) {
  if (airports == NULL) {
    printf("null\n");
    return;
  }
  printf("%s, %s, %s, %f, %f, %d, %s, %s\n", airports->gpsId, airports->type,
         airports->name, airports->latitude, airports->longitude, airports->elevationFeet, airports->city, airports->countryAbbrv);
}

void printAllAirports(Airport *airports, int size) {
  int i;
  for (i = 0; i < size; i++) {
    printAirport(&airports[i]);
  }
}
/**
 * A function that generates and prints several reports on the
 * given array of Airport structures.
 */
void generateReports(Airport *airports, int n){
  printf("============================================================\n");
  printf("Airport, original order:\n");
	printAllAirports(airports, n);
  printf("\n");
    printf("============================================================\n");
	printf("Sorted by gps id in ascending: \n");
	qsort(airports, n, sizeof(Airport), cmpByGPSId);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by type in ascending: \n");
	qsort(airports, n, sizeof(Airport), cmpByType);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by name in ascending: \n");
	qsort(airports, n, sizeof(Airport), cmpByName);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by name in descending: \n");
	qsort(airports, n, sizeof(Airport), cmpByNameDesc);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by country and city in ascending: \n");
	qsort(airports, n, sizeof(Airport), cmpByCountryCity);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by latitude in ascending: \n");
	qsort(airports, n, sizeof(Airport), cmpByLatitude);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by longitude in ascending: \n");
	qsort(airports, n, sizeof(Airport), cmpByLongitude);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("Sorted by distance to lincoln in asending: \n");
	qsort(airports, n, sizeof(Airport), cmpByLincolnDistance);
	printAllAirports(airports, n);
  printf("\n");
  printf("============================================================\n");
	printf("This is the closest airport to lincoln: \n");
	qsort(airports, n, sizeof(Airport), cmpByLincolnDistance);
	printAllAirports(airports, 1);
  printf("\n");
  printf("============================================================\n");
	printf("This is the airport that is the geographic west-east median of the given airports: \n");
	qsort(airports , n, sizeof(Airport), cmpByLongitude);
	printAllAirports(airports, ceil(0.5 * n));
  printf("\n");
	printf("Testing\n");
	qsort(airports, n, sizeof(Airport), cmpByCountryCity);
	int i;
	for(i = 0; i < n; i++) {
		if(strcmp(airports->city, "New York") == 0) {
			printAirport(&airports[i]);
			break;
		}else if(i == (n - 1)) {
			printf("Airport not found \n");
		}
	}

	printf("Testing\n");
	qsort(airports, n, sizeof(Airport), cmpByCountryCity);
	for(i = 0; i < n; i++) {
		if(strcmp(airports->countryAbbrv, "CA-QC") == 0) {
			printAirport(&airports[i]);
			break;
		}else if(i == (n - 1)) {
			printf("Airport not found \n");
		}
	}


	printf("Testing\n");
	qsort(airports, n, sizeof(Airport), cmpByType);
	for(i = 0; i < n; i++) {
		if(strcmp(airports->type, "large_airport") == 0) {
			printAirport(&airports[i]);
			break;
		}else if(i == (n - 1)) {
			printf("Airport not found \n");
		}
	}
}
