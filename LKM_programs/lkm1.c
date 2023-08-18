#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
// #include <linux/fs/proc/array.c>


struct task_struct *task;
 
static int proc_list_init(void)
{
    printk(KERN_INFO "%s","LOADING RUNNING-RUNNABLE PROC LIST MODULE\n");
     
    for_each_process( task ){               //iterating through all the processes 
        if(task_state_index(task)==0){      //task_state_index == 0 indicates the status of process is R which indicates the process is RUNNING / RUNNABLE
            printk(KERN_INFO "PID: %d PROCESS: %s STATE: R (running/runnable) \n",task->pid, task->comm);
        }
        
    }    
     
 
    return 0;
 
}               
     
static void proc_list_exit(void)       
{
 
 
    printk(KERN_INFO "%s","REMOVING RUNNING-RUNNABLE PROC LIST MODULE\n");
 
}          
 
module_init(proc_list_init); 
module_exit(proc_list_exit);   
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LIST ALL RUNNING/RUNNABLE PROCESSES IN THE OS");
MODULE_AUTHOR("Sri Harsha Thota");
