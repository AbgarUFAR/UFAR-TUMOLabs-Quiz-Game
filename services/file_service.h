#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include "../models/player_results.h"

int printQuestion(const char *FILE_NAME);

void saveResults(PlayerResults*, const char *FILE_NAME);

void emptyFile(const char *FILE_NAME);

void deleteSpecificLine(const char *FILE_NAME, const char *userName);

#endif
