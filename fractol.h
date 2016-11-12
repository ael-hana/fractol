/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:02:32 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/12 21:36:12 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "keyboard.h"
# include "libft/libft.h"
# include <math.h>
# include "minilibx/mlx.h"
# include <stdio.h>
# define WINDOW_X 800
# define WINDOW_Y 600
# define DESTROY_NOTIFY 17
# define DESTROY_MASK (1L<<17)
# define MOTION_NOTIFY 6
# define PTR_MOTION_MASK (1L<<6)
# define BUTTONPRESS 4
# define BUTTONPRESS_MASK (1L<<10)
# define MOUSE_WHEEL_UP 5
# define MOUSE_WHEEL_DOWN 4

typedef struct			s_img
{
	void				*img;
	char				*data;
	int					bpp;
	int					s_line;
	int					endian;
}						t_img;

typedef struct			s_fractal
{
	void				*ptr;
	int					i;
	double				z_r;
	double				z_i;
	double				c_r;
	double				c_i;
	double				tmp;
	int					it_max;
	double				x1;
	double				y1;
	double				x2;
	double				y2;
	double				zoom;
	double				i_x;
	double				i_y;
}						t_fractal;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	int					switch_fractal;
	t_img				img;
	int					opt;
	int					color;
	int					mouse_x;
	int					mouse_y;
}						t_env;
void					ft_mandelbrot(t_env *ptr, int x, int y, t_fractal *f);
void					init_value_mandelbrot(t_fractal *f);
void					set_color(t_env *ptr, char color);
void					ft_run_mandelbrot(t_env *ptr, t_fractal *f);
void					ft_run_julia(t_env *ptr, t_fractal *f);
void					pixel_put_to_image(t_env *ptr, int x, int y);
void					init_value_mandelbrot(t_fractal *f);
void					init_value_julia(t_fractal *f);
int						ft_exit_prog(t_env *ptr);
void					ft_julia(t_env *ptr, int x, int y, t_fractal *f);
int						mouse_slide(int x, int y, t_fractal *f);
void					ft_switch_fractal(t_env *ptr, t_fractal *f);
void					ft_burningship(t_env *e, int x, int y, t_fractal *f);
void					ft_run_burn(t_env *ptr, t_fractal *f);
void					display_menu(t_env *ptr);
void					ft_display_menu();
void					get_mlx_img(t_env *ptr);
void					zoom_more_mouse(t_fractal *f, double x1, double y1);
void					zoom_less_mouse(t_fractal *f, double x1, double y1);
int						mouse_btn(int keycode, int x, int y, t_fractal *f);
#endif
