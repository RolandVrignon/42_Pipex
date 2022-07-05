/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:47:45 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/05 11:52:59 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_opt(int cmd_nbr, char **av, int heredoc)
{
	int		i;
	int		j;
	char	**tab;
	char	**split;

	i = 0;
	j = 2 + heredoc;
	tab = malloc(sizeof(char *) * (cmd_nbr + 1));
	if (!tab)
		return (NULL);
	while (i < cmd_nbr)
	{
		split = ft_split(av[i + j], ' ');
		if (!split)
			return (NULL);
		if (split[1] == NULL)
			tab[i] = ft_strdup("pipexnull");
		else
			tab[i] = ft_strdup(split[1]);
		free_double(split);
		i++;
	}
	tab[i] = 0;
	return (tab);
}

static char	*return_value(char *cmd_path, char **paths)
{
	free_double(paths);
	return (cmd_path);
}

char	*get_cmd_path(char *cmd, char *envp_PATH)
{
	char	**paths;
	char	*tmp;
	char	*cmd_path;
	int		i;

	paths = ft_split(envp_PATH, ':');
	if (!paths)
		return (0);
	i = 0;
	while (paths[i++])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	i = 0;
	while (paths[i++])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK | X_OK))
			return (return_value(cmd_path, paths));
		free(cmd_path);
	}
	free_double(paths);
	return (NULL);
}

char	**get_paths(t_pipex pipex)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (pipex.cmd_nbr + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < pipex.cmd_nbr)
	{
		tab[i] = get_cmd_path(pipex.cmd[i], pipex.env_path);
		if (!tab[i])
		{
			perror(pipex.cmd[i]);
			free_double(tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = 0;
	return (tab);
}

// void	print_test(t_pipex pipex)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("PIPEEEEX\n");
// 	ft_printf("Nb cmd\t:\t%d\n", pipex.cmd_nbr);
// 	ft_printf("infile\t:\t%d\n", pipex.infile_fd);
// 	ft_printf("outfile\t:\t%d\n", pipex.outfile_fd);
// 	while (pipex.cmd[i])
// 	{
// 		ft_printf("i = %d\t||\tcommand : %s\t||\toption : %s\t\t||\tpath : %s\n",
// 			i, pipex.cmd[i], pipex.opt[i], pipex.cpath[i]);
// 		i++;
// 	}
// }
