#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <zconf.h>
# include "libft.h"

# define BUFFER_SIZE 1024

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef struct s_repository
{
	char		mess[BUFFER_SIZE];
	int			bit;
	int			position;
	_Bool		overflow;
	_Bool		ready;
}				t_repository;

t_repository	g_print_message = {{0}, 1 << 7, 0, FALSE, FALSE};

void			error(char *emessage);

#endif
