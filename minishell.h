/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:09:24 by thomasvan         #+#    #+#             */
/*   Updated: 2020/12/21 13:58:33 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft.h"
# include "get_next_line.h"

# define STDIN						0
# define STDOUT						1
# define STDERR						2

# define ERROR_CMD_NOT_FOUND		"Command not found"
# define ERROR_PARSE				"Parse error"
# define ERROR_TOO_MANY_ARG			"Too many arguments"
# define ERROR_NOT_ENOUGH_ARG		"Not enough arguments"
# define ERROR_NAN					"Numeric argument required"
# define ERROR_INVALID_IDENTIFIER	"Invalid identifier"
# define ERROR_GNL					"Prompt fail"
# define ERROR_CYCLING				"Execution cycling error"

//Remove for defense
#include <stdio.h>

typedef	enum	e_tokentype
{
	WORD,
	OPERATOR,
}				t_tokentype;

typedef	struct	s_token
{
	int		type;
	char	*s;
}				t_token;

typedef	enum	e_commandtype
{
	SIMPLE,
	PIPE,
	REDIRECTION,
	REDIRIN,
	REDIRTRUNC,
	REDIRAPPEND
}				t_commandtype;

typedef	struct	s_command
{
	int		type;
	char	*cmd;
	char	**argv;
}				t_command;

typedef	struct	s_env
{
	char	*name;
	char	*val;
}				t_env;

typedef	struct	s_shell
{
	t_list	*env;
	int		stdincpy;
	int		stdoutcpy;
}				t_shell;

//Parsing
t_list	*tokenize(char *input, t_list *env);
t_list	*makecommands(t_list *tokens);

//Tokens
int		addword(t_list **atoken, const char *input, size_t l, t_list *env);
int		addmetachar(t_list **atoken, const char *input);
char	*unquote(char *s, t_list *env);
int		gettokentype(t_list *token);
char	*gettokenstr(t_list *token);
int		gettokencommandtype(t_list *token);
int		emptytokenexception(char *word, t_list *env);
int		isquote(int c);
int		ismetachar(int c);
int		isoperator(int c);
int		isspecialchar(int c);
void	deltoken(void *p);

//Commands
void	assigncmd(t_list *token, t_list *command);
int		assignargv(t_list *token, t_list *command);
int		getcommandtype(t_list *command);
char	*getcmd(t_list *command);
char	**getcommandargv(t_list *command);
char	**getprocessargv(char **argv, char *path);
void	delcommand(void *p);

//Environment
t_list	*findenv(t_list *env, const char *name);
char	*getenvname(t_list *env);
char	*getenvval(t_list *env);
char	**getenvp(t_list *env);
int		addenv(t_list **aenv, char *input);
void	delenv(void *p);

//Execution
void	cyclecommand(t_list *command, t_shell *shell);
void	execute(t_list *command, t_shell *shell);
int		process(char *path, t_list *command, t_shell *shell);
int		minipipe(t_list *command, t_shell *shell);
int		redirect(t_list *command, t_shell *shell);

//Signal
void	sigint(int n);
void	sigquit(int n);

//Builtins
int		cd(char **argv, t_list **aenv);
int		echo(char **argv);
int		pwd(char **argv);
int		env(char **argv, t_list *env);
int		export(char **argv, t_list **aenv);
int		unset(char **argv, t_list **aenv);
int		exitshell(char **argv);

//Error
void	puterror(char *msg);
void	*error(char *msg);

//Debug functions, remove for defense or remove printf
void	showtoken(void *p);
void	showcommand(void *p);
void	showenv(void *p);

extern	int		g_skipeof;
extern	int		g_pid;
extern	int		g_exitstatus;

#endif
