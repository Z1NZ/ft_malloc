#ifndef MALLOC_H

#include "ft_list.h"
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

#define MALLOC_H

#define CHECK_BIT(var,pos)	(var & pos)
#define OPT_FREE			1
#define OPT_TYNI			2
#define OPT_SMALL			4
#define OPT_LARGE			8
#define OPT_5				16
#define OPT_6				32
#define OPT_7				64
#define TYNI_MAX			32
#define SMALL_MIN			512
#define SMALL_MAX			1024	
#define LARGE_MIN			1024

typedef struct			s_block
{
	size_t				size;		/*la taille du bloc alloué*/
	struct list_head	list;		/*les pointeurs sur les méta-données des blocs suivants et précédants;*/
	int					free;		/*indicateur de disponibilité du bloc;*/
	void				*ptr;		/*le pointeur sur les données, pour le contrôleur d'erreur de free*/
	char				data[1];	/* A pointer to the allocated block */
}						t_block;

typedef struct			s_mem
{
	t_block				m_tyni;
	t_block				m_small;
	t_block				m_large;
}						t_mem;

#endif