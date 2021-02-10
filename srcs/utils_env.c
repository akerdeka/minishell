/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:13:13 by akerdeka          #+#    #+#             */
/*   Updated: 2021/02/10 13:25:13 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_add_env(t_minishell *ms)
{
	t_env_var *temp;
	t_env_var *actual;

	if (!(ms->ev = malloc(sizeof(t_env_var) * 1)))
			ft_exit(ms);
	ms->ev->var = NULL;
	actual = ms->ev;
	if (!(temp = malloc(sizeof(t_env_var) * 1)))
		ft_exit(ms);
	temp->var = ft_strdup("PWD");
	temp->content = ft_strdup(getcwd(ms->current_workdir, 100));
	actual->next_var = temp;
	temp->prev_var = actual;
	actual = actual->next_var;
	if (!(temp = malloc(sizeof(t_env_var) * 1)))
		ft_exit(ms);
	temp->var = ft_strdup("SHLVL");
	temp->content = ft_strdup("2");
	actual->next_var = temp;
	temp->prev_var = actual;
	actual = actual->next_var;
	actual->next_var = NULL;
}