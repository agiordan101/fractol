/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   launcher.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 15:56:00 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 19:03:59 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fractol.h"

int	main(int ac, char **av)
{
	int		i;
	char	*exec;
	char	*input;
	char	*et;

	et = ft_strdup(" &");
	i = 0;
	if (ac > 1)
		while (++i < ac)
		{
			exec = ft_strdup("./fractol ");
			input = ft_strdup(av[i]);
			ft_strcat(exec, input);
			ft_strcat(exec, et);
			system(exec);
			ft_strdel(&input);
			ft_strdel(&exec);
		}

	ft_strdel(&et);
	return (0);
}
