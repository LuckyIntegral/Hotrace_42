CC		= cc
CFLAGS	= -Wall -Wextra -Werror

NAME	= hotrace

SRCS	= hotrace.c lib_table.c lib_tree.c reader.c utils.c

OBJS	= ${SRCS:.c=.o}

${NAME}	: ${LIBFT} ${OBJS}
		${CC} -o $@ ${OBJS}

%.o		: %.c
		${CC} ${CFLAGS} -c $< -o $@

all		: ${NAME}

clean	:
		rm -f ${OBJS}

fclean	: clean
		rm -f ${NAME}

re		: fclean all

.PHONY: all, clean, fclean, re
