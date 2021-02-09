/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:13:39 by user42            #+#    #+#             */
/*   Updated: 2021/02/09 14:37:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	getexecdata(char *path, DIR *stream,
	char **executable, struct dirent *entry)
{
	size_t	fullpathlen;

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

int
	findexec(char *filename, char **paths, char **executable)
{
	DIR				*stream;
	struct dirent	*entry;
	size_t			filenamelen;

	filenamelen = ft_strlen(filename);
	while (*paths)
	{
		if ((stream = opendir(*paths)))
		{
			while ((entry = readdir(stream)))
			{
				if (!ft_strncmp(entry->d_name, filename, filenamelen + 1))
				{
					free(*executable);
					getexecdata(*paths, stream, executable, entry);
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
