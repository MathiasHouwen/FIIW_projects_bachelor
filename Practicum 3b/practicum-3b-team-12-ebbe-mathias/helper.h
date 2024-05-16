#ifndef helper_H
#define helper_H

#define NUMBERS_IN_ALPHABHET 26

#include "movieList.h"

//build index
void buildIndex(MovieNode* movieHead, MovieNode* index[NUMBERS_IN_ALPHABHET]);
//printers / extra
void printMallocErr(const char* type, const char* name);
void freeAll(MovieNode** movieHead, ActorNode** actorHead);

#endif
