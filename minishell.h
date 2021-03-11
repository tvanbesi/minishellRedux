/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasvanbesien <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 17:09:24 by thomasvan         #+#    #+#             */
/*   Updated: 2021/03/11 02:04:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"

# define STDIN						0
# define STDOUT						1
# define STDERR						2

# define EXIT_STAT_SUCCESS			0
# define EXIT_STAT_FAIL				1
# define EXIT_STAT_ERRORPARSE		2
# define EXIT_STAT_NOEXEC			126
# define EXIT_STAT_NOCMD			127

# define ERROR_NOCMD				"Command not found"
# define ERROR_PARSE				"Parse error"
# define ERROR_BADREDIR				"Ambiguous redirect"
# define ERROR_TOO_MANY_ARG			"Too many arguments"
# define ERROR_NOT_ENOUGH_ARG		"Not enough arguments"
# define ERROR_NAN					"Numeric argument required"
# define ERROR_INVALID_IDENTIFIER	"Invalid identifier"
# define ERROR_INVALID_OPTION		"Invalid option"
# define ERROR_GNL					"Prompt fail"
# define ERROR_CYCLING				"Execution cycling error"
# define ERROR_ISDIR				"is a directory"
# define ERROR_ISNEXEC				"permission denied"
# define ERROR_NOHOME				"HOME not set"
# define ERROR_NOFILE				"no such file or directory"
# define ERROR_FATAL				"Fatal error"

# define BUFFER_SIZE_ERRORMSG		4096

typedef	enum		e_command_r
{
	ERROR_START,
	NOCMD,
	NOEXEC,
	ISDIR,
	NOFILE,
	ERROR_END,
	SUCCESS_START,
	EMPTY,
	EXEC,
	BUILTIN_START,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXITSHELL,
	BUILTIN_END,
	SUCCESS_END
}					t_command_r;

typedef struct		s_readstdindata
{
	char			buf[2];
	char			*tmp;
	int				lenfactor;
	size_t			len;
}					t_readstdindata;

typedef struct		s_unquotedata
{
	size_t			l;
	size_t			i;
	size_t			j;
	int				q;
	char			*param;
}					t_unquotedata;

typedef struct		s_parsedata
{
	int				i;
	int				j;
	int				qt;
	int				idlen;
	int				escape;
	unsigned int	s;
	size_t			l;
}					t_parsedata;

typedef	enum		e_prompt_r
{
	OK,
	ERROR,
	EXIT,
	BREAK
}					t_prompt_r;

typedef	enum		e_tokentype
{
	WORD,
	OPERATOR
}					t_tokentype;

typedef	struct		s_token
{
	int				type;
	char			*s;
}					t_token;

typedef enum		e_redirtype
{
	REDIRIN,
	REDIRTRUNC,
	REDIRAPPEND
}					t_redirtype;

typedef struct		s_redir
{
	int				type;
	t_list			*fd_str;
}					t_redir;

typedef	enum		e_commandtype
{
	SIMPLE,
	PIPE
}					t_commandtype;

typedef	struct		s_command
{
	int				type;
	t_list			*argv;
	t_list			*redirections;
}					t_command;

typedef	struct		s_env
{
	char			*name;
	char			*val;
}					t_env;

typedef	struct		s_shell
{
	t_list			*env;
	int				stdincpy;
	int				stdoutcpy;
	int				(*b[7])(t_list *argv, t_list **aenv);
	int				exit;
}					t_shell;

t_shell				*initshell(char **envp);

/*
***	DEBUG
*/

void				showtoken(void *p);
void				showcommand(void *p);

/*
***	PARSING
*/

char				*readstdin(void);
int					prompt(char **line);
int					expandcommand(t_list *command, t_list *env);
char				*expand(char *s, t_list *env);
t_list				*tokenize(char *input);
t_list				*parse_token(char *input);
t_list				*parse_token_expanded(char *input);
t_list				*parse_command(t_list *token);
int					isidentifiervalid(char *s);
int					shouldescape(int c1, int c2, int qt);
int					shouldexpand(int c1, int c2, int qt);
void				expansion(char *dst, char *src, t_list *env, t_parsedata *pd);
void				expand_and_escape(char **dst, char *src, int idlen, t_list *env);
int					expandtoken(t_list **dst, t_list *src, t_list *env);
int					parse_redircmd(t_list *token, t_list *command);
int					trimcommand(t_list **argv);
int					parse_redir(t_list *current, t_list *env);
int					operatorsanity(t_list *token);
void				*errorparse(t_list **token);
void				*fail(t_list **token);
int					addword(t_list **r, char *input, t_parsedata *pd);
int					addwordexpanded(t_list **r, char *input, t_parsedata *pd);
int					openquote(char *s, t_parsedata *pd);
int					closequote(char *s, t_parsedata *pd, t_list **r);

