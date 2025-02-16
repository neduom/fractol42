/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:14:34 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/16 21:20:37 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    julia(t_fractol *fractal, int x, int y)
{
    int     iterations;
    double  temp;

    iterations = 0;
    fractal->z.real = (double)x / (double)WIDTH * 4.1 / fractal->scale - fractal->move.real;
    fractal->z.img = (double)y / (double)HEIGHT * 4.1 / fractal->scale - fractal->move.img;
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

void    draw_julia(t_fractol *fractal)
{
    int x;
    int y;

    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            julia(fractal, x, y);
            mlx_put_pixel(fractal->image, x, y, fractal->color);
            y++;
        }
        x++;
    }
}