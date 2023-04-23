/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:04:18 by acouture          #+#    #+#             */
/*   Updated: 2023/03/06 10:36:12 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	file_fail(char *m)
{
	if (errno == 0)
		write(2, "Error\n", 6);
	else
		perror(m);
	exit(EXIT_FAILURE);
}

void	pipe_fail(void)
{
	perror("Pipe failed");
	exit(EXIT_FAILURE);
}

void	fork_fail(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

void	dup_fail(void)
{
	perror("Dup failed");
	exit(EXIT_FAILURE);
}

void	malloc_fail(void)
{
	exit(EXIT_FAILURE);
}
