#include "../includes/minishell.h"

int		ft_find_equal(char *envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return(i);
		i++;
	}
	return (0);
}

void	ft_init_env_var(t_minishell *ms)
{
	int		i;
	t_env_var *temp;
	t_env_var *actual;

	i = 0;
	if (!(ms->ev = malloc(sizeof(t_env_var) * 1)))
			ft_exit(ms);
	ms->ev->var = ft_substr(ms->envp[i], 0, ft_find_equal(ms->envp[i]));
	ms->ev->content = ft_substr(ms->envp[i], ft_find_equal(ms->envp[i]) + 1, ft_strlen(ms->envp[i]) - ft_find_equal(ms->envp[i]));
	ms->ev->last = 0;
	i++;
	ms->ev->first_var = ms->ev;
	actual = ms->ev;
	while (ms->envp[i])
	{
		if (!(temp = malloc(sizeof(t_env_var) * 1)))
			ft_exit(ms);
		temp->var = ft_substr(ms->envp[i], 0, ft_find_equal(ms->envp[i]));
		temp->content = ft_substr(ms->envp[i], ft_find_equal(ms->envp[i]) + 1, ft_strlen(ms->envp[i]) - ft_find_equal(ms->envp[i]));
		temp->last = 0;
		if (i > 0)
		{
			actual->next_var = temp;
			actual->first_var = ms->ev;
			temp->prev_var = actual;
			actual = actual->next_var;
		}
		if (ms->envp[i + 1] == NULL)
			actual->last = 1;
		i++;
	}
}

void	ft_init(t_minishell *ms)
{
	ms->line = NULL;
    ms->command = NULL;
    ms->current_workdir = NULL;
	ms->return_value = 0;
	get_next_line(1, NULL); //à vérifier
	ft_init_env_var(ms);
}

int		get_command(t_minishell *ms)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ms->line[i] && ms->line[i] == ' ')
		i++;
	j = i;
	while (ms->line[j] && ms->line[j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->line, i, j - i)))
		return (0);
	while (ms->line[j] && ms->line[j] == ' ')
		j++;
	if (!(ms->line = ft_substr_free(ms->line, j , ft_strlen(ms->line))))
		return (0);
	return (1);
}

void	get_path_arg(t_minishell *ms)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;
	int			id;
	i = 0;
	temp = ms->ev;
	while (temp->last != 1 && ft_strcmp(temp->var, "PATH") != 0)
	{
		temp = temp->next_var;
	}
	path = ft_split(temp->content, ':');
	while(path[i])
	{
		tempo = ft_strjoin(path[i], "/");
		tempo = ft_strjoin_free_s1(tempo, ms->command);
		id = open(tempo, O_RDONLY);
		if (id > 0)
		{
			break;
		}
		//ft_printf("%s = %d\n", tempo, id);
		close(id);
		free(tempo);
		i++;
	}
	ms->line = ft_strjoin_free_s2(" ", ms->line);
	ms->line = ft_strjoin_free_s2(ms->command, ms->line);
	ms->argv = ft_split(ms->line, ' ');
	ms->argv[0] = tempo;
}

void	try_exec(t_minishell *ms)
{
	int		id;
	int		ret;
	char	*buffer;

	get_path_arg(ms);
	buffer = malloc(sizeof(char *) * 10000);
	pipe(ms->pfd);
	id = fork();
	if(id == 0)
	{
		close(ms->pfd[0]);
		dup2(ms->pfd[1], 1);
		execve(ms->argv[0], ms->argv, NULL);
	}
	else
	{
		free(ms->line);
		ms->line = ft_strdup("");
		close(ms->pfd[1]);
		while (((ret = read(ms->pfd[0], buffer, 1023)) > 0))
		{
			buffer[ret] = 0;
			ms->line = ft_strjoin_free_s1(ms->line, buffer);
		}
		close(ms->pfd[0]);
	}
	free(buffer);
}

void	get_different_option(t_minishell *ms, int i)
{
	i = 0;
	if (!(get_command(ms)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo(ms);
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "cd") == 0)
		ft_cd(ms);
	else if (ft_strcmp(ms->command, "exit") == 0)
		check_exit(ms);
	else if (ft_strcmp(ms->command, "export") == 0)
		ft_export(ms);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec(ms);
}

