/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse_hook.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/06 16:38:20 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/22 17:52:22 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

static void	mouse_hook2(int button, int x, int y, t_window *win)
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
