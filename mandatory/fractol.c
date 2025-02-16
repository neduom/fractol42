/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:56:34 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/16 21:13:37 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int get_rgb(int red, int green, int blue, int alpha)
{
    return (red << 24 | green << 16 | blue << 8 | alpha);
}

int get_color(int i, t_fractol *fract)
{
    double  ratio;

    ratio = (double)i / fract->max_iterations;
    int blue = (int)(1 * (1 - ratio) * ratio * ratio * ratio * 255);  // Moved blue formula to red
    int green = (int)(2 * (1 - ratio) * (1 - ratio) * ratio * ratio * 255);
    int red = (int)(10 * (1 - ratio) * (1 - ratio) * (1 - ratio) * ratio * 255); // Moved red formula to blue
    return (get_rgb(red, green, blue, 255));
}


char    *checke(int ac, char **av, t_fractol *fractol)
{
    if (ac < 2)
        return (NULL);
    if (!ft_strcmp(av[1], "mandelbrot"))
        return (ft_strdup("mandelbrot"));
    else if (!ft_strcmp(av[1], "julia"))
    {
        if (ac < 4)
            return (NULL);
        fractol->c.real = atof(av[2]);
        fractol->c.img = atof(av[3]);
        fractol->scale = 1.0;
        fractol->move.real = 2.0;
        fractol->move.img = 2.0;
        return (ft_strdup("julia"));
    }
    return (NULL);
}

int main(int ac ,char **av)
{
    t_fractol   fractal;

    fractal.mlx = NULL;
    fractal.image = NULL;
    fractal.fract_name = checke(ac, av, &fractal);
    if (!fractal.fract_name)
    {
        ft_putendl_fd("Error", 2);
        exit(EXIT_FAILURE);
    }
    fractal.mlx = mlx_init(WIDTH, HEIGHT, fractal.fract_name, false);
    if (!fractal.mlx)
        return (1);
    fractal.image = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
    if (!fractal.image)
        return (1);
    fractal.max_iterations = 100;
    fractal.zoom = 1.0;
    mlx_image_to_window(fractal.mlx, fractal.image, 0, 0);
    mlx_loop_hook(fractal.mlx, controls, &fractal);
    mlx_loop(fractal.mlx);
    ft_free((void **)&fractal.fract_name);
    mlx_delete_image(fractal.mlx, fractal.image);
    mlx_terminate(fractal.mlx);
    return (0);
}
