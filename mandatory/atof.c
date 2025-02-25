/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-moud <mel-moud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:41:42 by mel-moud          #+#    #+#             */
/*   Updated: 2025/02/21 17:16:12 by mel-moud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	my_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	get_integer(char **str)
{
	int	num;

	num = 0;
	if (!my_digit(**str))
		return (-1);
	while (**str && my_digit(**str))
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

static double	get_decimal(char **str)
{
	double	fract;
	double	result;

	fract = 1.0;
	result = 0.0;
	if (**str == '.')
		(*str)++;
	if (!my_digit(**str))
		return (-1);
	while (**str && my_digit(**str))
	{
		fract /= 10;
		result += (**str - '0') * fract;
		(*str)++;
	}
	return (result);
}

double	ft_atof(char *str)
{
	int		integer_part;
	double	decimal_part;
	int		sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!my_digit(*str))
		(write(2, "Error\n", 6), exit(EXIT_FAILURE));
	integer_part = get_integer(&str);
	decimal_part = 0.0;
	if (*str == '.')
		decimal_part = get_decimal(&str);
	if (integer_part == -1 || decimal_part == -1 || *str != '\0')
		(write(2, "Error\n", 6), exit(EXIT_FAILURE));
	return ((integer_part + decimal_part) * sign);
}
