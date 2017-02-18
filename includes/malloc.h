/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:25:37 by srabah            #+#    #+#             */
/*   Updated: 2017/02/18 15:00:13 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/mman.h>

# define CHECK_BIT(var,pos)	(var & pos)
# define OPT_FREE			1
# define OPT_TYNI			2
# define OPT_SMALL			4
# define OPT_LARGE			8
# define OPT_MAP_HEAD		16
# define OPT_6				32
# define SIZE_ST_HEAD		32
# define TYNI_MAX			32/* la taille de la struct block fait 32 donc 32 + 32 = 64*/
# define TYNI_BLOCK			(TYNI_MAX + 32)
# define SMALL_MIN			480/* la taille de la structure fait 32 donc 480 + 32 = 512*/
# define SMALL_BLOCK		(SMALL_MIN + 32)
# define LARGE_MIN			1024
# define FLAG_MALLOC		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE | MAP_SHARED
# define ROUND_UP_PAGE(x) 	((x % 4096)  != 0) ? x / 4096 + 1 : x / 4096
# define OFFSETOFF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

// #define mmap(x, y, z, q, b, c) (void *) -1               /* test du mmap*/
typedef struct			s_block
{
	size_t				size;/*la taille du bloc alloué*/
	int					info;/*indicateur de disponibilité du bloc et les information complementaire*/ 
	struct s_block		*next;/*les pointeurs sur les méta-données des blocs suivants et précédants;*/
	void				*ptr;/*le pointeur sur les données, pour le contrôleur d'erreur de free*/
	char				data[];/* A pointer to the allocated block */
}						t_block;

typedef struct			s_mem
{
	pthread_mutex_t		mutex;/*variable pour la getion des mutex*/
	size_t				page;/*taille d'une page*/
	size_t				size_tyni;/*taille total de la memoire donner a tyni*/
	size_t				use_tyni;/*taille total uttilise tyni*/
	t_block				*m_tyni;/*pointeur sur la list chainneé tyni*/
	size_t				size_small;/*taille total de la memoire donner a small*/
	size_t				use_small;/*taille total uttilise small*/
	t_block				*m_small;/*pointeur sur la list chainneé small*/
	size_t				size_large;/*taille total de la memoire donner a large*/
	size_t				use_large;/*taille total uttilise large*/
	t_block				*m_large;
	
}						t_mem;

t_mem					g_mem;/*global general memoire*/
void					*alloc_large(size_t size);
void					*alloc_tyni(size_t size);
void					*alloc_small(size_t size);

/*
** free
*/
void 					ft_free(void *ptr);
/*
** TOOLS
*/

void					*find_fusion_location(t_block *block, size_t size);

#endif