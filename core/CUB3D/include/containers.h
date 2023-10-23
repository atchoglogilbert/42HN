/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajaobe <rrajaobe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:06:56 by katchogl          #+#    #+#             */
/*   Updated: 2023/02/28 10:57:28 by rrajaobe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_H
# define CONTAINERS_H
# include <stddef.h>

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;
typedef struct s_dims
{
	int	width;
	int	height;
}	t_dims;
#endif