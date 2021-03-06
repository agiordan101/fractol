/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:09:58 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 21:33:54 by agiordan    ###    #+. /#+    ###.fr     */
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
**	Fonctionnalitées :
**
**	- Mandelbrot
**	- Julia
**	- Burningship							(3)
**	- Zoom									(MOLETTE)
**	- Deplacement 							(FLECHES)
**	- Varier le paramètre de Julia			(DEPLACEMENT SOURIS)
**
**			<!> BONUS <!>
**	- Plusieures fractales simultane		(./launcher)
**	- Varier le paramètre de Mandelbrot		(DEPLACEMENT SOURIS)
**	- Varier le paramètre de Burningship	(DEPLACEMENT SOURIS)
**	- Pause tracking souris					(SPACE)
**	- Arbre									(4)
**	- Triangle de Sierpinski 				(5)
**	- Tapis de Sierpinski 					(6)
**	- Star									(7)
**	- Barnsley fern (fougere)				(8)
**	- Approximation de PI avec Mandelbrot	(9)
**	- Zoom sur le centre					(+/-)
**	- Zoom vers le curseur de la souris		(ROULETTE SOURIS)
**	- Recadrage de la fractale				(CLICK)
**	- Modif. des iterations					('<' et '>')
**	- Changements couleurs					('[' et ']')
**	- Varier hauteur triangle fractale star	('(' et ')')
**	- Flags -name/-len/-tree
*/

int			ft_clear_memory(t_window *win)
{
	if (!win->mlx)
	{
		ft_putstr("usage: ./fractol 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9");
		ft_putstr(" [-len width height] ");
		ft_putendl("[-name window's name] [-tree angle1 angle2]");
		ft_putendl("\n1 -> Mandelbrot set");
		ft_putendl("2 -> Julia set");
		ft_putendl("3 -> Burningship");
		ft_putendl("4 -> Tree");
		ft_putendl("5 -> Sierpinski's triangle");
		ft_putendl("6 -> Sierpinski's carpet");
		ft_putendl("7 -> Star");
		ft_putendl("8 -> Barnsley fern");
		ft_putendl("9 -> Approximation of PI");
	}
	if (win->map.image.image_ptr)
		mlx_destroy_image(win->mlx, win->map.image.image_ptr);
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	ft_tab2del((void ***)(&(win->threads)));
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
	map->julia = (t_complexe){.a = 0, .b = 0};
	map->track = 0;
	map->ox = 0;
	map->oy = 0;
	win->n_iter = 40;
	win->n_iter_ser = 6;
	win->n_iter_fern = 1000000;
	win->n_digits = 1;
	win->n_zoom = 0;
	win->map.psy = N_COLORS;
	win->h_star = 0;
	win->tree.length = win->height / 10;
}

int			init(t_window *win, t_map *map, t_image *image)
{
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	image->image_ptr = mlx_new_image(win->mlx, win->width, win->height);
	image->image = (int *)mlx_get_data_addr(image->image_ptr, &(image->bpp),\
											&(image->s_l), &(image->endian));
	win->ptr_fonctions[0] = &mandelbrot;
	win->ptr_fonctions[1] = &julia;
	win->ptr_fonctions[2] = &burningship;
	win->ptr_fonctions[3] = NULL;
	init_colors(win);
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
