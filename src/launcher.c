/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launcher.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 15:56:00 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/26 18:15:47 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	int		i;
	char	*exec;

	i = 0;
	if (ac > 1)
		while (++i < ac)
		{
			exec = ft_strjoin("./fractol ", av[i]);
			ft_strcat(exec, " &");
			system(exec);
			ft_strdel(&exec);
		}
	return (0);
}
