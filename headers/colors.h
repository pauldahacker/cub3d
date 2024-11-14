/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:21:31 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/14 19:48:28 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "cub3d.h"

// Colors
# define GREY				0x808080
# define BLACK				0x000000
# define WHITE				0xFFFFFF
# define BLUE				0x0000FF
# define YELLOW				0xFFFF00
# define SKY_BLUE			0xADD8E6
# define ELECTRIC_BLUE		0x7df9ff
# define BROWN				0x964B00
# define TEAL 				0x013230
# define GREYFOV			0xC7C7C7
# define GREYFLOOR			0x383838
# define AVOCADO			0x568203
# define BLUEBERRY			0x0041C2
# define CHILI				0xC21807
# define COFFEE				0x351E10
# define CREAM				0xEBD58D
# define ORANGE				0xFFA500

// sRGB coefficients for calculating Luminance
# define SRGB_X				0.2126
# define SRGB_Y				0.7152
# define SRGB_Z				0.0722

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}			t_rgb;

// colors/colors.c
double	linearize(int val);
int		r_g_or_b(t_rgb rgb);
int		contrasting(int color);

#endif
