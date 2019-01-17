/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flags.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:39:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 17:39:39 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

void	flags(t_window *win, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-name"))
	{
		if (*i + 1 < ac)
			win->name = av[(*i)++ + 1];
	}
	else if (!ft_strcmp(av[*i], "-len"))
	{
		if (*i + 1 < ac)
			win->width = ft_atoi(av[++(*i)]);
		if (*i + 1 < ac)
			win->height = ft_atoi(av[++(*i)]);
	}
}

void	params(t_window *win, int ac, char **av)
{
	int	i;

	printf("Debut params\n");
	i = 0;
	win->name = "Fract'ol";
	win->width = 1000;
	win->height = 1000;
	while (++i < ac)
		flags(win, ac, av, &i);
	printf("Fin params\n");
}

void	ft_clear_memory(t_window *win, t_map *map)
{

}
