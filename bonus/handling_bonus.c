/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:12:43 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/24 12:03:49 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	ft_free(void **av)
{
	if (av && *av)
	{
		free(*av);
		*av = NULL;
	}
}

void	clean(t_fractol *fract)
{
	if (fract->mlx && fract->image)
		mlx_delete_image(fract->mlx, fract->image);
	if (fract->mlx)
	{
		mlx_terminate(fract->mlx);
		fract->mlx = NULL;
	}
}

void	proc(void *str)
{
	write(2, "Error\n", 6);
	free(str);
	exit(EXIT_FAILURE);
}
