/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:07:08 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/16 19:44:23 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    handle_exit(t_fractol *fractal)
{
    mlx_close_window(fractal->mlx);
    mlx_delete_image(fractal->mlx, fractal->image);
    mlx_terminate(fractal->mlx);
    exit(EXIT_FAILURE);
}

void    handle_movement(t_fractol *fractal, double move_step)
{
    double  dx;
    double  dy;

    dx = 0.0;
    dy = 0.0;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_UP))
        dy -= move_step;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_DOWN))
        dy += move_step;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_RIGHT))
        dx += move_step;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_LEFT))
        dx -= move_step;
    fractal->center_pos.real += dx;
    fractal->center_pos.img += dy;
}

void    handle_zoom_iterations(t_fractol *fractal)
{
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_I))
        fractal->zoom *= 0.9;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_O))
        fractal->zoom *= 1.1;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_KP_ADD) && fractal->max_iterations < 500)
        fractal->max_iterations += 20;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_KP_SUBTRACT) && fractal->max_iterations > 20)
        fractal->max_iterations -= 20;
}

void    controls(void *arg)
{
    t_fractol   *fractal;
    double      move_step;

    fractal = (t_fractol *)arg;
    move_step = 0.04 * fractal->zoom;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
        handle_exit(fractal);
    handle_movement(fractal, move_step);
    handle_zoom_iterations(fractal);
    if (!ft_strcmp(fractal->fract_name, "mandelbrot"))
        draw_mandelbrot(fractal);
    else if (!ft_strcmp(fractal->fract_name, "julia"))
        draw_julia(fractal);
}
