/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 22:22:52 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/27 22:28:01 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_over(t_data *data)
{
	pthread_mutex_lock (data->mutex_philo_dead);
	if (data->philo_died)
	{
		pthread_mutex_unlock (data->mutex_philo_dead);
		return (TRUE);
	}
	pthread_mutex_unlock (data->mutex_philo_dead);
	if (data->n_m_eat != -1)
	{
		pthread_mutex_lock (data->mutex_eatc);
		if (data->eatc >= data->n_m_eat * data->philoc)
		{
			pthread_mutex_unlock (data->mutex_eatc);
			return (TRUE);
		}
		pthread_mutex_unlock (data->mutex_eatc);
	}
	return (FALSE);
}

int	ft_philo_time_exceeded(t_philo *philo)
{
	t_time	t;

	pthread_mutex_lock (philo->mutex_t_start);
	ft_get_time (philo->data, &t, FALSE);
	if (philo->t_start != 0 && t >= philo->t_start
		&& t - philo->t_start >= (t_time)(philo->data->t_die * 1000))
	{
		pthread_mutex_unlock (philo->mutex_t_start);
		return (TRUE);
	}
	pthread_mutex_unlock (philo->mutex_t_start);
	return (FALSE);
}

int	ft_lock(t_data *data, pthread_mutex_t *mutex)
{
	if (ft_philo_over (data))
		return (FALSE);
	pthread_mutex_lock (mutex);
	if (ft_philo_over (data))
	{
		pthread_mutex_unlock (mutex);
		return (FALSE);
	}
	return (TRUE);
}

int	ft_unlock(pthread_mutex_t *mutex, pthread_mutex_t *mutex2)
{
	if (mutex != NULL)
		pthread_mutex_unlock (mutex);
	if (mutex2 != NULL)
		pthread_mutex_unlock (mutex2);
	return (FALSE);
}

int	ft_get_time(t_data *data, t_time *time, int msecs)
{
	struct timeval	timeval;

	if (gettimeofday (&timeval, NULL) == -1)
		return (ft_error (data, ERR_GTIME_FAIL));
	if (msecs)
		*time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	else
		*time = timeval.tv_sec * 1000000 + timeval.tv_usec;
	return (0);
}
