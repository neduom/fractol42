/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:07:08 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/22 15:19:57 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    handle_exit(t_fractol *fractal)
{
    if (!fractal || !fractal->mlx)
        return;
    mlx_close_window(fractal->mlx);
    mlx_delete_image(fractal->mlx, fractal->image);
    mlx_terminate(fractal->mlx);
    exit(EXIT_FAILURE);
}

void    handle_zoom_iterations(t_fractol *fractal)
{
    if (!fractal || !fractal->mlx)
        return;
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
    handle_zoom_iterations(fractal);
    if (!ft_strcmp(fractal->fract_name, "mandelbrot"))
        draw_mandelbrot(fractal);
    else if (!ft_strcmp(fractal->fract_name, "julia"))
        draw_julia(fractal);
}
