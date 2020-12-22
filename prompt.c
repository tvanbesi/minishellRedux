#include "minishell.h"

static char
	*readstdin(void)
{
	char	*line;
	char	buf[2];
	char	*tmp;
	int		lenfactor;
	size_t	len;
	size_t	r;

	if (!(line = malloc(BUFFER_SIZE)))
		return (NULL);
	lenfactor = 1;
	len = BUFFER_SIZE;
	ft_bzero(line, len);
	buf[1] = '\0';
	while ((r = read(STDIN, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			return (line);
		else if (ft_strlcat(line, buf, len) >= len)
		{
			lenfactor++;
			len = BUFFER_SIZE * lenfactor;
			tmp = line;
			if (!(line = malloc(len)))
			{
				free(tmp);
				return (NULL);
			}
			ft_bzero(line, len);
			ft_strlcpy(line, tmp, len);
			free(tmp);
		}
	}
	if (r == 0)
	{
		write(STDOUT, "exit", 4);
		exit(EXIT);
	}
	else
		return (NULL);
}

int
	prompt(char **line)
{
	int		fd[2];
	int		stat_loc;
	int		gnl;

	if (pipe(fd) == -1)
		return (-1);
	if ((g_pid = fork()) == -1)
		return (-1);
	if (g_pid == 0)
	{
		*line = readstdin();
		write(fd[1], *line, ft_strlen(*line));
		write(fd[1], "\n", 1);
		close(fd[0]);
		close(fd[1]);
		if (line == NULL)
			exit(ERROR);
		else
			exit(OK);
	}
	else if (waitpid(g_pid, &stat_loc, 0) != g_pid)
		return (-1);
	g_pid = 0;
	if (WIFEXITED(stat_loc))
	{
		if (WEXITSTATUS(stat_loc) == ERROR)
		{
			g_exitstatus = EXIT_STAT_FAIL;
			return (-1);
		}
		else if (WEXITSTATUS(stat_loc) == BREAK)
		{
			g_exitstatus = 128 + SIGINT;
			if (!(*line = ft_strdup("")))
				return (-1);
		}
		else if (WEXITSTATUS(stat_loc) == EXIT)
			exit(EXIT_STAT_SUCCESS);
		else if (WEXITSTATUS(stat_loc) == OK)
		{
			while ((gnl = get_next_line(fd[0], line)) != 1)
				if (gnl == -1)
					return (-1);
		}
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

