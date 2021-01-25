#include "../includes/minishell.h"

//NORME

int		check_var_unset(t_minishell *ms)
{
	int		i;

	i = 0;
	while (ms->line[i] && ms->line[i] != ' ')
	{
		if (!(ft_isalnum(ms->line[i])) && ms->line[i] != '=' &&
			ms->line[i] != '_' && ms->line[i] != ' ')
		{
			ft_printf("wrong ID\n");
			return(0);
		}
		i++;
	}
	if (!(ms->line = ft_substr_free(ms->line, 0, i)))
		ft_exit(ms);
	return(1);
}

void    ft_unset(t_minishell *ms)
{
	t_env_var	*temp;
	t_env_var	*temp_swap;
    if (check_var_unset(ms))
    {
		temp = ms->ev;
		while (temp->last != 1)
		{
			if (ft_strcmp(temp->var, ms->line) == 0)
			{
				free(temp->var);
				free(temp->content);
				temp_swap = temp->next_var;
				temp_swap->prev_var = temp->prev_var;
				temp_swap = temp->prev_var;
				temp_swap->next_var = temp->next_var;
				free(temp);
				temp = temp_swap;
				break;
			}
			temp = temp->next_var;
		}
		if (ft_strcmp(temp->var, ms->line) == 0)
		{
			free(temp->var);
			free(temp->content);
			temp_swap = temp->prev_var;
			temp_swap->last = 1;
			free(temp);
			temp = temp_swap;
		}
    }
}