/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 21:30:34 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/12 21:30:35 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_run_burn(t_env *ptr, t_fractal *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			ft_burningship(ptr, x, y, f);
			pixel_put_to_image(ptr, x, y);
			x++;
		}
		y++;
	}
}

void	ft_burningship(t_env *e, int x, int y, t_fractal *f)
{
	f->c_r = x / f->zoom + f->x1;
	f->c_i = y / f->zoom + f->y1;
	f->z_r = 0.0;
	f->z_i = 0.0;
	f->i = 0;
	while (f->z_r * f->z_r + f->z_i * f->z_i < 4 && f->i < f->it_max)
	{
		f->tmp = f->z_r;
		f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
		f->z_i = 2.0 * fabs(f->tmp * f->z_i) + f->c_i;
		++f->i;
	}
	if (f->i == f->it_max)
		set_color(e, 0);
	else
		set_color(e, (f->i % 256) * 255 / f->it_max);
}
