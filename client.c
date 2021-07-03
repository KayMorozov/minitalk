#include "minitalk.h"

void	err_input(void)
{
	ft_putstr_fd("usage: ./client [server-pid] [message]\n", 1);
	exit(0);
}

void	send_to_server(int pid, int ch)
{
	int	mask;

	mask = 1 << 7;
	while (mask)
	{
		if (ch & mask)
		{
			if (kill(pid, SIGUSR1) == -1)
				error("incorrect pid\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error("incorrect pid\n");
		}
		mask >>= 1;
		usleep(100);
	}
}

void	client_handler(char *str_pid, char *mess)
{
	int	pid;

	pid = ft_atoi(str_pid);
	while (*mess)
		send_to_server(pid, *mess++);
	send_to_server(pid, *mess);
}

int 	main(int argc, char **argv)
{
	if (argc != 3)
		err_input();
	client_handler(argv[1], argv[2]);
}
