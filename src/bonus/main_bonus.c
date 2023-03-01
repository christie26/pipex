/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:46 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/01 18:13:12 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_err_msg(ac < 5, "Invalid number of arguments", __FILE__, __LINE__);
	data.number = ac - 3;
	data.cmd = (char **)malloc(sizeof(char *) * data.number);
	ft_err_msg(!data.cmd, "Fail to malloc();", __FILE__, __LINE__);
	data.cmd_options = (char ***)malloc(sizeof(char **) * data.number);
	ft_err_msg(!data.cmd_options, "Fail to malloc();", __FILE__, __LINE__);
	pipex_set(av, env, &data);
	pipex_execute(&data, env);
	return (EXIT_SUCCESS);
}
