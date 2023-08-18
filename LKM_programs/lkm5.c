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

unsigned long phy_addr(struct task_struct *task2, unsigned long virt_addr){//returns physical address of a virtual address corresponding to the memory struct of a given task struct
//returns 0 if no such physical map exists
    // struct task_struct *task;
    struct mm_struct *mm;
    // struct page *pg;
    unsigned long phys_addr = 0;
    // struct vm_area_struct *vma;
    pgd_t *pgd;
    p4d_t* p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    // task = pid_task(find_vpid(pid_val), PIDTYPE_PID);
    if(task2!=NULL){

        // mm = task->mm;
        mm = task2->mm;
        pgd = pgd_offset(mm, virt_addr);
        if(pgd_none(*pgd) || pgd_bad(*pgd)){
            // printk(KERN_INFO "PGD : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }
        pmd = pmd_off(mm, virt_addr);

        p4d = p4d_offset(pgd, virt_addr);
        if(p4d_none(*p4d) || p4d_bad(*p4d)){
            // printk(KERN_INFO "P4D : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }

        pud = pud_offset(p4d, virt_addr);
        if(pud_none(*pud) || pud_bad(*pud)){
            // printk(KERN_INFO "PUD : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }

        pmd = pmd_offset(pud, virt_addr);
        if(pmd_none(*pmd) || pmd_bad(*pmd)){
            // printk(KERN_INFO "PMD : VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }
        pte = pte_offset_kernel(pmd, virt_addr);
        // // pte = pte_offset_map_lock(mm, pmd, virt_addr, &ptl);
        if(pte_none(*pte)){
            // pte_unmap_unlock(pte, ptl);
            // printk(KERN_INFO "PTE::VIRTUAL ADDRESS: %ld IS NOT MAPPED\n", virt_addr);
            return 0;
        }

        phys_addr = (pte_val(*pte) & PAGE_MASK) | (virt_addr & ~PAGE_MASK);
        
    }
    return phys_addr;
}

int pid_val;
module_param(pid_val, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(pid_val, "PID value");
struct task_struct *task;
struct mm_struct* mm;
struct vm_area_struct* vma;
unsigned long tot_vm;
unsigned long alloc_m;
unsigned long p_addr;


static int lpa_init(void)
{
    printk(KERN_INFO "%s","LOADING LAZY MEMORY ALLOCATION MODULE\n");

    task = pid_task(find_vpid(pid_val), PIDTYPE_PID);
    if(task!=NULL&&task->mm!=NULL){
        tot_vm = 0;
        alloc_m = 0;
        mm = task->mm;
        for(vma = mm->mmap; vma; vma = vma->vm_next)
        {
            for(p_addr = vma->vm_start; p_addr < vma->vm_end; p_addr += PAGE_SIZE)
            {
                if(phy_addr(task, p_addr)){
                    alloc_m ++;
                }
                tot_vm += vma->vm_end - vma->vm_start;
            }
        }
        tot_vm = tot_vm/PAGE_SIZE;
        printk("PID: %d VIRTUAL MEMORY: %ld PHYSICAL MEMORY: %ld(IN PAGES)\n", task->pid, tot_vm, alloc_m);
    }

    return 0;

}

static void lpa_exit(void)       
{
 
 
    printk(KERN_INFO "%s","REMOVING LAZY MEMORY ALLOCATION MODULE\n");
 
}          
 
module_init(lpa_init); 
module_exit(lpa_exit);   
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LAZY PAGE ALLOCATION");
MODULE_AUTHOR("Sri Harsha Thota");
