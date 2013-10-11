/*
 * mocks.c
 *
 *  Created on: 10 oct. 2013
 *      Author: jean
 */

#include "mocks.h"
#include <string.h>
#include <stdlib.h>

const int FIN_STR = 1	;

char SORTIE_STDOUT[1000];

void printf(char* str) {
	strcat(SORTIE_STDOUT, str);
}
