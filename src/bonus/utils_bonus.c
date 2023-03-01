/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:25 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/01 17:39:58 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"

void	ft_err_msg(int condition, char *error_message, char *file, int line)
{
	if (!condition)
		return ;
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(": error: ", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	ft_err_sys(int condition, char *file, int line)
{
	if (!condition)
		return ;
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	perror(": error");
	exit (EXIT_FAILURE);
}
