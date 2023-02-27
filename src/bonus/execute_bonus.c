/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/27 16:43:13 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	first_process(t_data *data, int pipefd[], char **env)
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
	execve(data->cmd[0], data->cmd_options[0], env);
}

void	middle_process(t_data *data, int pipefd[], char **env, int i)
{
	int	ret;

	ret = dup2(pipefd[READ], STDIN_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	ret = dup2(pipefd[WRITE], STDOUT_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	execve(data->cmd[i], data->cmd_options[i], env);
}

void	last_process(t_data *data, int pipefd[], char **env, int i)
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
	execve(data->cmd[i], data->cmd_options[i], env);
}

int	pipex_execute(t_data *data, char **env)
{
	int		pipefd[2];
	pid_t	cpid;
	int		i;

	i = 0;
	while (i < data->number)
	{
		if (pipe(pipefd) == -1)
			ft_error_msg("Fail to call pipe();", __FILE__, __LINE__);
		cpid = fork();
		if (cpid == -1)
			ft_error_msg("Fail to call fork();", __FILE__, __LINE__);
	
		if (cpid == 0)
		{
			printf("%dth process start\n", i);
			if (i == 0)	
				first_process(data, pipefd, env);
			else if (i == data->number - 1)
				last_process(data, pipefd, env, i);
			else
				middle_process(data, pipefd, env, i);
		}
		else
		{
			close(pipefd[READ]);
			close(pipefd[WRITE]);
			waitpid(cpid, 0, 0);
		}
		i++;
	}

	return (0);
}
