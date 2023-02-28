/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:21:32 by acouture          #+#    #+#             */
/*   Updated: 2023/02/28 15:14:12 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	struct_init(t_env *data)
{
	data->env_list = NULL;
	data->path_str = NULL;
	data->fd1 = 0;
	data->fd2 = 0;
	data->child1_status = 0;
	data->child2_status = 0;
}

char	*get_path_from_env(char *env)
{
	char	*path_start;
	char	*path_end;
	char	*path;
	int		size;

	path_start = ft_strnstr(env, "PATH=", ft_strlen(env));
	if (!path_start)
		malloc_fail();
	path_start += 5;
	path_end = ft_strnstr(path_start, "LOGNAME=", ft_strlen(path_start));
	if (!path_end)
		path_end = env + ft_strlen(env);
	size = ft_strlen(path_start) - ft_strlen(path_end);
	if (size < 0)
		return (NULL);
	path = ft_substr(path_start, 0, size);
	return (path);
}

char	*env_string(char **env)
{
	size_t	env_len;
	char	*env_str;
	char	*path_str;
	int		i;

	env_len = 0;
	i = 0;
	while (env[i])
		env_len += ft_strlen(env[i++]);
	env_str = malloc(sizeof(char) * env_len + 1);
	if (!env_str)
		malloc_fail();
	env_str[0] = '\0';
	i = 0;
	while (env[i++])
		ft_strlcat(env_str, env[i], env_len + 1);
	path_str = get_path_from_env(env_str);
	free(env_str);
	return (path_str);
}

void	wait_and_close(int *pipe_end, t_env *data)
{
	close(pipe_end[0]);
	close(pipe_end[1]);
	waitpid(data->child1, &data->child1_status, 0);
	waitpid(data->child2, &data->child2_status, 0);
}
