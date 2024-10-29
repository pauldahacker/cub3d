#include <math.h>
#include "cub3d.h"

int add_shade(double shade, int color)
{
    return ((int)(shade * 0xFF) << 24 | color);
}

double linearize(int val)
{
    double norm = val / 255.0;
    if (norm <= 0.04045)
        return (norm / 12.92);
    return (pow((norm + 0.055) / 1.055, 2.4));
}

int b_or_w(int color)
{
    t_rgb rgb;
    double Y;

    rgb.r = linearize((color >> 16) & 0xFF);
    rgb.g = linearize((color >> 8) & 0xFF);
    rgb.b = linearize(color & 0xFF);
    Y = SRGB_X * rgb.r + SRGB_Y * rgb.g + SRGB_Z * rgb.b;
	if (Y >= 0.5)
		return (BLACK);
    return (WHITE);
}

int r_g_or_b(t_rgb rgb)
{
    double c_max = fmax(fmax(rgb.r, rgb.g), rgb.b);
    double c_min = fmin(fmin(rgb.r, rgb.g), rgb.b);
    double delta = c_max - c_min;
    double hue;

    if (delta == 0)
        hue = 0;
    else if (c_max == rgb.r)
        hue = 60 * fmod(((rgb.g - rgb.b) / delta), 6);
    else if (c_max == rgb.g)
        hue = 60 * (((rgb.b - rgb.r) / delta) + 2);
    else
        hue = 60 * (((rgb.r - rgb.g) / delta) + 4);

    if (hue < 0)
        hue += 360;

    if (hue >= 0 && hue < 60)      // Reds and reddish hues
        return (AVOCADO);          // Return contrasting green
    if (hue >= 60 && hue < 180)    // Greens and yellow-greens
        return (CHILI);            // Return contrasting red
    if (hue >= 180 && hue <= 300)  // Blues and blue-greens
        return (CHILI);            // Return contrasting red
    return (AVOCADO);              // Fallback for purples
}

int return_contrasting(int color)
{
    t_rgb rgb;
    double sat;
    double Y;

    // Convert RGB to linear space
    rgb.r = linearize((color >> 16) & 0xFF);
    rgb.g = linearize((color >> 8) & 0xFF);
    rgb.b = linearize(color & 0xFF);

    // Calculate saturation
    double max_val = fmax(fmax(rgb.r, rgb.g), rgb.b);
    double min_val = fmin(fmin(rgb.r, rgb.g), rgb.b);
    sat = (max_val - min_val) / max_val;

    // High saturation: Use black or white for strong contrast
    if (sat > 0.5)
    {
        // Calculate luminance (Y)
        Y = SRGB_X * rgb.r + SRGB_Y * rgb.g + SRGB_Z * rgb.b;
        if (Y >= 0.5)
            return (BLACK);  // Dark text on light background
        return (WHITE);       // Light text on dark background
    }
    
    // Low saturation: Use complementary color
    return r_g_or_b(rgb);
}