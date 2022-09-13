/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/13 17:04:46 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**find_path(char **e)
{
	int		i;
	char	**paths;

	if (!e[0])
		return (NULL);
	i = 0;
	while (e[i + 1] && (ft_strnstr(e[i], "PATH", 4) == 0 || e[i][4] != '='))
		i++;
	if (ft_strnstr(e[i], "PATH", 4) == 0 || e[i][4] != '=')
		return (NULL);
	paths = ft_split(e[i] + 5, ':');
	return (paths);
}

char	*find_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = find_path(envp);
	if (!paths)
		return (0);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	free_double(paths);
	return (0);
}

void	err_return(char **cmd, int i, int *fd)
{
	char	*err;

	if (!cmd)
		ft_putstr_fd("Command '' not found\n", 2);
	else
	{
		err = ft_strjoin(cmd[0], ": Command not found\n");
		ft_putstr_fd(err, 2);
		free(err);
	}
	if (cmd)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	close_pipes(fd);
}

void	execute(char *av, char **envp, int *fd)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = NULL;
	if (ft_strlen(av) == 0)
		path = NULL;
	else
	{
		cmd = ft_split(av, ' ');
		if (access(cmd[0], F_OK) == 0)
			path = cmd[0];
		else
			path = find_cmdpath(cmd[0], envp);
	}
	if (!path)
	{
		err_return(cmd, i, fd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
		exit(EXIT_FAILURE);
}
