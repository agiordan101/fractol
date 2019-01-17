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
**		   = (a + bi)(a + bi) + (ca + cb * i)
**		   = (a*a - b*b + ca) + (2 * a * b + cb) * i
**
**	Re(Z(n+1)) = a*a - b*b + ca
**	Im(Z(n+1)) = 2 * a * b + cb
*/

void	mandelbrot(t_window *win, t_map *map, t_image *image)
{
	int		i;
	int		j;
	int		n;
	float	tmpa;

	map->dx = (map->xmax - map->xmin) / (float)win->width;
	map->dy = (map->ymax - map->ymin) / (float)win->height;
	map->c.b = map->ymin;
	i = -1;
	while (++i < win->height)
	{
		map->c.a = map->xmin;
		j = -1;
		while (++j < win->width)
		{
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
		map->c.b += map->dy;
	}
}

void	julia(t_window *win, t_map *map, t_image *image)
{
	int		i;
	int		j;
	int		n;
	float	tmpa;

	map->dx = (map->xmax - map->xmin) / (float)win->width;
	map->dy = (map->ymax - map->ymin) / (float)win->height;
	map->z.b = map->ymin;
	i = -1;
	while (++i < win->height)
	{
		map->z.a = map->xmin;
		j = -1;
		while (++j < win->width)
		{
			//ca et cb = complexe qui correspont au curseur de la souris en temps reel
			map->c.a = 0.8;
			map->c.b = -0.4;
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
		map->z.b += map->dy;
	}
}

//map->c.a = map->origin.a - (map->xmax - map->xmin) / 2 + (float)j * (map->xmax - map->xmin) / (float)win->width;
//map->c.b = map->origin.b + (map->ymax - map->ymin) / 2 - (float)i * (map->ymax - map->ymin) / (float)win->height;