void	get_path_arg_pipe_inf(t_minishell *ms)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;
	int			id;
	i = 0;
	temp = ms->ev;
	while (temp->last != 1 && ft_strcmp(temp->var, "PATH") != 0)
	{
		temp = temp->next_var;
	}
	path = ft_split(temp->content, ':');
	while(path[i])
	{
		tempo = ft_strjoin(path[i], "/");
		tempo = ft_strjoin_free_s1(tempo, ms->command);
		id = open(tempo, O_RDONLY);
		if (id > 0)
		{
			break;
		}
		close(id);
		free(tempo);
		i++;
	}
	//ft_printf("%s = %d\n", tempo, id);
	ms->command_inf[0] = ft_strjoin_free_s2(" ", ms->command_inf[0]);
	ms->command_inf[0] = ft_strjoin_free_s2(ms->command, ms->command_inf[0]);
	ms->argv = ft_split(ms->command_inf[0], ' ');
	ms->argv[0] = tempo;
}

void	get_path_arg_pipe(t_minishell *ms, int k)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;
	int			id;
	i = 0;
	temp = ms->ev;
	while (temp->last != 1 && ft_strcmp(temp->var, "PATH") != 0)
	{
		temp = temp->next_var;
	}
	path = ft_split(temp->content, ':');
	while(path[i])
	{
		tempo = ft_strjoin(path[i], "/");
		tempo = ft_strjoin_free_s1(tempo, ms->command);
		id = open(tempo, O_RDONLY);
		if (id > 0)
		{
			break;
		}
		close(id);
		free(tempo);
		i++;
	}
	//ft_printf("%s = %d\n", tempo, id);
	ms->command_pipe[k] = ft_strjoin_free_s2(" ", ms->command_pipe[k]);
	ms->command_pipe[k] = ft_strjoin_free_s2(ms->command, ms->command_pipe[k]);
	ms->argv = ft_split(ms->command_pipe[k], ' ');
	ms->argv[0] = tempo;
}

void	try_exec_pipe_inf(t_minishell *ms, int k)
{
	int		id;
	int		ret;
	char	*buffer;

	k = 0;
	get_path_arg_pipe_inf(ms);
	buffer = malloc(sizeof(char *) * 10000);
	pipe(ms->pfd);
	id = fork();
	if(id == 0)
	{
		close(ms->pfd[0]);
		dup2(ms->pfd[1], 1);
		execve(ms->argv[0], ms->argv, NULL);
	}
	else
	{
		free(ms->line);
		ms->line = ft_strdup("");
		close(ms->pfd[1]);
		while (((ret = read(ms->pfd[0], buffer, 1023)) > 0))
		{
			buffer[ret] = 0;
			ms->line = ft_strjoin_free_s1(ms->line, buffer);
		}
		close(ms->pfd[0]);
	}
	//ft_printf("%s\n", ms->line);
	free(buffer);
}

void	try_exec_pipe(t_minishell *ms, int k)
{
	int		id;
	//int		ret;
	char	*buffer;

	get_path_arg_pipe(ms, k);
	buffer = malloc(sizeof(char *) * 10000);
	//pipe(ms->pfd);
	id = fork();
	if(id == 0)
	{
		//close(ms->pfd[0]);
		//dup2(ms->pfd[1], 1);
		execve(ms->argv[0], ms->argv, NULL);
	}
	else
	{
		//free(ms->line);
		//ms->line = ft_strdup("");
		//close(ms->pfd[1]);
		//while (((ret = read(ms->pfd[0], buffer, 1023)) > 0))
		//{
		//	buffer[ret] = 0;
		//	ms->line = ft_strjoin_free_s1(ms->line, buffer);
		//}
		//close(ms->pfd[0]);
	}
	//ft_printf("%s\n", ms->line);
	free(buffer);
}

int		get_command_pipe_inf(t_minishell *ms, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;
	k = 0;
	while (ms->command_inf[0][i] && ms->command_inf[0][i] == ' ')
		i++;
	j = i;
	while (ms->command_inf[0][j] && ms->command_inf[0][j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->command_inf[0], i, j - i)))
		return (0);
	while (ms->command_inf[0][j] && ms->command_inf[0][j] == ' ')
		j++;
	if (!(ms->command_inf[0] = ft_substr_free(ms->command_inf[0], j , ft_strlen(ms->command_inf[1]))))
		return (0);
	return (1);
}

