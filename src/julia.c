/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   julia.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 19:41:00 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 16:42:39 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int			tracking_mouse(int x, int y, t_window *win)
{
	t_map	*map;

	if ((win->choice <= 3 || win->choice >= 1) && win->map.track)
	{
		map = &(win->map);
		map->julia.a = map->xmin + map->origin.a + x * map->dx;
		map->julia.b = map->ymax + map->origin.b - y * map->dy;
		ft_refresh(win, &(win->map), &(win->map.image));
	}
	return (0);
}

static void	calcul_pixel(t_thread *thread, t_map *map, int i, int j)
{
	double	aa;
	double	bb;
	double	tmpa;
	int		n;
	int		n_max;

	thread->z.a = map->xmin + map->origin.a + j * map->dx;
	thread->z.b = map->ymax + map->origin.b - i * map->dy;
	aa = thread->z.a * thread->z.a;
	bb = thread->z.b * thread->z.b;
	thread->c = (t_complexe){.a = map->julia.a, .b = map->julia.b};
	n_max = thread->win->n_iter;
	n = -1;
	while (++n < n_max && aa + bb < BORNE)
	{
		tmpa = aa - bb + thread->c.a;
		thread->z.b = 2 * thread->z.a * thread->z.b + thread->c.b;
		thread->z.a = tmpa;
		aa = thread->z.a * thread->z.a;
		bb = thread->z.b * thread->z.b;
	}
	//set_pixel(thread->win, j, i, map_color(
	//					COLORMAX, COLORMIN, map->psy * n / (double)(n_max)));
	set_pixel(thread->win, j, i, tab_color(thread->win, n));
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
}
