#include "libft.h"

int	ft_ismaj(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}