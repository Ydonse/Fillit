/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:28:29 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/17 11:29:29 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_printnb(long nb)
{
	if (nb > 9)
	{
		ft_printnb(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	else
		ft_putchar(nb + '0');
}

void		ft_putnbr(int n)
{
	long l;

	l = n;
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	ft_printnb(l);
}
