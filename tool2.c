/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 20:56:19 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/12 21:34:05 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_display_menu(void)
{
	ft_putstr("Menu - ");
	ft_putstr("Les options dispo :\n");
	ft_putstr("mandelbrot :./fractol m\n");
	ft_putstr("julia :./fractol j\n");
	ft_putstr("burningship :./fractol b\n");
	exit(1);
}

void	zoom_more_mouse(t_fractal *f, double x1, double y1)
{
	double	x;
	double	y;

	x = (x1 / f->zoom) + f->x1;
	y = (y1 / f->zoom) + f->y1;
	f->zoom *= 1.1;
	f->x1 = x - (x1 / f->zoom);
	f->y1 = y - (y1 / f->zoom);
}

void	display_menu(t_env *ptr)
{
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300, 2,
			0x00FFFFFF, "ESC : Exit");
	mlx_string_put(ptr->mlx, ptr->win, WINDOW_X - 300, 30,
			0x00FFFFFF, "- = : iteration");
}

void	zoom_less_mouse(t_fractal *f, double x1, double y1)
{
	double	x;
	double	y;

	x = (x1 / f->zoom) + f->x1;
	y = (y1 / f->zoom) + f->y1;
	f->zoom /= 1.1;
	f->x1 = x - (x1 / f->zoom);
	f->y1 = y - (y1 / f->zoom);
}

int		mouse_btn(int keycode, int x, int y, t_fractal *f)
{
	t_env	*ptr;

	ptr = f->ptr;
	if (keycode == SCROLL_UP)
		zoom_more_mouse(f, x, y);
	if (keycode == SCROLL_DOWN)
		zoom_less_mouse(f, x, y);
	ft_switch_fractal(f->ptr, f);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	display_menu(ptr);
	return (0);
}
