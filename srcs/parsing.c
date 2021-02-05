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

static void	ft_dollar_var(t_minishell *ms)
{
	int		i;
	int		j = 0;

	i = 0;
	t_env_var *temp;
	char	tempo[2];

	tempo[0] = -56;
	tempo[1] = '\0';
	if (ft_strchr(ms->line, -55))
	{
		ms->command_tab = ft_split(ms->line, -55);
		while(ms->command_tab[i + 1])
		{
			j = 0;
			temp = ms->ev->next_var;
			ft_printf("|%s|\n", ms->command_tab[i + 1]);
			if (ms->command_tab[i + 1][(int)ft_strlen(ms->command_tab[i + 1]) - 1] == ' ')
				j = 1;
			get_command(ms, i + 1);
			while (temp->next_var)
			{
				if (ft_strcmp(temp->var, ms->command) == 0)
					break ;
				temp  = temp->next_var;
			}
			free(ms->command);
			ms->command = ft_strdup(temp->content);
			ft_printf("%d\n", j);
			if (ms->command && j == 1)
				ms->command_tab[0] = ft_strjoin_free_s1(ms->command, tempo);
			ms->command_tab[0] = ft_strjoin_free_s1(ms->command_tab[0], ms->command);
			ms->command_tab[0] = ft_strjoin_free_s1(ms->command_tab[0], ms->command_tab[i + 1]);
			free(ms->line);
			ms->line = ft_strdup(ms->command_tab[0]);
			i++;
		}
	}
}

static void	ft_delete_useless_space(t_minishell *ms)
{
	char **temp;
	int		i;

	i = 0;
	if (ft_strchr(ms->line, ' ') != 0)
	{
		temp = ft_split(ms->line, ' ');
		while (temp[i + 1])
		{
			temp[0] = ft_strjoin_free_s1(temp[0], " ");
			temp[0] = ft_strjoin_free_s1(temp[0], temp[i + 1]);
			free(temp[i + 1]);
			i++;
		}
		free(ms->line);
		ms->line = ft_strdup(temp[0]);
		free(temp[0]);
		free(temp);
	}
	i = 0;
	while (ms->line[i])
	{
		if(ms->line[i] == -56)
			ms->line[i] = ' ';
		i++;
	}
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
	ft_dollar_var(ms);
	ft_delete_useless_space(ms);
	ms->command_tab = ft_split(ms->line, -50);
}
