/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:10:15 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/13 11:58:47 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_tab(short len, char **str)
{
	short x;
	short y;

	x = 0;
	y = 0;
	while (y < len)
	{
		while (x < len)
		{
			ft_putchar(str[x][y]);
			x++;
		}
		x = 0;
		ft_putchar('\n');
		y++;
	}
}

void	free_memory(t_tab *tab, t_tlist *list)
{
	int		i;
	t_tlist	*node;

	i = 0;
	while (tab->content[i])
	{
		ft_strdel(&(tab->content[i]));
		i++;
	}
	free(tab->content);
	free(tab);
	while ((list)->next)
	{
		free(list->tetri);
		list->tetri = NULL;
		node = list;
		list = list->next;
		free(node);
	}
	free(list->tetri);
	list->tetri = NULL;
	free(list);
	list = NULL;
}

int		main(int ac, char **av)
{
	t_tlist *list;
	t_tlist	*node;
	t_tab	*tab;

	if (ac != 2)
	{
		ft_putstr("usage : ./fillit source_file\n");
		return (0);
	}
	if (!((list = malloc(sizeof(t_tlist)))))
		return (0);
	if (!((list->tetri = malloc(sizeof(t_tetri)))))
		return (0);
	list->tetri->letter = 'A' - 1;
	list->next = NULL;
	node = list;
	if (!((tab = malloc(sizeof(t_tab)))))
		return (0);
	if (!(fill_list(node, av, tab)) || (!(init_tab(tab))))
		exit(0);
	resolve_tab(tab, list->next);
	print_tab(tab->size, tab->content);
	free_memory(tab, list);
	return (0);
}
