/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanbesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:46:31 by tvanbesi          #+#    #+#             */
/*   Updated: 2020/12/14 18:19:46 by tvanbesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	process(t_list *command, t_shell *shell)
{
	pid_t	pid;
	int		stat_loc;
	char	*path;
	char	**argv;
	char	**envp;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		path = getcmd(command);
		if (!(argv = getprocessargv(getcommandargv(command), path)))
			puterror(strerror(errno));
		else if (!(envp = getenvp(shell->env)))
			puterror(strerror(errno));
		else if (execve(path, argv, envp) == -1)
			puterror(strerror(errno));
		exit(0); //Should return correct exit status
	}
	else if (waitpid(pid, &stat_loc, 0) != pid)
		return (-1);
	return (0);
}
