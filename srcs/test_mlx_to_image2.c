#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define FENETRE_X 800
#define FENETRE_Y 600
#define WHITE 0xFFFFFF
/*
typedef struct texture
{
    char            *path;
    void            *img;
    int             width;
    int             height;
    int             endian;
    int             bpp;
    int             line_length;
    char            *texture_addr;
}               t_text;

typedef struct data
{
    char            *data_addr;
    void            *img;
    int             endian;
    int             bpp;
    int             line_length;
}               t_dt;

typedef struct var
{
    void        *mlx;
    void        *win;
    t_dt        data;
    t_text      tex;
}   t_var;

void my_mlx_pixel_put2(t_var *var, int x, int y, int color)
{
    if (x >= 0 && x < FENETRE_X && y >= 0 && y < FENETRE_Y) // Vérifie que les coordonnées sont valides
    {
        char *dst = var->data.data_addr + (y * var->data.line_length + x * (var->data.bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_complete_texture(t_var *var)
{
    int x;
    int y;

    y = 0;
    while (y < FENETRE_Y)
    {
        x = 0;
        while (x < FENETRE_X)
        {
            my_mlx_pixel_put2(var, x, y, WHITE);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(var->mlx, var->win, var->data.img, 0, 0);
}

int main(void)
{
    t_var var;

    var.mlx = mlx_init();
    if (!var.mlx)
    {
        fprintf(stderr, "Erreur: Initialisation de mlx échouée.\n");
        return (EXIT_FAILURE);
    }

    var.win = mlx_new_window(var.mlx, FENETRE_X, FENETRE_Y, "textures");
    if (!var.win)
    {
        fprintf(stderr, "Erreur: Création de la fenêtre échouée.\n");
        return (EXIT_FAILURE);
    }

    var.tex.path = "./textures/texture_simon.xpm";
    var.tex.img = mlx_xpm_file_to_image(var.mlx, var.tex.path, &var.tex.width, &var.tex.height);
    if (!var.tex.img)
    {
        fprintf(stderr, "Erreur: Chargement de l'image échoué.\n");
        return (EXIT_FAILURE);
    }

    var.tex.texture_addr = mlx_get_data_addr(var.tex.img, &(var.tex.bpp), &(var.tex.line_length), &(var.tex.endian));
    if (!var.tex.texture_addr)
    {
        fprintf(stderr, "Erreur: Récupération de data_addr de la texture échouée.\n");
        return (EXIT_FAILURE);
    }

    var.data.img = mlx_new_image(var.mlx, FENETRE_X, FENETRE_Y);
    if (!var.data.img)
    {
        fprintf(stderr, "Erreur: Création de l'image échouée.\n");
        return (EXIT_FAILURE);
    }

    var.data.data_addr = mlx_get_data_addr(var.data.img, &(var.data.bpp), &(var.data.line_length), &(var.data.endian));
    if (!var.data.data_addr)
    {
        fprintf(stderr, "Erreur: Récupération de data_addr de l'image échouée.\n");
        return (EXIT_FAILURE);
    }

    printf("apres mlx_get_data_addr\n");
    printf("var.tex.texture_addr = _%p_ <=> %i\n var.tex.bpp = %i, var.tex.line_length = %i, var.tex.endian = %i\n",
        (void *)var.tex.texture_addr, *(int *)var.tex.texture_addr, var.tex.bpp, var.tex.line_length, var.tex.endian);

    draw_complete_texture(&var);
    mlx_loop(var.mlx);
    return (0);
}
*/