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

/*void	calcul_pixel(t_window *win, t_map *map, int i, int j)
{

}*/
//calcul_pixel(win, &(win->map), i, j);

void	mandelbrot(t_thread *thread)
{
	t_map		*map;
	int			i;
	int			imax;
	int			j;
	float		tmpa;
	int	n;

	map = &(thread->win->map);
	i = thread->win->height/NBR_THREADS * thread->quarter - 1;
	imax = thread->win->height/NBR_THREADS * (thread->quarter + 1);
	thread->c.b = map->ymax + map->origin.b - (i + 1) * map->dy;
	while (++i < imax)
	{
		thread->c.a = map->xmin + map->origin.a;
		//printf("c.a = %f\txmin = %f\torigin x = %f\n", thread->c.a, map->xmin, map->origin.a);
		j = -1;
		while (++j < thread->win->width)
		{
			thread->z.a = 0;
			thread->z.b = 0;
			n = -1;
			while (++n < N_ITER)
			{
				tmpa = thread->z.a * thread->z.a - thread->z.b * thread->z.b + thread->c.a;
				thread->z.b = 2 * thread->z.a * thread->z.b + thread->c.b;
				thread->z.a = tmpa;
				if (thread->z.a * thread->z.a + thread->z.b * thread->z.b > BORNE)
					break ;
			}
			set_pixel(thread->win, j, i, map_color(thread->win, COLORMAX, COLORMIN, n / (double)N_ITER));
			thread->c.a += map->dx;
		}
		thread->c.b -= map->dy;
	}
	printf("Fin quarter : %i\n", thread->quarter);
}
