/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/27 15:40:57 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_data *data, int pipefd[], char **env)
{
	int	ret;

	close(pipefd[READ]);
	ret = dup2(data->file_fd[READ], STDIN_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	ret = dup2(pipefd[WRITE], STDOUT_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	close(data->file_fd[READ]);
	close(pipefd[WRITE]);
	execve(data->path_cmd1, data->cmd_options1, env);
}

void	parent_process(t_data *data, int pipefd[], char **env)
{
	int	ret;

	close(pipefd[WRITE]);
	wait(0);
	ret = dup2(pipefd[READ], STDIN_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	ret = dup2(data->file_fd[WRITE], STDOUT_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	close(pipefd[READ]);
	close(data->file_fd[WRITE]);
	execve(data->path_cmd2, data->cmd_options2, env);
}

int	pipex_execute(t_data *data, char **env)
{
	int		pipefd[2];
	pid_t	cpid;

	if (pipe(pipefd) == -1)
		ft_error_msg("Fail to call pipe();", __FILE__, __LINE__);
	cpid = fork();
	if (cpid == -1)
		ft_error_msg("Fail to call fork();", __FILE__, __LINE__);
	if (cpid == 0)
		child_process(data, pipefd, env);
	else
		parent_process(data, pipefd, env);
	return (0);
}
