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
	pthread_t	p1;
	pthread_t	p2;
	pthread_t	p3;

	//mlx_clear_window(win->mlx, win->win);//
	mlx_destroy_image(win->mlx, image->image_ptr);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	
	printf("Debut refresf threads\n");
	win->quarter = 1;
	pthread_create(&p1, NULL, win->ptr_fonctions[win->choice - 1], win);
	printf("Apres thread 1\n");
	win->quarter = 2;
	pthread_create(&p2, NULL, win->ptr_fonctions[win->choice - 1], win);
	printf("Apres thread 2\n");
	win->quarter = 3;
	pthread_create(&p3, NULL, win->ptr_fonctions[win->choice - 1], win);
	printf("Apres thread 3\n");
	
	win->quarter = 4;
	if (win->choice == 1)
		mandelbrot(win);
	else if (win->choice == 2)
		julia(win, &(win->map), &(win->map.image));
	else
		burningship(win, &(win->map), &(win->map.image));

	printf("Apres quarter 4\n");
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	printf("Apres join\n");
	mlx_put_image_to_window(win->mlx, win->win, image->image_ptr, 0, 0);
}

		/*win->quarter = 1;
		mandelbrot(win);
		win->quarter = 2;
		mandelbrot(win);
		win->quarter = 3;
		mandelbrot(win);
		win->quarter = 4;*/


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
