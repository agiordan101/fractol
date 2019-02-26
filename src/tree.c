/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tree.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 19:09:24 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 18:39:53 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	trace(t_tree *tree, t_dot *d1, t_dot *d2, int i)
{
	if (i)
	{
		d2->x = d1->x + tree->length * cos(tree->tmpdir + tree->angle2);
		d2->y = d1->y - tree->length * sin(tree->tmpdir + tree->angle2);
	}
	else
	{
		d2->x = d1->x + tree->length * cos(tree->tmpdir + tree->angle1);
		d2->y = d1->y - tree->length * sin(tree->tmpdir + tree->angle1);
	}
	tree->x = d2->x;
	tree->y = d2->y;
	tree->dir = tree->tmpdir + (i ? tree->angle2 : tree->angle1);
}

static void	recursive(t_window *win, t_tree tree, int step)
{
	t_dot	d1;
	t_dot	d2;
	int		i;

	if (step > win->n_iter_ser)
		return ;
	d1 = (t_dot){.x = tree.x, .y = tree.y, .color =\
				map_color(0x49e55b, 0xc456f7, step / (double)win->n_iter_ser)};
	tree.length -= tree.length / 5;
	tree.tmpdir = tree.dir;
	i = -1;
	while (++i < 2)
	{
		trace(&tree, &d1, &d2, i);
		if (!((d1.x < 0 || d1.x > win->width || d1.y < 0 ||\
				d1.y > win->height) && (d2.x < 0 || d2.x > win->width ||\
				d2.y < 0 || d2.y > win->height)))
		{
			d2.color = map_color(0x49e55b, 0xc456f7,\
								step / (double)win->n_iter_ser);
			ft_put_line(win, d1, d2);
		}
		recursive(win, tree, step + 1);
	}
}

void		tree(t_window *win, t_image *image, t_tree *tree)
{
	t_dot	d1;
	t_dot	d2;

	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	tree->x = win->width / 2 + win->map.ox;
	tree->y = win->height / 2 - win->map.oy;
	d1.x = tree->x;
	d1.y = tree->y + tree->length;
	d2.x = tree->x;
	d2.y = tree->y;
	d1.color = map_color(0x49e55b, 0xc456f7, 0);
	d2.color = map_color(0x49e55b, 0xc456f7, 0);
	ft_put_line(win, d1, d2);
	tree->dir = PI / 2;
	recursive(win, *tree, 0);
}
