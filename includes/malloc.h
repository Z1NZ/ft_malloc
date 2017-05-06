/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:25:37 by srabah            #+#    #+#             */
/*   Updated: 2017/03/14 17:15:50 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>
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
# define TYNI_MAX			32
# define TYNI_BLOCK			(TYNI_MAX + 32)
# define SMALL_MIN			480
# define SMALL_BLOCK		(SMALL_MIN + 32)
# define LARGE_MIN			1024
# define FLAG_MALLOC		PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED | MAP_HASSEMAPHORE
# define ROUND_UP_PAGE(x, page)	((x % page)  != 0) ? x / page + 1 : x / page
# define OFFSETOFF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
# define align8(x) (((((x)-1)>>4)<<4) + 8)
# define align4(x) (((((x)-1)>>2)<<2) + 4)
# define ABS(number)			(number < 0) ? -(number) : (number)


typedef struct			s_block
{
	size_t				size;
	int					pad;
	int					info;
	struct s_block		*next;
	void				*ptr;
	char				data[];
}						t_block;

typedef struct			s_mem
{
	pthread_mutex_t		mutex;
	pthread_mutex_t		mutex_free;
	pthread_mutex_t		mutex_real;
	pthread_mutex_t		mutex_cal;
	pthread_mutex_t		mutex_show;
	pthread_mutex_t		mutex_show_ex;
	unsigned int		page;
	int					pad;
	size_t				size_tyni;
	size_t				use_tyni;
	t_block				*m_tyni;
	size_t				size_small;
	size_t				use_small;
	t_block				*m_small;
	size_t				size_large;
	size_t				use_large;
	t_block				*m_large;
	void				*main_memory;
}						t_mem;

t_mem					g_mem;
/*
** LIB
*/
int						init_memory(size_t block_tyni, size_t block_small);
void					*alloc_large(size_t size);
void					*alloc_tyni(size_t size);
void					*alloc_small(size_t size);
void					*malloc(size_t size);
void					*calloc(size_t count, size_t size);
void					*realloc(void *ptr, size_t nb);
void					*reallocf(void *ptr, size_t size);
void					free(void *ptr);

/*
** TOOLS
*/
size_t					ft_strlen(const char *s);
void					ft_putnbr(int n);
void					ft_putstr(char *s);
size_t					ft_strlen(const char *s);
void					ft_putchar(char c);
void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);
int						check_addr(void *ptr);
void					*unlock_return_null(pthread_mutex_t *m);
void					*find_fusion_location(t_block *block, size_t size);


#endif
