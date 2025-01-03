#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/highmem.h>
#include <linux/pid.h>
#include <linux/uaccess.h>
#include <linux/sched/mm.h>
#include <linux/pgtable.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cybersecurity Researcher");
MODULE_DESCRIPTION("Kernel module to print page tables and attributes of a target PID");

static int target_pid = -1;
module_param(target_pid, int, 0644);
MODULE_PARM_DESC(target_pid, "PID of the target process");

static void print_pte_attributes(pte_t pte)
{
    if (pte_present(pte)) {
        pr_info("  PTE: %lx, Present: Yes, Writable: %s\n",
                pte_val(pte),
                pte_write(pte) ? "Yes" : "No");
    } else {
        pr_info("  PTE: %lx, Present: No\n", pte_val(pte));
    }
}

static void walk_page_tables(struct task_struct *task)
{
    struct mm_struct *mm;
    struct vma_iterator iter;
    struct vm_area_struct *vma;
    unsigned long vaddr;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    if (!task || !(mm = task->mm)) {
        pr_err("Invalid task or mm_struct\n");
        return;
    }

    down_read(&mm->mmap_lock);

    vma_iter_init(&iter, mm, 0);
    for_each_vma(iter, vma) {
        pr_info("VMA: Start: 0x%lx, End: 0x%lx\n", vma->vm_start, vma->vm_end);

        for (vaddr = vma->vm_start; vaddr < vma->vm_end; vaddr += PAGE_SIZE) {
            pgd = pgd_offset(mm, vaddr);
            if (pgd_none(*pgd) || pgd_bad(*pgd))
                continue;

            p4d = p4d_offset(pgd, vaddr);
            if (p4d_none(*p4d) || p4d_bad(*p4d))
                continue;

            pud = pud_offset(p4d, vaddr);
            if (pud_none(*pud) || pud_bad(*pud))
                continue;

            pmd = pmd_offset(pud, vaddr);
            if (pmd_none(*pmd) || pmd_bad(*pmd))
                continue;

            pte = pte_offset_kernel(pmd, vaddr);
            if (!pte)
                continue;

            print_pte_attributes(*pte);
            pte_unmap(pte);
        }
    }

    up_read(&mm->mmap_lock);
}

static int __init page_table_module_init(void)
{
    struct task_struct *task;

    if (target_pid < 0) {
        pr_err("Invalid target PID\n");
        return -EINVAL;
    }

    task = get_pid_task(find_get_pid(target_pid), PIDTYPE_PID);
    if (!task) {
        pr_err("Could not find task with PID %d\n", target_pid);
        return -ESRCH;
    }

    pr_info("Walking page tables for PID %d\n", target_pid);
    walk_page_tables(task);
    put_task_struct(task);

    return 0;
}

static void __exit page_table_module_exit(void)
{
    pr_info("Page table module unloaded\n");
}

module_init(page_table_module_init);
module_exit(page_table_module_exit);
