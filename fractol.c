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

int		init(t_map *map)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	map->origin.x = map->width / 2;
	map->origin.y = map->height / 2;
	return (0);
}

int main(int ac, char **av)
{
	t_map	map;

	if (params(&map, ac, av) == -1)
		return (1);
	if (init(&map))
		return (1);
	mandelbrot(&map);
	mlx_mouse_hook(map.win, mouse_hook, &win);
	mlx_key_hook(map.win, key_hook, &win);
	mlx_loop(map.mlx);
	return (0);
}
