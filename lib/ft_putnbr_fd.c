/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:32:30 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/07 18:32:31 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lib.h>

static	void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static	int		ft_get_size(int n)
{
	int size;

	size = 0;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static	int		ft_get_dec_in_pow(int pow)
{
	int i;
	int n;

	i = 0;
	n = 1;
	while (i < pow - 1)
	{
		n *= 10;
		i++;
	}
	return (n);
}

void			ft_putnbr_fd(int n, int fd)
{
	int size;

	if (n == -2147483648)
	{
		ft_putstr_fd(ft_strdup("-2147483648"), fd);
		return ;
	}
	if (n < 0)
	{
		n *= (-1);
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
	{
		ft_putchar_fd((char)(n + 48), fd);
		return ;
	}
	size = ft_get_size(n);
	while (size > 0)
	{
		ft_putchar_fd((char)(n / ft_get_dec_in_pow(size) + 48), fd);
		n %= ft_get_dec_in_pow(size);
		size--;
	}
}
