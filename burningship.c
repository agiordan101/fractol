/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiordan <agiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:48:42 by agiordan          #+#    #+#             */
/*   Updated: 2019/01/23 18:48:45 by agiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burningship(t_thread *thread)
{
	int		i;
	int		imax;
	int		j;
	int		n;
	float	tmpa;
	t_map	*map;

	map = &(thread->win->map);
	i = thread->win->height/NBR_THREADS * thread->quarter - 1;
	imax = thread->win->height/NBR_THREADS * (thread->quarter + 1);
	thread->c.b = map->ymax + map->origin.b - (i + 1) * map->dy;
	while (++i < imax)
	{
		thread->c.a = map->xmin + map->origin.a;
		j = -1;
		while (++j < thread->win->width)
		{
			thread->z.a = 0;
			thread->z.b = 0;
			n = -1;
			while (++n < thread->win->n_iter)
			{
				tmpa = thread->z.a * thread->z.a - thread->z.b * thread->z.b + thread->c.a;
				thread->z.b = 2 * ft_abs(thread->z.a * thread->z.b) + thread->c.b;
				thread->z.a = tmpa;
				if (thread->z.a * thread->z.a + thread->z.b * thread->z.b > BORNE)
					break ;
			}
			set_pixel(thread->win, j, i, map_color(thread->win, COLORMAX, COLORMIN, n / (double)(thread->win->n_iter)));
			thread->c.a += map->dx;
		}
		thread->c.b -= map->dy;
	}
}
