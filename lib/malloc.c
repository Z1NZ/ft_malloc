/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:23:41 by srabah            #+#    #+#             */
/*   Updated: 2017/03/13 11:11:29 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

void		ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putchar_fd(char c, int fd)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	write(fd, &chr, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int	count;
	unsigned int	u_nbr;

	count = 0;
	u_nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u_nbr = -n;
	}
	if (u_nbr / 10)
		ft_putnbr_fd(u_nbr / 10, fd);
	ft_putchar_fd(u_nbr % 10 + '0', fd);
}


static inline void	set_zero_block(void *ptr)
{
	size_t len;
	size_t i;

	i = 0;
	ptr -= OFFSETOFF(t_block, data);
	len = ((t_block *)(ptr))->size - SIZE_ST_HEAD;
	while(i < len)
	{
		((t_block *)(ptr))->data[i] = 0;
		i++;
	}
}

void	*calloc(size_t count, size_t size)
{
	// write(2, "calloc\n", 7);
	void *ptr;

	if (size == 0)
		size = 1;
	ptr = malloc((count * size));
	if (ptr)
		set_zero_block(ptr);
	return(ptr);
}

void	*realloc(void *ptr, size_t size)
{
	// write(2, "realloc\n", 8);
	char	*tmp;
	size_t	len;
	size_t	i;

	if (!ptr)
		return(malloc(size));
	else if (ptr && size == 0)
	{
		free(ptr);
		return(NULL);
	}
	else if ((check_addr(ptr)) == 0)
	{
		return(NULL);
	}
	else
	{
		ptr -= OFFSETOFF(t_block, data);
		len = ((t_block *)(ptr))->size - SIZE_ST_HEAD;
		if (len >= size)
			return(((t_block *)(ptr))->data);
		else
		{
			tmp = (void *)malloc(size);
			if (!tmp)
				return(tmp);
			i = 0;
			while(i < len)
			{
				tmp[i] = ((t_block *)(ptr))->data[i];
				i++;
			}
			free(((t_block *)(ptr))->data);
			return((void *)tmp);
		}
	}
	return(NULL);
}

void	*malloc(size_t size)
{
	size_t	len;
	size_t	len_small;

	pthread_mutex_lock(&(g_mem.mutex));
	// ft_putnbr_fd(size, 2);
	// ft_putchar_fd('\n', 2);

	if (g_mem.page == 0)
		g_mem.page = getpagesize();
	if (!g_mem.size_tyni && !g_mem.size_small)
		init_memory(100, 100);
	len = (size <= TYNI_MAX) ? 1 : (ROUND_UP_PAGE(size, TYNI_MAX));
	len_small = (size <= SMALL_MIN) ? 1 : (ROUND_UP_PAGE(size, SMALL_MIN));
	if (len <= 4)
		return (alloc_tyni(len));
	else if (len_small <= 4)
		return (alloc_small(len_small));
	else
		return (alloc_large(size));
}
