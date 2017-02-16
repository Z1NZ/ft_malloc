/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:23:41 by srabah            #+#    #+#             */
/*   Updated: 2017/02/15 16:26:14 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	pthread_mutex_lock(&(g_mem.mutex));
	/// code un repartiteur de charge proportionnel a espace libre dans les maillon 


	if (g_mem.page == 0)
		g_mem.page = getpagesize();
	if (size <= TYNI_MAX)
		return (alloc_tyni(1)); // rajouter dans size la taille demander en nombre de block
	else if (size < SMALL_MIN)
		return (alloc_small(1));
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
		ptr = (char *)ft_malloc(atol(argv[1]));
	printf("%s\n", "test");	

	if (!ptr)
	{
		return(1);
	}
	// while(i <= atoi(argv[1]))
	// {
	// 	ptr[i] = 'a';
	// 	i++;
	// }
	printf("------addr ptr  [%p]\n", ptr);
	// printf("value ptr [%s]\n", ptr);
	printf("taille de la espace%zu\ntaille de l'espace uttiliser %zu\n\n\n", g_mem.size_tyni, g_mem.use_tyni);
	if (argc == 2)
		ptr2 = (char *)ft_malloc(atol(argv[1]));
	i = 0;
	// while(i <= atoi(argv[1]))
	// {
	// 	ptr2[i] = 'b';
	// 	i++;
	// }
	printf("------addr ptr2	[%p]\n", ptr2);
	// printf("value ptr2	[%s]\n\n\n\n\n\n\n",ptr2);

	printf("taille de la espace[%zu]\ntaille de l'espace uttiliser[%zu]\n\n\n", g_mem.size_tyni, g_mem.use_tyni);
	printf("addr ptr  [%p]\n", ptr);
	printf("value ptr [%s]\n", ptr);
	i = 0;
	while (i < 300)
	{
		printf("%d => ", i);
		ptr2 = (char *)ft_malloc(atol(argv[1]));
		printf("%p null = %p\n", ptr2, NULL);
		i++;
	}
	printf("\ng_Memory tyni -> (%zu / %zu)\n", g_mem.use_tyni, g_mem.size_tyni);
	printf("\ng_Memory small -> (%zu / %zu)\n", g_mem.use_small, g_mem.size_small);
	printf("\ng_Memory large -> (%zu / %zu)\n", g_mem.use_large, g_mem.size_large);


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