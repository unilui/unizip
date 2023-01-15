ENCODER_SRCS	=	encoder_src/* memory/*
ENCODER_OBJS	=	${ENCODER_SRCS:%.c=$(OBJS_DIR)%.o}
ENCODER_NAME	=	encoder
DECODER_SRCS	=	decoder_src/* memory/*
DECODER_OBJS	=	${DECODER_SRCS:%.c=$(OBJS_DIR)%.o}
DECODER_NAME	=	decoder
OBJS_DIR		=	objects/
CC				=	cc
CFLAGS			=	-g -Wall -Wextra -Werror
RM				=	rm -rf

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@

all:		$(ENCODER_NAME) $(DECODER_NAME)

$(DECODER_NAME):	$(DECODER_OBJS)
			@$(CC) $(DECODER_OBJS) -o $(DECODER_NAME) -I includes

$(ENCODER_NAME):	$(ENCODER_OBJS)
			@$(CC) $(ENCODER_OBJS) -o $(ENCODER_NAME) -I includes

clean:
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(ENCODER_NAME)
			@$(RM) $(DECODER_NAME)

re:			fclean all

.PHONY:		all clean fclean re run
