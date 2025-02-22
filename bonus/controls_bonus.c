/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:47:25 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/18 17:20:47 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_KP_ADD) && fractal->max_iterations < 500)
        fractal->max_iterations += 20;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_KP_SUBTRACT) && fractal->max_iterations > 20)
        fractal->max_iterations -= 20;
}

void    control(void *arg)
{
    t_fractol   *fractal;
    double      move_step;
    int         butoon;

    butoon = 0;
    fractal = (t_fractol *)arg;
    move_step = 0.04 * fractal->zoom;
    if (mlx_is_key_down(fractal->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(fractal->mlx);
        mlx_delete_image(fractal->mlx, fractal->image);
        mlx_terminate(fractal->mlx);
        exit(EXIT_FAILURE);
    }
    handle_movement(fractal, move_step);
    if (!ft_strcmp(fractal->fract_name, "burning_ship"))
        draw_burning_ship(fractal);
}
