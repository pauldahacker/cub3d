# define FENETRE_X	128
# define FENETRE_Y	128

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <cub3d.h>

/*typedef struct textures
{
	char			*path;
	int				width;
	int				height;
	int				endian;
	int				bpp;
	int				line_length;//quelle est la difference entre line_length/width/height ?
	unsigned char	*data;
	void			*img;//qu'est ce que c'est ?
}				t_texture;*/


typedef struct texture
{
	char			*path;//chemin de la texture a charger 
	void			*img;//l'adresse memoire de la texture xpm en image
	int				width;//largeur de la texture, ici 64
	int				height;//hauteur de la texture, ici 64
	//les 4 premieres variables sont plutot reserves pour l'image xpm en soi
	//les 4 suivants sont plutot reserves pour comment on va imprimer le pixel sur l'image
	int				endian;
	int				bpp;
	int				line_length;
	char			*data;
}				t_text;

typedef struct var
{
	void		*mlx;
	void		*win;
	t_text		tex;
}	t_var;

void	my_mlx_pixel_put2(t_var *var, int x, int y, int color)
{
	char	*dst;

	printf("pixel_put 1");
	dst = var->tex.data + (y * var->tex.line_length + x
			* (var->tex.bpp / 8));
	printf("pixel_put 2");
	*(unsigned int *)dst = color;
	printf("pixel_put 3\n");
}

//on veut creer une fonction, qui au lieu de dessiner la texture 64 par 64
//elle la dessine FENETRE_X par FENETRE_Y
//	var->tex.img = mlx_xpm_file_to_image(var->mlx, "./textures/wall_4.xpm", &var->tex.width, &var->tex.height);
void	draw_complete_texture(t_var *var)
{
	int	scale_x;
	int	scale_y;
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	// static int i = 0;
	// int			j = 1;

	scale_x = FENETRE_X / var->tex.width;
	scale_y = FENETRE_Y / var->tex.height;
	y = 0;
	while (y < FENETRE_Y)
	{
		x = 0;
//		tex_y = (y / scale_y) % var->tex.height;
		tex_x = 0;
		while (x < FENETRE_X)
		{
			if (tex_x < scale_x)
			{
				color = *(int *)(var->tex.data + (y * var->tex.line_length) + (tex_x * (var->tex.bpp / 8)));
				my_mlx_pixel_put2(var, x, y, color);
				tex_x++;
			}
			else
				break ;
			x++;
		}
		y++;
	}
	(void)scale_y;
	(void)tex_y;
	mlx_put_image_to_window(var->mlx, var->win, var->tex.img, 0, 0);
}

//	var.tex.img = mlx_new_image(var.mlx, FENETRE_X, FENETRE_Y);
int	main(void)
{
	t_var	var;

	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, FENETRE_X, FENETRE_Y, "textures");
	var.tex.path = ft_strdup("./textures/texture_simon.xpm");
	var.tex.img = mlx_xpm_file_to_image(var.mlx, var.tex.path, &var.tex.width, &var.tex.height);
//	mlx_put_image_to_window(var.mlx, var.win, var.tex.img, 0, 0);
	// printf("avant mlx_get_data_addr\n");
	// printf("var.tex.data = %i\n var.tex.bpp = %i, var.tex.line_length = %i, var.tex.endian = %i\n",
	// *(int *)var.tex.data, var.tex.bpp, var.tex.line_length, var.tex.endian);
//	var.tex.data = mlx_get_data_addr(var.tex.img, &(var.tex.bpp), &(var.tex.line_length), &(var.tex.endian));
	// printf("apres mlx_get_data_addr\n");
	// printf("var.tex.data = %i\n var.tex.bpp = %i, var.tex.line_length = %i, var.tex.endian = %i\n",
	// *(int *)var.tex.data, var.tex.bpp, var.tex.line_length, var.tex.endian);
	draw_complete_texture(&var);
	mlx_loop(var.mlx);
	return (0);
}
