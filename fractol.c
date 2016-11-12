/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:02:37 by ael-hana          #+#    #+#             */
/*   Updated: 2016/11/12 21:33:17 by ael-hana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_btn_event_2(int keycode, t_fractal *f)
{
	if (keycode == KEY_UP)
	{
		f->y1 -= 0.01;
		f->y2 -= 0.01;
	}
	else if (keycode == KEY_DOWN)
	{
		f->y1 += 0.01;
		f->y2 += 0.01;
	}
	else if (keycode == KEY_LEFT)
	{
		f->x1 -= 0.01;
		f->x2 -= 0.01;
	}
	else if (keycode == KEY_RIGHT)
	{
		f->x1 += 0.01;
		f->x2 += 0.01;
	}
}

int		ft_btn_event(int keycode, t_fractal *f)
{
	t_env	*ptr;

	ptr = f->ptr;
	if (keycode == KEY_NUM_PLUS)
		f->zoom += 100;
	else if (keycode == KEY_NUM_MINUS)
		f->zoom -= 100;
	else if (keycode == KEY_ESC)
		ft_exit_prog(ptr);
	else if (keycode == KEY_UP || keycode == KEY_DOWN ||
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		ft_btn_event_2(keycode, f);
	else if (keycode == KEY_MIN)
		f->it_max -= 10;
	else if (keycode == KEY_EQUAL)
		f->it_max += 10;
	else if (keycode == KEY_C)
		++ptr->opt;
	else
		return (0);
	ft_switch_fractal(ptr, f);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	display_menu(ptr);
	return (0);
}

void	init_mlx(t_env *ptr)
{
	ptr->mlx = mlx_init();
	ptr->opt = 0;
	ptr->win = mlx_new_window(ptr->mlx, WINDOW_X, WINDOW_Y, "fractol");
	get_mlx_img(ptr);
}

void	ft_parse_params(int ac, char **av, t_env *ptr, t_fractal *f)
{
	if (ac != 2)
		ft_display_menu();
	else if (av[1][0] == 'm')
	{
		ptr->switch_fractal = 1;
		init_value_mandelbrot(f);
	}
	else if (av[1][0] == 'j')
	{
		ptr->switch_fractal = 2;
		init_value_julia(f);
	}
	else if (av[1][0] == 'b')
	{
		ptr->switch_fractal = 3;
		init_value_mandelbrot(f);
	}
	else
		ft_display_menu();
}

int		main(int ac, char **av)
{
	t_env		s;
	t_fractal	f;

	f.zoom = 200;
	f.ptr = &s;
	ft_parse_params(ac, av, &s, &f);
	init_mlx(&s);
	ft_switch_fractal(&s, &f);
	mlx_put_image_to_window(s.mlx, s.win, s.img.img, 0, 0);
	display_menu(&s);
	mlx_hook(s.win, DESTROY_NOTIFY, DESTROY_MASK, ft_exit_prog, &s);
	mlx_hook(s.win, MOTION_NOTIFY, PTR_MOTION_MASK, mouse_slide, &f);
	mlx_hook(s.win, BUTTONPRESS, BUTTONPRESS_MASK, mouse_btn, &f);
	mlx_key_hook(s.win, ft_btn_event, &f);
	mlx_loop(s.mlx);
	return (0);
}
