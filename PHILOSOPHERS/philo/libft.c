/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:07:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/01 15:23:57 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

static char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen (s1);
	s2 = (char *) malloc (len + 1);
	i = 0;
	while (i < len)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[len] = '\0';
	return (s2);
}

static int	ft_isnumber(char *s)
{
	int	digitsc;

	if (s == NULL || ft_strlen (s) == 0)
		return (0);
	digitsc = 0;
	if (s[0] == '+' || s[0] == '-')
		s++;
	else if (!(s[0] >= '0' && s[0] <= '9'))
		return (0);
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
		{
			digitsc++;
			s++;
		}
		else
			return (0);
	}
	if (digitsc > 0)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;
	int	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		nbr = -nbr;
	}
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
		if (nbr == 0)
			nbr += str[i] - '0';
	else
			nbr = (nbr * 10) + str[i] - '0';
	return (nbr * sign);
}

int	ft_isint(char *s, int i)
{
	char	*m;
	int		res;

	if (s == NULL || !ft_isnumber (s) || ft_strlen (s) > 11)
		return (0);
	m = ft_strdup ("2147483647");
	if (m == NULL)
		return (0);
	if (s[0] == '-')
		m[9] = '8';
	if (s[0] == '+' || s[0] == '-')
		s++;
	res = 1;
	while (s[++i] != '\0')
	{
		if (s[i] < m[i] || (s[i] > m[i] && ft_strlen (s) == 10))
		{
			if (s[i] > m[i] && ft_strlen (s) == 10)
				res = 0;
			break ;
		}
	}
	free (m);
	return (res);
}
