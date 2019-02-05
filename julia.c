/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   julia.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 19:41:00 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:07:57 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	calcul_pixel(t_thread *thread, t_map *map, int i, int j)
{
	double	tmpa;
	int		n;

	thread->z.a = map->xmin + map->origin.a + j * map->dx;
	thread->z.b = map->ymax + map->origin.b - i * map->dy;
	thread->c.a = map->julia.a;
	thread->c.b = map->julia.b;
	n = -1;
	while (++n < thread->win->n_iter &&\
	thread->z.a * thread->z.a + thread->z.b * thread->z.b < BORNE)
	{
		tmpa = thread->z.a * thread->z.a - thread->z.b * thread->z.b +\
		thread->c.a;
		thread->z.b = 2 * thread->z.a * thread->z.b + thread->c.b;
		thread->z.a = tmpa;
	}
	set_pixel(thread->win, j, i, map_color(thread->win,\
	COLORMAX, COLORMIN, map->psy * n / (double)(thread->win->n_iter)));
	thread->c.a += map->dx;
}

void		julia(t_thread *thread)
{
	int		i;
	int		imax;
	int		j;
	t_map	*map;

	map = &(thread->win->map);
	i = thread->win->height / NBR_THREADS * thread->quarter - 1;
	imax = thread->win->height / NBR_THREADS * (thread->quarter + 1);
	while (++i < imax)
	{
		j = -1;
		while (++j < thread->win->width)
			calcul_pixel(thread, map, i, j);
	}
	printf("fin quarter\n");
}
