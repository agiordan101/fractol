/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mandelbrot.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 19:40:54 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 18:26:59 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	calcul_pixel(t_thread *thread, t_map *map, int i, int j)
{
	double	aa;
	double	bb;
	double	tmpa;
	int		n;
	int		n_max;

	thread->z = (t_complexe){.a = 0, .b = 0};
	aa = thread->z.a * thread->z.a;
	bb = thread->z.b * thread->z.b;
	n_max = thread->win->n_iter;
	n = -1;
	while (++n < n_max && aa + bb < BORNE)
	{
		tmpa = aa - bb + thread->c.a;
		thread->z.b = map->power * thread->z.a * thread->z.b + thread->c.b;
		thread->z.a = tmpa;
		aa = thread->z.a * thread->z.a;
		bb = thread->z.b * thread->z.b;
	}
	set_pixel(thread->win, j, i, map_color(\
		COLORMAX, COLORMIN, map->psy * n / (double)n_max));
	thread->c.a += map->dx;
}

void		mandelbrot(t_thread *thread)
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
}
