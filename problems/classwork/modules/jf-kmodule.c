#include <linux/module.h>
#include <linux/printk.h>

// module information
MODULE_AUTHOR("Jala Foundation");
MODULE_DESCRIPTION("Jala Foundation Kernel Module");
MODULE_LICENSE("GPL");

static int _init jf_kmodule_init(void)
{
    printk(KERN_ALERT "JF Module loaded");
    return 0;
}

static void jf_module_exit(void)
{
    printk(KERN_ALERT "JF Module unloaded");
}
// init
module_init(jf_kmodule_init);

// exit

module_exit(jf_kmodule_exit);