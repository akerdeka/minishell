/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:42:01 by pbesson           #+#    #+#             */
/*   Updated: 2020/03/12 18:27:17 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "ft_printf/ft_printf.h"
# define BUFFERSIZE = 1

int			ft_atoi(const char *str);
void		ft_bzero(void *b, size_t len);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int nbr);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *src, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
char		**ft_split(char const *str, char c);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_free_s1(char *s1, char *s2);
char		*ft_strjoin_free_s2(char *s1, char *s2);
char		*ft_strjoin_tab_free(char **tab);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_strrchr(const char *str, int c);
char		*ft_strtrim(char const *str, char const *set);
char		*ft_substr(char const *src, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *str, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar(char c);
void		ft_putstr(char *str);
void		ft_putnbr(int nb);
char		*ft_itoa_base(int nbr, char *set);
void		ft_memdel(void **ptr);
void		ft_strdel(char *str);
int			ft_strchr_count(char *str, int c);
char		*ft_strchr_set(const char *str, char *set);
char		*ft_itoa_base_ll(unsigned long long nbr, char *set);
char		*ft_itoa_ll(long long nbr);
char		*ft_substr_free(char *src, unsigned int start, size_t len);
int			ft_norme(char **line, char **str, char **storage);
int			ft_norme_2(int *ret, char **line, char **str, char **storage);
int			get_next_line(int fd, char **line);
char		*ft_read(int fd, char *str, int *ret);
int			ft_strlen_line(char *str);
char		*ft_strchr(const char *str, int c);
char		*ft_convert_base(char *nbr, char *base_from, char *base_to);
int			ft_strchr_all(char *str, char c);
char		*ft_strremove_chr(char *src, char c);
int			ft_is_set(char *set, char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strtrim_free(char *str, char const *set);

#endif
