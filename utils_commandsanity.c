/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commandsanity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:24:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 12:21:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	iserror(int n)
{
	return (n > ERROR_START && n < ERROR_END);
}

int
	isbuiltin(int n)
{
	return (n > BUILTIN_START && n < BUILTIN_END);
}

static int
	builtinsanity(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (PWD);
	else if (!ft_strncmp(cmd, "export", 7))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (UNSET);
	else if (!ft_strncmp(cmd, "env", 4))
		return (ENV);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (EXITSHELL);
	else
		return (0);
}

static int
	filesanity(char *filename)
{
	struct stat	buf;

	if (stat(filename, &buf) == -1)
		return (-1);
	if (buf.st_mode & S_IFDIR || !(buf.st_mode & S_IXUSR))
	{
		if (buf.st_mode & S_IFDIR)
			return (ISDIR);
		else
			return (NOEXEC);
	}
	return (EXEC);
}

int
	commandsanity(t_list *command, t_shell *shell)
{
	t_command	*content;
	int			r;
	t_list		*pathenv;
	char		**paths;

	content = command->content;
	if (!content->cmd)
		return (EMPTY);
	if (!ft_strchr(content->cmd, '/'))
	{
		r = builtinsanity(content->cmd);
		if (r)
			return (r);
		pathenv = findenv(shell->env, "PATH");
		if (!pathenv)
			return (filesanity(content->cmd));
		paths = ft_split(getenvval(pathenv), ':');
		if (!paths)
			return (-1);
		r = findexec(content->cmd, paths, &content->cmd);
		if (r == -1)
			return (-1);
		else if (r)
			return (filesanity(content->cmd));
		else
			return (NOCMD);
	}
	else
		return (filesanity(content->cmd));
}
