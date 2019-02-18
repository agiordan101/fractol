/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putinttab.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/16 15:50:58 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 15:51:02 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putinttab(int *tab, size_t len)
{
	int	i;

	i = 0;
	while (i < (int)len)
	{
		ft_putnbr(tab[i++]);
		ft_putchar('\n');
	}
}