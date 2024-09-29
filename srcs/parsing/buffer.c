#include "parsing.h"

/*
check_add_texture: checks line for errors and adds it as a texture to t_buffer.
It checks if the line is properly formatted, and if the path exists.
It will also check for the extension.
*/
void        check_add_texture(t_buffer *buf, char *line)
{
    int     i;
    char    *texture_path;

    if (!line || ft_strlen(line) < 3)
        handle_error("Error\nTexture Error\n");
    i = 3;
    while (line[i] && is_space(line[i]))
        ++i;
    texture_path = ft_strdup(line + i);
    if (!texture_path)
        handle_error("Malloc Error\n");
    texture_path = trim_end_spaces(texture_path);
    if (!ft_strncmp(line, "NO ", 3) && is_readable(texture_path))
        buf->north_path = texture_path;
    else if (!ft_strncmp(line, "SO ", 3) && is_readable(texture_path))
        buf->south_path = texture_path;
    else if (!ft_strncmp(line, "WE ", 3) && is_readable(texture_path))
        buf->west_path = texture_path;
    else if (!ft_strncmp(line, "EA ", 3) && is_readable(texture_path))
        buf->east_path = texture_path;
    else
        handle_error("Error\nTexture Error\n");
}

void    check_add_color(t_buffer *buf, char *line)
{
    if (!line || ft_strlen(line) < 2)
        handle_error("Error\nColor Error\n");
    if (!ft_strncmp(line, "F ", 2))
        buf->floor_color = return_rgb(line + 2);
    if (!ft_strncmp(line, "C ", 2))
        buf->ceiling_color = return_rgb(line + 2); 
}

/*
add_textures: uses get_next_line N_TEXTURES times or upon error.
For each line, it uses check_and_add and adds the texture to buffer if correct.
*/
void        add_textures(int fd, t_buffer *buf)
{
    char    *line;
    int     n_line;

    n_line = 0;
    line = get_next_line(fd);
    while (line && n_line < N_TEXTURES)
    {
        if (*line != '\n')
        {
            check_add_texture(buf, line);
            ++n_line;
        }
        free(line);
        line = get_next_line(fd);
    }
    if (line)
        free(line);
    if (n_line != N_TEXTURES)
        handle_error("Error\nTexture Error\n");
}

void        add_colors(int fd, t_buffer *buf)
{
    char    *line;
    int     n_line;

    n_line = 0;
    line = get_next_line(fd);
    while (line && n_line < N_COLORS)
    {
        if (*line != '\n')
        {
            check_add_color(buf, line);
            ++n_line;
        }
        free(line);
        line = get_next_line(fd);
    }
    if (line)
        free(line);
    if (n_line != N_COLORS)
        handle_error("Error\nColor Error\n");
}

t_buffer    *buffer(int fd)
{
    t_buffer    *buf;

    buf = (t_buffer *)malloc(sizeof(t_buffer));
    if (!buf)
        handle_error("Malloc Error\n");
    add_textures(fd, buf);
    add_colors(fd, buf);
    printf("NORTH: %s\n", buf->north_path);
    printf("SOUTH: %s\n", buf->south_path);
    printf("WEST: %s\n", buf->west_path);
    printf("EAST: %s\n", buf->east_path);
    printf("FLOOR COLOR: %d\n", buf->floor_color);
    printf("CEILING COLOR: %d\n", buf->ceiling_color);
    return (buf);
}