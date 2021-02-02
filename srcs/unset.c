#include "../includes/minishell.h"
#include "stdio.h"
static int		check_var_unset(t_minishell *ms, int j)
{
	int		i;

	i = 0;
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	while (ms->command_tab[j][i] && ms->command_tab[j][i] != ' ')
	{
		if (!(ft_isalnum(ms->command_tab[j][i])) && ms->command_tab[j][i] != '=' &&
			ms->command_tab[j][i] != '_' && ms->command_tab[j][i] != ' ')
		{
			ft_printf("wrong ID\n");
			return (0);
		}
		i++;
	}
	if (!(ms->command = ft_substr_free(ms->command_tab[j], 0, i)))
		ft_exit(ms);
	return (1);
}
#include "stdio.h"
void	ft_unset(t_minishell *ms, int i)
{
	t_env_var	*temp;
	t_env_var	*temp_swap;
	int		j;

	j = 0;
	ms->command_tab[i] = ft_strtrim_free(ms->command_tab[i], " ");
	if (check_var_unset(ms, i))
	{
		temp = ms->ev->next_var;
		while (temp->next_var)
		{
			if (ft_strcmp(temp->var, ms->command_tab[i]) == 0)
			{
				if (j == 0)
				{
					free(temp->var);
					free(temp->content);
					ms->ev->next_var = temp->next_var;
					temp_swap = temp->next_var;
					temp_swap->prev_var = ms->ev;
				}
				else
				{
					free(temp->var);
					free(temp->content);
					temp_swap = temp->next_var;
					temp_swap->prev_var = temp->prev_var;
					temp_swap = temp->prev_var;
					temp_swap->next_var = temp->next_var;
					free(temp);
					temp = temp_swap;
					free(ms->command);
					ms->command = ft_strdup("");
					j = 1;
				}
				break ;
			}
			j++;
			temp = temp->next_var;
		}
		if (j != 1 && ft_strcmp(temp->var, ms->command) == 0)
		{
			free(temp->next_var);
			free(temp->content);
			temp_swap = temp->prev_var;
			temp_swap->next_var = NULL;
			free(temp);
			temp = temp_swap;
		}
	}
}
