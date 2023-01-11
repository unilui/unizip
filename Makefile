SRCS		= unizip.c get_symbols.c get_hufftree.c utils.c

OBJS		= ${SRCS:%.c=$(OBJS_DIR)%.o}
OBJS_DIR	= objects/
NAME		= encoder
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -rf

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -g -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@${CC} $(CFLAGS) $(OBJS) -g -o $(NAME)

clean:
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

test:		re
			@./$(NAME)

.PHONY:		all clean fclean re
