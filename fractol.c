/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:09:58 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 17:10:25 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int		ft_clear_memory(t_window *win, t_map *map)
{
	if (!win->mlx)
	{
		ft_putendl("usage: ./fractol [-len width height] [-name window's name] 1 | 2 | 3");
		ft_putendl("1 -> Ensemble de Mandelbrot");
		ft_putendl("2 -> Ensemble de Julia");
		ft_putendl("3 -> ");
	}
	return (1);
}

void	init(t_window *win, t_map *map, t_image *image)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	map->xmin = -(float)win->width / 1000;
	map->xmax = (float)win->width / 1000;
	map->ymin = -(float)win->height / 1000;
	map->ymax = (float)win->height / 1000;
	map->origin.a = 0;
	map->origin.b = 0;
	//printf("%f\n%f\n%f\n%f\n", map->xmin, map->xmax, map->ymin, map->ymax);
}

int main(int ac, char **av)
{
	t_window	win;

	win.mlx = NULL;
	if ((win.choice = params(&win, ac, av)) == -1)
		return (ft_clear_memory(&win, &(win.map)));
	init(&win, &(win.map), &(win.map.image));
	ft_refresh(&win, &(win.map.image));
	mlx_mouse_hook(win.win, mouse_hook, &win);
	mlx_key_hook(win.win, key_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}

//Entrer la precision en parametre, ce qui changera N_ITER
//Ouvrir plusieures fenetre si plusieurs arguments