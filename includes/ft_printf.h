/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:57:02 by jterrazz          #+#    #+#             */
/*   Updated: 2017/06/04 10:28:16 by jterrazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <wchar.h>

# define CONVERSIONS "sScCpdDioOuUxXfF%"
# define FLAGS "#0-+ .123456789hljz*"

typedef struct	s_flags
{
	char	conv;
	int		flag_hash;
	int		flag_zero;
	int		flag_minus;
	int		flag_plus;
	int		flag_space;
	int		null;
	int		width;
	int		flag_width;
	int		flag_precision;
	enum {
		none,
		hh,
		h,
		l,
		ll,
		j,
		z
	}		data_type;
}				t_flags;

typedef struct	s_conv
{
	char	index;
	char	* (*fn)(va_list *va, t_flags *flags);
}				t_conv;

int				ft_printf(const char *restrict format, ...);
int				dispatch(va_list *va, char **conv, char buff[4096], int *i);
int				set_flags(t_flags *flags, char **str, va_list *va);
void			set_flags_to_null(t_flags *flags);
void			set_padding(char **str, t_flags *flags);
int				is_conv(char c);
int				is_flag(char c);
void			set_precision_number(char **str, t_flags *flags, int is_null);
void			set_precision_str(char **str, t_flags *flags);
int				print_buff(char buff[4096], int *i);

int				ft_atoi(char **str);
char			*ft_itoa_base(intmax_t nb, intmax_t base, char letter);
char			*ft_uitoa_base(uintmax_t nb, intmax_t base, char letter);
char			*ft_strnew(size_t size);
void			*ft_memalloc(size_t size);
char			*ft_strsub_free(char *s, unsigned int start, size_t len);
int				ft_putchar(int c);
int				ft_putchar_fd(int c, int fd);
int				ft_putstr(char *s);
int				ft_putstr_free(char *s);
int				ft_putstr_fd(char const *s, int fd);
int				ft_putpercent(void);
void			*ft_memset(void *b, int c, size_t len);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *s1);
char			*ft_strjoin_inside_free(char *s1, char *s2, unsigned int x);
char			*ft_strjoin_free(char *s1, char *s2, int x, int y);
char			*ft_strnew(size_t size);

char			*render_char(va_list *va, t_flags *flags);
char			*render_char_from_c(char c);
char			*render_wchar(va_list *va, t_flags *flags);
char			*render_wchar_from_c(wchar_t c);
char			*render_str(va_list *va, t_flags *flags);
char			*render_octal(va_list *va, t_flags *flags);
char			*render_nbr(va_list *va, t_flags *flags);
char			*render_unsigned(va_list *va, t_flags *flags);
char			*render_hex(va_list *va, t_flags *flags);
char			*render_pointer(va_list *va, t_flags *flags);
char			*render_double(va_list *va, t_flags *flags);
char			*render_hex_nb(uintmax_t nb, t_flags *flags);

intmax_t		get_intmax(va_list *va, t_flags *flags);
uintmax_t		get_uintmax(va_list *va, t_flags *flags);

#endif
