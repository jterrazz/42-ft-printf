/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:42:36 by jterrazz          #+#    #+#             */
/*   Updated: 2017/06/04 09:52:13 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	set_conv_tab_next(t_conv *conv_tab)
{
	conv_tab[8].index = 'o';
	conv_tab[8].fn = &render_octal;
	conv_tab[9].index = 'O';
	conv_tab[9].fn = &render_octal;
	conv_tab[10].index = 'u';
	conv_tab[10].fn = &render_unsigned;
	conv_tab[11].index = 'U';
	conv_tab[11].fn = &render_unsigned;
	conv_tab[12].index = 'x';
	conv_tab[12].fn = &render_hex;
	conv_tab[13].index = 'X';
	conv_tab[13].fn = &render_hex;
	conv_tab[14].index = 'f';
	conv_tab[14].fn = &render_double;
	conv_tab[15].index = 'F';
	conv_tab[15].fn = &render_double;
}

static void	set_conv_tab(t_conv *conv_tab)
{
	conv_tab[0].index = 's';
	conv_tab[0].fn = &render_str;
	conv_tab[1].index = 'c';
	conv_tab[1].fn = &render_char;
	conv_tab[2].index = 'S';
	conv_tab[2].fn = &render_str;
	conv_tab[3].index = 'C';
	conv_tab[3].fn = &render_char;
	conv_tab[4].index = 'p';
	conv_tab[4].fn = &render_pointer;
	conv_tab[5].index = 'd';
	conv_tab[5].fn = &render_nbr;
	conv_tab[6].index = 'D';
	conv_tab[6].fn = &render_nbr;
	conv_tab[7].index = 'i';
	conv_tab[7].fn = &render_nbr;
	set_conv_tab_next(conv_tab);
}

static int	print_null(t_flags *flags)
{
	int i;

	i = 1;
	if (flags->flag_width == 1 && flags->width > 0)
	{
		while (--(flags->width) && i++)
			write(1, flags->flag_zero ? "0" : " ", 1);
	}
	if (flags->conv == 'c' || flags->conv == 'C')
		write(1, "\0", 1);
	if (flags->flag_width == 1 && flags->width < 0)
	{
		flags->width *= -1;
		while (--(flags->width) && i++)
			write(1, flags->flag_zero ? "0" : " ", 1);
	}
	return (i);
}

static void	get_str_ret(char **str_ret, va_list *va, t_flags *flags, char **str)
{
	t_conv	conv_tab[16];
	int		i;

	i = 0;
	set_conv_tab(conv_tab);
	while (i < 16)
	{
		if (conv_tab[i].index == **str)
		{
			*str_ret = conv_tab[i].fn(va, flags);
			return ;
		}
		i++;
	}
	if (**str == '%')
		*str_ret = render_char_from_c('%');
}

int			dispatch(va_list *va, char **str, char buff[4096], int *buff_i)
{
	t_flags	flags;
	char	*str_ret;
	int		ret;

	if ((ret = set_flags(&flags, str, va)) == -1)
		return (0);
	flags.conv = **str;
	if (ret == 0)
	{
		if (!(str_ret = ft_memset(ft_strnew(1), **str, 1)))
			return (0);
	}
	else
		get_str_ret(&str_ret, va, &flags, str);
	if (flags.null)
	{
		if (str_ret)
			free(str_ret);
		return (print_buff(buff, buff_i) + print_null(&flags));
	}
	else if (!str_ret && (flags.conv == 'C' || flags.conv == 'S'
	|| (flags.data_type == l && (flags.conv == 'c' || flags.conv == 's'))))
		return (-1);
	else if (str_ret)
		set_padding(&str_ret, &flags);
	if (!str_ret)
		return (0);
	return (print_buff(buff, buff_i) + ft_putstr_free(str_ret));
}
