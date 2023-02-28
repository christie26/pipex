/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/28 19:19:38 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	first_child(t_data *data, int *p_fd, char **env, int i)
{
	int	ret;
	int	infile;

	close(p_fd[READ]);
	infile = open(data->infile, O_RDONLY);
	ret = dup2(infile, STDIN_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	ret = dup2(p_fd[WRITE], STDOUT_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	close(infile);
	close(p_fd[WRITE]);
	execve(data->cmd[0], data->cmd_options[0], env);
	exit(0);
}

void	middle_child(t_data *data, int *p_fd, char **env, int i)
{
	int	ret;

	close(p_fd[READ]);
	ret = dup2(data->read_fd, STDIN_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	ret = dup2(p_fd[WRITE], STDOUT_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	close(p_fd[WRITE]);
	close(data->read_fd);
	execve(data->cmd[i], data->cmd_options[i], env);
	exit(0);
}

void	last_child(t_data *data, int *p_fd, char **env, int i)
{
	int	ret;
	int	outfile;

	outfile = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(p_fd[READ]);
	close(p_fd[WRITE]);
	ret = dup2(data->read_fd, STDIN_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	ret = dup2(outfile, STDOUT_FILENO);
	if (ret == -1)
		ft_error_syscall(__FILE__, __LINE__);
	close(outfile);
	execve(data->cmd[i], data->cmd_options[i], env);
	exit(0);
}

void	first_parent(t_data *data, int *p_fd, int i)
{
	data->read_fd = p_fd[READ];
	close(p_fd[WRITE]);
}

void	middle_parent(t_data *data, int *p_fd, int i)
{
	close(data->read_fd);
	close(p_fd[WRITE]);
	data->read_fd = p_fd[READ];
}

void	last_parent(t_data *data, int *p_fd, int i)
{
	close(data->read_fd);
	close(p_fd[READ]);
	close(p_fd[WRITE]);
}

int	pipex_execute(t_data *data, char **env)
{
	pid_t	cpid;
	int		i;
	int		p_fd[2];

	i = 0;
	while (i < data->number)
	{
		if (pipe(p_fd) == -1)
			ft_error_msg("Fail to call pipe();", __FILE__, __LINE__);
		cpid = fork();
		if (cpid == -1)
			ft_error_msg("Fail to call fork();", __FILE__, __LINE__);
	
		if (cpid == 0)
		{
			if (i == 0)
				first_child(data, p_fd, env, i);
			else if (i == data->number - 1)
				last_child(data, p_fd, env, i);
			else
				middle_child(data, p_fd, env, i);
		}
		else
		{
			if (i == 0)
				first_parent(data, p_fd, i);
			else if (i == data->number - 1)
				last_parent(data, p_fd, i);
			else
				middle_parent(data, p_fd, i);
		}
		i++;
	}
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (0);
}
