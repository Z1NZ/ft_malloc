/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:23:41 by srabah            #+#    #+#             */
/*   Updated: 2017/03/01 01:41:00 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/mman.h>

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"
# define CHECK_BIT(var,pos)	(var & pos)
# define OPT_FREE			1
# define OPT_TYNI			2
# define OPT_SMALL			4
# define OPT_LARGE			8
# define OPT_MAP_HEAD		16
# define OPT_BUFF			32
# define SIZE_ST_HEAD		32
# define TYNI_MAX			32/* la taille de la struct block fait 32 donc 32 + 32 = 64*/
# define TYNI_BLOCK			(TYNI_MAX + 32)
# define SMALL_MIN			480/* la taille de la structure fait 32 donc 480 + 32 = 512*/
# define SMALL_BLOCK		(SMALL_MIN + 32)
# define LARGE_MIN			1024
# define FLAG_MALLOC		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED
# define ROUND_UP_PAGE(x, page) 	((x % page)  != 0) ? x / page + 1 : x / page
# define OFFSETOFF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
# define align8(x) (((((x)-1)>>4)<<4) + 8)
# define align4(x) (((((x)-1)>>2)<<2) + 4)

// #define mmap(x, y, z, q, b, c) (void *) -1               /* test du mmap*/
typedef struct			s_block
{
	size_t				size;/*la taille du bloc alloué*/
	int					pad;
	int					info;/*indicateur de disponibilité du bloc et les information complementaire*/ 
	struct s_block		*next;/*les pointeurs sur les méta-données des blocs suivants et précédants;*/
	void				*ptr;/*le pointeur sur les données, pour le contrôleur d'erreur de free*/
	char				data[];/* A pointer to the allocated block */
}						t_block;

typedef struct			s_mem
{
	pthread_mutex_t		mutex;/*variable pour la getion des mutex*/
	int					page;/*taille d'une page*/
	int					pad;
	size_t				size_tyni;/*taille total de la memoire donner a tyni*/
	size_t				use_tyni;/*taille total uttilise tyni*/
	t_block				*m_tyni;/*pointeur sur la list chainneé tyni*/
	size_t				size_small;/*taille total de la memoire donner a small*/
	size_t				use_small;/*taille total uttilise small*/
	t_block				*m_small;/*pointeur sur la list chainneé small*/
	size_t				size_large;/*taille total de la memoire donner a large*/
	size_t				use_large;/*taille total uttilise large*/
	t_block				*m_large;
	void				*main_memory;
	
}						t_mem;


int main(int argc, char const *argv[])
{

	dprintf(2, "TOTOTO");
	char	*ptr;
	char	*ptr2;
	int		i;

	i = 0;
	ptr = NULL;
	ptr2 = NULL;
	printf("taille du block ====		[%zu]		====\n", sizeof(t_block));
	if (argc != 2)
		return (1);
	// free(ptr); 
	while(i < 5)
	{
		printf("%s\n", "SIII");
		ptr = (char *)malloc(atol(argv[1]));
		printf("[%d] === > %p\n", i, ptr);
		// free(ptr);
		ptr = NULL;
		printf("%s\n", ";SIPPPPP");
	
		i++;
	}
	// if (!ptr)
		// return(1);
	// while(i <= atoi(argv[1]))
	// {
	// 	ptr[i] = 'a';
	// 	i++;
	// }
	// printf("value ptr [%s]\n", ptr);
	// if (argc == 2)
		// ptr2 = (char *)malloc(atol(argv[1]));
	// i = 0;
	// while(i <= atoi(argv[1]))
	// {
	// 	ptr2[i] = 'b';
	// 	i++;
	// }
	// printf("------addr ptr2	[%p]\n", ptr2);
	// printf("value ptr2	[%s]\n\n\n\n\n\n\n",ptr2);

	// printf("taille de la espace[%zu]\ntaille de l'espace uttiliser[%zu]\n\n\n", g_mem.size_tyni, g_mem.use_tyni);
	// printf("addr ptr  [%p]\n", ptr);
	// printf("value ptr [%s]\n", ptr);
	// i = 0;
	// while (i < 300)
	// {
	// 	printf("%d => ", i);
	// 	ptr2 = (char *)malloc(atol(argv[1]));
	// 	printf("%p null = %p\n", ptr2, NULL);
	// 	i++;
	// }

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
	// t_block *tmp;

	// tmp = g_mem.m_tyni;
	// int j = 0;
	// while(tmp)
	// {
	// 	printf("TYNI "RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
	// 	tmp = tmp->next;
	// 	j++;
	// }

	// tmp = g_mem.m_small;
	// j = 0;
	// while(tmp)
	// {
	// 	printf("SMALL "RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
	// 	tmp = tmp->next;
	// 	j++;
	// }

	// tmp = g_mem.m_large;
	// j = 0;
	// while(tmp)
	// {
	// 	printf("LARGE "RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
	// 	tmp = tmp->next;
	// 	j++;
	// }
	// printf("\ng_Memory tyni -> (%zu / %zu)\n", g_mem.use_tyni, g_mem.size_tyni);
	// printf("\ng_Memory small -> (%zu / %zu)\n", g_mem.use_small, g_mem.size_small);
	// printf("\ng_Memory large -> (%zu / %zu)\n", g_mem.use_large, g_mem.size_large);
	// printf("%p\n", ptr);

	return 0;
}