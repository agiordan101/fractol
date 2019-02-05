/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hook.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:12:11 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/05 19:56:22 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	key_hook4(int keycode, t_window *win)
{
	if (keycode == 43)
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
}

static void	key_hook3(int keycode, t_window *win)
{
	double	tmp;

	if (keycode == 78)
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
}

static void	key_hook2(int keycode, t_window *win)
{
	if (keycode == 126)
	{
		win->map.origin.b -= (win->map.xmax - win->map.xmin) / 10;
		win->tree.oy += win->height / 10;
	}
	else if (keycode == 83)
	{
		re_init(win, &(win->map));
		win->choice = 1;
	}
	else if (keycode == 84)
	{
		re_init(win, &(win->map));
		win->choice = 2;
	}
	else if (keycode == 85)
	{
		re_init(win, &(win->map));
		win->choice = 3;
	}
	else if (keycode == 86)
	{
		re_init(win, &(win->map));
		win->choice = 4;
	}
}

int			key_hook(int keycode, t_window *win)
{
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
	key_hook2(keycode, win);
	key_hook3(keycode, win);
	key_hook4(keycode, win);
	ft_refresh(win, &(win->map), &(win->map.image));
	return (0);
}

int			mouse_hook2(int button, int x, int y, t_window *win)
{
	double	tmp;

	if (button == 5)
	{
		win->map.origin.a += ((win->map.origin.a + win->map.xmin +\
									x * win->map.dx) - win->map.origin.a) / 5;
		win->map.origin.b += ((win->map.origin.b + win->map.ymin +\
					(win->height - y) * win->map.dy) - win->map.origin.b) / 5;
		tmp = win->map.xmin + (win->map.xmax - win->map.xmin) / 50;
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 50;
		win->map.xmin = tmp;
		tmp = win->map.ymin + (win->map.ymax - win->map.ymin) / 50;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 50;
		win->map.ymin = tmp;
		win->tree.length += win->tree.length / 5;
	}
}

int			mouse_hook(int button, int x, int y, t_window *win)
{
	double	tmp;

	if (button == 1 || button == 2)
	{
		win->map.origin.a += win->map.xmin + x * win->map.dx;
		win->map.origin.b += win->map.ymax - y * win->map.dy;
	}
	if (button == 4)
	{
		win->map.origin.a -= ((win->map.origin.a + win->map.xmin +\
									x * win->map.dx) - win->map.origin.a) / 5;
		win->map.origin.b -= ((win->map.origin.b + win->map.ymin +\
					(win->height - y) * win->map.dy) - win->map.origin.b) / 5;
		tmp = win->map.xmin - (win->map.xmax - win->map.xmin) / 50;
		win->map.xmax += (win->map.xmax - win->map.xmin) / 50;
		win->map.xmin = tmp;
		tmp = win->map.ymin - (win->map.ymax - win->map.ymin) / 50;
		win->map.ymax += (win->map.ymax - win->map.ymin) / 50;
		win->map.ymin = tmp;
		win->tree.length -= win->tree.length / 5;
	}
	else
		mouse_hook2(button, x, y, win);
	ft_refresh(win, &(win->map), &(win->map.image));
	return (0);
}
