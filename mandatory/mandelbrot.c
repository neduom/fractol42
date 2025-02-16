/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:07:16 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/16 20:30:56 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    mandelbrot(t_fractol *fractal)
{
    int iterations;
    double temp;
    
    fractal->z.real = 0;
    fractal->z.img = 0;
    iterations = 0;
    while (iterations < fractal->max_iterations)
    {
        temp = fractal->z.real * fractal->z.real - fractal->z.img * fractal->z.img + fractal->c.real;
        fractal->z.img = 2 * fractal->z.real * fractal->z.img + fractal->c.img;
        fractal->z.real = temp;
        if (fractal->z.real * fractal->z.real + fractal->z.img * fractal->z.img > 4)
            break;
        iterations++;
    }
    if (iterations == fractal->max_iterations)
        fractal->color = get_rgb(0, 0, 0, 255);
    else
        fractal->color = get_color(iterations, fractal);
}

void    draw_mandelbrot(t_fractol *fractal)
{
    int x;
    int y;
    double x_scale;
    double y_scale;
    
    x_scale = (4.0 / WIDTH) * fractal->zoom;
    y_scale = (4.0 / HEIGHT) * fractal->zoom;
    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            fractal->c.real = (x - WIDTH / 2.0) * x_scale + fractal->center_pos.real;
            fractal->c.img = (y - HEIGHT / 2.0) * y_scale + fractal->center_pos.img;
            mandelbrot(fractal);
            mlx_put_pixel(fractal->image, x, y, fractal->color);
            y++;
        }
        x++;
    }
}