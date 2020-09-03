/*
 * data.h
 *
 *  Created on: 9. 3. 2015
 *      Author: dulik
 */

#ifndef DATA_H_
#define DATA_H_

#include <stdbool.h>

/************************************************************************/
/** \struct Data_t
 * Zde je definovan datovy typ, se kterym budeme pracovat.
 */
typedef struct {
  char name[255];             /**< jmeno cloveka */
  double age, weight, height; /**< vek, vaha, height */
} Data_t;

/************************************************************************/
/** \fn int Data_Get(Data_t* data)
 * \brief Ziska od uzivatele hodnoty pro data jednoho uzlu seznamu
 * \param data - ukazatel na strukturu data, kterou ma uzivatel naplnit
 */

int Data_Cmp(const Data_t* d1, const Data_t* d2);
bool Data_Get(Data_t* data);
void Data_Print(Data_t* data);

#endif /* DATA_H_ */
