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

int		flags(t_map *map, int ac, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-name"))
	{
		if (*i + 1 < ac)
			map->name = av[(*i)++ + 1];
	}
	else if (!ft_strcmp(av[*i], "-len"))
	{
		if (*i + 1 < ac)
			map->width = ft_atoi(av[++(*i)]);
		if (*i + 1 < ac)
			map->height = ft_atoi(av[++(*i)]);
	}
	else
		return (1);
	return (0);
}

int		params(t_map *map, int ac, char **av)
{
	int	i;
	int	ifile;

	i = 1;
	ifile = -1;
	map->name = "Fract'ol";
	map->width = 1000;
	map->height = 1000;
	while (i < ac)
	{
		if (flags(map, ac, av, &i))
			ifile = i;
		i++;
	}
	return (ifile);
}
