/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   burningship.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 18:48:42 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:08:05 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	calcul_pixel(t_thread *thread, t_map *map, int i, int j)
{
	double	tmpa;
	int		n;

	thread->z.a = 0;
	thread->z.b = 0;
	n = -1;
	while (++n < thread->win->n_iter &&\
	thread->z.a * thread->z.a + thread->z.b * thread->z.b < BORNE)
	{
		tmpa = thread->z.a * thread->z.a - thread->z.b * thread->z.b +\
		thread->c.a;
		thread->z.b = 2 * ft_abs(thread->z.a * thread->z.b) + thread->c.b;
		thread->z.a = tmpa;
	}
	set_pixel(thread->win, j, i, map_color(thread->win,\
	COLORMAX, COLORMIN, map->psy * n / (double)(thread->win->n_iter)));
	thread->c.a += map->dx;
}

void		burningship(t_thread *thread)
{
	t_map	*map;
	int		i;
	int		imax;
	int		j;

	map = &(thread->win->map);
	i = thread->win->height / NBR_THREADS * thread->quarter - 1;
	imax = thread->win->height / NBR_THREADS * (thread->quarter + 1);
	thread->c.b = map->ymax + map->origin.b - (i + 1) * map->dy;
	while (++i < imax)
	{
		thread->c.a = map->xmin + map->origin.a;
		j = -1;
		while (++j < thread->win->width)
			calcul_pixel(thread, map, i, j);
		thread->c.b -= map->dy;
	}
	//printf("Fin quarter : %i\n", thread->quarter);
}
