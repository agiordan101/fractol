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

void	julia(t_thread *thread)
{
	int		i;
	int		j;
	int		n;
	float	tmpa;
	t_map	*map;

	map = &(thread->win->map);
	i = -1;
	while (++i < thread->win->height)
	{
		j = -1;
		while (++j < thread->win->width)
		{
			thread->z.a = map->xmin + map->origin.a + j * map->dx;
			thread->z.b = map->ymax + map->origin.b - i * map->dy;
			thread->c.a = 0.3;
			thread->c.b = 0.5;
			n = -1;
			while (++n < N_ITER)
			{
				tmpa = thread->z.a * thread->z.a - thread->z.b * thread->z.b + thread->c.a;
				thread->z.b = 2 * thread->z.a * thread->z.b + thread->c.b;
				thread->z.a = tmpa;
				if (thread->z.a * thread->z.a + thread->z.b * thread->z.b > BORNE)
					break ;
			}
			//printf("tmp = %f\ta = %f\tb = %f\tc.a = %f\n", tmpa, thread->z.a, thread->z.b, thread->c.a);
			set_pixel(thread->win, j, i, map_color(thread->win, COLORMAX, COLORMIN, n / (double)N_ITER));			
		}
	}
	//printf("z.a = %f\n", thread->z.a);
}
