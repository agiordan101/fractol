/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   triangle.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 18:50:58 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 17:23:14 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static t_dot		middle(t_dot d1, t_dot d2)
{
	return ((t_dot){.x = (d1.x + d2.x) / 2, .y = (d1.y + d2.y) / 2});
}

static void			draw(t_window *win, t_triangle triangle, int step)
{
	triangle.dot[0].color = map_color(0x30EE30, 0xAA2020,\
								step / (double)win->n_iter_ser);
	triangle.dot[1].color = triangle.dot[0].color;
	triangle.dot[2].color = triangle.dot[0].color;
	ft_put_line(win, triangle.dot[0], triangle.dot[1]);
	ft_put_line(win, triangle.dot[1], triangle.dot[2]);
	ft_put_line(win, triangle.dot[2], triangle.dot[0]);
}

static void			recursive(t_window *win, t_triangle triangle, int step)
{
	t_triangle t1;
	t_triangle t2;
	t_triangle t3;

	draw(win, triangle, step);
	if (step++ == win->n_iter_ser)
		return ;
	t1.dot[0] = triangle.dot[0];
	t1.dot[1] = middle(triangle.dot[0], triangle.dot[1]);
	t1.dot[2] = middle(triangle.dot[0], triangle.dot[2]);
	t2.dot[0] = middle(triangle.dot[0], triangle.dot[1]);
	t2.dot[1] = triangle.dot[1];
	t2.dot[2] = middle(triangle.dot[1], triangle.dot[2]);
	t3.dot[0] = middle(triangle.dot[0], triangle.dot[2]);
	t3.dot[1] = middle(triangle.dot[1], triangle.dot[2]);
	t3.dot[2] = triangle.dot[2];
	recursive(win, t1, step);
	recursive(win, t2, step);
	recursive(win, t3, step);
}

void				triangle(t_window *win, t_image *image)
{
	t_triangle	triangle;

	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr, &(image->bpp),\
											&(image->s_l), &(image->endian));
	triangle.dot[0] = (t_dot){.x = 1 + win->map.ox,\
								.y = win->height - 1 - win->map.oy};
	triangle.dot[1] = (t_dot){.x = win->width / 2 + win->map.ox,\
								.y = 1 - win->map.oy};
	triangle.dot[2] = (t_dot){.x = win->width - 1 + win->map.ox,\
								.y = win->height - 1 - win->map.oy};
	recursive(win, triangle, 0);
}
