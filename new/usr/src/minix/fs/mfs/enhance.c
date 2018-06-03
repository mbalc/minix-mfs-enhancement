#include "fs.h"
#include <minix/vfsif.h>
#include "enhance.h"
#include "inode.h"
#include <string.h>
#include <stdio.h>

int handle_trunc(struct inode *rip) {
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

int handle_mock(struct inode *dirp, const char *name, struct inode *rip) {
	printf ("mockin\n");
	char mock_name[MFS_NAME_MAX];
	strcpy(mock_name, name);
	mock_name[0] = '_';
	struct inode *new_file = new_node(dirp, mock_name, rip->i_mode, rip->i_zone[0]);
	if (new_file == NULL) {
		return IMPR_THROW_ERR;
	}
	put_inode(new_file);
	return IMPR_DO_DELETE;
}

int improve_delete(struct inode *dirp, const char *name, struct inode *rip) {
	if (rip->i_mode & I_DIRECTORY) return IMPR_DO_DELETE;
	printf("hello there, %s\n", name);  //TODO remove debug
	if (strstr(name, IMPR_TRIG_ABORT) != NULL) {
		printf ("abortin\n");
		return IMPR_SKIP_DELETE;
	}
	if (strstr(name, IMPR_TRIG_TRUNC) != NULL) {
		return handle_trunc(rip);
	}
	if (strstr(name, IMPR_TRIG_MOCK) != NULL) {
		handle_mock(dirp, name, rip);
	}
	return IMPR_DO_DELETE;
}

