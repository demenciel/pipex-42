/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:54:28 by acouture          #+#    #+#             */
/*   Updated: 2023/03/06 11:01:10 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exec_cmd(char *cmd, t_env *data)
{
	int		i;
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
		search_cmd = ft_strjoin(my_paths[i], my_cmd[0]);
		if (access(search_cmd, 0) == 0)
		{
			if (execve(search_cmd, my_cmd, data->env_list) == -1)
				free(search_cmd);
		}
		else
			data->flag = 1;
	}
	if (data->flag == 1)
		perror("Command not found");
}

void	child_one(t_env *data, int end_write, char *cmd)
{
	if (dup2(data->fd1, STDIN_FILENO) == -1)
		dup_fail();
	if (dup2(end_write, STDOUT_FILENO) == -1)
		dup_fail();
	close(data->fd1);
	exec_cmd(cmd, data);
}

void	child_two(t_env *data, int end_write, char *cmd)
{
	if (dup2(end_write, STDIN_FILENO) == -1)
		dup_fail();
	if (dup2(data->fd2, STDOUT_FILENO) == -1)
		dup_fail();
	close(data->fd2);
	exec_cmd(cmd, data);
}

void	pipex(char **av, t_env *data)
{
	int	pipe_end[2];

	if (pipe(pipe_end) == -1)
		pipe_fail();
	data->child1 = fork();
	if (data->child1 < 0)
		fork_fail();
	if (data->child1 == 0)
	{
		close(pipe_end[0]);
		child_one(data, pipe_end[1], av[2]);
	}
	data->child2 = fork();
	if (data->child2 < 0)
		fork_fail();
	if (data->child2 == 0)
	{
		close(pipe_end[1]);
		child_two(data, pipe_end[0], av[3]);
	}
	else
		wait_and_close(pipe_end, data);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*data;

	data = malloc(sizeof(t_env));
	if (!data)
		exit(1);
	struct_init(data);
	data->env_list = envp;
	data->path_str = env_string(envp);
	if (ac != 5)
		perror("Wrong number of arguments");
	if (!av[2] || !av[3])
		exit(1);
	data->fd1 = open(av[1], O_RDONLY);
	if (data->fd1 < 0)
		file_fail(av[1]);
	data->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (data->fd2 < 0)
		file_fail(av[4]);
	pipex(av, data);
	free(data->path_str);
	free(data);
}
