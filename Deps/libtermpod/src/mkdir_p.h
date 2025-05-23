#ifndef _MKDIR_P_H
#define _MKDIR_P_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <ctype.h>

/* recursive mkdir */
int mkdir_p(const char *pathname, const int mode);


/* recursive mkdirat based on openat2 */
//int mkdirat_p(int fd, const char *pathname, const mode_t mode);

#endif /* _MKDIR_P_H */
