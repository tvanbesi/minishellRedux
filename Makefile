SRCS		= ${wildcard *.c}
OBJS		= ${SRCS:.c=.o}
CC			= clang
CFLAGS		= 
#CFLAGS		= -Wall -Wextra -Werror
NAME		= minishell
RM			= rm -f

%.o :		%.c
			${CC} ${CFLAGS} -Ilibft -c $<
all :		${NAME}
${NAME} :	${OBJS}
			clang -o ${NAME} ${OBJS} libft/libft.a
clean :
			${RM} ${OBJS}
fclean :	clean
			${RM} ${NAME}
re :		fclean all
.PHONY :
			all ${NAME} clean fclean re
