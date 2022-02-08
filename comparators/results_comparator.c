#include <string.h>
#include "results_comparator.h"
#include "../models/player_results.h"

int resultsComparator(const void *p, const void *q) {
	return strcmp( ((PlayerResults*)p)->username,
				((PlayerResults*)q)->username);
}
