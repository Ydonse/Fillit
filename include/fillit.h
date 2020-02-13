/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:58:45 by ydonse            #+#    #+#             */
/*   Updated: 2018/12/21 16:54:15 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

typedef struct		s_tab
{
	char	**content;
	short	size;
}					t_tab;

typedef struct		s_tetri
{
	char			letter;
	short			x1;
	short			y1;
	short			x2;
	short			y2;
	short			x3;
	short			y3;
	short			x4;
	short			y4;
}					t_tetri;

typedef	struct		s_tlist
{
	t_tetri			*tetri;
	struct s_tlist	*next;
}					t_tlist;

void				delete_tab(char **tab);
int					put_tetri(char **tab, t_tetri tetri, short size);
int					check_tab_limits(t_tab *tab, t_tetri *tetri,
					short x, short y);
char				**global_verif(char **av);
int					check_pos(t_tab *grid, t_tetri *tetri, short x, short y);
int					resolve_tab(t_tab *tab, t_tlist *list);
char				**extend_tab(t_tab *tab);
void				print_tab(short len, char **str);
void				str_to_struct(t_tlist *list, char *str);
t_tlist				*add_tetri_list(t_tlist *list, short *tab);
int					init_tab(t_tab *tab);
int					fill_list(t_tlist *list, char **av, t_tab *tab);
void				free_memory(t_tab *tab, t_tlist *list);
int					ft_sqrt_high(int nb);
#endif
