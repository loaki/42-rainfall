#include <limits.h>
#include <stdio.h>

int		main(void)
{
	int i = INT_MIN;
	while ((size_t)(i * 4) < 44)
		i+=1;
	printf("%d", i);
}