#include "parsing.h"

int	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == ' '
		|| c == '\f' || c == '\r' || c == '\v');
}

/*
Returns str with ending whitespaces removed.
e.g. "Hello I am Paul  \n \t " --> "Hello I am Paul"
*/
char    *trim_end_spaces(char *str)
{
    int len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    while (is_space(str[len - 1]))
        str[len - 1] = '\0';
    return (str);
}

/*
Takes line, which should be formatted like this: "r,g,b"
Where r,g,b represent numbers in range [0,255].
Returns color in decimal form, or exits with error if not correctly formatted.
*/
int     return_rgb(char *line)
{
    int r;
    int g;
    int b;

    r = ft_atoi(line);
    line = ft_strchr(line, ',') + 1;
    g = ft_atoi(line);
    line = ft_strchr(line, ',') + 1;
    b = ft_atoi(line);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        handle_error("Error\nColor Error\n");
    return (r << 16 | g << 8 | b);
}