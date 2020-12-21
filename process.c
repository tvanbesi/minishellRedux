/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:46:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/21 15:32:18 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	process(char *path, t_list *command, t_shell *shell)
{
	int				stat_loc;
	struct	stat	buf;
	char			**argv;
	char			**envp;

	if (stat(path, &buf) == -1)
		return (-1);
	if (buf.st_mode & S_IFDIR || !(buf.st_mode & S_IXUSR))
	{
		if (buf.st_mode & S_IFDIR)
			puterror(ERROR_ISDIR);
		else
			puterror(ERROR_ISNEXEC);
		g_exitstatus = 126;
		return (0);
	}
	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		if (!(argv = getprocessargv(getcommandargv(command), path)))
			puterror(strerror(errno));
		else if (!(envp = getenvp(shell->env)))
			puterror(strerror(errno));
		else if (execve(path, argv, envp) == -1)
			puterror(strerror(errno));
		exit(0); //Should return correct exit status
	}
	else if (waitpid(g_pid, &stat_loc, 0) != g_pid)
		return (-1);
	return (0);
}
