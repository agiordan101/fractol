/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:09:58 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 18:15:40 by agiordan    ###    #+. /#+    ###.fr     */
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
**	(a^3 - 3ba^2 + ca) + (3ab^2-b^3 + cb)i
**
**	Fonctionnalitées :
**
**	- Mandelbrot
**	- Julia
**	- Zoom									(MOLETTE)
**	- Deplacement 							(FLECHES)
**	- Varier le paramètre de Julia			(DEPLACEMENT SOURIS)
**			<!> BONUS <!>
**	- Plusieures fractales simultane		(./launcher)
**	- Burningship							(3)
**	- Arbre									(4)
**	- Sierpinski Triangle					(5)
**	- Zoom sur le centre					(+/-)
**	- Zoom souris vers le curseur
**	- Recadrage de la fractale				(CLICK)
**	- Pause tracking souris Julia			(SPACE)
**	- Modif. de la prescision				('<' et '>')
**	- Changements couleurs					('[' et ']')
**	- Modif dimension de mandelbrot			('(' et ')')
**	- Flags -name/-len/-tree
*/

int			ft_clear_memory(t_window *win)
{
	int	i;

	if (!win->mlx)
	{
		ft_putstr("usage: ./fractol 1 | 2 | 3 | 4 | 5");
		ft_putstr(" [-len width height] ");
		ft_putendl("[-name window's name] [-tree angle1 angle2]");
		ft_putendl("1 -> Mandelbrot set");
		ft_putendl("2 -> Julia sset");
		ft_putendl("3 -> Burningship");
		ft_putendl("4 -> Tree");
		ft_putendl("5 -> Sierpinski's triangle");
		ft_putendl("6 -> Sierpinski's carpet");
		ft_putendl("7 -> ");
		ft_putendl("8 -> ");
	}
	if (win->ptr_fonctions)
		free(win->ptr_fonctions);
	i = -1;
	if (win->threads)
	{
		while (++i < NBR_THREADS)
			if (win->threads[i])
				free(win->threads[i]);
		free(win->threads);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

static int	init_threads_arbre(t_window *win)
{
	int	i;

	if (!(win->threads = (t_thread **)malloc(sizeof(t_thread *) *\
											(NBR_THREADS + 1))))
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

void		re_init(t_window *win, t_map *map)
{
	map->xmin = -(double)win->width / 1000;
	map->xmax = (double)win->width / 1000;
	map->ymin = -(double)win->height / 1000;
	map->ymax = (double)win->height / 1000;
	map->origin = (t_complexe){.a = 0, .b = 0};
	map->julia = (t_complexe){.a = 0.3, .b = 0.5};
	map->track = 1;
	map->power = 2;
	map->ox = 0;
	map->oy = 0;
	win->n_iter = 100;
	win->n_iter_ser = 5;
	win->map.psy = 1;
	win->tree.length = win->height / 10;
}

int			init(t_window *win, t_map *map, t_image *image)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr,
					&(image->bpp), &(image->s_l), &(image->endian));
	if (!(win->ptr_fonctions = (void **)malloc(sizeof(void *) * (3 + 1))))
		return (1);
	win->ptr_fonctions[0] = &mandelbrot;
	win->ptr_fonctions[1] = &julia;
	win->ptr_fonctions[2] = &burningship;
	win->ptr_fonctions[3] = NULL;
	re_init(win, map);
	if (init_threads_arbre(win))
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	t_window	win;

	win.mlx = NULL;
	if ((win.choice = params(&win, ac, av)) == -1)
		ft_clear_memory(&win);
	if (init(&win, &(win.map), &(win.map.image)))
		ft_clear_memory(&win);
	ft_refresh(&win, &(win.map), &(win.map.image));
	mlx_hook(win.win, 17, 0, &ft_clear_memory, &win);
	mlx_hook(win.win, 6, 0, &tracking_mouse, &win);
	mlx_mouse_hook(win.win, mouse_hook, &win);
	mlx_key_hook(win.win, key_hook, &win);
	mlx_loop(win.mlx);
	return (0);
}
