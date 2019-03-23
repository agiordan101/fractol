/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   colors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/22 20:26:59 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 21:56:29 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	init_colors(t_window *win)
{
	win->map.colors[0] = 0x5DDE14;
	win->map.colors[1] = 0x21DD8A;
	win->map.colors[2] = 0x21BEDD;
	win->map.colors[3] = 0x3621E6;
	win->map.colors[4] = 0x831BE6;
	win->map.colors[5] = 0xE61BBE;
	win->map.colors[6] = 0xE6741B;
	win->map.colors[7] = 0xE4EA2D;
}

int		map_color(int mincolor, int maxcolor, double prop)
{
	int r;
	int g;
	int b;

	r = (int)(prop * (((maxcolor >> 16) & 0xFF) - ((mincolor >> 16) & 0xFF))) +\
		((mincolor >> 16) & 0xFF);
	g = (int)(prop * (((maxcolor >> 8) & 0xFF) - ((mincolor >> 8) & 0xFF))) +\
		((mincolor >> 8) & 0xFF);
	b = (int)(prop * ((maxcolor & 0xFF) - (mincolor & 0xFF))) +\
		(mincolor & 0xFF);
	return ((r << 16) | (g << 8) | b);
}

int		select_color(t_window *win, int i)
{
	return (win->map.colors[i % win->map.psy]);
}
