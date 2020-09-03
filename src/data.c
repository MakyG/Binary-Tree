/*
 * data.c
 *
 *  Created on: 9. 3. 2015
 *      Author: dulik
 */

#include "data.h"
#include <stdio.h>
#include <string.h>
#include "ioutils.h"

int Data_Cmp(const Data_t *d1, const Data_t *d2) {
  return strcmp(d1->name, d2->name);
}

bool Data_Get(Data_t *data) {
  int eoln_pos = 0;
  printf("Please, enter a name: ");

  if (!io_utils_get_string(data->name, 255)) {
    return false;
  }

  eoln_pos = strcspn(data->name, "\n\r"); /* Najdi pozici konce radku */
  data->name[eoln_pos] = 0;               /* a "ustrihni" konec radku */
  printf("Enter age, weight and height (separated by Enter):\n");

  if (!io_utils_get_double(&data->age)) {
    return false;
  }

  if (!io_utils_get_double(&data->weight)) {
    return false;
  }

  if (!io_utils_get_double(&data->height)) {
    return false;
  }

  return true;
}

void Data_Print(Data_t *data) {
  printf("Name=%s, age=%0.1lf, weight=%0.1lf, height=%0.1lf\n", data->name,
         data->age, data->weight, data->height);
}
