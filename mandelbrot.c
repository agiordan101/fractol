/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mandelbrot.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:25:41 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 17:25:42 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"
/*
**	Z(n) = a + bi
**
**	Z(n+1) = Z(n) * Z(n) + c
**		   = (a + bi)(a + bi) + c
**		   = (a*a - b*b) + (2 * a * b) * i
**
**	Im(Z(n+1)) = a*a - b*b
**	Re(Z(n+1)) = 2 * a * b
*/

void	mandelbrot(t_map *map)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			map->z.a = 
			map->z.b = 
			map->c.a = 0;
			map->c.b = 0;
			n = -1;
			while (++n < N_ITER)
			{
				
			}
		}	
	}
}