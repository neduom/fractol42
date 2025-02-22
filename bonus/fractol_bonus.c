/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:07:34 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/22 16:11:45 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int get_rgb(int yellow, int alpha)
{
    return ((yellow << 16) | (yellow << 24) | alpha);
}

int get_color(int i, t_fractol *fract)
{
    double  ratio;

    ratio = (double)i / fract->max_iterations;
    int yellow = (int)(100 * (1 - ratio) * ratio * ratio * ratio * 255);
    return (get_rgb(yellow, 255));
}

char    *check(int ac, char **av, t_fractol *fractal)
{
    if (!ft_strcmp(av[1], "burning_ship"))
    {
        if (ac != 2)
            (write (2, "Error\n", 6), exit(1));
        fractal->scale = 1.0;
        fractal->move.real = 2.0;
        fractal->move.img = 2.0;
        return (ft_strdup("burning_ship"));
    }
    return (NULL);
}

void scroll(double x, double y, void *param)
{
    t_fractol *fractal = (t_fractol *)param;
    double zoom_factor = 1.1;
    int32_t mouse_x;
    int32_t mouse_y;

    (void)x;
    double old_zoom =  fractal->zoom;
    mlx_get_mouse_pos(fractal->mlx, &mouse_x, &mouse_y);
    if (y == 1)
        fractal->zoom /= zoom_factor;
    else if (y == -1)
        fractal->zoom *= zoom_factor;
    fractal->center_pos.real += scale(mouse_x, -2, 2, WIDTH) * (old_zoom - fractal->zoom);
    fractal->center_pos.img += scale(mouse_y, -2, 2, HEIGHT) * (old_zoom - fractal->zoom);
    draw_burning_ship(fractal);
}

int main(int ac, char **av)
{
    t_fractol fractal;
    
    if (HEIGHT < 0 || WIDTH < 0)
        (write (2, "Error\n", 6), exit(1));
    fractal.fract_name = check(ac, av, &fractal);
    if (!fractal.fract_name)
        (write (2, "Error\n", 6), exit(EXIT_FAILURE));
    fractal.mlx = mlx_init(WIDTH, HEIGHT, fractal.fract_name, false);
    if (!fractal.mlx)
        return (EXIT_FAILURE);
    fractal.image = mlx_new_image(fractal.mlx, WIDTH, HEIGHT);
    if (!fractal.image)
        (write (2, "Error\n", 6), exit(EXIT_FAILURE));
    mlx_image_to_window(fractal.mlx, fractal.image, 0, 0);
    fractal.zoom = 1.0;
    fractal.max_iterations = 50;
    mlx_loop_hook(fractal.mlx, control, &fractal);
    mlx_scroll_hook(fractal.mlx, (void *)scroll, &fractal);
    mlx_loop(fractal.mlx);
    clean(&fractal);
    free(fractal.fract_name);
}
