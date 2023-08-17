// by jrzanol
// 

#include "stdafx.h"

void* test(void* arg)
{
	return NULL;
}

int main(int argc, const char* argv[])
{
	pthread_t th;
	pthread_create(&th, NULL, test, NULL);

	return EXIT_SUCCESS;
}

