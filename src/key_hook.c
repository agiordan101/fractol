/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_hook.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:12:11 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 21:56:18 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	key_hook4(int keycode, t_window *win)
{
	if (keycode == 78)
		win->n_zoom--;
	else if (keycode == 69 && win->n_zoom < 120)
		win->n_zoom++;
	else if (keycode == 33)
		win->map.psy -= win->map.psy - 1 < 0 ? 0 : 1;
	else if (keycode == 30)
		win->map.psy += win->map.psy + 1 >= 8 ? 0 : 1;
	else if (keycode == 15)
		win->tree.angle2 -= PI / 16;
	else if (keycode == 14)
		win->tree.angle2 += PI / 16;
	else if (keycode == 13)
		win->tree.angle1 -= PI / 16;
	else if (keycode == 12)
		win->tree.angle1 += PI / 16;
	else if (keycode == 49)
		win->map.track = !(win->map.track);
	else if (keycode == 29)
		win->h_star += 10;
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
	else if (keycode == 69 && win->n_zoom < 120)
	{
		tmp = win->map.xmin + (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin + (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		win->tree.length += win->tree.length / 5;
	}
	else if (keycode == 25)
		win->h_star -= 10;
}

static void	key_hook2(int keycode, t_window *win)
{
	if (keycode == 43)
	{
		win->n_iter -= win->n_iter - 10 < 0 ? 0 : 10;
		win->n_iter_ser -= win->n_iter_ser - 1 < 0 ? 0 : 1;
		win->n_iter_fern /= 2;
	}
	else if (keycode == 47)
	{
		win->n_iter += 10;
		win->n_iter_ser++;
		win->n_iter_fern *= 2;
	}
	else if (keycode == 126)
	{
		win->map.origin.b -= (win->map.xmax - win->map.xmin) / 10;
		win->map.oy += win->height / 10;
	}
	else if (keycode >= 83 && keycode <= 89)
	{
		re_init(win, &(win->map));
		win->choice = keycode - 82;
	}
}

int			key_hook(int keycode, t_window *win)
{
	if (keycode == 53)
		ft_clear_memory(win);
	else if (keycode == 124)
	{
		win->map.origin.a -= (win->map.xmax - win->map.xmin) / 10;
		win->map.ox += win->width / 10;
	}
	else if (keycode == 123)
	{
		win->map.origin.a += (win->map.xmax - win->map.xmin) / 10;
		win->map.ox -= win->width / 10;
	}
	else if (keycode == 125)
	{
		win->map.origin.b += (win->map.xmax - win->map.xmin) / 10;
		win->map.oy -= win->height / 10;
	}
	else
	{
		key_hook2(keycode, win);
		key_hook3(keycode, win);
		key_hook4(keycode, win);
	}
	ft_refresh(win, &(win->map), &(win->map.image));
	return (0);
}
