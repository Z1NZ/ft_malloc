#include "malloc.h"
#include "ft_list.h"

void	init_tyni_page(void)
{
	t_block *ptr
	mem.size_tyni = mem.page;
	ptr = (t_block *)mmap(NULL, mem.page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	ptr.size = TYNI_BLOCK;
	ptr.info =| OPT_MAP_HEAD;
	mem.size_use_block += TYNI_BLOCK;
	list_add_tail(&(ptr->list), &head);
}

void	*alloc_tyni(size_t size)
{
	if (mem.size == 0)
		init_tyni_page();
	
	return()
}