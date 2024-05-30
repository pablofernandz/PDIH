/**
 * @file    counter.c
 * @author  Pablo Fernandez
 * @date    30 May 2024
 * @version 0.1
 * @brief  A simple loadable kernel module (LKM) that counts the number of times it is loaded
 * and unloaded, displaying the counts in the /var/log/kern.log file.
 */

#include <linux/init.h>             // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>           // Core header for loading LKMs into the kernel
#include <linux/kernel.h>           // Contains types, macros, functions for the kernel

MODULE_LICENSE("GPL");              ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Pablo");             ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux driver that counts loads and unloads."); ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module

static int load_count = 0;          ///< Count of how many times the module is loaded
static int unload_count = 0;        ///< Count of how many times the module is unloaded

/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init counter_init(void){
   load_count++;
   printk(KERN_INFO "Counter Module: Loaded %d times.\n", load_count);
   return 0;
}

/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit counter_exit(void){
   unload_count++;
   printk(KERN_INFO "Counter Module: Unloaded %d times.\n", unload_count);
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(counter_init);
module_exit(counter_exit);

