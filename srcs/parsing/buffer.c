#include "cub3d.h"

static int	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == ' '
		|| c == '\f' || c == '\r' || c == '\v');
}

void        check_and_add(t_buffer *buf, char *line)
{
    int i;

    i = 0;
    if (ft_strncmp(line, "NO ", 3))
    {
        while ((line + 3)[i] && is_space((line + 3)[i]))
            ++i;
    }
}

void        add_textures(int fd, t_buffer *buf)
{
    char    *line;
    int     n_line;

    n_line = 0;
    line = get_next_line(fd);
    while (line)
    {

    }
}

t_buffer    *buffer(int fd)
{
    t_buffer    *buf;

    buf = (t_buffer *)malloc(sizeof(t_buffer));
    if (!buf)
        handle_error("Malloc Error\n");

}