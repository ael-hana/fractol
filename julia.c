/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:58:19 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/10 20:40:23 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_run_julia(t_env *ptr, t_fractal *f)
{
	int	x;
	int	y;

	init_value_julia(f);
	y = 0;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			ft_julia(ptr, x, y, f);
			pixel_put_to_image(ptr, x, y);
			x++;
		}
		y++;
	}
}

void		ft_julia(t_env *ptr, int x, int y, t_fractal *f)
{
	f->c_r = /*ptr->mouse_x*/0.285;
	f->c_i = /*ptr->mouse_y*/0.01;
	f->z_r = x / f->zoom + f->x1;
	f->z_i = y / f->zoom + f->y1;
	f->i = 0;
	while (f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->it_max)
	{
		f->tmp = f->z_r;
		f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
		f->z_i = 2.0 * f->tmp * f->z_i + f->c_i;
		++f->i;
	}
	if (f->i == f->it_max)
		set_color(ptr, 0);
	else
		set_color(ptr, (f->i % 256) * 255 / f->it_max);
}

void	init_value_julia(t_fractal *f)
{
	f->it_max = 150;
	f->x1 = -1;
	f->x2 = 1;
	f->y1 = -1.2;
	f->y2 = 1.2;
}
