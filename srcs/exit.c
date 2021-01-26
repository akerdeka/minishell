#include "../includes/minishell.h"

static void free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		ft_strdel(tab[i]);
	}
	free(tab);
}

static int tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_exit(t_minishell *ms)
{
	ft_strdel(ms->command);
	ft_strdel(ms->line);
	ft_strdel(ms->current_workdir);
	exit(ms->return_value);
}

void	check_exit(t_minishell *ms, int j)
{
	char **tab;
	int i;

	i = -1;
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	if (!(tab = ft_split(ms->command_tab[j], ' ')))
		ft_exit(ms);
	if (tab[0] != NULL && tab_len(tab) > 1)
	{
		ft_printf("Error : Too many arguments for exit\n");
		free_tab(tab);
	}
	else
	{
		if (tab[0] != NULL && tab_len(tab) > 0)
			while (tab[0][++i])
				if (!(ft_isdigit(tab[0][i])))
				{
					ft_printf("Error : Wrong argument\n");
					break;
				}
		if (tab[0] != NULL && tab[0][i] == '\0')
		{
			ms->return_value = ft_atoi(tab[0]);
			free_tab(tab);
			ft_exit(ms);
		}
		else
			ft_exit(ms);
	}
}