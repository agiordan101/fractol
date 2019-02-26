/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   star.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/26 18:50:42 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 19:25:44 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static t_dot	tier(t_line line, int n)
{
	return ((t_dot){.x = line.d1.x + n * (line.d2.x - line.d1.x) / 3,\
					.y = line.d1.y + n * (line.d2.y - line.d1.y) / 3});
}

static void			draw(t_window *win, t_line line, int step)
{
	line.d1.color = map_color(0x30EE30, 0xAA2020,\
								step / (double)win->n_iter_ser);
	line.d2.color = map_color(0x30EE30, 0xAA2020,\
								step / (double)win->n_iter_ser);
	ft_put_line(win, line.d1, line.d2);
}

static void			recursive(t_window *win, t_line line, int step)
{
	t_line l1;
	t_line l2;
	t_line l3;
	t_line l4;

	if (step++ > win->n_iter_ser)
	{
		draw(win, line, step);
		return ;
	}
	l1.d1 = line.d1;
	l1.d2 = tier(line, 1);
	l2.d1 = l1.d2;
	l2.d2 = 
	l3.d1 = l2.d2;
	l3.d2 = tier(line, 2);
	l4.d1 = l3.d2;
	l4.d2 = line.d2;
	recursive(win, l1, step);
	recursive(win, l2, step);
	recursive(win, l3, step);
	recursive(win, l3, step);
}

void				line(t_window *win, t_image *image)
{
	t_line	line;

	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	line.d1 = (t_dot){.x = 1 + win->map.ox,\
								.y = win->height / 2 - win->map.oy};
	line.d2 = (t_dot){.x = win->width - 1 + win->map.ox,\
								.y = win->height / 2 - win->map.oy};
	recursive(win, line, 0);
}