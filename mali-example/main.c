#define _GNU_SOURCE
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/prctl.h>

#include "mali.h"

#define SYSCHK(x) ({          \
  typeof(x) __res = (x);      \
  if (__res == (typeof(x))-1) \
    err(1, "SYSCHK(" #x ")"); \
  __res;                      \
})

#define KBASE_IOCTL_TYPE 0x80

#define __u8  uint8_t
#define __u16 uint16_t
#define __u32 uint32_t
#define __u64 uint64_t

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    // Open Device
    int mali_fd = SYSCHK(open("/dev/mali0", O_RDWR));

    // Check Version
    struct kbase_ioctl_version_check vc = { .major = 1, .minor = -1 };
    SYSCHK(ioctl(mali_fd, KBASE_IOCTL_VERSION_CHECK, &vc));

    // Set Flags
    struct kbase_ioctl_set_flags set_flags = { .create_flags = 0 };
    SYSCHK(ioctl(mali_fd, KBASE_IOCTL_SET_FLAGS, &set_flags));

    // Setup Tracking Page
    void *region = SYSCHK(mmap(NULL, 0x1000, 0, MAP_SHARED, mali_fd, BASE_MEM_MAP_TRACKING_HANDLE));
    printf("Region: %p\n", region);

    // Close Device
    close(mali_fd);

    exit(0);
}
