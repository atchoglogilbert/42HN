/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 07:39:09 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/02 19:08:23 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_isnbr(char *str)
{
	if (str == NULL)
		return (false);
	if (str[0] == '+' || str[0] == '-')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit (*str))
			return (false);
		str++;
	}
	return (true);
}

size_t	ft_tablen(char **tab)
{
	size_t	len;

	if (tab == NULL)
		return (0);
	len = 0;
	while (*tab++)
		len++;
	return (len);
}

char	*ft_str_rm_endl(char *str)
{
	char	*nstr;

	if (str == NULL)
		return (NULL);
	if (str[ft_strlen(str) - 1] == '\n')
	{
		nstr = ft_substr (str, 0, ft_strlen (str) - 1);
		free (str);
		return (nstr);
	}
	return (str);
}

void	ft_push(t_game *game, char ***tab, char *str)
{
	char	**ntab;
	int		size_tab;
	int		i;

	if (str == NULL)
		return ;
	size_tab = 0;
	if (*tab != NULL)
	{
		i = -1;
		while ((*tab)[++i] != NULL)
			size_tab++;
	}
	ntab = (char **) malloc ((size_tab + 2) * sizeof (char *));
	if (ntab == NULL)
		ft_throw (game, "malloc fail /ft_push");
	i = -1;
	while (++i < size_tab)
		ntab[i] = ft_strdup ((*tab)[i]);
	ntab[i] = ft_strdup (str);
	ntab[i + 1] = NULL;
	if (*tab != NULL)
		ft_destroy_tab (*tab);
	*tab = ntab;
}

bool	ft_isempty(t_game *game, char *str)
{
	if (str == NULL)
		ft_throw (game, "null str");
	while (*str)
	{
		if (*str != ' ' && !(*str == '\n' && *(str + 1) == '\0'))
			return (false);
		str++;
	}
	return (true);
}
