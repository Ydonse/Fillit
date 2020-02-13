/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 10:03:54 by ydonse            #+#    #+#             */
/*   Updated: 2018/12/21 16:12:56 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tlist		*add_tetri_list(t_tlist *list, short *tab)
{
	char c;

	c = list->tetri->letter;
	if (!((list->next = malloc(sizeof(t_tlist)))))
		return (NULL);
	list = list->next;
	if (!((list->tetri = malloc(sizeof(t_tetri)))))
		return (0);
	list->tetri->letter = c + 1;
	list->tetri->x1 = 0;
	list->tetri->y1 = 0;
	list->tetri->x2 = tab[2];
	list->tetri->y2 = tab[3];
	list->tetri->x3 = tab[4];
	list->tetri->y3 = tab[5];
	list->tetri->x4 = tab[6];
	list->tetri->y4 = tab[7];
	list->next = NULL;
	return (list);
}

void		str_to_struct(t_tlist *list, char *str)
{
	short tab[8];
	short i;
	short y;
	short z;

	i = 0;
	y = 0;
	z = 0;
	while (i < 9)
		tab[i++] = 0;
	i = 0;
	while (i <= 3 && str[i] == '.')
		i++;
	z = i;
	i = 0;
	while (i < 15)
	{
		if (str[i] == '#')
		{
			tab[y++] = i % 4 - z;
			tab[y++] = i / 4;
		}
		i++;
	}
	list = add_tetri_list(list, tab);
}

int			fill_list(t_tlist *list, char **av, t_tab *tab)
{
	char	**tab2;
	int		i;

	i = 0;
	if (!((tab2 = global_verif(av))))
	{
		ft_putstr("error\n");
		exit(0);
	}
	while (tab2[i])
	{
		str_to_struct(list, tab2[i]);
		list = list->next;
		i++;
	}
	delete_tab(tab2);
	tab->size = ft_sqrt_high((i) * 4);
	return (i);
}

void		delete_tab(char **tab)
{
	int	j;

	j = 0;
	while (j < 27)
	{
		ft_strdel(&tab[j]);
		j++;
	}
	ft_memdel((void **)&tab);
	tab = NULL;
}

int			init_tab(t_tab *tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(tab->content = malloc(sizeof(char *) * (tab->size + 1))))
		return (0);
	while (i < tab->size)
	{
		if (!(tab->content[i] = malloc(sizeof(char) * (tab->size + 1))))
			return (0);
		while (j < tab->size)
		{
			tab->content[i][j] = '.';
			j++;
		}
		tab->content[i][j] = '\0';
		j = 0;
		i++;
	}
	tab->content[i] = NULL;
	return (1);
}
