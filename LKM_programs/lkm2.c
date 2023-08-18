#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/mm.h>



struct task_struct *task;
unsigned long heap_size;
unsigned long proc_heap_size;
pid_t t_pid;
struct vm_area_struct* vma;
 
static int largest_heap_init(void)
{
    printk(KERN_INFO "%s","LOADING DISPLAY LARGEST IN-USE HEAP MODULE\n");
    heap_size = 0;
    // proc_heap_size = 0;
    t_pid = 0; // task pid corresponding to largest heap size

     
    for_each_process( task ){            //iterate through all the processes
        if(task->mm!=NULL){
            proc_heap_size = 0;

            for(vma = task->mm->mmap; vma;vma = vma->vm_next){
                if(vma->vm_start <= task->mm->brk && vma->vm_end >= task->mm->start_brk){

                    // if(vma->vm_flags & VM_GROWSDOWN){
                        proc_heap_size += vma->vm_end - vma->vm_start;
                    // }
                }
            }
            if(proc_heap_size >= heap_size){
                t_pid = task->pid;
                heap_size = proc_heap_size;
            }

        }
        
    }    
    printk(KERN_INFO "PID: %d HEAP MEMORY: %ld\n", t_pid, heap_size);
 
    return 0;
 
}               
     
static void largest_heap_exit(void)       
{
 
 
    printk(KERN_INFO "%s","REMOVING DISPLAY LARGEST IN-USE HEAP MODULE\n");
 
}          
 
module_init(largest_heap_init); 
module_exit(largest_heap_exit);   
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DISPLAYING THE PROCESS WITH THE LARGEST IN USE HEAP MEMORY");
MODULE_AUTHOR("Sri Harsha Thota");
