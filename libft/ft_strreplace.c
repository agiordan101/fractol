/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strreplace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 17:08:22 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/12 17:08:47 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_strreplace(char *str, char *target, char *replace)
{
	char	*left;
	char	*right;
	int		ifind;

	while ((ifind = ft_stristr(str, target)) != -1)
	{
		left = ft_strsub(str, 0, ifind);
		right = ft_strsub(str, ifind + ft_strlen(target),\
			ft_strlen(str) - ifind - ft_strlen(target));
		str = ft_strnew(ft_strlen(left) +\
			ft_strlen(replace) + ft_strlen(right));
		ft_strcat(str, left);
		ft_strcat(str, replace);
		ft_strcat(str, right);
		ft_strdel(&left);
		ft_strdel(&right);
	}
	return (0);
}
