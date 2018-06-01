#include "fs.h"
#include <minix/vfsif.h>
#include "enhance.h"
#include "inode.h"
#include <string.h>
#include <stdio.h>

int improve_delete(const char *name, struct inode *rip) {
	printf("hello there, %s\n", name);  //TODO remove debug
	if (strstr(name, IMPR_TRIG_ABORT) != NULL) {
		printf ("abortin\n");
		return IMPR_SKIP_DELETE;
	}
	if (strstr(name, IMPR_TRIG_TRUNC) != NULL) {
		unsigned short threshold = IMPR_TRUNC_THRESHOLD(rip);
		if (rip->i_size <= threshold) {
			printf ("avoidin\n");
			return IMPR_DO_DELETE;
		}
		printf ("truncin\n");
		u32_t old_ctime = rip->i_ctime;
		truncate_inode(rip, threshold);
		rip->i_ctime = old_ctime;
		return IMPR_SKIP_DELETE;
	}
	if (strstr(name, IMPR_TRIG_MOCK) != NULL) {
		printf ("mockin\n");
		return IMPR_DO_DELETE;
	}
	return IMPR_DO_DELETE;
}

