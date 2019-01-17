/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 06:31:50 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/17 06:32:00 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	ft_refresh(t_window *win, t_image *image)
{
	mlx_clear_window(win->mlx, win->win);//
	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	if (win->choice == 1)
		mandelbrot(win, &(win->map), &(win->map.image));
	else if (win->choice == 2)
		julia(win, &(win->map), &(win->map.image));
	//else
		////
	mlx_put_image_to_window(win->mlx, win->win, image->image_ptr, 0, 0);
}

int		map_color(t_window *win, int mincolor, int maxcolor, double prop)
{
	int r;
	int g;
	int b;

	r = (int)(prop * (((maxcolor >> 16) & 0xFF) - ((mincolor >> 16) & 0xFF))) +
		((mincolor >> 16) & 0xFF);
	g = (int)(prop * (((maxcolor >> 8) & 0xFF) - ((mincolor >> 8) & 0xFF))) +
		((mincolor >> 8) & 0xFF);
	b = (int)(prop * ((maxcolor & 0xFF) - (mincolor & 0xFF))) +
		(mincolor & 0xFF);
	return ((r << 16) | (g << 8) | (b | 0));
}

void	set_pixel(t_window *win, int x, int y, int color)
{
	if ((x > 0 && x < win->width) && (y > 0 && y < win->height))
		win->map.image.image[x + y * win->width] = color;
}
