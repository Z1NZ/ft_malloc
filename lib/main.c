#include "malloc.h"

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>


	// mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
#define align8(x) (((((x)-1)>>4)<<4) + 8)
#define align4(x) (((((x)-1)>>2)<<2) + 4)



void	*ft_malloc(size_t size)
{
	pthread_mutex_lock(&(mem.mutex));
	if (mem.page == 0)
		mem.page = getpagesize();
	if (size < TYNI_MAX)
		return (alloc_tyni(size));
	else if (size < SMALL_MAX)
		return (alloc_small(size));
	else
		return (alloc_large(size));
}


int main(int argc, char const *argv[])
{

	char	*ptr;
	char	*ptr2;
	int		i;

	i = 0;
	ptr = NULL;
	ptr2 = NULL;

	printf("taille du block ====		[%zu]		====\n", sizeof(t_block));


	if (argc == 2)
		ptr = (char *)ft_malloc(atoi(argv[1]));
	while(i <= 94)
	{
		ptr[i] = 'a';
		i++;
	}
	printf("------addr ptr  [%p]\n", ptr);
	printf("value ptr [%s]\n", ptr);
	printf("taille de la espace%zu\ntaille de l'espace uttiliser %zu\n\n\n", mem.size_tyni, mem.use_tyni);
	if (argc == 2)
		ptr2 = (char *)ft_malloc(atoi(argv[1]));
	i = 0;
	while(i <= 94)
	{
		ptr2[i] = 'b';
		i++;
	}

	printf("------addr ptr2	[%p]\n", ptr2);
	printf("value ptr2	[%p\n]", ptr2);
	printf("taille de la espace[%zu]\ntaille de l'espace uttiliser[%zu]\n\n\n", mem.size_tyni, mem.use_tyni);


	printf("addr ptr  [%p]\n", ptr);
	printf("value ptr [%s]\n", ptr);

	i = 0;
	while (i < 300)
	{
		printf("%d => ", i);
		ptr2 = (char *)ft_malloc(atoi(argv[1]));
		printf("%p\n", ptr2);
		i++;
	}

	// LIST_HEAD(head);
	// int page = getpagesize();
	// t_block *ptr = malloc(sizeof(t_block));
	// list_add_tail(&(ptr->list), &head);
	// ptr->free = 88999;
	// t_block *ptr2 = (t_block *)malloc(sizeof(t_block));
	// list_add_tail(&(ptr2->list), &head);
	// ptr2->free = 999999;
	// int *test = &(ptr2->free);
	// t_block *ptr3 = list_entry(test, t_block, free);
	// printf("ptr2 == [%p] -> ptr3 [%p] \n", ptr2, ptr3);
	// printf("page size ===> [%d]", getpagesize());
	// printf("\ntaille du block[%lu]\n", sizeof(t_block));
	// char *toto = (char *)mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	// printf("[%zd]", write(1, toto, page));
	// printf("[%p]", toto);
	// toto = malloc(0);
	// printf("[%p]", toto);
	return 0;
}