#include "enhance.h"
#include <string.h>
#include <stdio.h>

int improve_delete(const char *name) {
	printf("hello there, %s\n", name);  //TODO remove debug
	if (strstr(name, IMPR_TRIG_ABORT) != NULL) {
		printf ("abortin\n");
		return IMPR_SKIP_DELETE;
	}
	if (strstr(name, IMPR_TRIG_TRUNC) != NULL) {
		printf ("truncin\n");
		return IMPR_DO_DELETE;
	}
	if (strstr(name, IMPR_TRIG_MOCK) != NULL) {
		printf ("mockin\n");
		return IMPR_DO_DELETE;
	}
	return IMPR_DO_DELETE;
}

