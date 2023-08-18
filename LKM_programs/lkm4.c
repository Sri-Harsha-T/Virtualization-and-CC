#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <asm/page.h>
// #include <asm-generic/page.h>
#include <linux/moduleparam.h>
#include <linux/vmalloc.h>
#include <linux/pgtable.h>



struct task_struct *task;
struct mm_struct *mm;
struct page *pg;
struct vm_area_struct *vma;
pgd_t *pgd;
p4d_t* p4d;
pud_t *pud;
pmd_t *pmd;
pte_t *pte;
unsigned long pfn;
// spinlock_t *ptl;
unsigned long phys_addr;
int pid_val;
unsigned long virt_addr;
module_param(pid_val, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(pid_val, "PID value");
// MODULE_PARM(virt_addr, "l");
module_param(virt_addr, long, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(virt_addr, "VIRTUAL ADDRESS value");
 
static int vpm_init(void)
{
    printk(KERN_INFO "%s","LOADING VIRTUAL PHYSICAL ADDRESS MAP MODULE\n");
    // pid_val = 1;
    // virt_addr = 0x0000256c5aba;
    
    task = pid_task(find_vpid(pid_val), PIDTYPE_PID);
    if(task!=NULL){ // Performing a page table walk for the given virtual address in the task->mm memory space

        mm = task->mm;
        pgd = pgd_offset(mm, virt_addr);
        if(pgd_none(*pgd) || pgd_bad(*pgd)){
            printk(KERN_INFO "PGD : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }
        pmd = pmd_off(mm, virt_addr);

        p4d = p4d_offset(pgd, virt_addr);
        if(p4d_none(*p4d) || p4d_bad(*p4d)){
            printk(KERN_INFO "P4D : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }

        pud = pud_offset(p4d, virt_addr);
        if(pud_none(*pud) || pud_bad(*pud)){
            printk(KERN_INFO "PUD : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }

        pmd = pmd_offset(pud, virt_addr);
        if(pmd_none(*pmd) || pmd_bad(*pmd)){
            printk(KERN_INFO "PMD : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }
        pte = pte_offset_kernel(pmd, virt_addr);
        // // pte = pte_offset_map_lock(mm, pmd, virt_addr, &ptl);
        if(pte_none(*pte)){
            // pte_unmap_unlock(pte, ptl);
            printk(KERN_INFO "PTE::VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }

        phys_addr = (pte_val(*pte) & PAGE_MASK) | (virt_addr & ~PAGE_MASK);
        printk(KERN_INFO "PID: %d VIRTUAL ADDRESS: 0x%lX PHYSICAL ADDRESS: 0x%lX\n", pid_val,virt_addr, phys_addr);
        
    }
    else
    {
        printk(KERN_INFO "TASK WITH PID: %d DOES NOT EXIST\n", pid_val);
        return -1;
    }
   
 
    return 0;
 
}               
     
static void vpm_exit(void)       
{
 
 
    printk(KERN_INFO "%s","REMOVING VIRTUAL PHYSICAL ADDRESS MAP MODULE\n");
 
}          
 
module_init(vpm_init); 
module_exit(vpm_exit);   
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("VIRTUAL TO PHYSICAL MAP");
MODULE_AUTHOR("Sri Harsha Thota");
