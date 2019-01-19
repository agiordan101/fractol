/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hook.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:12:11 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 17:12:12 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int		key_hook(int keycode, t_window *win)
{
	float	tmp;

	printf("key : %i\n", keycode);
	if (keycode == 53)
		ft_clear_memory(win);
	else if (keycode == 124)
		win->map.origin.a -= (win->map.xmax - win->map.xmin) / 10;
	else if (keycode == 123)
		win->map.origin.a += (win->map.xmax - win->map.xmin) / 10;
	else if (keycode == 125)
		win->map.origin.b += (win->map.xmax - win->map.xmin) / 10;
	else if (keycode == 126)
		win->map.origin.b -= (win->map.xmax - win->map.xmin) / 10;
	else if (keycode == 83)
		win->choice = 1;
	else if (keycode == 84)
		win->choice = 2;
	else if (keycode == 85)
		win->choice = 3;
	else if (keycode == 78)
	{
		tmp = win->map.xmin - (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax += (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin - (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax += (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		ft_refresh(win, &(win->map.image));
	}
	else if (keycode == 69)
	{
		tmp = win->map.xmin + (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin + (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		ft_refresh(win, &(win->map.image));
	}
	if (keycode >= 123 && keycode <= 126)
		ft_refresh(win, &(win->map.image));
	return (0);
}

int		mouse_hook(int button, int x, int y, t_window *win)
{
	float	tmp;

	if (button == 1 || button == 2)
	{
		win->map.origin.a = x * win->map.dx + win->map.xmin;
		win->map.origin.b = (win->height - y) * win->map.dy + win->map.ymin;
		ft_refresh(win, &(win->map.image));
	}
	if (button == 4 || button == 5)
	{
		//printf("x = %i\ty = %i\n", x, y);
		win->map.origin.a = x * win->map.dx + win->map.xmin;
		win->map.origin.b = (win->height - y) * win->map.dy + win->map.ymin;
		//win->map.origin.a = ((float)x / ((float)(win->width))) * (win->map.xmax - win->map.xmin) + win->map.xmin;
		//win->map.origin.b = (((float)(win->height) - (float)y) / (float)(win->height)) * (win->map.ymax - win->map.ymin) + win->map.ymin;
		//printf("origin x = %f\ty = %f\n", win->map.origin.a, win->map.origin.b);
	}
	if (button == 4)
	{
		tmp = win->map.xmin - (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax += (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin - (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax += (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		ft_refresh(win, &(win->map.image));
	}
	else if (button == 5)
	{
		tmp = win->map.xmin + (win->map.xmax - win->map.xmin) / 10;
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin = tmp;
		tmp = win->map.ymin + (win->map.ymax - win->map.ymin) / 10;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin = tmp;
		ft_refresh(win, &(win->map.image));
	}
	return (0);
}
//(value - inter1.x) / (inter1.y - inter1.x) * (inter2.y - inter2.x)
//250 / 1000 * (90 - 50) + 50