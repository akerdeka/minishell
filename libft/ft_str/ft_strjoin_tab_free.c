/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:59:39 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:23:38 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_tab_free(char **tab)
{
	int		i;
	char	*dst;

	i = 0;
	dst = ft_strdup("");
	while (tab[i])
	{
		dst = ft_strjoin_free_s2(dst, tab[i]);
		i++;
	}
	free(tab);
	return (dst);
}
