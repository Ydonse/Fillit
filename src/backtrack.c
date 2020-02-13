/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 10:30:52 by ydonse            #+#    #+#             */
/*   Updated: 2018/12/21 16:12:47 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	write_tetri(t_tab *tab, t_tlist *list, short x, short y)
{
	tab->content[x][y] = list->tetri->letter;
	tab->content[x + list->tetri->x2][y + list->tetri->y2] =
		list->tetri->letter;
	tab->content[x + list->tetri->x3][y + list->tetri->y3] =
		list->tetri->letter;
	tab->content[x + list->tetri->x4][y + list->tetri->y4] =
		list->tetri->letter;
}

int		check_tab_limits(t_tab *tab, t_tetri *tetri, short x, short y)
{
	if (tetri->x1 + x >= tab->size || tetri->y1 + y >= tab->size ||
			tetri->x1 + x < 0 || tetri->y1 + y < 0)
		return (0);
	if (tetri->x2 + x >= tab->size || tetri->y2 + y >= tab->size ||
			tetri->x2 + x < 0 || tetri->y2 + y < 0)
		return (0);
	if (tetri->x3 + x >= tab->size || tetri->y3 + y >= tab->size ||
			tetri->x3 + x < 0 || tetri->y3 + y < 0)
		return (0);
	if (tetri->x4 + x >= tab->size || tetri->y4 + y >= tab->size ||
			tetri->x4 + x < 0 || tetri->y4 + y < 0)
		return (0);
	if (tab->content[x + tetri->x1][y + tetri->y1] != '.')
		return (0);
	if (tab->content[x + tetri->x2][y + tetri->y2] != '.')
		return (0);
	if (tab->content[x + tetri->x3][y + tetri->y3] != '.')
		return (0);
	if (tab->content[x + tetri->x4][y + tetri->y4] != '.')
		return (0);
	return (1);
}

int		check_final_tetri(t_tab *tab, t_tlist *list, short x, short y)
{
	if (!(list))
		return (1);
	if (x <= tab->size - 1 && y <= tab->size - 1 &&
			!(check_tab_limits(tab, list->tetri, x, y)))
		return (check_final_tetri(tab, list, x + 1, y));
	else if (x >= tab->size - 1 && y < tab->size - 1 &&
			!(check_tab_limits(tab, list->tetri, x, y)))
		return (check_final_tetri(tab, list, 0, y + 1));
	if (y >= tab->size - 1 && x >= tab->size - 1 &&
		!(check_tab_limits(tab, list->tetri, x, y)))
		return (0);
	if (check_tab_limits(tab, list->tetri, x, y))
	{
		write_tetri(tab, list, x, y);
		if (check_final_tetri(tab, list->next, 0, 0))
			return (1);
		tab->content[x][y] = '.';
		tab->content[x + list->tetri->x2][y + list->tetri->y2] = '.';
		tab->content[x + list->tetri->x3][y + list->tetri->y3] = '.';
		tab->content[x + list->tetri->x4][y + list->tetri->y4] = '.';
		return (check_final_tetri(tab, list, x + 1, y));
	}
	return (0);
}

char	**extend_tab(t_tab *tab)
{
	char	**newtab;
	int		i;
	int		j;

	tab->size += 1;
	i = 0;
	j = 0;
	if (!(newtab = malloc(sizeof(char*) * (tab->size + 1))))
		return (0);
	while (i < tab->size)
	{
		if (!(newtab[i] = malloc(sizeof(char) * (tab->size + 1))))
			return (0);
		while (j < tab->size)
		{
			newtab[i][j] = '.';
			j++;
		}
		newtab[i][j] = '\0';
		j = 0;
		i++;
	}
	newtab[i] = NULL;
	return (newtab);
}

int		resolve_tab(t_tab *tab, t_tlist *list)
{
	char	**newtab;
	int		i;

	while (!check_final_tetri(tab, list, 0, 0))
	{
		newtab = extend_tab(tab);
		i = 0;
		while (i < tab->size)
		{
			ft_strdel(&(tab->content[i]));
			i++;
		}
		free(tab->content);
		tab->content = newtab;
	}
	return (0);
}
