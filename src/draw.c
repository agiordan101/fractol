/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 06:31:50 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 21:27:57 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	my_fractals(t_window *win, t_image *image, t_tree *s_tree)
{
	if (win->choice == 4)
		tree(win, image, s_tree);
	else if (win->choice == 5)
		triangle(win, image);
	else if (win->choice == 6)
		carre(win, image);
	else if (win->choice == 7)
		star(win, image);
	else if (win->choice == 8)
		fern(win, image);
	else
		approaching_pi(win);
}

void	ft_refresh(t_window *win, t_map *map, t_image *image)
{
	int	i;

	if (win->choice >= 4 && win->choice <= 9)
		my_fractals(win, &(win->map.image), &(win->tree));
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
