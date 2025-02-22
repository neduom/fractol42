/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:17:04 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/20 16:15:54 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void    burning_ship(t_fractol *fractal)
{
    int iterations;
    double  temp;

    iterations = 0;
    fractal->z.real = 0;
    fractal->z.img = 0;
    while (iterations < fractal->max_iterations)
    {
        fractal->z.real = fabs(fractal->z.real);
        fractal->z.img = fabs(fractal->z.img);
        temp = fractal->z.real * fractal->z.real - fractal->z.img * fractal->z.img + fractal->c.real;
        fractal->z.img = 2 * fractal->z.real * fractal->z.img + fractal->c.img;
        fractal->z.real = temp;
        if (fractal->z.real * fractal->z.real + fractal->z.img * fractal->z.img > 4)
            break;
        iterations++;
    }
    fractal->color = get_color(iterations, fractal);    
}

void    draw_burning_ship(t_fractol *fractal)
{
    int x;
    int y;
    double x_scale;
    double y_scale;
    

    y = 0;
    x_scale = (4.0 / WIDTH) * fractal->zoom;
    y_scale = (4.0 / HEIGHT) * fractal->zoom;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            fractal->c.real = (x - WIDTH / 2.02) * x_scale + fractal->center_pos.real;
            fractal->c.img = (y - HEIGHT / 2.02) * y_scale + fractal->center_pos.img;
            burning_ship(fractal);
            mlx_put_pixel(fractal->image, x, y, fractal->color);
            x++;
        }
        y++;
    }
}
