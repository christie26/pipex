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

int	pipex_execute(t_data *data, char **env)
{
	int		pipefd[2];
	int		ret;
	pid_t	cpid;


	if (pipe(pipefd) == -1)
		ft_error_msg("Fail to call pipe();", __FILE__, __LINE__);
	cpid = fork();	// fork(); return child process's PID
	if (cpid == -1)
		ft_error_msg("Fail to call fork();", __FILE__, __LINE__);


	if (cpid == 0)	// child process	[infile -> pipefd[WRITE]]
	{
		printf("I am the child process\n");
		printf("Child read %d, write %d\n", pipefd[READ], pipefd[WRITE]);
		ret =  dup2(STDIN_FILENO, data->infile_fd);
		printf("dup2: %d -> %d\nreturn = %d\n", STDIN_FILENO, data->infile_fd, ret);
		execve(data->path_cmd1, data->cmd_options1, env);


	}


	else 			// parent process	[pipefd[READ] -> outfile]
	{
		printf("I am the parent process\n");
		printf("Parent read %d, write %d\n", pipefd[READ], pipefd[WRITE]);
	}



	return (0);
}
