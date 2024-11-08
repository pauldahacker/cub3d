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
	void			*img;//l'adresse memoire de la texture xpm en image ⚠️ a initialiser avant d'utiliser mlx_get_data_addr
	int				width;//largeur de la texture, ici 64
	int				height;//hauteur de la texture, ici 64
	//les 4 premieres variables sont plutot reserves pour l'image xpm en soi
	//les 4 suivants sont plutot reserves pour comment on va imprimer le pixel sur l'image
	int				endian;
	int				bpp;
	int				line_length;
	char			*texture_addr;
}				t_text;

typedef struct data
{
	char			*data_addr;
	void			*img;//a initialiser avant d'utiliser mlx_get_data_addr
	int				endian;
	int				bpp;
	int				line_length;
}				t_dt;

typedef struct var
{
	void		*mlx;
	void		*win;
	t_dt		data;
	t_text		tex;
}	t_var;

void	my_mlx_pixel_put2(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->data.data_addr + (y * var->data.line_length + x	* (var->data.bpp / 8));
	*(unsigned int *)dst = color;
}

//on veut creer une fonction, qui au lieu de dessiner la texture 64 par 64
//elle la dessine FENETRE_X par FENETRE_Y
//	var->tex.img = mlx_xpm_file_to_image(var->mlx, "./textures/wall_4.xpm", &var->tex.width, &var->tex.height);
void	draw_complete_texture(t_var *var)
{
	// int	scale_x;
	// int	scale_y;
	int	x;
	int	y;
	int	color;
	int	check_x;

	// scale_x = FENETRE_X / var->tex.width;
	// scale_y = FENETRE_Y / var->tex.height;
	y = 0;
	while (y < FENETRE_Y)
	{
		x = 0;
		check_x = 0;
		while (x < FENETRE_X)
		{
			if (check_x < 2)
			{
				color = *(int *)(var->data.data_addr + (y * var->data.line_length) + (x * (var->data.bpp / 8)));
				my_mlx_pixel_put2(var, x, y, color);
				check_x++;
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(var->mlx, var->win, var->tex.img, 0, 0);
}

//	var.tex.img = mlx_new_image(var.mlx, FENETRE_X, FENETRE_Y);
	// printf("apres mlx_get_data_addr\n");
	// printf("var.tex.texture_addr = _%s_ <=> %i\n var.tex.bpp = %i, var.tex.line_length = %i, var.tex.endian = %i\n",
	// var.tex.texture_addr, *(int *)var.tex.texture_addr, var.tex.bpp, var.tex.line_length, var.tex.endian);
int	main(void)
{
	t_var	var;

	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, FENETRE_X, FENETRE_Y, "textures");
	var.tex.path = ft_strdup("./textures/texture_simon.xpm");
	var.tex.img = mlx_xpm_file_to_image(var.mlx, var.tex.path, &var.tex.width, &var.tex.height);
	var.tex.texture_addr = mlx_get_data_addr(var.tex.img, &(var.tex.bpp), &(var.tex.line_length), &(var.tex.endian));
	var.data.img = mlx_new_image(var.mlx, FENETRE_X, FENETRE_Y);
	var.data.data_addr = mlx_get_data_addr(var.data.img, &(var.data.bpp), &(var.data.line_length), &(var.data.endian));
	draw_complete_texture(&var);
	mlx_loop(var.mlx);
	return (0);
}
