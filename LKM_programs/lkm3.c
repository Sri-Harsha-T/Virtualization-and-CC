#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>



struct task_struct *task;
 
static int ksp_init(void)
{
    printk(KERN_INFO "%s","LOADING KERNEL STACK POINTER (PID=1) MODULE\n");

    task = pid_task(find_vpid(1), PIDTYPE_PID);
    

            printk(KERN_INFO "PID: %d KERNEL STACK POINTER: 0x%lX\n", task->pid, (task->thread.sp));
    
 
    return 0;
 
}               
     
static void ksp_exit(void)       
{
 
 
    printk(KERN_INFO "%s","REMOVING KERNEL STACK POINTER (PID=1) MODULE\n");
 
}          
 
module_init(ksp_init); 
module_exit(ksp_exit);   
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DISPLAYING THE KERNEL STACK POINTER OF THE PROCESS WITH PID 1");
MODULE_AUTHOR("Sri Harsha Thota");
