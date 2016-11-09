/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:02:32 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/09 21:57:30 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef fractol_h
# define fractol_h
# include "libft/libft.h"
# include <math.h>
# include "minilibx/mlx.h"
#include <stdio.h>
# define WINDOW_X 2000
# define WINDOW_Y 1000
# define DESTROY_NOTIFY 17
# define DESTROY_MASK (1L<<17)
# define SCROLL_UP 4
# define SCROLL_DOWN 5

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
	double				zoom_x;
	double				zoom_y;
	double				i_x;
	double				i_y;
}						t_fractal;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	int					switch_fractal;
	t_img				img;
	char				color;
}						t_env;
#endif
