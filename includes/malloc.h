/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:25:37 by srabah            #+#    #+#             */
/*   Updated: 2017/03/09 15:48:18 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H

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

t_mem					g_mem;/*global general memoire*/
void					init_memory(size_t block_tyni, size_t block_small);
void					*alloc_large(size_t size);
void					*alloc_tyni(size_t size);
void					*alloc_small(size_t size);
void					*malloc(size_t size);
void					*calloc(size_t count, size_t size);
void    				*realloc(void *, size_t);

/*
** free
*/
void 					free(void *ptr);
int						ft_printf(const char * restrict format, ...);
/*
** TOOLS
*/
void					ft_mem_show(int opt);
void					*find_fusion_location(t_block *block, size_t size);

#endif
