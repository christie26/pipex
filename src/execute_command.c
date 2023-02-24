/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/24 19:43:17 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	execute_command(t_data *data, char **env)
{
	int		pipefd[2];
	pid_t	cpid;
	execve(data->path_cmd1, data->cmd_options1, env);

	return (0);
}