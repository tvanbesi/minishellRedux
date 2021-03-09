/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:13:39 by user42            #+#    #+#             */
/*   Updated: 2021/03/09 21:24:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	getexecdata(char *path, DIR *stream,
	char **executable, struct dirent *entry)
{
	size_t	fullpathlen;

	free(*executable);
	if (entry->d_type != DT_REG)
		return (0);
	fullpathlen = ft_strlen(path) + ft_strlen(entry->d_name) + 2;
	if (!(*executable = malloc(fullpathlen)))
	{
		closedir(stream);
		return (-1);
	}
	ft_strlcpy(*executable, path, fullpathlen);
	ft_strlcat(*executable, "/", fullpathlen);
	ft_strlcat(*executable, entry->d_name, fullpathlen);
	return (0);
}

static int
	isdirectory(char *d_name, char *filename)
{
	return (!ft_strncmp(d_name, filename, ft_strlen(filename) + 1));
}

int
	findexec(char *filename, char **paths, char **executable)
{
	DIR				*stream;
	struct dirent	*entry;
	int				r;

	while (*paths)
	{
		if ((stream = opendir(*paths)))
		{
			while ((entry = readdir(stream)))
			{
				if (isdirectory(entry->d_name, filename))
				{
					getexecdata(*paths, stream, executable, entry);
					r = entry->d_type == DT_REG;
					if (closedir(stream) == -1)
						return (-1);
					return (r);
				}
			}
			if (closedir(stream) == -1)
				return (-1);
		}
		paths++;
	}
	return (0);
}
