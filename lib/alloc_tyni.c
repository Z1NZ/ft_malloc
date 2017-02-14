#include "malloc.h"
#include <sys/types.h>
 #include <sys/mman.h>
 


 static inline	void set_block_tyni(t_block *ptr, size_t size, int on)
{	
	ptr->size = TYNI_BLOCK * size;
	if (on)
		ptr->info |= OPT_FREE;
	ptr->ptr = ptr->data;
	if (on)
		mem.use_tyni += TYNI_BLOCK * size;
}

static inline	void set_page(t_block *ptr)
{
	int		i;
	int		len;
	t_block *new;
	t_block *tmp;

	i = 1;
	new = NULL;
	new = NULL;
	len = mem.page / (TYNI_BLOCK);
	tmp = ptr;
	while (i < len)
	{
		new = tmp->ptr + TYNI_MAX;
		tmp->next = new;
		set_block_tyni(new, 1, 0);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;

}

int  init_tyni_page(void)
{
	t_block *ptr;

	mem.size_tyni = mem.page;
	ptr = (t_block *)mmap(NULL, mem.page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED , -1, 0);
	if (ptr == ((void *) -1))
		return(1);
	ptr->size = TYNI_BLOCK;
	ptr->info |= OPT_MAP_HEAD;
	set_block_tyni(ptr, 1, 0);
	ptr->next = NULL;
	mem.m_tyni = ptr;
	set_page(ptr);
	return (0);
}

void	*tyni_push_back(void)
{
	t_block *tmp;
	t_block *new;

	tmp = mem.m_tyni;
	while(tmp->next)	
		tmp = tmp->next;
	new = tmp->ptr + TYNI_MAX;
	new->next = NULL;
	return(new);
}



void	*add_page(void)
{
	t_block		*ptr;
	t_block		*tmp;

	ptr = (t_block *)mmap(NULL, mem.page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED , -1, 0);
	if (ptr == ((void *) -1))
		return(NULL);
	mem.size_tyni += mem.page;
	ptr->info |= OPT_MAP_HEAD;
	ptr->next = NULL;
	tmp = mem.m_tyni;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = ptr;
	return (ptr);
}

void	*alloc_tyni(size_t size)
{
	t_block *ptr;

	ptr = NULL;
	if (mem.size_tyni == 0)
	{
		if (init_tyni_page() == 1)
			return (NULL);
	}
	if ((mem.size_tyni - mem.use_tyni) >= TYNI_BLOCK * size)
	{
		ptr = find_fusion_location(mem.m_tyni, size);
		if (ptr == NULL)
		{
			ptr = tyni_push_back(); // rajouter une verification de memoire
		}

	}
	else
		ptr = add_page();
	if (ptr)
	 	set_block_tyni(ptr, size, OPT_FREE);
	printf("%d\n", ptr->info);
	pthread_mutex_unlock(&(mem.mutex));
	return(((ptr)?ptr->data : NULL));
}