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

/*
**	Z(n) = a + bi
**
**	Z(n+1) = Z(n) * Z(n) + c
**		   = (a + bi)(a + bi) + (ca + cb * i)
**		   = (a*a - b*b + ca) + (2 * a * b + cb) * i
**
**	Re(Z(n+1)) = a*a - b*b + ca
**	Im(Z(n+1)) = 2 * a * b + cb
**
**	Z(n) = (abs(a) + i * abs(b))(...) + (ca + i * cb)
**		 =	(a*a - b*b + ca) + (2 * abs(a)abs(b) + cb) * i
**	
**	Re(Z(n+1)) = a*a - b*b + ca
**	Im(Z(n+1)) = 2 * abs(a)abs(b) + cb
**
**	<!!!> BONUS <!!!>
**
**	- Burningship
**	-
**	-
**	- Deplacement fleches
**	- Zoom centre -/+
**	- Zoom souris ciblé
**	- Recadrage du centre click souris
**	- Pause tracking souris Julia
**	- Modif de la prescision
**	- Flags name/len
*/

int			ft_clear_memory(t_window *win)
{
	int	i;

	if (!win->mlx)
	{
		ft_putendl("usage: ./fractol [-len width height] [-name window's name] 1 | 2 | 3");
		ft_putendl("1 -> Ensemble de Mandelbrot");
		ft_putendl("2 -> Ensemble de Julia");
		ft_putendl("3 -> Burningship");
	}
	i = -1;
	if (win->threads)
	{
		while (++i < NBR_THREADS)
			free(win->threads[i]);
		free(win->threads);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

static int	init_threads(t_window *win, t_map *map, t_image *image)
{
	int	i;

	if (!(win->threads = (t_thread **)malloc(sizeof(t_thread *) * (NBR_THREADS + 1))))
		return (1);
	win->threads[NBR_THREADS] = NULL;
	i = -1;
	while (++i < NBR_THREADS)
	{
		if (!(win->threads[i] = (t_thread *)malloc(sizeof(t_thread))))
			return (1);
		win->threads[i]->win = win;
	}	
	return (0);
}

int			init(t_window *win, t_map *map, t_image *image)
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
	map->julia.a = 0.3;
	map->julia.b = 0.5;
	map->track = 1;
	win->ptr_fonctions = (void **)malloc(sizeof(void *) * (3 + 1));
	win->ptr_fonctions[0] = &mandelbrot;
	win->ptr_fonctions[1] = &julia;
	win->ptr_fonctions[2] = &burningship;
	win->ptr_fonctions[3] = NULL;
	win->n_iter = 200;
	win->map.psy = 1;
	if (init_threads(win, map, image))
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	t_window	win;

	win.mlx = NULL;
	if ((win.choice = params(&win, ac, av)) == -1)
		ft_clear_memory(&win);
	printf("Fin params\n");
	if (init(&win, &(win.map), &(win.map.image)))
		ft_clear_memory(&win);
	printf("Fin init\n");
	ft_refresh(&win, &(win.map), &(win.map.image));
	mlx_hook(win.win, 17, 0, &ft_clear_memory, &win);
	mlx_hook(win.win, 6, 0, &tracking_mouse, &win);
	mlx_mouse_hook(win.win, mouse_hook, &win);
	mlx_key_hook(win.win, key_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}

//Multi threads
//Makefile qui recompile pas la mlx