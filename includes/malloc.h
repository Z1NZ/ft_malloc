#ifndef MALLOC_H

#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>

#define MALLOC_H

#define CHECK_BIT(var,pos)	(var & pos)
#define OPT_FREE			1
#define OPT_TYNI			2
#define OPT_SMALL			4
#define OPT_LARGE			8
#define OPT_MAP_HEAD		16
#define OPT_6				32
#define TYNI_MAX			32 // la taille de la struct block fait 32 donc 32 + 96 = 128
#define TYNI_BLOCK			TYNI_MAX + 32
#define SMALL_MIN			512
#define SMALL_MAX			1024	
#define LARGE_MIN			1024


typedef	struct s_test
{
	char		t[383];
}				t_test;

typedef struct			s_block
{
	size_t				size;		/*la taille du bloc alloué*/
	int					info;		/*indicateur de disponibilité du bloc et les information complementaire*/ 
	struct s_block		*next;		/*les pointeurs sur les méta-données des blocs suivants et précédants;*/
	void				*ptr;		/*le pointeur sur les données, pour le contrôleur d'erreur de free*/
	char				data[];	/* A pointer to the allocated block */
}						t_block;

typedef struct			s_mem
{
	pthread_mutex_t		mutex; // variable pour la getion des mutex 
	size_t				page;	// taille d'une page 
	size_t				size_tyni; // taille total de la memoire donner a tyni
	size_t				use_tyni; // taille total uttilise tyni
	t_block				*m_tyni; // pointeur sur la list chainneé tyni
}						t_mem;

t_mem mem; // global general memoire 

void	*alloc_large(size_t size);
void	*alloc_tyni();
void	*alloc_small(size_t size);


#endif