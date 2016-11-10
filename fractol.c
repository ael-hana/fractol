/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:02:37 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/10 20:40:24 by ael-hana         ###   ########.fr       */
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

void	ft_switch_fractal(t_env *ptr, t_fractal *f)
{
	if (ptr->switch_fractal == 1)
		ft_run_mandelbrot(ptr, f);
	if (ptr->switch_fractal == 2)
		ft_run_julia(ptr, f);
	if (ptr->switch_fractal == 3)
		ft_run_mandelbrot(ptr, f);
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
	if (keycode == KEY_NUM_PLUS)
		f->zoom += 10;
	else if (keycode == KEY_NUM_MINUS)
		f->zoom -= 10;
	ft_switch_fractal(ptr, f);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	return (0);
}

void	init_mlx(t_env *ptr)
{
	ptr->mlx = mlx_init();
	ptr->win = mlx_new_window(ptr->mlx, WINDOW_X, WINDOW_Y, "fractol");
	get_mlx_img(ptr);
}

void	ft_parse_params(int ac, char **av, t_env *ptr)
{
	if (ac == 1)
		ptr->switch_fractal = 1;
	else if (av[1][0] == 'm')
		ptr->switch_fractal = 1;
	else if (av[1][0] == 'j')
		ptr->switch_fractal = 2;
	else
		ptr->switch_fractal = 1;
}

int		main(int ac, char **av)
{
	t_env		s;
	t_fractal	f;

	f.zoom = 100;
	f.ptr = &s;
	ft_parse_params(ac, av, &s);
	init_mlx(&s);
	ft_switch_fractal(&s, &f);
	mlx_put_image_to_window(s.mlx, s.win, s.img.img, 0, 0);
	mlx_hook(s.win, DESTROY_NOTIFY, DESTROY_MASK, ft_exit_prog, &s);
	mlx_key_hook(s.win, ft_zoom_mouse, &f);
	mlx_loop(s.mlx);
	return (0);
}
