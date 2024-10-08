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

char	*get_next_line(int fd, t_game *game)
{
	char		*line;
	char		*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(game->stash), free(buf), game->stash = NULL, buf = NULL, NULL);
	if (!buf)
		return (NULL);
	line = complete_stash_and_line(fd, game->stash, buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	game->stash = clean_stash_and_line(line);
    if (game->stash)
    {
        printf("------------\nSTASH: [%s]\nbytes: %d\n-----------\n", game->stash, (int)ft_strlen(game->stash));
    }
    return (line);
}