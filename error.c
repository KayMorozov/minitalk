#include "libft.h"

void	error(char *emessage)
{
	ft_putstr_fd(emessage, 2);
	exit(1);
}
