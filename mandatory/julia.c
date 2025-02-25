/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:14:34 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/24 13:11:13 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_fractol *fractal, int x, int y)
{
	int		iterations;
	double	temp;

	iterations = 0;
	fractal->z.real = -((x - WIDTH / 2.0) * fractal->zoom * 4.0 / WIDTH
			+ fractal->center_pos.real);
	fractal->z.img = (y - HEIGHT / 2.0) * fractal->zoom * 4.0 / HEIGHT
		+ fractal->center_pos.img;
	while (iterations < fractal->max_iterations)
	{
		temp = fractal->z.real * fractal->z.real - fractal->z.img
			* fractal->z.img + fractal->c.real;
		fractal->z.img = 2 * fractal->z.real * fractal->z.img + fractal->c.img;
		fractal->z.real = temp;
		if (fractal->z.real * fractal->z.real + fractal->z.img
			* fractal->z.img > 4)
			break ;
		iterations++;
	}
	if (iterations == fractal->max_iterations)
		fractal->color = get_rgb(0, 0, 0, 255);
	else
		fractal->color = get_color(iterations, fractal);
}

void	draw_julia(t_fractol *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			julia(fractal, x, y);
			mlx_put_pixel(fractal->image, x, y, fractal->color);
			x++;
		}
		y++;
	}
}
