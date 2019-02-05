/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hook.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:12:11 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 16:15:49 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int		tracking_mouse(int x, int y, t_window *win)
{
	t_map	*map;

	if (win->choice == 2 && win->map.track)
	{
		map = &(win->map);
		map->julia.a = map->xmin + map->origin.a + x * map->dx;
		map->julia.b =  map->ymax + map->origin.b - y * map->dy;
		ft_refresh(win, &(win->map), &(win->map.image));
	}
	return (0);
}

int		key_hook(int keycode, t_window *win)
{
	double	tmp;

	printf("key : %i\n", keycode);
	if (keycode == 53)
		ft_clear_memory(win);
	else if (keycode == 124)
	{
		win->map.origin.a -= (win->map.xmax - win->map.xmin) / 10;
		win->tree.ox += win->width / 10;
	}
	else if (keycode == 123)
	{
		win->map.origin.a += (win->map.xmax - win->map.xmin) / 10;
		win->tree.ox -= win->width / 10;
	}
	else if (keycode == 125)
	{
		win->map.origin.b += (win->map.xmax - win->map.xmin) / 10;
		win->tree.oy -= win->height / 10;
	}
	else if (keycode == 126)
	{
		win->map.origin.b -= (win->map.xmax - win->map.xmin) / 10;
		win->tree.oy += win->height / 10;
	}
	else if (keycode == 83)
		win->choice = 1;
	else if (keycode == 84)
		win->choice = 2;
	else if (keycode == 85)
		win->choice = 3;
	else if (keycode == 86)
		win->choice = 4;
	else if (keycode == 78)
	{
		tmp = win->map.xmin - (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax += (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin - (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax += (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		win->tree.length -= win->tree.length / 5;
	}
	else if (keycode == 69)
	{
		tmp = win->map.xmin + (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin + (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		win->tree.length += win->tree.length / 5;
	}
	else if (keycode == 43)
		win->n_iter -= win->n_iter - 10 < 1 ? 0 : 10;
	else if (keycode == 47)
		win->n_iter += 10;
	else if (keycode == 33)
		win->map.psy -= win->map.psy - 10 < 1 ? 0 : 10;
	else if (keycode == 30)
		win->map.psy += 10;
	else if (keycode == 15)
		win->tree.angle1 -= PI / 16;
	else if (keycode == 14)
		win->tree.angle1 += PI / 16;
	else if (keycode == 13)
		win->tree.angle2 -= PI / 16;
	else if (keycode == 12)
		win->tree.angle2 += PI / 16;
	else if (keycode == 49)
		win->map.track = !(win->map.track);
	ft_refresh(win, &(win->map), &(win->map.image));
	return (0);
}

int		mouse_hook(int button, int x, int y, t_window *win)
{
	double	tmp;

	//printf("key : %i\n", button);
	if (button == 1 || button == 2)
	{
		win->map.origin.a += win->map.xmin + x * win->map.dx;
		win->map.origin.b += win->map.ymax - y * win->map.dy;
	}
	if (button == 4)
	{
		printf("xmin = %.20f\ndx = %.20f\nox = %.20f\n\n\n", win->map.xmin, win->map.dx, win->map.origin.a);
		win->map.origin.a -= ((win->map.origin.a + win->map.xmin + x * win->map.dx) - win->map.origin.a) / 5;
		win->map.origin.b -= ((win->map.origin.b + win->map.ymin + (win->height - y) * win->map.dy) - win->map.origin.b) / 5;
		
		tmp = win->map.xmin - (win->map.xmax - win->map.xmin) / 50;
		win->map.xmax += (win->map.xmax - win->map.xmin) / 50;
		win->map.xmin = tmp;
		tmp = win->map.ymin - (win->map.ymax - win->map.ymin) / 50;
		win->map.ymax += (win->map.ymax - win->map.ymin) / 50;
		win->map.ymin = tmp;
		win->tree.length -= win->tree.length / 5;
		//printf("xmin = %f\ndx = %f\nox = %f\n\n\n", win->map.xmin, win->map.dx, win->map.origin.a);
	}
	else if (button == 5) //ZOOM
	{
		printf("Souris = %.20f\n", win->map.xmin + x * win->map.dx);
		printf("xmin = %.20f\nxmax = %.20f\ndx = %.20f\nox = %.20f\n\n\n", win->map.xmin, win->map.xmax, win->map.dx, win->map.origin.a);
		
		win->map.origin.a += ((win->map.origin.a + win->map.xmin + x * win->map.dx) - win->map.origin.a) / 5;
		win->map.origin.b += ((win->map.origin.b + win->map.ymin + (win->height - y) * win->map.dy) - win->map.origin.b) / 5;

		tmp = win->map.xmin + (win->map.xmax - win->map.xmin) / 50;
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 50;
		win->map.xmin = tmp;
		tmp = win->map.ymin + (win->map.ymax - win->map.ymin) / 50;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 50;
		win->map.ymin = tmp;
		win->tree.length += win->tree.length / 5;
		//printf("xmin = %f\ndx = %f\nox = %f\n\n\n", win->map.xmin, win->map.dx, win->map.origin.a);
	}
	ft_refresh(win, &(win->map), &(win->map.image));
	return (0);
}
//(value - inter1.x) / (inter1.y - inter1.x) * (inter2.y - inter2.x)
//250 / 1000 * (90 - 50) + 50
