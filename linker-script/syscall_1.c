#include "./syscall_1.h"
#include "./user_ta.h"

void syscall_1_write() {
    puts("calling syscall_1_write");
    void *result = to_user_ta_ctx();
    printf("result = %p\n", result);
}

