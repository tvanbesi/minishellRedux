/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commandsanity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:24:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/13 12:57:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (NOFILE);
	if (buf.st_mode & S_IFDIR || !(buf.st_mode & S_IXUSR))
	{
		if (buf.st_mode & S_IFDIR)
			return (ISDIR);
		else
			return (NOEXEC);
	}
	return (EXEC);
}

static int
	ret(int r, char *cmd)
{
	if (r == -1)
		return (-1);
	else if (r)
		return (filesanity(cmd));
	else
		return (NOCMD);
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
		if ((r = builtinsanity(content->cmd)))
			return (r);
		if (!(pathenv = findenv(shell->env, "PATH")))
			return (filesanity(content->cmd));
		if (!(paths = ft_split(getenvval(pathenv), ':')))
			return (-1);
		r = findexec(content->cmd, paths, &content->cmd);
		ft_cafree(paths);
		return (ret(r, content->cmd));
	}
	else
		return (filesanity(content->cmd));
}
