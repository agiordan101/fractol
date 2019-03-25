/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pi.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/25 16:13:07 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 20:35:31 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Soit A le complexe (-0.75, 0)
**	Soit E = 0.1^(n_digit - 1)
**
**	On prend c = A + E et la suite z(n+1) = z(n) * z(n) + c, avec z(0) = 0
**	On iter jusqua ce que z(n) ne soit plus borne
**	Le nombre d'iteration est une approximation de pi a 'n_digit - 1' pres
**
**	(Lorsque E tend vers 0 le nombre d'iteration de la suite tend vers
**	les chiffres de PI)
*/

void	approaching_pi(t_window *win)
{
	int			pi;
	t_complexe	z;
	t_complexe	c;
	double		tmp;

	ft_putstr("n_digits = ");
	ft_putnbr(win->n_digits);
	c = (t_complexe){.a = -0.75, .b = pow(0.1, win->n_digits - 1)};
	z = (t_complexe){.a = 0, .b = 0};
	pi = 0;
	while (z.a * z.a + z.b * z.b < 2 && ++pi)
	{
		tmp = z.a * z.a - z.b * z.b + c.a;
		z.b = 2 * z.a * z.b + c.b;
		z.a = tmp;
	}
	ft_putendl("\nReal PI ~= 3,14159265...");
	ft_putstr("My PI  ~=  ");
	if (win->n_digits == 1)
		ft_putnbr(pi);
	else
	{
		ft_putstr("3,");
		ft_putnbr(pi % (int)pow(10, ft_nbrlen(pi) - 1));
	}
	ft_putstr("\n\n\n");
}
