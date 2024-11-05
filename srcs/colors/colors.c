/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:51:50 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/04 10:51:51 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

/*
add_shade: adds an alpha value to color based on the given shade intensity
shade should be a value between 0 and 1, representing a percentage (1 - opacity).
How it works:
Colors were treated as
		R		|		G		|		B
	[xxxxxxxx]	|	[xxxxxxxx]	|	[xxxxxxxx]
 {0,255} (<<16) | {0,255} (<<8) |	 {0,255}

We simply add
		A		|		R		|		G		|		B
	[xxxxxxxx]	|	[xxxxxxxx]	|	[xxxxxxxx]  |	[xxxxxxxx]
 {0,255} (<<24) |{0,255} (<<16) | {0,255} (<<8)	|	 {0,255}

!!! NOTE !!!
The way ARGB is read depends on the system we are using.
After testing:
A = 255 (or 11111111 in binary or 0xFF in hex)
-> means FULL opacity on Linux
-> means NO opacity on MacOS
*/
int	add_shade(double shade, int color)
{
	return ((int)((1 - shade) * 0xFF) << 24 | color);
}

/*
linearize: linearizes a standard RGB (sRGB) component value
It first normalizes val to a range of 0-1, then applies gamma correction
to convert it to a linear space using the sRGB formula.
For more info on the formula:
https://entropymine.com/imageworsener/srgbformula/
*/
double	linearize(int val)
{
	double	norm;

	norm = val / 255.0;
	if (norm <= 0.04045)
		return (norm / 12.92);
	return (pow((norm + 0.055) / 1.055, 2.4));
}

/*
r_g_or_b: returns contrasting color based on hue of the given RGB values.
Contrasting color depends on the most dominant component in RGB.
When the maximum component is RED, return green contrast.
When the maximum component is GREEN or BLUE, return red contrast.
If the color is neutral or grayscale (delta = 0), return blue contrast.
This function should only be used on low saturation colors.
*/
int	r_g_or_b(t_rgb rgb)
{
	double	c_max;
	double	c_min;
	double	delta;

	c_max = fmax(fmax(rgb.r, rgb.g), rgb.b);
	c_min = fmin(fmin(rgb.r, rgb.g), rgb.b);
	delta = c_max - c_min;
	if (delta == 0)
		return (BLUEBERRY);
	else if (c_max == rgb.r)
		return (AVOCADO);
	else
		return (CHILI);
}

/*
return_contrasting: takes any color and returns a contrasting color.
It first calculates saturation:
If the saturation is HIGH (above 0.5), we return either black or white.
	This choice depends on the luminance of the color, which we calculate
	using the Rec. 709 standard coefficients for relative luminance:
	https://en.wikipedia.org/wiki/Rec._709#Luma_coefficients
	If the luminance is high (above 0.5), we return black. Else return white.
If the saturation is LOW, we use r_g_or_b to find a contrasting color.
*/
int	contrasting(int color)
{
	t_rgb	rgb;
	double	sat;
	double	lum;
	double	max_val;
	double	min_val;

	rgb.r = linearize((color >> 16) & 0xFF);
	rgb.g = linearize((color >> 8) & 0xFF);
	rgb.b = linearize(color & 0xFF);
	max_val = fmax(fmax(rgb.r, rgb.g), rgb.b);
	min_val = fmin(fmin(rgb.r, rgb.g), rgb.b);
	if (max_val == 0)
		return (WHITE);
	sat = (max_val - min_val) / max_val;
	if (sat > 0.5)
	{
		lum = SRGB_X * rgb.r + SRGB_Y * rgb.g + SRGB_Z * rgb.b;
		if (lum > 0.5)
			return (BLACK);
		return (WHITE);
	}
	return (r_g_or_b(rgb));
}
