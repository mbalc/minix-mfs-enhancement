#ifndef __MFS_ENHANCE_H__
#define __MFS_ENHANCE_H__

#include "fs.h"
#include "inode.h"
#include <minix/vfsif.h>

//TODO will need some include here

#define IMPR_DO_DELETE		42
#define IMPR_THROW_ERR	 	66
#define IMPR_SKIP_DELETE 	7

#define IMPR_TRUNC_THRESHOLD(rip)	rip->i_sp->s_block_size
//TODO find block size and use it instead of a hardcoded value

#define IMPR_TRIG_ABORT		"haha"
#define IMPR_TRIG_TRUNC		"hehe"
#define IMPR_TRIG_MOCK		"hihi"

int improve_delete(struct inode *dirp, const char *name, struct inode *rip);

#endif //__MFS_ENHANCE_H__

