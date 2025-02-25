/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:56:34 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/25 16:21:33 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_rgb(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

int	get_color(int i, t_fractol *fract)
{
	double	ratio;
	int		blue;
	int		green;
	int		red;

	ratio = (double)i / fract->max_iterations;
	blue = (int)(15 * (1 - ratio) * ratio * ratio * ratio * 100);
	green = (int)(15 * (1 - ratio) * (1 - ratio) * ratio * ratio * 100);
	red = (int)(50 * (1 - ratio) * (1 - ratio) * (1 - ratio) * ratio * 200);
	return (get_rgb(red, green, blue, 255));
}

char	*check(int ac, char **av, t_fractol *fractol)
{
	if (!fractol)
		(write(2, "error\n", 6), exit(EXIT_FAILURE));
	if (!ft_strcmp(av[1], "mandelbrot"))
	{
		if (ac != 2)
			(write(2, "Error\n", 6), exit(EXIT_FAILURE));
		fractol->scale = 1.0;
		fractol->move.real = 2.0;
		fractol->move.img = 2.0;
		return (ft_strdup("mandelbrot"));
	}
	else if (!ft_strcmp(av[1], "julia"))
	{
		if (ac != 4)
			(write(2, "Error\n", 6), exit(EXIT_FAILURE));
		fractol->c.real = ft_atof(av[2]);
		fractol->c.img = ft_atof(av[3]);
		fractol->scale = 1.0;
		fractol->move.real = 2.0;
		fractol->move.img = 2.0;
		return (ft_strdup("julia"));
	}
	(write(2, "Error\n", 6), exit(EXIT_FAILURE));
}

void	scroll(double x, double y, void *param)
{
	t_fractol	*fractal;
	double		zoom_factor;

	fractal = (t_fractol *)param;
	zoom_factor = 1.1;
	(void)x;
	if (y > 0)
		fractal->zoom /= zoom_factor;
	else if (y < 0)
		fractal->zoom *= zoom_factor;
}

int	main(int ac, char **av)
{
	t_fractol	fractal;

	if (HEIGHT < 0 || WIDTH < 0)
		(write(2, "Error\n", 6), exit(1));
	fractal.mlx = NULL;
	fractal.image = NULL;
	if (ac > 1)
		fractal.fract_name = check(ac, av, &fractal);
	else
		(write(2, "please try mandelbrot or julia\n", 41), exit(EXIT_FAILURE));
	fractal.mlx = mlx_init(WIDTH, HEIGHT, fractal.fract_name, false);
	if (!fractal.mlx)
		proc(fractal.mlx);
	fractal.image = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	if (!fractal.image)
		return (write(2, "Error\n", 6), free(fractal.fract_name),
			clean(&fractal), 1);
	fractal.max_iterations = 100;
	fractal.zoom = 1.0;
	mlx_image_to_window(fractal.mlx, fractal.image, 0, 0);
	mlx_scroll_hook(fractal.mlx, (void *)scroll, &fractal);
	mlx_loop_hook(fractal.mlx, controls, &fractal);
	mlx_loop(fractal.mlx);
	ft_free((void **)&fractal.fract_name);
	clean(&fractal);
}
