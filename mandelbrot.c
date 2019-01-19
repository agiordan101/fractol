/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mandelbrot.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 19:40:54 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 19:40:55 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	calcul_pixel(t_window *win, t_map *map, int i, int j)
{
	int	tmpa;
	int	n;

	map->z.a = 0;
	map->z.b = 0;
	n = -1;
	while (++n < N_ITER)
	{
		tmpa = map->z.a * map->z.a - map->z.b * map->z.b + map->c.a;
		map->z.b = 2 * map->z.a * map->z.b + map->c.b;
		map->z.a = tmpa;
		if (map->z.a * map->z.a + map->z.b * map->z.b > BORNE)
			break ;
	}
	set_pixel(win, j, i, map_color(win, COLORMAX, COLORMIN, n / (double)N_ITER));
}

void	mandelbrot(void *param)
{
	t_thread	*thread;
	t_map		*map;
	int			i;
	int			imax;
	int			j;
	int	tmpa;
	int	n;

	thread = (t_thread *)param;
	printf("Debut quarter : %i\n", thread->quarter);
	map = &(thread->win->map);


	map->dx = (map->xmax - map->xmin) / (float)thread->win->width;
	map->dy = (map->ymax - map->ymin) / (float)thread->win->height;


	i = thread->win->height/4 * thread->quarter - 1;
	imax = thread->win->height/4 * (thread->quarter + 1);


	map->c.b = map->ymax + map->origin.b - i * map->dy;
	while (++i < imax)
	{
		map->c.a = map->xmin + map->origin.a - 1;
		j = 0;
		while (++j < thread->win->width)
		{
			//calcul_pixel(win, &(win->map), i, j);
			map->z.a = 0;
			map->z.b = 0;
			n = -1;
			while (++n < N_ITER)
			{
				tmpa = map->z.a * map->z.a - map->z.b * map->z.b + map->c.a;
				map->z.b = 2 * map->z.a * map->z.b + map->c.b;
				map->z.a = tmpa;
				if (map->z.a * map->z.a + map->z.b * map->z.b > BORNE)
					break ;
			}
			set_pixel(thread->win, j, i, map_color(thread->win, COLORMAX, COLORMIN, n / (double)N_ITER));
			map->c.a += map->dx;
		}
		map->c.b -= map->dy;
	}
	printf("Fin quarter : %i\n", thread->quarter);
}

//param [0,4]
//i = height/4 * (param - 1)

//imax = height/4 * param