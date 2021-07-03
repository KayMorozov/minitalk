#include "minitalk.h"

static	void	print_pid(void)
{
	ft_putstr_fd("pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

static	void	working_bit_handler(int sign, siginfo_t *inf, void *context)
{
	(void)sign;
	(void)context;
	(void)inf;
	if (!g_print_message.bit)
	{
		g_print_message.bit = 1 << 7;
		g_print_message.position++;
	}
	g_print_message.mess[g_print_message.position] += g_print_message.bit;
	g_print_message.bit >>= 1;
	if (g_print_message.position == BUFFER_SIZE - 2
		&& !g_print_message.bit)
		g_print_message.overflow = TRUE;
}

static	void	null_bit_handler(int sign, siginfo_t *inf, void *context)
{
	(void)sign;
	(void)context;
	(void)inf;
	if (!g_print_message.bit)
	{
		g_print_message.bit = 1 << 7;
		g_print_message.position++;
	}
	g_print_message.bit >>= 1;
	if (g_print_message.position == BUFFER_SIZE - 2
		&& !g_print_message.bit)
		g_print_message.overflow = TRUE;
	else if (!g_print_message.mess[g_print_message.position]
		&& !g_print_message.bit)
		g_print_message.ready = TRUE;
}

static	void	server_handler(void)
{
	while (1)
	{
		pause();
		if (g_print_message.ready || g_print_message.overflow)
		{
			ft_putstr_fd(g_print_message.mess, 1);
			if (g_print_message.ready)
				ft_putchar_fd('\n', 1);
			ft_bzero(g_print_message.mess, BUFFER_SIZE);
			g_print_message.overflow = FALSE;
			g_print_message.ready = FALSE;
			g_print_message.bit = 1 << 7;
			g_print_message.position = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	working_act;
	struct sigaction	null_act;

	working_act.sa_sigaction = working_bit_handler;
	null_act.sa_sigaction = null_bit_handler;
	working_act.sa_flags = SA_SIGINFO;
	null_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &working_act, NULL) == -1)
		error("Signal error\n");
	if (sigaction(SIGUSR2, &null_act, NULL) == -1)
		error("Signal error\n");
	print_pid();
	ft_bzero(g_print_message.mess, BUFFER_SIZE);
	server_handler();
}
