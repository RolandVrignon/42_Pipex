/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 21:18:22 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex_bonus.h"

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

int		is_path(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char **test(char **tab)
{
	char	**test;
	int 	i;
	
	i = 0;
	while (tab[i] != NULL)
		i++;
	test = (char **)malloc(sizeof(char *) * (i + 3));
	if (!test)
		return (NULL);
	test[0] = (char *)malloc(sizeof(char) * ft_strlen("bash") + 1);
	if (!test[0])
		return (NULL);
	test[0] = "bash\0";
	i = 0;
	while (tab[i] != NULL)
	{
		test[i + 1] = (char *)malloc(sizeof(char) * ft_strlen(tab[i]) + 1);
		if (!test[i + 1])
			return (NULL);
		test[i + 1] = tab[i];
		i++;
	}
	test[i + 1] = NULL;
	return (test);
}

void	execute(char *av, char **envp, int *fd)
{
	char	*path;
	char	**cmd;

	(void)fd;
	cmd = NULL;
	path = NULL;
	if (!av)
		path = NULL;
	else if (ft_strlen(av) > 0)
	{
		cmd = ft_split(av, ' ');
		if (!cmd)
			cmd = NULL;
		if (!is_path(av))
			path = setpath(av, envp);
		else
			path = cmd[0];
		if (access(path, F_OK) != 0)
			path = NULL;
	}
	if (!path)
		return (err_return(cmd, fd));
	if (execve(path, cmd, envp) == -1)
	{
		if (access(path, X_OK != 0))
			perror(path);
		else
		{
			if (execve("/usr/bin/bash", test(cmd), envp) == -1)
				exit(EXIT_FAILURE);
		}
	}
}