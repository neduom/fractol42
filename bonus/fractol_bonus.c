/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:07:34 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/25 16:23:32 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	get_rgb(int red, int green, int blue, int alpha)
{
	return (red << 24 | green << 16 | blue << 8 | alpha);
}

int	get_color(int i, t_fractol *fract)
{
	double	t;

	if (i == fract->max_iterations)
		return (get_rgb(0, 0, 0, 255));
	t = (double)i / fract->max_iterations;
	if (fract->color_shift == 0)
		return (get_rgb(255 * pow(t, 0.3), 200 * pow(t, 0.5), 50 * pow(1 - t,
					2), 255));
	else if (fract->color_shift == 1)
		return (get_rgb(50 * (1 - t), 100 * pow(t, 0.6), 255 * pow(t, 0.3),
				255));
	else if (fract->color_shift == 2)
		return (get_rgb(200 * pow(t, 0.5), 50 * (1 - t), 100 * pow(1 - t, 0.7),
				255));
	return (get_rgb(255, 255, 255, 255));
}

char	*check(int ac, char **av, t_fractol *fractal)
{
	if (!fractal)
		(write(2, "error\n", 6), exit(EXIT_FAILURE));
	if (!ft_strcmp(av[1], "burning_ship"))
	{
		if (ac != 2)
			(write(2, "Error\n", 6), exit(1));
		fractal->scale = 1.0;
		fractal->move.real = 2.0;
		fractal->move.img = 2.0;
		return (ft_strdup("burning_ship"));
	}
	return (NULL);
}

void	scroll(double x, double y, void *param)
{
	t_fractol	*fractal;
	double		zoom_factor;
	int32_t		mouse_x;
	int32_t		mouse_y;
	double		old_zoom;

	fractal = (t_fractol *)param;
	zoom_factor = 1.1;
	(void)x;
	old_zoom = fractal->zoom;
	mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
	if (y == 1)
		fractal->zoom /= zoom_factor;
	else if (y == -1)
		fractal->zoom *= zoom_factor;
	fractal->center_pos.real += scale(mouse_x, -2, 2, WIDTH) * (old_zoom
			- fractal->zoom);
	fractal->center_pos.img += scale(mouse_y, -2, 2, HEIGHT) * (old_zoom
			- fractal->zoom);
}

int	main(int ac, char **av)
{
	t_fractol	fractal;

	if (HEIGHT < 0 || WIDTH < 0)
		(write(2, "Error\n", 6), exit(1));
	fractal.fract_name = check(ac, av, &fractal);
	if (!fractal.fract_name)
		(write(2, "please try burnig_ship\n", 23), exit(EXIT_FAILURE));
	fractal.mlx = mlx_init(WIDTH, HEIGHT, fractal.fract_name, false);
	if (!fractal.mlx)
		proc(fractal.mlx);
	fractal.image = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
	if (!fractal.image)
		return (write(2, "Error\n", 6), free(fractal.fract_name),
			clean(&fractal), 1);
	mlx_image_to_window(fractal.mlx, fractal.image, 0, 0);
	fractal.zoom = 1.0;
	fractal.max_iterations = 50;
	fractal.color_shift = 0;
	mlx_loop_hook(fractal.mlx, control, &fractal);
	mlx_scroll_hook(fractal.mlx, (void *)scroll, &fractal);
	mlx_loop(fractal.mlx);
	clean(&fractal);
	free(fractal.fract_name);
}
