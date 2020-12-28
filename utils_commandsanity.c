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
	findexec(char *filename, char **paths, char **executable)
{
	DIR				*stream;
	struct	dirent	*entry;
	size_t			filenamelen;
	size_t			fullpathlen;

	filenamelen = ft_strlen(filename);
	while (*paths)
	{
		if ((stream = opendir(*paths)))
		{
			while ((entry = readdir(stream)))
			{
				if (!ft_strncmp(entry->d_name, filename, filenamelen + 1))
				{
					if (entry->d_type == DT_REG)
					{
						fullpathlen = ft_strlen(*paths) + ft_strlen(entry->d_name) + 2;
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
					return (entry->d_type == DT_REG);
				}
			}
			if (closedir(stream) == -1)
				return (-1);
		}
		paths++;
	}
	return (0);
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
	struct	stat	buf;

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
		if ((r = builtinsanity(content->cmd)))
			return (r);
		if (!(pathenv = findenv(shell->env, "PATH")))
			return (filesanity(content->cmd));
		if (!(paths = ft_split(getenvval(pathenv), ':')))
			return (-1);
		if ((r = findexec(content->cmd, paths, &content->cmd)) == -1)
			return (-1);
		else if (r)
			return (filesanity(content->cmd));
		else
			return (NOCMD);
	}
	else
		return (filesanity(content->cmd));
}
