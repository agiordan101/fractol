/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arbre.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/23 19:09:24 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/24 18:16:06 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	recursive(t_window *win, t_arbre arbre, int step)
{
	t_dot   d1;
	t_dot   d2;
	int		i;

	if (step < win->n_iter / 10)
	{
		d1.x = arbre.x;
		d1.y = arbre.y;
		d1.color = map_color(win, 0x49e55b, 0xc456f7, step / (double)(win->n_iter / 10));
		//printf("Color : %#x\tstep : %i\tmaxstep : %i\n", d1.color, step, win->n_iter / 10);
		i = -1;
		while (++i < 2)
		{
			d2.x = d1.x + arbre.length * cos(arbre.dir +
			(i ? arbre.angle2 : arbre.angle1));
			d2.y = d1.y - arbre.length * sin(arbre.dir +
			(i ? arbre.angle2 : arbre.angle1));
			d2.color = map_color(win, 0x49e55b, 0xc456f7, (step + 1) / (double)(win->n_iter / 10));
			if (step > 6)
				ft_put_line(win, d1, d2);
			arbre.x = d2.x;
			arbre.y = d2.y;
			arbre.dir = arbre.dir + (i ? arbre.angle2 : arbre.angle1);
			arbre.length -= arbre.length / 5;
			recursive(win, arbre, step + 1);
		}
	}
}

void		arbre(t_window *win, t_image *image, t_arbre *arbre)
{
	printf("New arbre\n");
	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	arbre->x = win->width / 2 + arbre->ox;
	arbre->y = win->height + arbre->oy;
	arbre->length = win->height / 4;
	arbre->dir = PI / 2;
	arbre->angle1 = -PI / 4;
	arbre->angle2 = PI / 4;
	recursive(win, *arbre, 0);
}
