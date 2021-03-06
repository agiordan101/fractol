/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fractol.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/16 17:12:04 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/25 20:37:47 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define NBR_THREADS 8
# define BORNE 16
# define N_COLORS 8
# define COLORMIN 0x50CC50
# define COLORMAX 0x202020
# define PI 3.141592653589793238462643383279502884197169399375105820974944592307

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <pthread.h>
# include <stdio.h>

typedef struct		s_complexe
{
	double			a;
	double			b;
}					t_complexe;

typedef struct		s_dot
{
	double			x;
	double			y;
	int				color;
}					t_dot;

typedef struct		s_image
{
	void			*image_ptr;
	int				bpp;
	int				s_l;
	int				endian;
	int				*image;
}					t_image;

typedef struct		s_thread
{
	pthread_t		thread;
	struct s_window	*win;
	int				quarter;
	t_complexe		z;
	t_complexe		c;
}					t_thread;

typedef struct		s_tree
{
	double			x;
	double			y;
	double			length;
	double			dir;
	double			tmpdir;
	double			angle1;
	double			angle2;
}					t_tree;

typedef struct		s_triangle
{
	t_dot			dot[3];
}					t_triangle;

typedef struct		s_carre
{
	t_dot			dot[4];
}					t_carre;

typedef struct		s_line
{
	t_dot			d1;
	t_dot			d2;
}					t_line;

typedef struct		s_map
{
	double			ox;
	double			oy;
	t_image			image;
	t_complexe		origin;
	double			xmin;
	double			xmax;
	double			ymin;
	double			ymax;
	double			dx;
	double			dy;
	t_complexe		z;
	t_complexe		c;
	t_complexe		julia;
	int				track;
	int				psy;
	int				colors[N_COLORS];
}					t_map;

typedef struct		s_window
{
	void			*win;
	void			*mlx;
	char			*name;
	int				width;
	int				height;
	t_map			map;
	t_tree			tree;
	void			*ptr_fonctions[4];
	int				choice;
	t_thread		**threads;
	int				n_iter;
	int				n_iter_ser;
	int				n_iter_fern;
	int				n_digits;
	int				n_zoom;
	double			h_star;
	double			b_star;
}					t_window;

int					params(t_window *win, int ac, char **av);
int					ft_clear_memory(t_window *win);
int					init(t_window *win, t_map *map, t_image *image);
void				re_init(t_window *win, t_map *map);
void				init_colors(t_window *win);

void				mandelbrot(t_thread *thread);
void				julia(t_thread *thread);
void				burningship(t_thread *thread);
void				tree(t_window *win, t_image *image, t_tree *tree);
void				triangle(t_window *win, t_image *image);
void				carre(t_window *win, t_image *image);
void				star(t_window *win, t_image *image);
void				fern(t_window *win, t_image *image);
void				approaching_pi(t_window *win);

int					map_color(int mincolor, int maxcolor, double prop);
int					select_color(t_window *win, int i);
void				set_pixel(t_window *win, int x, int y, int color);
void				ft_put_line(t_window *win, t_dot d1, t_dot d2);

int					key_hook(int keycode, t_window *win);
int					mouse_hook(int button, int x, int y, t_window *win);
int					tracking_mouse(int x, int y, t_window *win);
void				ft_refresh(t_window *win, t_map *map, t_image *image);

#endif
