SRCS		=	builtin.c \
				cd.c \
				debug.c \
				echo.c \
				emptytokenexception.c \
				env.c \
				error.c \
				errorcmd.c \
				execute.c \
				exit.c \
				expand_and_escape.c \
				expandcommand.c \
				export.c \
				findexec.c \
				getidentifier.c \
				getidlen.c \
				getpipeexitstatus.c \
				getprocessargv.c \
				getenvdata.c \
				initshell.c \
				main.c \
				operatorsanity.c \
				parse_command.c \
				parse_token.c \
				pipe.c \
				pipechildren.c \
				process.c \
				prompt.c \
				pwd.c \
				readstdin.c \
				redirection.c \
				signal.c \
				unset.c \
				utils_addtoken.c \
				utils_cd.c \
				utils_command.c \
				utils_commandsanity.c \
				utils_commandsanity2.c \
				utils_del.c \
				utils_env.c \
				utils_expand.c \
				utils_parsing.c \
				utils_quoting.c \
				utils_fd.c \
				utils_getcommand.c \
				utils_getenv.c \
				utils_gettoken.c \
				utils_operator.c \
				utils_token.c \
				utils_redir.c
OBJS		= ${SRCS:.c=.o}
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
NAME		= minishell
RM			= rm -f

%.o :		%.c
			${CC} ${CFLAGS} -Ilibft -c $<
all :		${NAME}
${NAME} :	${OBJS}
			cd libft && make
			clang -o ${NAME} ${OBJS} libft/libft.a
clean :
			${RM} ${OBJS}
			cd libft && make clean
fclean :	clean
			${RM} ${NAME}
			cd libft && make fclean
re :		fclean all
.PHONY :
			all ${NAME} clean fclean re