/*
***	TOKENS
*/

t_list				*newtoken(int type);
int					addtoken(t_list **atoken, const char *input, size_t l, int type);
int					addnulltoken(t_list **atoken);
int					addtokenexpanded(t_list **atoken, const char *input, size_t l, int type);
t_token				*tokendup(void *p);
char				*getidentifier(char *s, t_list *env);
size_t				getidlen(char *s, t_list *env);
//char				*unquote(char *s, t_list *env);
int					gettokentype(t_list *token);
char				*gettokenstr(t_list *token);
int					gettokencommandtype(t_list *token);
int					emptytokenexception(char *word, t_list *env);
int					isquote(int c);
int					ismetachar(int c);
int					isoperator(int c);
int					isspecialchar(int c);
int					isrediroperator(t_list *token);
int					ispipeorsemicolon(t_list *token);
int					isvalidoperator(t_list *token);
void				deltoken(void *p);

/*
***	COMMANDS
*/

void				assigncmd(t_list *token, t_list *command);
int					assignargv(t_list *token, t_list *command);
int					getcommandtype(t_list *command);
int					getargc(char **argv);
char				*getcmd(t_list *command);
t_list				*getcommandredir(t_list *command);
int					getredirtype(t_list *redir);
t_token				*getredirtoken(t_list *redir);
char				*getredirstr(t_list *redir);
t_list				*getredirtokenlst(t_list *redir);
t_list				*getcommandargv(t_list *command);
char				**getprocessargv(t_list *argv, char *path);
t_list				*newcommand(int type);
t_list				*newredir(char *s);
void				delcommand(void *p);
void				delredir(void *p);

/*
***	ENVIRONMENT
*/

t_list				*findenv(t_list *env, const char *name);
char				*getenvname(t_list *env);
char				*getenvval(t_list *env);
char				**getenvp(t_list *env);
int					getenvdata(char *input, char **val,
					char **name, t_list **aenv);
int					addenv(t_list **aenv, char *input);
void				delenv(void *p);

/*
***	COMMAND SANITY
*/

int					commandsanity(t_list *command, t_shell *shell);
int					csanityextracheck(t_list *token);
int					findexec(char *filename, char **paths, char **executable);
int					iserror(int n);
int					isbuiltin(int n);

/*
***	EXECUTION
*/

void				cyclecommand(t_list *command, t_shell *shell);
void				execute(t_list *command, t_shell *shell);
void				builtin(t_list *command, t_shell *shell, int csanity);
int					process(t_list *command, t_shell *shell);
int					minipipe(t_list *command, t_shell *shell);
int					minipipechildren(t_list *command, t_shell *shell, int *fd, int npipe);
int					getpipeexitstatus(int nchildren, int *pid_children);
void				closefd(int *fd, int n);
int					redirect(t_list *command);

/*
***	SIGNALS
*/

void				sigint(int n);
void				sigquit(int n);

/*
***	BUILTINS
*/

int					cd(t_list *argv, t_list **aenv);
int					setpwdenv(t_list **aenv, char *cd_arg);
int					echo(t_list *argv, t_list **aenv);
int					pwd(t_list *argv, t_list **aenv);
int					env(t_list *argv, t_list **aenv);
int					export(t_list *argv, t_list **aenv);
int					unset(t_list *argv, t_list **aenv);
int					exitshell(t_list *argv, t_list **aenv);

/*
***	ERROR
*/

void				puterrorcmd(char *cmd, int csanity);
void				puterror(char *msg);
void				*error(char *msg);

/*
***	MISC
*/

void				collapsestr(char *s, int i);

extern	int			g_pid;
extern	int			g_exitstatus;

#endif
