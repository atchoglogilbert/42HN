/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:52:22 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/31 20:37:12 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_freephilos(t_data *data)
{
	int	i;

	if (data == NULL || data->philos == NULL)
		return ;
	i = -1;
	while (++i < data->philoc)
	{
		if (data->philos[i] != NULL)
		{
			free (data->philos[i]->pthread);
			if (data->philos[i]->mutex_state != NULL)
			{
				pthread_mutex_destroy (data->philos[i]->mutex_state);
				free (data->philos[i]->mutex_state);
				pthread_mutex_destroy (data->philos[i]->mutex_t_start);
				free (data->philos[i]->mutex_t_start);
			}
			free (data->philos[i]);
		}
	}
	free (data->philos);
}

static void	ft_freemutexes(t_data *data)
{
	int	i;

	if (data->mutexes == NULL)
		return ;
	i = -1;
	while (++i < data->philoc)
	{
		if (data->mutexes[i] != NULL)
		{
			pthread_mutex_destroy (data->mutexes[i]);
			free (data->mutexes[i]);
		}
	}
	free (data->mutexes);
}

static void	ft_freemutexespl(t_data *data)
{
	if (data->mutex_out != NULL)
	{
		pthread_mutex_destroy (data->mutex_out);
		free (data->mutex_out);
	}
	if (data->mutex_philo_dead != NULL)
	{
		pthread_mutex_destroy (data->mutex_philo_dead);
		free (data->mutex_philo_dead);
	}
	if (data->mutex_eatc != NULL)
	{
		pthread_mutex_destroy (data->mutex_eatc);
		free (data->mutex_eatc);
	}
}

int	ft_free(t_data *data)
{
	char	**errors;
	int		err;	

	errors = (char *[ERR_C]){"failed to allocate memory on the heap",
		"null check fail", "invalid amount of philosophers",
		"invalid count of arguments", "invalid argument",
		"failed to create thread of execution", "failed to initialize mutex",
		"failed to join thread", "failed to get time"};
	if (data == NULL)
		return (EXIT_FAILURE);
	ft_freemutexes (data);
	ft_freemutexespl (data);
	ft_freephilos (data);
	if (data->err > 0 && data->err < ERR_C)
		printf ("Error:\n%s.\n", errors[data->err]);
	err = data->err;
	free (data);
	return (err != 0);
}
