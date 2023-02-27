/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:36 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/24 18:19:35 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	while (*env++)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			break ;
	}
	path = ft_split((*env + 5), ':');
	if (!path)
		ft_error_msg("Fail to malloc();", __FILE__, __LINE__);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			ft_error_msg("Fail to malloc();", __FILE__, __LINE__);
		free(tmp);
		i++;
	}
	return (path);
}

int	get_cmd(t_data *data, char **av)
{
	int		i;

	data->cmd_options1 = ft_split(av[2], ' ');
	if (!data->cmd_options1)
		return (EXIT_FAILURE);
	data->cmd_options2 = ft_split(av[3], ' ');
	if (!data->cmd_options2)
		return (EXIT_FAILURE);
	data->cmd1 = data->cmd_options1[0];
	data->cmd2 = data->cmd_options2[0];
	return (EXIT_SUCCESS);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (path[i])
	{
		// don't add / if they already have it
		path_cmd = ft_strjoin(path[i], cmd);
		if (!path_cmd)
			ft_error_msg("Fail to malloc();", __FILE__, __LINE__);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
	i++;
	}
	return (0);
}

int	get_path_cmd(t_data *data, char **path)
{
	char	*path_cmd;

	path_cmd = check_access(data->cmd1, path);
	if (!path_cmd)
		return (EXIT_FAILURE);
	data->path_cmd1 = path_cmd;
	path_cmd = check_access(data->cmd2, path);
	if (!path_cmd)
		return (EXIT_FAILURE);
	data->path_cmd2 = path_cmd;
	return (EXIT_SUCCESS);
}

int	pipex_set(char **av, char **env, t_data *data)
{
	char	**path;

	path = get_path(env);
	data->file_fd[READ] = open(av[1], O_RDONLY);
	if (data->file_fd[READ] == -1)
		ft_error_syscall(__FILE__, __LINE__);
	data->file_fd[WRITE] = open(av[4], O_CREAT | O_WRONLY);
	if (data->file_fd[WRITE] == -1)
		ft_error_syscall(__FILE__, __LINE__);
	if (get_cmd(data, av))
		ft_error_syscall(__FILE__, __LINE__);
	if (get_path_cmd(data, path))
		ft_error_msg("Invalid command", __FILE__, __LINE__);
	return (0);
}
