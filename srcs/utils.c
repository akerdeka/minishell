/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:25:39 by pbesson           #+#    #+#             */
/*   Updated: 2021/02/03 10:14:24 by akerdeka         ###   ########lyon.fr   */
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
	char		*str;
	int			j;
	int			k;

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

void	get_environement(t_minishell *ms)
{
	t_env_var	*temp;
	int			i;

	i = 0;
	temp = ms->ev->next_var;
	while (temp->next_var)
	{
		temp = temp->next_var;
		i++;
	}
	ms->envps = malloc(sizeof(char **) * i + 1);
	ms->envps[i + 1] = NULL;
	temp = ms->ev->next_var;
	i = 0;
	while (temp->next_var)
	{
		ms->envps[i] = ft_strjoin("", temp->var);
		ms->envps[i] = ft_strjoin_free_s1(ms->envps[i], "=");
		ms->envps[i] = ft_strjoin_free_s1(ms->envps[i], temp->content);
		temp = temp->next_var;
		i++;
	}
}

void	ft_add_shlvl(t_minishell *ms)
{
	t_env_var *temp;

	temp = ms->ev->next_var;
	while (temp->next_var)
	{
		if ((ft_strcmp("SHLVL", temp->var)) == 0)
			break ;
		temp = temp->next_var;
	}
	temp->content = ft_itoa(ft_atoi(temp->content) + 1);
}
