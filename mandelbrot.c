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

void	mandelbrot(t_window *win)
{
	t_map		*map;
	int			i;
	int			imax;
	int			j;
	int	tmpa;
	int	n;

	printf("Debut quarter : %i\n", win->quarter);
	map = &(win->map);
	map->dx = (map->xmax - map->xmin) / (float)win->width;
	map->dy = (map->ymax - map->ymin) / (float)win->height;
	i = win->height/4 * (win->quarter - 1) - 1;
	imax = win->height/4 * win->quarter;
	map->c.b = map->ymax + win->map.origin.b - i * map->dy;
	while (++i < imax)
	{
		map->c.a = map->xmin + win->map.origin.a;
		j = 0;
		while (++j < win->width)
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
			set_pixel(win, j, i, map_color(win, COLORMAX, COLORMIN, n / (double)N_ITER));
			map->c.a += map->dx;
		}
		map->c.b -= map->dy;
	}
	printf("Fin quarter : %i\n", win->quarter);
}

//param [0,4]
//i = height/4 * (param - 1)

//imax = height/4 * param