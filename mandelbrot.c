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
	int	i;
	int	j;
	int	n;
	int	tmpa;
	int color;

	printf("Debut mandelbrot\n");
	i = -1;
	while (++i < win->width)
	{
		j = -1;
		while (++j < win->height)
		{
			map->z.a = map->origin.a - (map->xmax - map->xmin) / 2 + j * (map->xmax - map->xmin) / win->width;
			map->z.b = map->origin.b - (map->ymax - map->ymin) / 2 + i * (map->ymax - map->ymin) / win->height;
			//printf("x = %f - y = %f\n", map->z.a, map->z.b);
			map->c.a = 0;
			map->c.b = 0;
			n = -1;
			while (++n < N_ITER)
			{
				tmpa = map->z.a * map->z.a + map->z.b * map->z.b + map->c.a;
				map->z.b = 2 * map->z.a * map->z.b + map->c.b;
				map->z.a = tmpa;
				if (map->z.a * map->z.a + map->z.b * map->z.b > BORNE)
					break ;
			}
			color = map_color(win, COLORMIN, COLORMAX, n / N_ITER);
			//printf("N : %i\n", n);
			set_pixel(win, j, i, color);
		}	
	}
	printf("Fin mandelbrot\n");
}

//Entrer la precision en parametre, ce qui changera N_ITER