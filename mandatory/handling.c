/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:24:36 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/15 15:55:40 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void    ft_free(void ** av)
{
    if (av && *av)
    {
        free(*av);
        *av = NULL;
    }
}

void    clean(t_fractol *fract)
{
    if (fract->mlx && fract->image)
        mlx_delete_image(fract->mlx, fract->image);
    if (fract->mlx)
    {
        mlx_terminate(fract->mlx);
        fract->mlx = NULL;
    }
}


void    error_exit(t_fractol *fract, int flag)
{
    if (flag == 1)
        clean(fract);
    ft_putendl_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
    exit(EXIT_FAILURE);
}
