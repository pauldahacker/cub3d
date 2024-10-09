/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:17:31 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/09 15:17:32 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*clean_stash_and_line(char *line_buf)
{
	char	*stash;
	ssize_t	i;

	i = 0;
	while (line_buf[i] != '\n' && line_buf[i] != '\0')
		i++;
	if (line_buf[i] == 0 || line_buf[1] == 0)
		return (NULL);
	stash = ft_substr(line_buf, i + 1, ft_strlen(line_buf) - i);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	line_buf[i + 1] = 0;
	return (stash);
}

static char	*complete_stash_and_line(int fd, char *stash, char *buf)
{
	ssize_t	read_result;
	char	*tmp;

	read_result = 1;
	while (read_result > 0)
	{
		read_result = read(fd, buf, BUFFER_SIZE);
		if (read_result == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (read_result == 0)
			break ;
		buf[read_result] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stash);
}

/*
get_next_line has been modified to take game as an added parameter.
Helps a lot cause we store the stash (static variable in older version)
in the t_game structure (see parsing.h).
This allows to free the stash the moment we read an error in the .cub file,
instead of having to read the full file even when an error was found.
*/
char	*get_next_line2(int fd, t_game *game)
{
	char		*line;
	char		*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(game->stash), free(buf), game->stash = NULL,
			buf = NULL, NULL);
	if (!buf)
		return (NULL);
	line = complete_stash_and_line(fd, game->stash, buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	game->stash = clean_stash_and_line(line);
	return (line);
}
