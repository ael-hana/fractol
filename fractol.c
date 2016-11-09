/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:02:37 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/09 21:57:29 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color(t_env *ptr, char color)
{
	ptr->color = color;
}

void		pixel_put_to_image(t_env *ptr, int x, int y)
{
	int		pos;

	pos = (x * (ptr->img.bpp / 8)) + (y * ptr->img.s_line);
	ptr->img.data[pos] = (int)ptr->color;
	ptr->img.data[pos + 1] = (int)ptr->color >> 8;
	ptr->img.data[pos + 2] = (int)ptr->color >> 16;
}

void	ft_mandelbrot(t_env *ptr, int x, int y, t_fractal *f)
{
	f->c_r = (x / f->zoom_x) + f->x1;
	f->c_i = (y / f->zoom_x) + f->y1;
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

void	ft_switch_fractal(t_env *ptr, int ac, char **av, t_fractal *f)
{
	int			x;
	int			y;

	(void)av;
	y = 0;
	if (ac == 1)
	{
		ptr->switch_fractal = 1;
		init_value_mandelbrot(f);
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
	ptr->img.data = mlx_get_data_addr(ptr->img.img, &(ptr->img.bpp), &(ptr->img.s_line), &(ptr->img.endian));
}

int		ft_zoom_mouse(int keycode, t_fractal *f)
{
	t_env	*ptr;

	ptr = f->ptr;
	if (keycode == 126)
	{
		f->zoom_x += 10;
		//mlx_destroy_image(ptr->mlx, ptr->img.img);
		//get_mlx_img(ptr);
		ft_switch_fractal(ptr, 1, NULL, f);
		//mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	}
	return (0);
}

void	init_mlx(t_env *ptr)
{
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, WINDOW_X, WINDOW_Y, "fractol");
	get_mlx_img(ptr);
}

int		main(int ac, char **av)
{
	t_env		s;
	t_fractal	f;

	f.ptr = &s;
	f.zoom_x = 100;
	init_mlx(&s);
	ft_switch_fractal(&s, ac, av, &f);
	mlx_put_image_to_window(s.mlx, s.win, s.img.img, 0, 0);
	mlx_hook(s.win, DESTROY_NOTIFY, DESTROY_MASK, ft_exit_prog, &s);
	mlx_key_hook(s.win, ft_zoom_mouse, &s);
	mlx_loop(s.mlx);
	return (0);
}