int		get_command_pipe(t_minishell *ms, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (ms->command_pipe[k][i] && ms->command_pipe[k][i] == ' ')
		i++;
	j = i;
	while (ms->command_pipe[k][j] && ms->command_pipe[k][j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->command_pipe[k], i, j - i)))
		return (0);
	while (ms->command_pipe[k][j] && ms->command_pipe[k][j] == ' ')
		j++;
	if (!(ms->command_pipe[k] = ft_substr_free(ms->command_pipe[k], j , ft_strlen(ms->command_pipe[k]))))
		return (0);
	return (1);
}



void	get_different_option_pipe(t_minishell *ms, int i)
{
	if (!(get_command_pipe(ms, i)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo(ms);
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "cd") == 0)
		ft_cd(ms);
	else if (ft_strcmp(ms->command, "exit") == 0)
		check_exit(ms);
	else if (ft_strcmp(ms->command, "export") == 0)
		ft_export(ms);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec_pipe(ms, i);
}
#include "stdio.h"

void	manage_inf_pipe(t_minishell *ms, int i)
{
	int		j;
	int		k;
	int		tempstdout;

	tempstdout = dup(1);
	j = 1;
	k = 0;
	if (ft_strchr(ms->command_pipe[i], -51))
	{
		if (!(ms->command_inf = ft_split(ms->command_pipe[i], -51)))
			ft_exit(ms);
		free(ms->line);
		ms->line = ms->command_inf[0];
		get_different_option_pipe_inf(ms, i);
		while (ms->command_inf[j])
		{
			k = 0;
			while (ms->command_inf[j][i] && ms->command_inf[j][k] == ' ')				
				k++;
			ms->fd = open(ms->command_inf[j] + k, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |  S_IROTH);
			if (ms->command_inf[j + 1] == NULL)
				write(ms->fd, ms->line, ft_strlen(ms->line));
			close(ms->fd);
			j++;
		}
	}
	else if (ft_strchr(ms->command_pipe[i], -52))
	{
		if (!(ms->command_inf = ft_split(ms->command_pipe[i], -52)))
			ft_exit(ms);
		free(ms->line);
		ms->line = ms->command_inf[0];
			ft_printf("%s\n", ms->line);
	}
	else if (ft_strchr(ms->command_pipe[i], -53))
	{
		if (!(ms->command_inf = ft_split(ms->command_pipe[i], -53)))
			ft_exit(ms);
		free(ms->line);
		ms->line = ms->command_inf[0];
		get_different_option_pipe_inf(ms, i);
		while (ms->command_inf[j])
		{
			k = 0;
			while (ms->command_inf[j][i] && ms->command_inf[j][k] == ' ')				
				k++;
			ms->fd = open(ms->command_inf[j] + k, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |  S_IROTH);
			if (ms->command_inf[j + 1] == NULL)
				write(ms->fd, ms->line, ft_strlen(ms->line));
			close(ms->fd);
			j++;
		}
	}
	ft_strdel(ms->line);
	j = 0;
	// while (ms->command_inf[j])
	// {
	// 	ft_strdel(ms->command_inf[j]);
	// }
	// ft_strdel(ms->command_inf[j]);
	// ft_memdel((void **)ms->command_inf);
	//FREE COMMAND INF
}
void	manage_pipe(t_minishell *ms, int i)
{
	int		j;
	int		tempstdout;
	int		tempstdin;
	int		**fd;

	j = 0;
	i = 0;
	pipe(ms->pfd);
	tempstdout = dup(1);
	tempstdin = dup(0);
	ms->command_pipe = ft_split(ms->command_tab[i], -54);
	while (ms->command_pipe[i])
		i++;
	fd = malloc(sizeof(int *) * (i + 1));
	j = 0;
	while (j < i)
	{
		fd[j] = malloc(sizeof(int) * 2);
		pipe(fd[j]);
		j++;
	}
	j = 0;
	while (ms->command_pipe[j])
	{
		if (ft_strchr(ms->command_pipe[j], -51) || ft_strchr(ms->command_pipe[j], -52)
			|| ft_strchr(ms->command_pipe[j], -53))
			{
				manage_inf_pipe(ms, j);
			}
		else
		{
			if (j == 0 && ms->command_pipe[j + 1] != NULL)
			{
				dup2(fd[j][1], STDOUT_FILENO);
			}
			else if (ms->command_pipe[j + 1] != NULL)
			{
				close(fd[j - 1][1]);
				dup2(fd[j - 1][0], STDIN_FILENO);
				dup2(fd[j][1], STDOUT_FILENO);
			}
			else
			{
					dup2(tempstdout, 1);
					close(fd[j - 1][1]);
					dup2(fd[j - 1][0], STDIN_FILENO);
			}
			get_different_option_pipe(ms, j);
		}
		//if (ms->command_pipe[j + 1] != NULL)
		//	ft_printf("%s\n", ms->line);
		//ft_printf("%s\n", ms->command);
		//ft_printf("%s\n", ms->command_pipe[j]);
		j++;
	}
	dup2(tempstdin, 0);

	//close(ms->pfd[0]);
	//close(ms->pfd[1]);
	//ft_printf("%s\n", ms->line);

}

