/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:21:32 by acouture          #+#    #+#             */
/*   Updated: 2023/02/27 15:11:17 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char    *env_string(char **env)
{
    char    *env_str;
    char    *path_str;

    env_str = "";
    path_str = "";
    while (*env)
        env_str = ft_strjoin(env_str, *env++);
    path_str = ft_strnstr(env_str, "PATH=", ft_strlen(env_str));
    return (path_str);
}

char    *path_string(char *env)
{
    size_t  env_len;
    size_t  sub_len;
    size_t  i;
    char    *path;
    char    *sub;

    path = "";
    sub = "";
    env_len = ft_strlen(env);
    sub = ft_strnstr(env, "LOGNAME=", env_len);
    sub_len = ft_strlen(sub);
    path = ft_substr(env, 5, (env_len - sub_len) - 5);
    i = ft_strlen(path);
    path[i] = '\0';
    return (path);
}

void    struct_init(t_env *data)
{
    data->env_list = NULL;
    data->path_str = NULL;
    data->fd1 = 0;
    data->fd2 = 0;
}