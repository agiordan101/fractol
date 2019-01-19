/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   julia.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/18 19:41:00 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/18 19:41:01 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_window *win, t_map *map, t_image *image)
{
	int		i;
	int		j;
	int		n;
	float	tmpa;

	map->dx = (map->xmax - map->xmin) / (float)win->width;
	map->dy = (map->ymax - map->ymin) / (float)win->height;
	map->z.b = map->ymax + win->map.origin.b;
	i = -1;
	while (++i < win->height)
	{
		map->z.a = map->xmin + win->map.origin.a;
		j = -1;
		while (++j < win->width)
		{
			//ca et cb = complexe qui correspont au curseur de la souris en temps reel
			map->c.a = -0.8;
			map->c.b = 0.156;
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
			map->z.a += map->dx;
		}
		map->z.b -= map->dy;
	}
}
