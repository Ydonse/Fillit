/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:34:24 by fmerding          #+#    #+#             */
/*   Updated: 2018/12/21 16:56:57 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_stuck(char *str)
{
	int i;
	int link;

	i = 0;
	link = 0;
	while (i <= 15)
	{
		while (str[i] == '.')
			i++;
		if (i == 16)
			break ;
		if (i != 3 && i != 7 && i != 11 && i != 15 && str[i + 1] == '#')
			link++;
		if (i != 0 && i != 4 && i != 8 && i != 12 && str[i - 1] == '#')
			link++;
		if (i < 12 && str[i + 4] == '#')
			link++;
		if (i > 3 && str[i - 4] == '#')
			link++;
		i++;
	}
	if (link < 6)
		return (0);
	return (1);
}

char		*ft_topleft(char *str)
{
	int i;

	while (str[0] == '.' && str[4] == '.' && str[8] == '.' && str[12] == '.')
	{
		i = 1;
		while (str[i] != '\0')
		{
			str[i - 1] = str[i];
			i++;
		}
		str[15] = '.';
	}
	while (str[0] == '.' && str[1] == '.' && str[2] == '.' && str[3] == '.')
	{
		i = 4;
		while (str[i] != '\0')
		{
			str[i - 4] = str[i];
			i++;
		}
		i = 12;
		while (str[i] != '\0')
			str[i++] = '.';
	}
	return (str);
}

int			ft_verif(char **tab)
{
	int i;
	int u;
	int hashtag;

	u = 0;
	while (tab[u])
	{
		hashtag = 0;
		i = 0;
		if (ft_strlen(tab[u]) != 16 || ft_stuck(tab[u]) == 0)
			return (0);
		while (tab[u][i] != '\0')
		{
			if (tab[u][i] != '#' && tab[u][i] != '.')
				return (0);
			if (tab[u][i++] == '#')
				hashtag++;
		}
		if (hashtag != 4)
			return (0);
		tab[u] = ft_topleft(tab[u]);
		u++;
	}
	return (1);
}

char		**fill_tab(char **tab, int fd, char *line, int i)
{
	int		j;
	int		u;
	char	*res;

	u = -1;
	while (i == 1 && ++u <= 25)
	{
		res = ft_strdup("");
		j = -1;
		while (++j != 5)
		{
			i = get_next_line(fd, &line);
			if (j == 0 && ft_strlen(line) == 0)
				return (0);
			if ((res = ft_strjoin_free(&res, &line)) && i == 0)
				break ;
		}
		if (j == 0 && i == 0)
			return (tab);
		if (!(tab[u] = (char*)malloc(sizeof(char) * (ft_strlen(res) + 1))))
			exit(0);
		tab[u] = ft_strcpy(tab[u], res);
		ft_memdel((void **)&res);
	}
	return (j != 4 ? 0 : tab);
}

char		**global_verif(char **av)
{
	char	**tab;
	char	*line;
	int		fd;
	int		i;

	tab = NULL;
	i = 0;
	line = NULL;
	fd = open(av[1], O_RDONLY);
	if (fd < 1)
		return (0);
	if (!(tab = (char**)malloc(sizeof(char*) * 27)))
		exit(0);
	while (i < 27)
	{
		tab[i] = NULL;
		i++;
	}
	i = 1;
	if ((tab = fill_tab(tab, fd, line, i)) == NULL)
		return (0);
	if (ft_verif(tab) == 0)
		return (0);
	close(fd);
	return (tab);
}
