#include "malloc.h"

void	*alloc_large(size_t size)
{
	void *ptr;

	ptr = NULL;

	size = 0;
	printf("%s\n", "merci de coder la fonction");
	pthread_mutex_unlock(mem.mutex);
	return(ptr);
}