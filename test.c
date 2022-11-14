#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*auth = NULL;
char	*service = NULL;

int		main(void)
{
	char	buffer[128];
	int t = 0;
	while (1)
	{
		printf("%p, %p\n", auth, service);
		if (fgets(buffer, 128, stdin) == 0)
            break;
        if (strncmp(buffer, "auth ", 5) == 0)
		{
			auth = malloc(4);
			auth[0] = 0;
			if (strlen(buffer + 5) <= 30)
				strcpy(auth, buffer + 5);
            t =1;
		}
		if (strncmp(buffer, "reset", 5) == 0)
			free(auth);
		if (strncmp(buffer, "service", 6) == 0)
			service = strdup(buffer + 7);
            printf("%s",buffer + 7);
        if (t) {
            for (int i=0; i<strlen(auth);i++) {
                printf("%d = |%c|\n",i,auth[i]);
            }
            if (auth[32] != 0)
                printf("\nwin |%c|", auth[32]);
            if (auth[7] != 0)
                printf("\n7 |%c|", auth[32]);

        }
        
    }
}