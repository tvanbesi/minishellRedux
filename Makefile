SRCS		= ${wildcard *.c}
OBJS		= ${SRCS:.c=.o}
SRCS_LFT	= ${widlcard libft/*.c}
OBJS_LFT	= ${SRCS_LFT:.c=.o}
LFT			= libft/libft.a
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
NAME		= minishell
RM			= rm -f

%.o :		%.c
			${CC} ${CFLAGS} -Ilibft -c $<
all :		${LFT} ${NAME}
${LFT} :	${OBJS_LFT}
			cd libft && make
${NAME} :	${OBJS} ${LFT}
			clang -o ${NAME} ${OBJS} libft/libft.a
clean :
			${RM} ${OBJS}
			cd libft && make clean
fclean :	clean
			${RM} ${NAME}
			cd libft && make fclean
re :		fclean all
.PHONY :
			all ${NAME} ${LFT} clean fclean re
