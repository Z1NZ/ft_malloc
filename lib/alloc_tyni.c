#include "malloc.h"
#include <sys/types.h>
#include <sys/mman.h>

void	init_tyni_page(void)
{
	t_block *ptr;

	mem.size_tyni = mem.page;
	ptr = (t_block *)mmap(NULL, mem.page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED , -1, 0);
	ptr->size = TYNI_BLOCK;
	ptr->info |= OPT_MAP_HEAD;
	ptr->next = NULL;
	mem.m_tyni = ptr;
}

void	*find_location(void)
{
	t_block		*tmp

	tmp = mem.m_tyni;
	while(tmp)
	{
		if (CHECK_BIT(tmp->info, OPT_FREE))
		{
			tmp->info |= OPT_FREE;
			tmp->size = TYNI_BLOCK;
			mem.use_tyni = TYNI_BLOCK;
			return(tmp->data);
		}
	}

	return(ptr)
}

void	*alloc_tyni(size_t size)
{
	void *ptr;

	if (mem.size_tyni == 0)
		init_tyni_page();
	if ((mem.size_tyni - mem.use_tyni) >= TYNI_BLOCK)
		find_location();

	pthread_mutex_unlock(mem.mutex);
	return(ptr);
}