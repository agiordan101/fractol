/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tree.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 19:09:24 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 17:44:27 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	trace(t_window *win, t_dot *d1, t_dot *d2, int i)
{
	d2->x = d1->x + win->tree.length * cos(win->tree.tmpdir +
	(i ? win->tree.angle2 : win->tree.angle1));
	d2->y = d1->y - win->tree.length * sin(win->tree.tmpdir +
	(i ? win->tree.angle2 : win->tree.angle1));
	win->tree.x = d2->x;
	win->tree.y = d2->y;
	win->tree.dir = win->tree.tmpdir +\
									(i ? win->tree.angle2 : win->tree.angle1);
}

static void	recursive(t_window *win, t_tree tree, int step)
{
	t_dot	d1;
	t_dot	d2;
	int		i;

	if (step < win->n_iter / 6)
	{
		d1.x = tree.x;
		d1.y = tree.y;
		d1.color = map_color(win, 0x49e55b, 0xc456f7,\
								step / (double)(win->n_iter / 10));
		//printf("Color : %#x\tstep : %i\tmaxstep : %i\n", d1.color, step, win->n_iter / 10);
		tree.length -= tree.length / 5;
		tree.tmpdir = tree.dir;
		i = -1;
		while (++i < 2)
		{
			trace(win, &d1, &d2, i);
			d2.color = map_color(win, 0x49e55b, 0xc456f7,\
							(step + 1) / (double)(win->n_iter / 10));
			ft_put_line(win, d1, d2);
			recursive(win, tree, step + 1);
		}
	}
}

void		tree(t_window *win, t_image *image, t_tree *tree)
{
	//printf("New tree\n");
	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	tree->x = win->width / 2 + tree->ox;
	tree->y = win->height / 2 - tree->oy;
	tree->dir = PI / 2;
	recursive(win, *tree, 0);
}