void	manage_inf(t_minishell *ms, int i)
{
	int		j;
	int		k;

	j = 1;
	k = 0;
	if (ft_strchr(ms->command_tab[i], -51))
	{
		if (!(ms->command_inf = ft_split(ms->command_tab[i], -51)))
			ft_exit(ms);
		free(ms->line);
		ms->line = ms->command_inf[0];
		get_different_option(ms, i);
		while (ms->command_inf[j])
		{
			k = 0;
			while (ms->command_inf[j][i] && ms->command_inf[j][k] == ' ')				
				k++;
			ms->fd = open(ms->command_inf[j] + k, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |  S_IROTH);
			if (ms->command_inf[j + 1] == NULL)
				write(ms->fd, ms->line, ft_strlen(ms->line));
			close(ms->fd);
			j++;
		}
	}
	else if (ft_strchr(ms->command_tab[i], -52))
	{
		if (!(ms->command_inf = ft_split(ms->command_tab[i], -52)))
			ft_exit(ms);
		free(ms->line);
		ms->line = ms->command_inf[0];
			ft_printf("%s\n", ms->line);
	}
	else if (ft_strchr(ms->command_tab[i], -53))
	{
		if (!(ms->command_inf = ft_split(ms->command_tab[i], -53)))
			ft_exit(ms);
		free(ms->line);
		ms->line = ms->command_inf[0];
		get_different_option(ms, i);
		while (ms->command_inf[j])
		{
			k = 0;
			while (ms->command_inf[j][i] && ms->command_inf[j][k] == ' ')				
				k++;
			ms->fd = open(ms->command_inf[j] + k, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |  S_IROTH);
			if (ms->command_inf[j + 1] == NULL)
				write(ms->fd, ms->line, ft_strlen(ms->line));
			close(ms->fd);
			j++;
		}
	}
	ft_strdel(ms->line);
	j = 0;
	// while (ms->command_inf[j])
	// {
	// 	ft_strdel(ms->command_inf[j]);
	// }
	// ft_strdel(ms->command_inf[j]);
	// ft_memdel((void **)ms->command_inf);
	//FREE COMMAND INF
}

int		main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)), char **envp)
{
	t_minishell ms[1];
	int			i;

	i = 0;
	ms->envp = envp;
	ft_init(ms);
	while (1)
	{
		get_next_line(0, &ms->line);
		ft_testing(ms);
		while (ms->command_tab[i])
		{
			if (ft_strchr(ms->command_tab[i], -54))
				manage_pipe(ms, i);
			else if (ft_strchr(ms->command_tab[i], -51) || ft_strchr(ms->command_tab[i], -52)
			|| ft_strchr(ms->command_tab[i], -53))
				manage_inf(ms, i);
			else
			{
				ms->line = ms->command_tab[i];
				get_different_option(ms, i);
				ft_printf("%s", ms->line);
				ft_strdel(ms->line);
				ft_strdel(ms->command);
			}
			//ft_strdel(ms->command_tab[i]);
			i++;
		}
		//ft_strdel(ms->command_tab[i]);
		//ft_memdel((void **)ms->command_tab);
		i = 0;
	}
	ft_exit(ms);
	return (1);
}