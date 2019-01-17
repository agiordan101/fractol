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
# define BORNE 4
# define COLORMIN 0x80DD80
# define COLORMAX 0x303030

# include <stdio.h> /////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <fcntl.h>
# include <unistd.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"

typedef struct	s_complexe
{
	float		a;
	float		b;
}				t_complexe;

typedef struct	s_dot
{
	float		x;
	float		y;
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
	t_image		image;
	t_complexe	z;
	t_complexe	c;
	t_complexe	origin;
	float		xmin;
	float		xmax;
	float		ymin;
	float		ymax;
	float		dx;
	float		dy;
	float		valuemap;
}				t_map;

typedef struct	s_window
{
	void		*win;
	void		*mlx;
	char		*name;
	int			width;
	int			height;
	t_map		map;
	int			choice;
}				t_window;

int				params(t_window *win, int ac, char **av);
int				ft_clear_memory(t_window *win, t_map *map);
void			mandelbrot(t_window *win, t_map *map, t_image *image);
void			julia(t_window *win, t_map *map, t_image *image);
int				map_color(t_window *win, int mincolor, int maxcolor, double prop);
void			set_pixel(t_window *win, int x, int y, int color);
int				key_hook(int keycode, t_window *win);
int				mouse_hook(int button, int x, int y, t_window *win);
void			ft_refresh(t_window *win, t_image *image);

#endif
