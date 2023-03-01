#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define READ 0
# define WRITE 1

typedef struct s_data {
	int		number;
	char	**cmd;
	char	***cmd_options;
	int		file_fd[2];
	int		read_fd;
	char	*infile;
	char	*outfile;
}	t_data;

// handle error 
void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);

// set path and check accessibility
int		pipex_set(char **av, char **env, t_data *data);

// fork and execute 
int		pipex_execute(t_data *data, char **env);

#endif
