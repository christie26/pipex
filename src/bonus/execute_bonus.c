/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:50:50 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/01 18:19:10 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	close_center(t_data *data, int	*p_fd, int i)
{
	close(p_fd[READ]);
	close(p_fd[WRITE]);
	if (i != 0)
		close(data->read_fd);
}

void	child_process(t_data *data, int *p_fd, int i, char **env)
{
	int	infile;
	int	outfile;

	if (i == 0)
	{
		infile = open(data->infile, O_RDONLY);
		ft_err_sys(dup2(infile, STDIN_FILENO) == -1, __FILE__, __LINE__);
		ft_err_sys(dup2(p_fd[WRITE], STDOUT_FILENO) == -1, __FILE__, __LINE__);
		close(infile);
	}
	else if (i == data->number - 1)
	{
		outfile = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_err_sys(dup2(data->read_fd, STDIN_FILENO) == -1, __FILE__, __LINE__);
		ft_err_sys(dup2(outfile, STDOUT_FILENO) == -1, __FILE__, __LINE__);
		close(outfile);
	}
	else
	{
		ft_err_sys(dup2(data->read_fd, STDIN_FILENO) == -1, __FILE__, __LINE__);
		ft_err_sys(dup2(p_fd[WRITE], STDOUT_FILENO) == -1, __FILE__, __LINE__);
	}
	close_center(data, p_fd, i);
	execve(data->cmd[i], data->cmd_options[i], env);
	exit(0);
}

void	parent_process(t_data *data, int *p_fd, int i)
{
	if (i == 0)
	{
		data->read_fd = p_fd[READ];
		close(p_fd[WRITE]);
	}
	else if (i == data->number - 1)
	{
		close(data->read_fd);
		close(p_fd[READ]);
		close(p_fd[WRITE]);
	}
	else
	{
		close(data->read_fd);
		close(p_fd[WRITE]);
		data->read_fd = p_fd[READ];
	}
}

int	pipex_execute(t_data *data, char **env)
{
	pid_t	cpid;
	int		i;
	int		p_fd[2];

	i = 0;
	while (i < data->number)
	{
		ft_err_sys(pipe(p_fd) == -1, __FILE__, __LINE__);
		cpid = fork();
		ft_err_sys(cpid == -1, __FILE__, __LINE__);
		if (cpid == 0)
			child_process(data, p_fd, i, env);
		else
			parent_process(data, p_fd, i);
		i++;
	}
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (0);
}
