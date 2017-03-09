#include "malloc.h"

void ft_mem_show(int opt)
{
	t_block *tmp;
	int j;

	if (opt == 0 || opt == OPT_TYNI)
	{
		tmp = g_mem.m_tyni;
		j = 0;
		while(tmp)
		{
			ft_printf("TYNI "RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
			tmp = tmp->next;
			j++;
		}
	}
	if (opt == 0 || opt == OPT_SMALL)
	{
		tmp = g_mem.m_small;
		j = 0;
		while(tmp)
		{
			ft_printf("SMALL "RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
			tmp = tmp->next;
			j++;
		}
	}

	if (opt == 0 || opt == OPT_LARGE)
	{
		tmp = g_mem.m_large;
		j = 0;
		while(tmp)
		{
			ft_printf("LARGE "RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
			tmp = tmp->next;
			j++;
		}
	}
	ft_printf("\ng_Memory tyni -> (%zu / %zu)\n", g_mem.use_tyni, g_mem.size_tyni);
	ft_printf("\ng_Memory small -> (%zu / %zu)\n", g_mem.use_small, g_mem.size_small);
	ft_printf("\ng_Memory large -> (%zu / %zu)\n", g_mem.use_large, g_mem.size_large);
}