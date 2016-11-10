/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:59:13 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/10 19:57:55 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_run_mandelbrot(t_env *ptr, t_fractal *f)
{
	int	x;
	int	y;

	init_value_mandelbrot(f);
	y = 0;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			ft_mandelbrot(ptr, x, y, f);
			pixel_put_to_image(ptr, x, y);
			x++;
		}
		y++;
	}
}

void	ft_mandelbrot(t_env *ptr, int x, int y, t_fractal *f)
{
	f->c_r = (x / f->zoom) + f->x1;
	f->c_i = (y / f->zoom) + f->y1;
	f->z_r = 0.0;
	f->z_i = 0.0;
	f->i = 0;
	while (f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->it_max)
	{
		f->tmp = f->z_r;
		f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
		f->z_i = 2.0 * f->tmp * f->z_i + f->c_i;
		++(f->i);
	}
	if (f->i == f->it_max)
		set_color(ptr, 0);
	else
		set_color(ptr, ((f->i % 256) * 255 / f->it_max));
}

void	init_value_mandelbrot(t_fractal *f)
{
	f->it_max = 50;
	f->x1 = -2.1;
	f->y1 = -1.2;
	f->x2 = 0.6;
	f->y2 = 1.2;
}
