/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tapis.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/18 21:34:08 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 18:25:07 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static t_dot	tier(t_dot d1, t_dot d2)
{
	return ((t_dot){.x = d1.x + (d2.x - d1.x) / 3,\
					.y = d1.y + (d2.y - d1.y) / 3});
}

static t_carre	decale(t_carre carre, int x, int y)
{
	t_carre newcarre;
	double	dx;
	double	dy;

	dx = carre.dot[1].x - carre.dot[0].x;
	dy = carre.dot[3].y - carre.dot[0].y;
	newcarre.dot[0] = (t_dot){.x = carre.dot[0].x + dx * x,\
								.y = carre.dot[0].y + dy * y};
	newcarre.dot[1] = (t_dot){.x = carre.dot[1].x + dx * x,\
								.y = carre.dot[1].y + dy * y};
	newcarre.dot[2] = (t_dot){.x = carre.dot[2].x + dx * x,\
								.y = carre.dot[2].y + dy * y};
	newcarre.dot[3] = (t_dot){.x = carre.dot[3].x + dx * x,\
								.y = carre.dot[3].y + dy * y};
	return (newcarre);
}

static void		draw(t_window *win, t_carre carre, int step)
{
	carre.dot[0].color = map_color(0x30EE30, 0xAA2020,\
								step / (double)win->n_iter_ser);
	carre.dot[1].color = carre.dot[0].color;
	carre.dot[2].color = carre.dot[0].color;
	carre.dot[3].color = carre.dot[0].color;
	ft_put_line(win, carre.dot[0], carre.dot[1]);
	ft_put_line(win, carre.dot[1], carre.dot[2]);
	ft_put_line(win, carre.dot[2], carre.dot[3]);
	ft_put_line(win, carre.dot[3], carre.dot[0]);
}

static void		recursive(t_window *win, t_carre carre, int step)
{
	t_carre c[9];
	t_carre first;
	int		i;

	draw(win, carre, step);
	if (step++ == win->n_iter_ser)
		return ;
	first.dot[0] = carre.dot[0];
	first.dot[1] = tier(carre.dot[0], carre.dot[1]);
	first.dot[2] = tier(carre.dot[0], carre.dot[2]);
	first.dot[3] = tier(carre.dot[0], carre.dot[3]);
	i = -1;
	while (++i < 9)
		if (i != 4)
		{
			c[i] = decale(first, i % 3, i / 3);
			recursive(win, c[i], step);
		}
}

void			carre(t_window *win, t_image *image)
{
	t_carre	carre;

	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr, &(image->bpp),\
											&(image->s_l), &(image->endian));
	carre.dot[0] = (t_dot){.x = 1 + win->map.ox, .y = 1 - win->map.oy};
	carre.dot[1] = (t_dot){.x = win->width - 1 + win->map.ox,\
							.y = 1 - win->map.oy};
	carre.dot[2] = (t_dot){.x = win->width - 1 + win->map.ox,\
							.y = win->height - 1 - win->map.oy};
	carre.dot[3] = (t_dot){.x = 1 + win->map.ox,\
							.y = win->height - 1 - win->map.oy};
	recursive(win, carre, 0);
}
