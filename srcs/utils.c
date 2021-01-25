/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:25:39 by pbesson           #+#    #+#             */
/*   Updated: 2021/01/25 14:01:04 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strdel_free(char **str)
{
	free(*str);
	*str = NULL;
}

void	str_remove_index(int i, t_minishell *ms)
{
	char	*str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!(str = malloc(sizeof(char) * (ft_strlen(ms->line)))))
		ft_exit(ms);
	while (ms->line[j])
	{
		if (j != i)
		{
			str[k] = ms->line[j];
			k++;
		}
		j++;
	}
	str[k] = '\0';
	free(ms->line);
	ms->line = str;
}
