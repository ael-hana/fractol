/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 20:51:59 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/12 21:32:35 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color(t_env *ptr, char color)
{
	ptr->color = color;
}

void	pixel_put_to_image(t_env *ptr, int x, int y)
{
	int		pos;

	pos = (x * (ptr->img.bpp / 8)) + (y * ptr->img.s_line);
	if ((ptr->opt % 3) == 0)
	{
		ptr->img.data[pos] = (int)ptr->color;
		ptr->img.data[pos + 1] = (int)ptr->color >> 8;
		ptr->img.data[pos + 2] = (int)ptr->color >> 16;
	}
	else if ((ptr->opt % 3) == 1)
	{
		ptr->img.data[pos] = (int)ptr->color >> 16;
		ptr->img.data[pos + 1] = (int)ptr->color >> 8;
		ptr->img.data[pos + 2] = (int)ptr->color;
	}
	else
	{
		ptr->img.data[pos] = (int)ptr->color >> 8;
		ptr->img.data[pos + 1] = (int)ptr->color;
		ptr->img.data[pos + 2] = (int)ptr->color >> 16;
	}
}

void	ft_switch_fractal(t_env *ptr, t_fractal *f)
{
	if (ptr->switch_fractal == 1)
		ft_run_mandelbrot(ptr, f);
	if (ptr->switch_fractal == 2)
		ft_run_julia(ptr, f);
	if (ptr->switch_fractal == 3)
		ft_run_burn(ptr, f);
}

int		ft_exit_prog(t_env *ptr)
{
	mlx_destroy_window(ptr->mlx, ptr->win);
	exit(1);
	return (0);
}

void	get_mlx_img(t_env *ptr)
{
	ptr->img.img = mlx_new_image(ptr->mlx, WINDOW_X, WINDOW_Y);
	ptr->img.data = mlx_get_data_addr(ptr->img.img, &(ptr->img.bpp),
			&(ptr->img.s_line), &(ptr->img.endian));
}
