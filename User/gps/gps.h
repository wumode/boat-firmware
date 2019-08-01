#ifndef GPS_H
#define GPS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "minmea.h"
#include "sys.h"
#define INDENT_SPACES "  "

void AnalysisGPS(char* line);
#endif
