/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flags.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:39:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 20:42:01 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	flags(t_window *win, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-name"))
	{
		if (*i + 1 < ac)
			win->name = av[++(*i)];
	}
	else if (!ft_strcmp(av[*i], "-len"))
	{
		if (*i + 1 < ac)
			win->width = ft_atoi(av[++(*i)]);
		if (*i + 1 < ac)
			win->height = ft_atoi(av[++(*i)]);
	}
	else if (!ft_strcmp(av[*i], "-tree"))
	{
		if (*i + 1 < ac)
			win->tree.angle1 = ft_atoi(av[++(*i)]);
		if (*i + 1 < ac)
			win->tree.angle2 = ft_atoi(av[++(*i)]);
	}
	else if (ft_atoi(av[*i]) >= 1 && ft_atoi(av[*i]) <= 9)
		win->choice = ft_atoi(av[(*i)]);
}

int		params(t_window *win, int ac, char **av)
{
	int	i;

	i = 0;
	win->name = "Fract'ol";
	win->width = 1000;
	win->height = 1000;
	win->tree.angle1 = PI / 4;
	win->tree.angle2 = -PI / 4;
	win->choice = -1;
	win->threads = NULL;
	while (++i < ac)
		flags(win, ac, av, &i);
	return (win->choice);
}
