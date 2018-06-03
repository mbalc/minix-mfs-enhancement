#include "fs.h"
#include <minix/vfsif.h>
#include "enhance.h"
#include "inode.h"
#include <string.h>
#include <stdio.h>

int handle_trunc(struct inode *rip) {
	unsigned short threshold = IMPR_TRUNC_THRESHOLD(rip);
	if (rip->i_size <= threshold) {
		return IMPR_DO_DELETE;
	}
	u32_t old_ctime = rip->i_ctime;
	truncate_inode(rip, threshold);
	rip->i_ctime = old_ctime;
	return IMPR_SKIP_DELETE;
}

int handle_mock(struct inode *dirp, const char *name, struct inode *rip) {
	char mock_name[MFS_NAME_MAX];
	strcpy(mock_name, name);
	mock_name[0] = '_';
	err_code = 0;

	struct inode *new_file = new_node(dirp, mock_name, rip->i_mode, rip->i_zone[0]);
	put_inode(new_file);
	if (new_file == NULL || err_code) {
		return IMPR_THROW_ERR;
	}
	return IMPR_DO_DELETE;
}

int improve_delete(struct inode *dirp, const char *name, struct inode *rip) {
	if (rip->i_mode & I_DIRECTORY) return IMPR_DO_DELETE;
	if (strstr(name, IMPR_TRIG_ABORT) != NULL) {
		return IMPR_SKIP_DELETE;
	}
	if (strstr(name, IMPR_TRIG_TRUNC) != NULL) {
		return handle_trunc(rip);
	}
	if (strstr(name, IMPR_TRIG_MOCK) != NULL) {
		return handle_mock(dirp, name, rip);
	}
	return IMPR_DO_DELETE;
}

