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
	t_block		*tmp;

	tmp = mem.m_tyni;
	while(tmp)
	{
		if (!CHECK_BIT(tmp->info, OPT_FREE))
		{
			tmp->info |= OPT_FREE;
			tmp->size = TYNI_BLOCK;
			tmp->ptr = tmp->data;
			mem.use_tyni += TYNI_BLOCK;
			return(tmp->data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	*tyni_push_back()
{
	t_block *tmp;
	t_block *new;

	tmp = mem.m_tyni;
	while(tmp->next)
		tmp = tmp->next;

	new = tmp->ptr + TYNI_MAX;
	tmp->next = new;
	new->next = NULL;
	new->size = TYNI_BLOCK;
	new->info |= OPT_FREE;
	new->ptr = new->data;
	mem.use_tyni += TYNI_BLOCK;
	return(new->data);
}
void	*add_page()
{
	t_block		*ptr;
	t_block		*tmp;

	ptr = (t_block *)mmap(NULL, mem.page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED , -1, 0);
	mem.size_tyni += mem.page;
	ptr->size += TYNI_BLOCK;
	ptr->info |= OPT_MAP_HEAD;
	ptr->next = NULL;
	tmp = mem.m_tyni;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = ptr;
	return (ptr);
}

void	*alloc_tyni()
{
	void *ptr;

	ptr = NULL;
	if (mem.size_tyni == 0)
		init_tyni_page();
	if ((mem.size_tyni - mem.use_tyni) >= TYNI_BLOCK)
	{
		ptr = find_location();
		if (ptr == NULL)
			ptr = tyni_push_back();
	}
	else
		ptr = add_page();

	pthread_mutex_unlock(&(mem.mutex));
	return(ptr);
}