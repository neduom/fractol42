/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:30:18 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/24 13:09:10 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1200
# define HEIGHT 900

typedef struct s_complex
{
	double		real;
	double		img;
}				t_complex;

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		*fract_name;
	t_complex	c;
	t_complex	z;
	t_complex	center_pos;
	t_complex	move;
	int			color;
	int			max_iterations;
	double		zoom;
	double		scale;
}				t_fractol;

char			*ft_strdup(const char *s);
char			*check(int ac, char **av, t_fractol *fractol);

int				ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				get_rgb(int red, int green, int blue, int alpha);
int				get_color(int i, t_fractol *fract);
int				my_digit(char c);

void			ft_free(void **av);
void			clean(t_fractol *fract);
void			julia(t_fractol *fractal, int x, int y);
void			draw_julia(t_fractol *fractal);
void			mandelbrot(t_fractol *fractal);
void			draw_mandelbrot(t_fractol *fractal);
void			handle_exit(t_fractol *fractal);
void			handle_zoom_iterations(t_fractol *fractal);
void			controls(void *arg);
void			scroll(double x, double y, void *param);
void			proc(void *str);

double			ft_atof(char *str);
double			scale(double value, double min, double max, double dimension);
#endif