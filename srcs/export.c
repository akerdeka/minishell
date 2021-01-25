/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:25:39 by pbesson           #+#    #+#             */
/*   Updated: 2020/09/21 20:25:39 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//NORME

int		check_var_01(t_minishell *ms)
{
	int		i;

	i = 0;
	while (ms->line[i] && ms->line[i] != '=')
		i++;
	if (i == 0)
	{
		ft_printf("wrong ID\n");
		return(0);
	}
	if (ms->line[i] != '\0')
	{
		if (!(ft_isalnum(ms->line[i - 1])) && ms->line[i - 1] != '_')
		{
			ft_printf("wrong ID\n");
			return(0);
		}
	}
	return(1);
}

int		check_var(t_minishell *ms)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (ms->line[i] && ms->line[i++] != '=')
		if (!(ft_isalnum(ms->line[i])) && ms->line[i] != '=' &&
			ms->line[i] != '_' && ms->line[i] != ' ')
		{
			ft_printf("wrong ID\n");
			return(0);
		}
	i = 0;
	while (ms->line[i++])
		if (ms->line[i] == '=')
			count++;
	if (count==0)
		return(0);
	return(check_var_01(ms));
}

char	*ft_get_var(t_minishell *ms)
{
	int		i;
	int		j;

	i = 0;
	while (ms->line[i] && ms->line[i] != '=')
		i++;
	j = i - 1;
	while (j > 0 && ft_isalnum(ms->line[j]))
		j--;
	if (j != 0)
		j++;
	return(ft_substr(ms->line, j, i - j));
}

char	*ft_get_content(t_minishell *ms)
{
	int		i;
	int		j;

	i = 0;
	while (ms->line[i] && ms->line[i] != '=')
		str_remove_index(0, ms);
	j = 0;
	while (ms->line[j] && ms->line[j] != ' ')
		j++;
	return(ft_substr(ms->line, i + 1, j - (i + 1)));
}

void	ft_no_new_var(t_minishell *ms)
{
	t_env_var	*scroll_var;
	scroll_var = ms->ev;
	free(ms->line);
	ms->line = ft_strdup("");
	while(scroll_var->last != 1)
	{
		ms->line = ft_strjoin_free_s1(ms->line, "declare -x ");
		ms->line = ft_strjoin_free_s1(ms->line, scroll_var->var);
		ms->line = ft_strjoin_free_s1(ms->line, "=\"");
		ms->line = ft_strjoin_free_s1(ms->line, scroll_var->content);
		ms->line = ft_strjoin_free_s1(ms->line, "\"\n");
		scroll_var = scroll_var->next_var;
	}
	ms->line = ft_strjoin_free_s1(ms->line, "declare -x ");
	ms->line = ft_strjoin_free_s1(ms->line, scroll_var->var);
	ms->line = ft_strjoin_free_s1(ms->line, "=\"");
	ms->line = ft_strjoin_free_s1(ms->line, scroll_var->content);
	ms->line = ft_strjoin_free_s1(ms->line, "\"\n");
}

int		ft_export(t_minishell *ms)
{
	if (ms->line[0] == '\0')
	{
		ft_no_new_var(ms);
	}
	else if (check_var(ms))
	{
		t_env_var	*temp;
		t_env_var	*scroll_var;
		if (!(temp = malloc(sizeof(t_env_var) * 1)))
			ft_exit(ms);
		scroll_var = ms->ev;
		if (!(temp->var = ft_get_var(ms)))
			ft_exit(ms);


		//*******   CHECK SI IL Y A DEJA UNE VARIABLE NOMMÉ PAREIL	
		if (ms->ev->last != 1)
		{
			while (scroll_var->last != 1)
			{
				if (ft_strcmp(scroll_var->var, temp->var) == 0)
				{
					free(scroll_var->content);
					if (!(scroll_var->content = ft_get_content(ms)))
						ft_exit(ms);
					free(temp->var);
					free(temp);
					return(1);
				}
				scroll_var = scroll_var->next_var;
			}
			if (ft_strcmp(scroll_var->var, temp->var) == 0)
			{
				if (!(scroll_var->content = ft_get_content(ms)))
					ft_exit(ms);
				free(temp->var);
				free(temp);
				return(1);
			}
		}
		//************************


		if (!(temp->content = ft_get_content(ms)))
			ft_exit(ms);
		scroll_var->next_var = temp;
		temp->prev_var = scroll_var;
		temp->last = 1;
		scroll_var->last = 0;
	}
	return (1);
}