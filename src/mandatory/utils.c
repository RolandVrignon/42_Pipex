/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/19 13:03:42 by rvrignon         ###   ########.fr       */
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
		return (NULL);
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
	return (NULL);
}

char	*setpath(char *av, char **envp)
{
	char	**cmd;

	if (!av)
		return (NULL);
	else
	{
		cmd = ft_split(av, ' ');
		if (!cmd[0])
			return (NULL);
		else if (!find_cmdpath(cmd[0], envp))
			return (cmd[0]);
		else
			return (find_cmdpath(cmd[0], envp));
	}
}

void	execute(char *av, char **envp, int *fd)
{
	char	*path;
	char	**cmd;

	cmd = NULL;
	path = NULL;
	if (!av)
		path = NULL;
	else if (ft_strlen(av) > 0)
	{
		cmd = ft_split(av, ' ');
		if (!cmd[0])
			cmd = NULL;
		path = setpath(av, envp);
		if (access(path, X_OK) != 0)
			path = NULL;
	}
	if (!path)
	{
		err_return(cmd, fd);
		return ;
	}
	if (execve(path, cmd, envp) == -1)
		exit(EXIT_FAILURE);
}
