#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/sched/signal.h>

#define DEVICE_NAME "monitor"
#define GET_MEM 1

static int major;

// 🔹 IOCTL FUNCTION
static long monitor_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
    pid_t pid;
    struct task_struct *task;

    if (copy_from_user(&pid, (pid_t *)arg, sizeof(pid_t))) {
        return -EFAULT;
    }

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
        printk(KERN_INFO "Process not found\n");
        return -EINVAL;
    }

    if (cmd == GET_MEM && task->mm) {
        unsigned long mem = get_mm_rss(task->mm) << PAGE_SHIFT;
        printk(KERN_INFO "PID %d memory: %lu bytes\n", pid, mem);
    }

    return 0;
}

// 🔹 FILE OPS
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .unlocked_ioctl = monitor_ioctl,
};

// 🔹 INIT
static int __init monitor_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "Monitor module loaded\n");
    return 0;
}

// 🔹 EXIT
static void __exit monitor_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Monitor module unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("Memory monitor module");
