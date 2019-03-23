/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fern.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/23 20:47:32 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 21:52:52 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	new_point(int r, double *x, double *y)
{
	double	nextx;
	double	nexty;

	if (r < 1)
	{
		nextx = 0;
		nexty = 0.16 * *y;
	}
	else if (r < 86)
	{
		nextx = 0.85 * *x + 0.04 * *y;
		nexty = -0.04 * *x + 0.85 * *y + 1.6;
	}
	else if (r < 93)
	{
		nextx = 0.20 * *x - 0.26 * *y;
		nexty = 0.23 * *x + 0.22 * *y + 1.6;
	}
	else
	{
		nextx = -0.15 * *x + 0.28 * *y;
		nexty = 0.26 * *x + 0.24 * *y + 0.44;
	}
	*x = nextx;
	*y = nexty;
}

void		fern(t_window *win, t_image *image)
{
	int		r;
	double	x;
	double	y;
	t_dot	dot;
	int		i;

	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr, &(image->bpp),\
											&(image->s_l), &(image->endian));
	x = 0;
	y = 0;
	i = -1;
	while (++i < win->n_iter_fern)
	{
		r = rand() % 100;
		new_point(r, &x, &y);
		dot.x = (x - (-2.1820)) / (2.6558 - (-2.1820)) * win->width;
		dot.y = win->height - (y - 0) / (9.9983 - 0) * win->height;
		set_pixel(win, dot.x, dot.y, select_color(win, i));
	}
}
