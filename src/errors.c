/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouture <acouture@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:04:18 by acouture          #+#    #+#             */
/*   Updated: 2023/02/27 11:37:23 by acouture         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void    file_fail()
{
    perror("File failed");
    exit(EXIT_FAILURE);
}

void    pipe_fail()
{
    perror("Pipe failed");
    exit(EXIT_FAILURE);
}

void    fork_fail()
{
    perror("Fork failed");
    exit(EXIT_FAILURE);
}

void    dup_fail()
{
    perror("Dup failed");
    exit(EXIT_FAILURE);
}