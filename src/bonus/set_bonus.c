/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:36 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/01 17:39:52 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

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
	ft_err_msg(!path, "Fail to malloc();", __FILE__, __LINE__);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		ft_err_msg(!path[i], "Fail to malloc();", __FILE__, __LINE__);
		free(tmp);
		i++;
	}
	return (path);
}

int	get_cmd(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		data->cmd_options[i] = ft_split(av[i + 2], ' ');
		if (!data->cmd_options[i])
			return (EXIT_FAILURE);
		data->cmd[i] = data->cmd_options[i][0];
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (*cmd == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (0);
	}
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		ft_err_msg(!path_cmd, "Fail to malloc();", __FILE__, __LINE__);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
	i++;
	}
	return (0);
}

int	get_path_cmd(t_data *data, char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < data->number)
	{
		tmp = data->cmd[i];
		data->cmd[i] = check_access(data->cmd[i], path);
		if (!data->cmd[i])
			return (EXIT_FAILURE);
		free(tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	pipex_set(char **av, char **env, t_data *data)
{
	char	**path;

	path = get_path(env);
	data->infile = av[1];
	data->outfile = av[data->number + 2];
	ft_err_sys(get_cmd(data,av), __FILE__, __LINE__);
	ft_err_msg(get_path_cmd(data, path), "Invalid command", \
			__FILE__, __LINE__);
	return (0);
}
