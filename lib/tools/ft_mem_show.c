#include "malloc.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putnbr(int n)
{
	unsigned int	count;
	unsigned int	u_nbr;

	count = 0;
	u_nbr = n;
	if (n < 0)
	{
		ft_putchar('-');
		u_nbr = -n;
	}
	if (u_nbr / 10)
		ft_putnbr(u_nbr / 10);
	ft_putchar(u_nbr % 10 + '0');
}

size_t	ft_strlen(const char *s)
{
	char const	*p_s = s;

	while (*p_s)
		p_s++;
	return (p_s - s);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	pri_addr(unsigned long long number)
{
	char base[] = "0123456789abcdef";
	int current_rest = 0;
	char addr[16];
	int i;

	i = 0;
	while(number)
	{
		current_rest = number % 16;

		addr[i] = base[current_rest];
		number /= 16;
		i++;
	}
	i--;
	write(1, "0x", 2);
	while(i > -1)
	{
		write(1, &addr[i], 1);
		i--;
	}
}


void ft_mem_show(int opt)
{
	t_block *tmp;
	int j;
	int i;

	if (opt == 0 || opt == OPT_TYNI)
	{
		tmp = g_mem.m_tyni;
		j = 0;
		i = 0;
		while(tmp)
		{
			if (!CHECK_BIT(tmp->info, OPT_MAP_HEAD))
				i = 0;
			ft_putstr("TYNI "RED"pos = [");
			ft_putnbr(j);
			ft_putstr("][");
			ft_putnbr(i);
			ft_putstr("]"GRN" addr = [");
			pri_addr((unsigned long long)tmp);
			ft_putstr("]"CYN" size = [");
			ft_putnbr((int) (tmp->size));
			ft_putstr("]"RESET" info = [");
			ft_putnbr(tmp->info);
			ft_putstr("]\n");
			tmp = tmp->next;
			j++;
			i++;
		}
	}
	if (opt == 0 || opt == OPT_SMALL)
	{
		tmp = g_mem.m_small;
		j = 0;
		i = 0;
		while(tmp)
		{
			if (!CHECK_BIT(tmp->info, OPT_MAP_HEAD))
				i = 0;
			ft_putstr("SMALL "RED"pos = [");
			ft_putnbr(j);
			ft_putstr("][");
			ft_putnbr(i);
			ft_putstr("]"GRN" addr = [");
			pri_addr((unsigned long long)tmp);
			ft_putstr("]"CYN" size = [");
			ft_putnbr((int) (tmp->size));
			ft_putstr("]"RESET" info = [");
			ft_putnbr(tmp->info);
			ft_putstr("]\n");
			tmp = tmp->next;
			j++;
			i++;
		}
	}

	if (opt == 0 || opt == OPT_LARGE)
	{
		tmp = g_mem.m_large;
		j = 0;
		i = 0;
		while(tmp)
		{
			if (!CHECK_BIT(tmp->info, OPT_MAP_HEAD))
				i = 0;
			ft_putstr("LARGE "RED"pos = [");
			ft_putnbr(j);
			ft_putstr("][");
			ft_putnbr(i);
			ft_putstr("]"GRN" addr = [");
			pri_addr((unsigned long long)tmp);
			ft_putstr("]"CYN" size = [");
			ft_putnbr((int) (tmp->size));
			ft_putstr("]"RESET" info = [");
			ft_putnbr(tmp->info);
			ft_putstr("]\n");
			tmp = tmp->next;
			j++;
			i++;
		}
	}
}