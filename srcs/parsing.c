#include "../includes/minishell.h"

void	ischaracter_slash_next(t_minishell *ms, int i)
{
	if (ms->line[i] == '|')
		ms->line[i] = -54;
	if (ms->line[i] == '\\' && ms->line[i + 1] == '|')
		str_remove_index(i, ms);
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
		i++;
	}
	return (i);
}

void	ft_testing(t_minishell *ms)
{
	int		i;

	i = 0;
	while (ms->line[i])
	{
		ischaracter_slash(ms, i);
		if (ms->line[i] == '\\' && ms->line[i + 1] == '"')
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '\\' && ms->line[i + 1] == '\'')
		{
			str_remove_index(i, ms);
		}
		else if (ms->line[i] == '"')
		{
			i = ischaracter_quotes(ms, i);
		}
		else if (ms->line[i] == '\'')
		{
			i = ischaracter_squotes(ms, i);
		}
		i++;
	}
	ms->command_tab = ft_split(ms->line, -50);
}
