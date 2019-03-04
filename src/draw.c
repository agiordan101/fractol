/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 06:31:50 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/04 21:25:39 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	ft_refresh(t_window *win, t_map *map, t_image *image)
{
	int	i;

	if (win->choice == 4)
		tree(win, &(win->map.image), &(win->tree));
	else if (win->choice == 5)
		triangle(win, &(win->map.image));
	else if (win->choice == 6)
		carre(win, &(win->map.image));
	else if (win->choice == 7)
		star(win, &(win->map.image));
	else
	{
		map->dx = (map->xmax - map->xmin) / (double)win->width;
		map->dy = (map->ymax - map->ymin) / (double)win->height;
		i = -1;
		while (++i < NBR_THREADS)
		{
			win->threads[i]->quarter = i;
			pthread_create(&(win->threads[i]->thread), NULL,\
						win->ptr_fonctions[win->choice - 1], win->threads[i]);
		}
		i = -1;
		while (++i < NBR_THREADS)
			pthread_join(win->threads[i]->thread, NULL);
	}
	mlx_clear_window(win->mlx, win->win);
	mlx_put_image_to_window(win->mlx, win->win, image->image_ptr, 0, 0);
}

int		map_color(int mincolor, int maxcolor, double prop)
{
	int r;
	int g;
	int b;

	r = (int)(prop * (((maxcolor >> 16) & 0xFF) - ((mincolor >> 16) & 0xFF))) +\
		((mincolor >> 16) & 0xFF);
	g = (int)(prop * (((maxcolor >> 8) & 0xFF) - ((mincolor >> 8) & 0xFF))) +\
		((mincolor >> 8) & 0xFF);
	b = (int)(prop * ((maxcolor & 0xFF) - (mincolor & 0xFF))) +\
		(mincolor & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

void	set_pixel(t_window *win, int x, int y, int color)
{
	if ((x > 0 && x < win->width) && (y > 0 && y < win->height))
		win->map.image.image[x + y * win->width] = color;
}

void	ft_put_line(t_window *win, t_dot d1, t_dot d2)
{
	t_dot	pas;
	int		nbpixels;
	int		i;
	int		color;

	pas.x = d2.x - d1.x;
	pas.y = d2.y - d1.y;
	if (ft_abs(pas.x) > ft_abs(pas.y))
	{
		nbpixels = ft_abs(pas.x);
		pas.y /= ft_abs(pas.x);
		pas.x /= ft_abs(pas.x);
	}
	else
	{
		nbpixels = ft_abs(pas.y);
		pas.x /= ft_abs(pas.y);
		pas.y /= ft_abs(pas.y);
	}
	i = -1;
	while (++i < nbpixels)
	{
		color = map_color(d1.color, d2.color, i / (double)nbpixels);
		set_pixel(win, d1.x + pas.x * i, d1.y + pas.y * i, color);
	}
}
