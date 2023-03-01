/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:46 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/01 21:08:26 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_err_msg(ac != 5, "Invalid number of arguments", __FILE_NAME__, __LINE__);
	pipex_set(av, env, &data);
	pipex_execute(&data, env);
	return (EXIT_SUCCESS);
}
