#ifndef PRCTL_LIB_H
#define PRCTL_LIB_H

/**
 * Sets the name of the calling thread.
 *
 * @param name A string containing the new name. It should be no longer than 16 bytes,
 *             including the terminating null byte.
 * @return 0 on success, or -1 on failure with errno set appropriately.
 */
int set_process_name(const char *name);

#endif // PRCTL_LIB_H

