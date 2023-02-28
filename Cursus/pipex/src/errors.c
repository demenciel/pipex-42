/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:04:18 by acouture          #+#    #+#             */
/*   Updated: 2023/02/28 12:27:58 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	file_fail(void)
{
	perror("File failed");
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
