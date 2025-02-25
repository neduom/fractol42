/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:16:13 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/25 11:37:11 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

# define WIDTH 1200
# define HEIGHT 920

typedef struct s_complex
{
    double  real;
    double  img;
}           t_complex;

typedef struct s_fractol
{
    mlx_t       *mlx;
    mlx_image_t *image;
    char        *fract_name;
    t_complex   c;
    t_complex   z;
    t_complex   center_pos;
    t_complex   move;
    int         color;
    int         max_iterations;
    double      zoom;
    double      scale;
    int         color_shift;
}               t_fractol;

char	*ft_strdup(const char *s);
char    *check(int ac, char **av, t_fractol *fractal);

void    burning_ship(t_fractol *fractal);
void    draw_burning_ship(t_fractol *fractal);
void    ft_free(void ** av);
void    clean(t_fractol *fract);
void    handle_movement(t_fractol *fractal, double move_step);
void    control(void *arg);
void proc(void *str);

int     ft_strcmp(const char *s1, const char *s2);
int     ft_strlen(const char *s);
int     get_color(int i, t_fractol *fractal);
int get_rgb(int red, int green, int blue, int alpha);
void    scroll(double x, double y, void* param);
double	scale(double value, double min, double max, double dimension);

#endif 