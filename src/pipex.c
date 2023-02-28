/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:54:28 by acouture          #+#    #+#             */
/*   Updated: 2023/02/28 11:48:22 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exec_cmd(char *cmd, t_env *data)
{
	int		i;
	int		flag;
	char	**my_paths;
	char	**my_cmd;
	char	*search_cmd;

	my_paths = ft_split(data->path_str, ':');
	i = -1;
	while (my_paths[++i])
		my_paths[i] = ft_strjoin(my_paths[i], "/");
	my_cmd = ft_split(cmd, ' ');
	i = -1;
	while (my_paths[++i])
	{
		flag = 0;
		search_cmd = ft_strjoin(my_paths[i], my_cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			if (execve(search_cmd, my_cmd, data->env_list) == -1)
			{
				perror("Error");
				flag = -1;
				free(search_cmd);
			}
		}
	}
	if (flag == -1)
		perror("Wrong command");
}

void	child_one(t_env *data, int end_write, char *cmd)
{
	if (dup2(data->fd1, STDIN_FILENO) < 0 || dup2(end_write, STDOUT_FILENO) < 0)
		dup_fail();
	close(data->fd1);
	exec_cmd(cmd, data);
}

void	child_two(t_env *data, int end_write, char *cmd)
{
	if (dup2(end_write, STDIN_FILENO) == -1 || dup2(data->fd2, STDOUT_FILENO) ==
		-1)
		dup_fail();
	close(data->fd2);
	exec_cmd(cmd, data);
}

void	pipex(char **av, t_env *data)
{
	pid_t	child1;
	pid_t	child2;
	int		pipe_end[2];

	if (pipe(pipe_end) == -1)
		pipe_fail();
	child1 = fork();
	if (child1 < 0)
		fork_fail();
	if (child1 == 0)
	{
		close(pipe_end[0]);
		child_one(data, pipe_end[1], av[2]);
	}
	child2 = fork();
	if (child2 < 0)
		fork_fail();
	if (child2 == 0)
	{
		close(pipe_end[1]);
		child_two(data, pipe_end[0], av[3]);
	}
	else 
	{
		close(pipe_end[0]);
		close(pipe_end[1]);
		waitpid(child1, &data->child1_status, 0);
		waitpid(child2, &data->child2_status, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *data;

	data = malloc(sizeof(t_env));
	struct_init(data);
	data->env_list = envp;
	data->path_str = path_string(env_string(envp));
	if (ac == 5)
	{
		data->fd1 = open(av[1], O_RDONLY);
		data->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 00644);
		if (data->fd1 < 0 || data->fd2 < 0)
			file_fail();
		pipex(av, data);
	}
	else
		perror("Wrong argument count");
}