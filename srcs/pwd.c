/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:25:39 by pbesson           #+#    #+#             */
/*   Updated: 2021/02/09 15:42:39 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_pwd(t_minishell *ms)
{
	int i;

	i = 10;
	if (!(ms->current_workdir = malloc(sizeof(char) * i)))
		ft_exit(ms);
	while (!(getcwd(ms->current_workdir, i)))
	{
		i++;
		ft_strdel_free(&(ms->current_workdir));
		if (!(ms->current_workdir = malloc(sizeof(char) * i)))
			ft_exit(ms);
	}
	if (errno == 13)
	{
		ft_printf("Permission denied.");
		ft_strdel_free(&(ms->current_workdir));
	}
	else
	{
		ft_printf("%s\n", ms->current_workdir);
		ft_strdel_free(&(ms->current_workdir));
	}
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
}

void		ft_no_new_var(t_minishell *ms)
{
	t_env_var	*scroll_var;

	scroll_var = ms->ev->next_var;
	free(ms->line);
	ms->line = ft_strdup("");
	while (scroll_var->next_var)
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

t_env_var	*ft_export_norme(t_minishell *ms, int i,
	t_env_var *scroll_var, t_env_var *temp)
{
	if (ms->ev->next_var)
	{
		while (scroll_var->next_var != NULL)
		{
			if (ft_strcmp(scroll_var->var, temp->var) == 0)
			{
				free(scroll_var->content);
				if (!(scroll_var->content = ft_get_content(ms, i)))
					ft_exit(ms);
				free(temp->var);
				free(temp);
				return (NULL);
			}
			scroll_var = scroll_var->next_var;
		}
		if (ft_strcmp(scroll_var->var, temp->var) == 0)
		{
			if (!(scroll_var->content = ft_get_content(ms, i)))
				ft_exit(ms);
			free(temp->var);
			free(temp);
			return (NULL);
		}
	}
	return (scroll_var);
}
