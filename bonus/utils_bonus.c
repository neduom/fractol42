/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:18:36 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/24 14:47:56 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*c;

	i = 0;
	c = malloc(ft_strlen(s) + 1);
	if (!c)
		return (NULL);
	while (s[i] != '\0')
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

int	ft_strlen(const char *s)
{
	int l;

	l = 0;
	while (s[l] != '\0')
	{
		l++;
	}
	return (l);
}

int    ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

double	scale(double value, double min, double max, double dimension)
{
	return ((value / dimension) * (max - min) + min);
}

