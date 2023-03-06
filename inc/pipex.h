/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:56:00 by acouture          #+#    #+#             */
/*   Updated: 2023/03/06 10:23:53 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

typedef struct s_env
{
	char	**env_list;
	char	*path_str;
	int		fd1;
	int		fd2;
	pid_t	child1;
	pid_t	child2;
	int		child1_status;
	int		child2_status;
	int		flag;
}			t_env;

void		file_fail(char *m);
void		pipe_fail(void);
void		fork_fail(void);
void		dup_fail(void);
void		malloc_fail(void);
void		struct_init(t_env *data);
void		exec_cmd(char *cmd, t_env *data);
void		pipex(char **av, t_env *data);
void		child_one(t_env *data, int end_write, char *cmd);
void		child_two(t_env *data, int end_write, char *cmd);
void		wait_and_close(int *pipe_end, t_env *data);
void		ft_freeall(char **tab);

char		*env_string(char **env);
char		*get_path_from_env(char *env);

#endif