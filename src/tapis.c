/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tapis.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/18 21:34:08 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/18 22:12:52 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fractol.h"

static t_dot		tier(t_dot d1, t_dot d2)
{
	return ((t_dot){.x = d1.x + (d1.x + d2.x) / 3, .y = d1.y + (d1.y + d2.y) / 3});
}

static t_carre		decale(t_carre carre, int x, int y)
{
	t_carre newCarre;
	double	dx;
	double	dy;

	dx = carre.dot[1].x - carre.dot[0].x;
	dy = carre.dot[3].y - carre.dot[0].y;
	newCarre.dot[0] = (t_dot){carre.dot[0].x + dx * x, carre.dot[0].y + dy * y};
	newCarre.dot[1] = (t_dot){carre.dot[1].x + dx * x, carre.dot[1].y + dy * y};
	newCarre.dot[2] = (t_dot){carre.dot[2].x + dx * x, carre.dot[2].y + dy * y};
	newCarre.dot[3] = (t_dot){carre.dot[3].x + dx * x, carre.dot[3].y + dy * y};
	return (newCarre);
}

static void			draw(t_window *win, t_carre carre, int step)
{
	carre.dot[0].color = map_color(0x49e55b, 0xc456f7,\
								(step + 1) / (double)(win->n_iter / 10));
	carre.dot[1].color = map_color(0x49e55b, 0xc456f7,\
								(step + 1) / (double)(win->n_iter / 10));
	carre.dot[2].color = map_color(0x49e55b, 0xc456f7,\
								(step + 1) / (double)(win->n_iter / 10));
	carre.dot[3].color = map_color(0x49e55b, 0xc456f7,\
								(step + 1) / (double)(win->n_iter / 10));
	ft_put_line(win, carre.dot[0], carre.dot[1]);
	ft_put_line(win, carre.dot[1], carre.dot[2]);
	ft_put_line(win, carre.dot[2], carre.dot[3]);
	ft_put_line(win, carre.dot[3], carre.dot[0]);
}

static void			recursive(t_window *win, t_carre carre, int step)
{
	t_carre c[8];
	int		i;
	int		j;

	draw(win, carre, step);
	if (step++ > win->n_iter / 10)
		return ;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			c[i].dot[0] = carre.dot[0];
			c[i].dot[1] = tier(carre.dot[0], carre.dot[1]);
			c[i].dot[2] = tier(carre.dot[0], carre.dot[2]);
			c[i].dot[3] = tier(carre.dot[0], carre.dot[3]);
			decale(carre, j, i);
		}
	}
	i = -1;
	while (++i < 8)
		recursive(win, c[i], step);
}

void				carre(t_window *win, t_image *image)
{
	t_carre	carre;

	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	carre.dot[0] = (t_dot){.x = 1 + win->map.ox,\
								.y = win->height - 1 - win->map.oy};
	carre.dot[1] = (t_dot){.x = win->width / 2 + win->map.ox,\
								.y = 1 - win->map.oy};
	carre.dot[2] = (t_dot){.x = win->width - 1 + win->map.ox,\
								.y = win->height - 1 - win->map.oy};
	draw(win, carre, 0);
	recursive(win, carre, 1);
}