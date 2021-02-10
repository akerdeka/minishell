/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:14:49 by acharras          #+#    #+#             */
/*   Updated: 2021/02/09 14:14:58 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_minishell *ms)
{
	t_env_var	*temp;

	temp = ms->ev->next_var;
	ft_strdel(ms->line);
	ms->line = ft_strdup("");
	while (temp->next_var)
	{
		ms->line = ft_strjoin_free_s1(ms->line, temp->var);
		ms->line = ft_strjoin_free_s1(ms->line, "=");
		ms->line = ft_strjoin_free_s1(ms->line, temp->content);
		ms->line = ft_strjoin_free_s1(ms->line, "\n");
		temp = temp->next_var;
	}
	ms->line = ft_strjoin_free_s1(ms->line, temp->var);
	ms->line = ft_strjoin_free_s1(ms->line, "=");
	ms->line = ft_strjoin_free_s1(ms->line, temp->content);
	ms->line = ft_strjoin_free_s1(ms->line, "\n");
}
