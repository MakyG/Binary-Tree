/**
 * \file    ioutils.c
 * \author  Tomáš Dulík
 * \date    16.2.2012
 * \brief   Miniknihovna pro načítání vstupu
 */

#include "ioutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool get_string(char *line, int len);

/**
 * @brief   Načte řetězec ze standartního vstupu o maximální délce specifikované
 * parametrem nebo dokud nenarazí na znak konce řádku (\\n). Pokud se nepodaří
 * nic načíst a funkce narazí na EOF(konec souboru), funkce zavolá exit(), který
 * ukončí vykonávání programu.
 * @param   line    Ukazatel na textové pole, kam je vstup načten.
 * @param   len     Maximální délka načteného vstupu.
 */
bool get_string(char *line, int len) {
  if (fgets(line, len, stdin) == NULL) {
    printf("End of file.\n");
    return false;
  }

  return true;
#ifdef ECHO
  printf("%s", line);
#endif
}

/**
 * @brief Read one line from stdin
 * @param[out] c
 * @param[in] maxLen
 * @return
 */
bool io_utils_get_string(char *c, int maxLen) {
  if (c == NULL) {
    return false;
  }

  return get_string(c, maxLen);
}

/**
 * @brief Načte jeden znak ze standartního vstupu.
 * @return Vrací načtený znak.
 */
bool io_utils_get_char(char *c) {
  char line[255];

  if (get_string(line, 255) == true) {
    *c = line[0];
    return true;
  }

  return false;
}

/**
 * @brief   Načte hodnotu typu long ze standartního vstupu.
 * @param   val     Ukazatel na proměnnou typu long kam je uložen načtený
 * výsledek.
 * @return
 */
bool io_utils_get_long(long *val) {
  long hodnota;
  int ok;
  char line[255];

  do {
    if (get_string(line, 255) == false) {
      return false;
    }

    ok = sscanf(line, "%ld", &hodnota);

    if (ok != 1) {
      printf("Incorrect format, try again.\n");
    }
  } while (ok != 1);

  *val = hodnota;
  return true;
}

/**
 * @brief   Načte hodnotu typu double ze standartního vstupu.
 * @param   val     Ukazatel na proměnnou typu double kam je uložen načtený
 * výsledek.
 * @return
 */
bool io_utils_get_double(double *val) {
  double hodnota;
  int ok;
  char line[255];

  do {
    if (get_string(line, 255) == false) {
      return false;
    }

    ok = sscanf(line, "%lf", &hodnota);

    if (ok != 1) {
      printf("Incorrect format, try again.\n");
    }
  } while (ok != 1);

  *val = hodnota;
  return true;
}

/**
 * @brief Vyčistí jeden řádek vstupu.
 */
void io_utils_clear_stdin() {
  while (fgetc(stdin) != '\n')
    ;
}
