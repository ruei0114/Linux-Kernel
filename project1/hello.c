#include <linux/kernel.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

void *my_get_physical_addresses(void *addr) {
    return (void *)syscall(450, addr);
}

int main(){
    void *parent_use;
    int global_a = 123;

    parent_use = my_get_physical_addresses(&global_a);
    printf("&global_a virtual address : %p\n", &global_a);
    printf("physical address : %p\n", parent_use);

    return 0;
}
