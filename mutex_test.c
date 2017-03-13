
#include <pthread.h>
#include "malloc.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void	test(int mutex)
{
	printf("THREAD  : %d\n", mutex);
	pthread_mutex_lock(&lock);
	printf("HELLO JE SUIS LE THREAD  : %d JATTEND\n", mutex);
	sleep(5);
	pthread_mutex_unlock(&lock);
}

void	*start_thread_1(void * rien)
{
	while(1)
	test(1);
	return (NULL);
}


void	*start_thread_2(void * rien)
{
	while(1)
	test(2);
	return (NULL);
}

int main(void)
{
	pthread_t un;
	pthread_t deux;

	pthread_create (&un, NULL, start_thread_1, NULL);
	pthread_create (&deux, NULL, start_thread_2, NULL);
	sleep(2200);
}