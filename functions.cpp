/*	Functions, odda and sods	*/

#include "main.h"

void	strswap(char *token, char vieux, char neuve)
{
int i = 0;
	while(token[i] != '\0')
		{
			if(token[i] == vieux)
				{ token[i] = neuve; }
				i++;
		}
	return;
}
