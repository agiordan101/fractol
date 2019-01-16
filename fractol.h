/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:12:04 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/16 17:12:06 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define N_ITER 100

# include <fcntl.h>
# include <unistd.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

typedef struct	s_complexe
{
	int			a;
	int			b;
}				t_complexe;

typedef struct	s_dot
{
	int			x;
	int			y;
}				t_dot;

typedef struct	s_image
{
	void		*image_ptr;
	int			bpp;
	int			s_l;
	int			endian;
	int			*image;
}				t_image;

typedef struct	s_map
{
	
	t_image		*image;
	
	char		*name;
	t_complexe	z;
	t_complexe	c;
	t_dot		origin;
}				t_map;

typedef struct	s_window
{
	void		*win;
	void		*mlx;
	int			width;
	int			height;
}				t_window;

int				params(t_map *map, int ac, char **av);

#endif
