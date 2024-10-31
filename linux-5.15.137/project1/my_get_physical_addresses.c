#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/mm_types.h>
#include <asm/pgtable.h>
#include <asm/page.h> // 確保包含頁面大小和轉換相關的定義

SYSCALL_DEFINE2(my_get_physical_addresses, void __user *, user_vaddr, void __user *, user_paddr) {
    unsigned long vaddr = (unsigned long) user_vaddr;
    pgd_t *pgd;
    p4d_t *p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;
    struct page *page;

    printk("===================================\n");
    printk("This is my_get_physical_addresses\n");

    // 取得 pgd 頁表
    pgd = pgd_offset(current->mm, vaddr);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
        return -EFAULT;

    // 取得 p4d 頁表
    p4d = p4d_offset(pgd, vaddr);
    if (p4d_none(*p4d) || p4d_bad(*p4d))
        return -EFAULT;

    // 取得 pud 頁表
    pud = pud_offset(p4d, vaddr);
    if (pud_none(*pud) || pud_bad(*pud))
        return -EFAULT;

    // 取得 pmd 頁表
    pmd = pmd_offset(pud, vaddr);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
        return -EFAULT;

    // 取得 pte 頁表
    pte = pte_offset_map(pmd, vaddr);
    if (!pte || pte_none(*pte))
        return -EFAULT;

    // 確保頁面已經存在
    page = pte_page(*pte);
    if (!page)
        return -EFAULT;

    // 使用 page_to_pfn 並計算實體地址
    return (long)((page_to_pfn(page) << PAGE_SHIFT) | (vaddr & ~PAGE_MASK));
}
