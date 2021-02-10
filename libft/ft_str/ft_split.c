/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:07:41 by pbesson           #+#    #+#             */
/*   Updated: 2021/02/09 16:00:26 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char		**ft_free(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

static int		ft_wordcount(const char *str, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (str[i] == '\0')
		return (n);
	while (str[i] == c)
		i++;
	if (str[i] == '\0')
		return (n);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				i++;
			if (str[i] != '\0')
				n++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (n + 1);
}

static int		ft_len(int i, const char *str, char c)
{
	int		n;

	n = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		n++;
		i++;
	}
	return (n);
}

static char		**ft_algo(char const *str, char **tab, char c)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	j = 0;
	while (ft_wordcount(&str[i], c))
	{
		l = 0;
		while (str[i] == c)
			i++;
		if (!(tab[j] = (char*)malloc(sizeof(char) * (ft_len(i, str, c) + 1))))
			return (ft_free(tab, j));
		k = i;
		while (i < (k + ft_len(k, str, c)))
			tab[j][l++] = str[i++];
		tab[j][l] = '\0';
		if (j < ft_wordcount(str, c))
			j++;
	}
	tab[j] = NULL;
	return (tab);
}

char			**ft_split(char const *str, char c)
{
	char	**tab;

	if (!(str))
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * (ft_wordcount(str, c) + 1))))
		return (NULL);
	tab = ft_algo(str, tab, c);
	return (tab);
}
