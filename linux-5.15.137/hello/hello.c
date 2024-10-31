#include <linux/kernel.h> 
#include <linux/syscalls.h> 

SYSCALL_DEFINE0(hello){ 
	printk("Hello world!\n");
        printk("Add to test\n");	
	return 0; 
}
