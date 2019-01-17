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
	if (keycode == 53)
	{
		ft_clear_memory(win, &(win->map));
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 124)
		win->map.origin.a -= 0.1;
	else if (keycode == 123)
		win->map.origin.a += 0.1;
	else if (keycode == 125)
		win->map.origin.b -= 0.1;
	else if (keycode == 126)
		win->map.origin.b += 0.1;
	if (keycode >= 123 && keycode <= 126)
		ft_refresh(win, &(win->map.image));
	return (0);
}

int		mouse_hook(int button, int x, int y, t_window *win)
{
	if (button == 4 || button == 5)
	{
		printf("x = %i\ty = %i\n", x, y);
		win->map.origin.a = (x / (float)(win->width)) * (win->map.xmax - win->map.xmin) + win->map.xmin;
		win->map.origin.b = ((win->height - y) / (float)(win->height)) * (win->map.ymax - win->map.ymin) + win->map.ymin;
		//printf("%f\n", (x / (float)(win->width)) * (win->map.xmax - win->map.xmin) + win->map.xmin);
		//printf("%f\n", ((win->height - y) / (float)(win->height)) * (win->map.ymax - win->map.ymin) + win->map.ymin);
		//printf("origin x = %f\ty = %f\n", win->map.origin.a, win->map.origin.b);
		ft_refresh(win, &(win->map.image));
	}
	if (button == 4)
	{
		win->map.xmax += (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin -= (win->map.xmax - win->map.xmin) / 10;
		win->map.ymax += (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin -= (win->map.ymax - win->map.ymin) / 10;
	}
	else if (button == 5)
	{
		win->map.xmax -= (win->map.xmax - win->map.xmin) / 10;
		win->map.xmin += (win->map.xmax - win->map.xmin) / 10;
		win->map.ymax -= (win->map.ymax - win->map.ymin) / 10;
		win->map.ymin += (win->map.ymax - win->map.ymin) / 10;
	}
	return (0);
}
//(value - inter1.x) / (inter1.y - inter1.x) * (inter2.y - inter2.x)
//250 / 1000 * (90 - 50) + 50