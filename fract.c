/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fract.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 12:57:41 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 12:57:45 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"
/*
**	Z(n) = a + bi
**
**	Z(n+1) = Z(n) * Z(n) + c
**		   = (a + bi)(a + bi) + (ca + cb * i)
**		   = (a*a - b*b + ca) + (2 * a * b + cb) * i
**
**	Re(Z(n+1)) = a*a - b*b + ca
**	Im(Z(n+1)) = 2 * a * b + cb
*/
/*
**	Z(n) = (abs(a) + i * abs(b))(...) + (ca + i * cb)
**		 =	(a*a - b*b + ca) + (2 * abs(a)abs(b) + cb) * i
**	
**	Re(Z(n+1)) = a*a - b*b + ca
**	Im(Z(n+1)) = 2 * abs(a)abs(b) + cb
*/

void	burningship(t_thread *thread)
{
	int		i;
	int		j;
	int		n;
	float	tmpa;
	t_map	*map;

	map = &(thread->win->map);
	thread->c.b = map->ymax + map->origin.b;
	i = -1;
	while (++i < thread->win->height)
	{
		thread->c.a = map->xmin + map->origin.a;
		j = -1;
		while (++j < thread->win->width)
		{
			thread->z.a = 0;
			thread->z.b = 0;
			n = -1;
			while (++n < N_ITER)
			{
				tmpa = thread->z.a * thread->z.a - thread->z.b * thread->z.b + thread->c.a;
				thread->z.b = 2 * ft_abs(thread->z.a * thread->z.b) + thread->c.b;
				thread->z.a = tmpa;
				if (thread->z.a * thread->z.a + thread->z.b * thread->z.b > BORNE)
					break ;
			}
			set_pixel(thread->win, j, i, map_color(thread->win, COLORMAX, COLORMIN, n / (double)N_ITER));
			thread->c.a += map->dx;
		}
		thread->c.b -= map->dy;
	}
}

//map->c.a = map->origin.a - (map->xmax - map->xmin) / 2 + (float)j * (map->xmax - map->xmin) / (float)win->width;
//map->c.b = map->origin.b + (map->ymax - map->ymin) / 2 - (float)i * (map->ymax - map->ymin) / (float)win->height; 
