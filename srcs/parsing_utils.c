/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:21:27 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/08 17:21:43 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ischaracter_slash_next(t_minishell *ms, int i)
{
	if (ms->line[i] == '|')
		ms->line[i] = -54;
	if (ms->line[i] == '\\' && ms->line[i + 1] == '|')
		str_remove_index(i, ms);
	if (ms->line[i] == '$')
		ms->line[i] = -55;
}

void	ischaracter_slash(t_minishell *ms, int i)
{
	if (ms->line[i] == ';')
		ms->line[i] = -50;
	if (ms->line[i] == '>' && ms->line[i + 1] != '>')
		ms->line[i] = -51;
	if (ms->line[i] == '<')
		ms->line[i] = -52;
	if (ms->line[i] == '>' && ms->line[i + 1] == '>')
	{
		str_remove_index(i + 1, ms);
		ms->line[i] = -53;
	}
	if (ms->line[i] == '\\' && ms->line[i + 1] == '>')
		str_remove_index(i, ms);
	if (ms->line[i] == '\\' && ms->line[i + 1] == '<')
		str_remove_index(i, ms);
	if (ms->line[i] == '\\' && ms->line[i + 1] == ';')
		str_remove_index(i, ms);
	if (ms->line[i] == '\\' && ms->line[i + 1] == '\\')
		str_remove_index(i, ms);
	ischaracter_slash_next(ms, i);
}

int		ischaracter_quotes(t_minishell *ms, int i)
{
	str_remove_index(i, ms);
	if (i != 0)
		i--;
	while (ms->line[i])
	{
		if (ms->line[i] == '\\' && ms->line[i + 1] == '\\')
		{
			str_remove_index(i, ms);
		}
		if (ms->line[i] == '"')
		{
			str_remove_index(i, ms);
			if (i != 0)
				i--;
			break ;
		}
		if (ms->line[i] == '$')
			ms->line[i] = -55;
		if (ms->line[i] == ' ')
			ms->line[i] = -56;
		i++;
	}
	return (i);
}

int		ischaracter_squotes(t_minishell *ms, int i)
{
	str_remove_index(i, ms);
	if (i != 0)
		i--;
	while (ms->line[i])
	{
		if (ms->line[i] == '\'')
		{
			str_remove_index(i, ms);
			if (i != 0)
				i--;
			break ;
		}
		if (ms->line[i] == ' ')
			ms->line[i] = -56;
		i++;
	}
	return (i);
}
