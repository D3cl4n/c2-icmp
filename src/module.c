#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Declan Murphy");
MODULE_VERSION("1.0");

static int __init c2_init(void) {
    printk(KERN_INFO "Initializing module\n"); //KERN_INFO is log level flag
    return 0;
}

static void __exit c2_exit(void) {
    printk(KERN_INFO "Module exiting\n"); //printk outputs to kernel's log
}

module_init(c2_init);
module_exit(c2_exit);