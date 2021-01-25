/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:59:18 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:24:22 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int		ft_norme(char **line, char **str, char **storage);
int		ft_norme_2(int *ret, char **line, char **str, char **storage);
int		get_next_line(int fd, char **line);
char	*ft_read(int fd, char *str, int *ret);
size_t	ft_strlen(char *str);
int		ft_strlen_line(char *str);
char	*ft_substr(char *src, unsigned int start, size_t len);
char	*ft_strdup(char *src);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif
