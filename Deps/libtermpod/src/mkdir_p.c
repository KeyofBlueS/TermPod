#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // Add this line
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/stat.h>
#endif

#ifdef _WIN32
const char SEP = '\\';
#else
const char SEP = '/';
#endif

int mkdir_p(const char* dirname, const int mode)
{
    if (dirname == NULL) {
        return -1;
    } else if (strcmp(dirname, ".") == 0) {
        return 0;
    }
    
    char* p = strdup(dirname);
    bool ret = true;
    
#ifdef _WIN32
    /* Skip Windows drive letter. */
    if (p != NULL && strchr(dirname, ':') != NULL) {
        p++;
    }
#endif

    if (p == NULL) {
        return -1;
    }

    while ((p = strchr(p, SEP)) != NULL) {
        /* Skip empty elements. Could be a Windows UNC path or
           just multiple separators which is okay. */
        if (p != dirname && *(p - 1) == SEP) {
            p++;
            continue;
        }
        /* Put the path up to this point into a temporary to
           pass to the make directory function. */
        char* temp = strdup(dirname);
        if (temp == NULL) {
            ret = false;
            break;
        }
        temp[p - dirname] = '\0';
        p++;

#ifdef _WIN32
        if (CreateDirectory(temp, NULL) == FALSE) {
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                ret = false;
                break;
            }
        }
#else
        if (mkdir(temp, mode) != 0) {
            if (errno != EEXIST) {
                ret = false;
                break;
            }
        }
#endif
        free(temp);
    }

#ifdef _WIN32
    if (CreateDirectory(dirname, NULL) == FALSE) {
        if (GetLastError() != ERROR_ALREADY_EXISTS) {
            ret = false;
        }
    }
#else
    if (mkdir(dirname, mode) != 0) {
        if (errno != EEXIST) {
            ret = false;
        }
    }
#endif

    free(p);
    return ret ? 0 : -1;
}
