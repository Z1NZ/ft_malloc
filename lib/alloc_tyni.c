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

void	init_tyni_page(void)
{
	t_block *ptr;
	t_block *tmp;
	t_block *new;
	int		len;
	int		i;

	mem.size_tyni = mem.page;
	ptr = (t_block *)mmap(NULL, mem.page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED , -1, 0);
	ptr->size = TYNI_BLOCK;
	ptr->info |= OPT_MAP_HEAD;
	set_block_tyni(ptr, 1, 0);
	ptr->next = NULL;

	mem.m_tyni = ptr;
	i = 1;
	len = mem.page / (TYNI_BLOCK);
	printf("%d\n", len);
	tmp = ptr;
	while (i < len)
	{

		printf("len %d [i = %d]===>%p\n", mem.page, i, tmp);
		new = tmp->ptr + TYNI_MAX;
		tmp->next = new;
		printf("[i = %d]apres =>%p\n", i, tmp->next);
		set_block_tyni(new, 1, 0);
		tmp = tmp->next;
		i++;
		
	}


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
		init_tyni_page();
	if ((mem.size_tyni - mem.use_tyni) >= TYNI_BLOCK * size)
	{
		ptr = find_fusion_location(mem.m_tyni, size);
		if (ptr == NULL)
			ptr = tyni_push_back(); // rajouter une verification de memoire

	}
	else
		ptr = add_page();
	if (ptr)
	 	set_block_tyni(ptr, size, OPT_FREE);
	pthread_mutex_unlock(&(mem.mutex));
	return(((ptr)?ptr->data : NULL));
}