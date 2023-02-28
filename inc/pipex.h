/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:56:00 by acouture          #+#    #+#             */
/*   Updated: 2023/02/28 11:39:19 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>

typedef struct  s_env {
    char    **env_list;
    char    *path_str;
    int     fd1;
    int     fd2;
    int     child1_status;
    int     child2_status;
}               t_env;


void    file_fail();
void    pipe_fail();
void    fork_fail();
void    dup_fail();
void    struct_init(t_env *data);
void    exec_cmd(char *cmd, t_env *data);
void    pipex(char **av, t_env *data);
void    child_one(t_env *data, int end_write, char *cmd);
void    child_two(t_env *data, int end_write, char *cmd);

char    *env_string(char **env);
char    *path_string(char *env);