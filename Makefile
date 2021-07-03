CLIENT  = client
SERVER	= server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

CLIENT_SRC = client.c\
			error.c\

SERVER_SRC = server.c\
			error.c\

CLIENT_BSRC = client_bonus.c\
			error.c\

SERVER_BSRC = server_bonus.c\
			error.c\

CC	     = gcc
CFLAGS   = -Wall -Werror -Wextra -I./includes
RM = rm -f

LIBS	 = -L./libft -lft
LIBFT	 = libft.a

MINITALK_HEADER = includes/minitalk.h

CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
SERVER_OBJS = $(SERVER_SRC:.c=.o)
CLIENT_BOBJS = $(CLIENT_BSRC:.c=.o)
SERVER_BOBJS = $(SERVER_BSRC:.c=.o)

all : $(LIBFT) $(CLIENT) $(SERVER)
bonus : $(LIBFT) $(CLIENT_BONUS) $(SERVER_BONUS)

$(LIBFT) :
	@make -C libft

$(CLIENT) : $(CLIENT_OBJS) $(MINITALK_HEADER) $(SERVER) $(LIBFT)
			$(CC) $(FLAGS) $(CLIENT_OBJS) $(LIBS) -o $(CLIENT)

$(SERVER) : $(SERVER_OBJS) $(MINITALK_HEADER) $(LIBFT)
			$(CC) $(FLAGS) $(SERVER_OBJS) $(LIBS) -o $(SERVER)

$(CLIENT_BONUS) : $(CLIENT_BOBJS) $(MINITALK_HEADER) $(SERVER_BONUS) $(LIBFT)
			$(CC) $(FLAGS) $(CLIENT_BOBJS) $(LIBS) -o $(CLIENT_BONUS)

$(SERVER_BONUS) : $(SERVER_BOBJS) $(MINITALK_HEADER) $(LIBFT)
			$(CC) $(FLAGS) $(SERVER_BOBJS) $(LIBS) -o $(SERVER_BONUS)

clean:
	$(RM) $(CLIENT_OBJS)
	$(RM) $(SERVER_OBJS)
	$(RM) $(CLIENT_BOBJS)
	$(RM) $(SERVER_BOBJS)
	@make clean -C libft

fclean: clean
	$(RM) $(CLIENT)
	$(RM) $(SERVER)
	$(RM) $(CLIENT_BONUS)
	$(RM) $(SERVER_BONUS)
	@make fclean -C libft

re: fclean $(CLIENT) $(SERVER)
	@make re -C libft

.PHONY: all clean fclean re
