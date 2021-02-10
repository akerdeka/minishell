/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:29:32 by akerdeka          #+#    #+#             */
/*   Updated: 2021/02/09 14:39:54 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_var_unset(t_minishell *ms, int j)
{
	int		i;

	i = 0;
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	while (ms->command_tab[j][i] && ms->command_tab[j][i] != ' ')
	{
		if (!(ft_isalnum(ms->command_tab[j][i])) &&
			ms->command_tab[j][i] != '=' &&
			ms->command_tab[j][i] != '_' && ms->command_tab[j][i] != ' ')
		{
			ft_printf("wrong ID\n");
			return (0);
		}
		i++;
	}
	if (!(ms->command = ft_substr(ms->command_tab[j], 0, i)))
		ft_exit(ms);
	return (1);
}

int			ft_unset_check(t_minishell *ms, t_env_var *t, t_env_var *ts, int j)
{
	if (j == 0)
	{
		free(t->var);
		free(t->content);
		ms->ev->next_var = t->next_var;
		ts = t->next_var;
		ts->prev_var = ms->ev;
	}
	else
	{
		free(t->var);
		free(t->content);
		ts = t->next_var;
		ts->prev_var = t->prev_var;
		ts = t->prev_var;
		ts->next_var = t->next_var;
		free(t);
		t = ts;
		ft_strdel_free(&(ms->command));
		ms->command = ft_strdup("");
		j = 1;
	}
	return (j);
}

void		ft_unset_change(t_env_var *temp, t_env_var *ts)
{
	free(temp->next_var);
	free(temp->content);
	ts = temp->prev_var;
	ts->next_var = NULL;
	free(temp);
	temp = ts;
}

void		ft_unset(t_minishell *ms, int i)
{
	t_env_var	*temp;
	t_env_var	*temp_swap;
	int			j;

	j = 0;
	temp_swap = NULL;
	ms->command_tab[i] = ft_strtrim_free(ms->command_tab[i], " ");
	if (check_var_unset(ms, i))
	{
		temp = ms->ev->next_var;
		while (temp->next_var)
		{
			if (ft_strcmp(temp->var, ms->command_tab[i]) == 0)
			{
				j = ft_unset_check(ms, temp, temp_swap, j);
				break ;
			}
			j++;
			temp = temp->next_var;
		}
		if (j != 1 && ft_strcmp(temp->var, ms->command) == 0)
		{
			ft_unset_change(temp, temp_swap);
		}
	}
}
