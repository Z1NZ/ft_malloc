#include "malloc.h"
#include "ft_list.h"
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

	// mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
#define align8(x) (((((x)-1)>>4)<<4) + 8)
#define align4(x) (((((x)-1)>>2)<<2) + 4)

t_mem mem;

void inline set_block_info(t_block *ptr_b, size_t size, void *data, char nb)
{
	ptr_b->size = size;
	ptr_b->free = 0;
	ptr_b->ptr = data;
	ptr_b->data[1] = nb;
}

int main()
{

	LIST_HEAD(head);
	t_block *ptr = malloc(sizeof(t_block));
	list_add_tail(&(ptr->list), &head);
	ptr->free = 88999;
	t_block *ptr2 = (t_block *)malloc(sizeof(t_block));
	list_add_tail(&(ptr2->list), &head);
	ptr2->free = 999999;
	int *test = &(ptr2->free);
	t_block *ptr3 = list_entry(test, t_block, free);
	printf("ptr2 == [%p] -> ptr3 [%p] \n", ptr2, ptr3);
	printf("page size ===> [%d]", getpagesize());
	// printf("--[%d]--\n", align8(24));
	return 0;
}