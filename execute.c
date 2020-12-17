/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:41:35 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/17 13:17:41 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	builtin(t_list *command, t_shell *shell)
{
	char	*cmd;
	char	**argv;

	cmd = getcmd(command);
	argv = getcommandargv(command);
	if (!ft_strncmp(cmd, "echo", 5))
		return (echo(argv));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (cd(argv, &shell->env));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (pwd(argv));
	else if (!ft_strncmp(cmd, "export", 7))
		return (export(argv, &shell->env));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (unset(argv, &shell->env));
	else if (!ft_strncmp(cmd, "env", 4))
		return (env(argv, shell->env));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (exitshell(argv));
	return (-2);
}

static int
	findexec(char *filename, char **paths, char **executable)
{
	DIR				*stream;
	struct	dirent	*entry;
	size_t			filenamelen;
	size_t			fullpathlen;

	filenamelen = ft_strlen(filename);
	*executable = NULL;
	while (*paths)
	{
		if (!(stream = opendir(*paths)))
			return (-1);
		while ((entry = readdir(stream)))
		{
			if (!ft_strncmp(entry->d_name, filename, filenamelen + 1))
			{
				if (entry->d_type == 8)
				{
					fullpathlen = ft_strlen(*paths) + entry->d_namlen + 2;
					if (!(*executable = malloc(fullpathlen)))
					{
						closedir(stream);
						return (-1);
					}
					ft_strlcpy(*executable, *paths, fullpathlen);
					ft_strlcat(*executable, "/", fullpathlen);
					ft_strlcat(*executable, entry->d_name, fullpathlen);
				}
				if (closedir(stream) == -1)
					return (-1);
				return (entry->d_type == 8);
			}
		}
		if (errno != 0)
			return (-1);
		if (closedir(stream) == -1)
			return (-1);
		paths++;
	}
	return (0);
}

void
	execute(t_list *command, t_shell *shell)
{
	char	*cmd;
	int		builtinret;
	int		execfound;
	char	*executable;
	t_list	*pathenv;
	char	**paths;

	cmd = getcmd(command);
	if (!(ft_strchr(cmd, '/')))
	{
		if ((builtinret = builtin(command, shell)) == -1)
			puterror(strerror(errno));
		else if (builtinret == -2)
		{
			if (!(pathenv = findenv(shell->env, "PATH")))
				return ;	//To do
			if (!(paths = ft_split(getenvval(pathenv), ':')))
				puterror(strerror(errno));
			else if ((execfound = findexec(cmd, paths, &executable)) == -1)
				puterror(strerror(errno));
			else if (execfound)
			{
				if (process(executable, command, shell) == -1)
					puterror(strerror(errno));
			}
			else
				puterror(ERROR_CMD_NOT_FOUND);
			free(executable);
		}
	}
	else if (process(cmd, command, shell) == -1)
		puterror(strerror(errno));
}

void
	cyclecommand(t_list *command, t_shell *shell)
{
	t_list	*current;
	int		commandtype;

	if (!command)
		return ;
	current = command;
	while (current)
	{
		commandtype = getcommandtype(current);
		if (commandtype == SIMPLE)
			execute(current, shell);
		else if (commandtype == PIPE)
		{
			if (minipipe(current, shell) == -1)
				puterror(strerror(errno));
			while (getcommandtype(current) >= PIPE)
				current = current->next;
		}
		else if (commandtype > REDIRECTION)
		{
			if (redirect(current, shell) == -1)
				puterror(strerror(errno));
			while (getcommandtype(current) > REDIRECTION)
				current = current->next;
		}
		else
			puterror(ERROR_CYCLING);
		dup2(shell->stdincpy, STDIN);
		dup2(shell->stdoutcpy, STDOUT);
		current = current->next;
	}
	shell->exit = 0;
}
