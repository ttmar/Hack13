/**
Author: Victor Nguyen, Collin Sipple, Alexis Linhardt, Serigne Toure, Salman
Djingueinabaye, David Ryan
My NU ID: 02357235
CLASS: 155E
Section 250
Date Started: 11/15/2018
Date Finished: 11/16/2018
*/
/**
 *
 *A demo for airport.c file
 */

#include <stdio.h>
#include <stdlib.h>
#include "airport.h"
int main(int argc, char** argv) {
  Airport* test_1 =
      createAirport("OESB", "large_airport", "my airport", 23.514500, 34.654100,
                    1500, "my city", "SA-34");
  Airport* test_2 = createAirport("JC28", "heliport", "Air Pegasus Heliport",
                                  40.7548, 74.0071, 900, "New York", "FG-04");
  Airport* test_3 =
      createAirport("KW21", "airport", "not so cool airport", 10.514500,
                    83.973100, 550, "not so cool city", "WE-84");
  Airport* test_4 =
      createAirport("LA01", "large_airport", "UNL airport", 84.754500,
                    11.293800, 30, "UNL city", "EF-09");
  Airport* test_5 =
      createAirport("NA12", "heliport", "ungly airport", 11.923500, 41.344100,
                    0, "ugly city", "CA-UC");
  Airport* arrTest = (Airport*)malloc(sizeof(Airport) * 5);
  arrTest[0] = *test_1;
  arrTest[1] = *test_2;
  arrTest[2] = *test_3;
  arrTest[3] = *test_4;
  arrTest[4] = *test_5;
  generateReports(arrTest, 5);
  return 0;
}
