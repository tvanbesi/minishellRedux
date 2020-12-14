SRCS		= ${wildcard *.c}
OBJS		= ${SRCS:.c=.o}
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
NAME		= libft.a
RM			= rm -f

%.o :		%.c
			${CC} ${CFLAGS} -c $<
all :		${NAME}
${NAME} :	${OBJS}
			ar rc ${NAME} ${OBJS}
clean :
			${RM} ${OBJS}
fclean :	clean
			${RM} ${NAME}
re :		fclean all
.PHONY :
			all ${NAME} clean fclean re
