/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:34:29 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/31 20:19:30 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eat_state(t_philo *philo, t_pthread_mutex_index *philo_mutexes)
{
	if (!ft_lock (philo->data, philo->data->mutexes[philo_mutexes[1]]))
		return (FALSE);
	ft_notify_state_changed (philo, STATE_TAKEN_FORK);
	if (ft_philo_over (philo->data))
		return (ft_unlock (philo->data->mutexes[philo_mutexes[1]], NULL));
	if (philo_mutexes[0] == philo_mutexes[1])
		return (ft_unlock (philo->data->mutexes[philo_mutexes[1]], NULL));
	if (!ft_lock (philo->data, philo->data->mutexes[philo_mutexes[0]]))
		return (ft_unlock (philo->data->mutexes[philo_mutexes[1]], NULL));
	ft_notify_state_changed (philo, STATE_TAKEN_FORK);
	ft_notify_state_changed (philo, STATE_EAT);
	if (philo->data->n_m_eat != -1)
	{
		pthread_mutex_lock (philo->data->mutex_eatc);
		philo->data->eatc++;
		pthread_mutex_unlock (philo->data->mutex_eatc);
	}
	ft_sleep (philo->data, philo->data->t_eat);
	if (ft_philo_over (philo->data))
		return (ft_unlock (philo->data->mutexes[philo_mutexes[1]]
				, philo->data->mutexes[philo_mutexes[0]]));
	return (TRUE);
}

static int	ft_exec_state(t_philo *philo, enum e_state philo_state,
	t_pthread_mutex_index *philo_mutexes)
{
	if (philo_state == STATE_EAT)
		return (ft_eat_state (philo, philo_mutexes));
	else if (philo_state == STATE_SLEEP)
	{
		ft_notify_state_changed (philo, STATE_SLEEP);
		pthread_mutex_unlock (philo->data->mutexes[philo_mutexes[0]]);
		pthread_mutex_unlock (philo->data->mutexes[philo_mutexes[1]]);
		if (ft_philo_over (philo->data))
			return (FALSE);
		ft_sleep (philo->data, philo->data->t_sleep);
	}
	else if (philo_state == STATE_THINK)
		ft_notify_state_changed (philo, STATE_THINK);
	return (TRUE);
}

static int	ft_initargs(t_philo **philo, void *ptr,
	t_pthread_mutex_index *philo_mutexes)
{
	t_time	t_temp;

	*philo = (t_philo *) ptr;
	philo_mutexes[0] = (*philo)->n - 2;
	philo_mutexes[1] = (*philo)->n - 1;
	if ((*philo)->n == 1)
		philo_mutexes[0] = (*philo)->data->philoc - 1;
	if ((*philo)->n % 2 == 0)
		ft_sleep ((*philo)->data, (*philo)->data->t_eat);
	ft_get_time ((*philo)->data, &t_temp, FALSE);
	pthread_mutex_lock ((*philo)->mutex_t_start);
	(*philo)->t_start = t_temp;
	pthread_mutex_unlock ((*philo)->mutex_t_start);
	return (0);
}

void	*ft_philo_routine(void *ptr)
{
	t_philo					*philo;
	t_pthread_mutex_index	philo_mutexes[2];
	int						i;

	if (ft_initargs (&philo, ptr, philo_mutexes) != 0)
		return (0);
	while (1)
	{
		i = -1;
		while (++i < 3)
		{
			if (ft_philo_over (philo->data))
			{
				if (ft_state (i) == STATE_SLEEP)
					ft_unlock (philo->data->mutexes[philo_mutexes[0]],
						philo->data->mutexes[philo_mutexes[1]]);
				return (0);
			}
			if (!ft_exec_state (philo, ft_state (i), philo_mutexes))
				return (0);
		}
	}
	return (0);
}

void	*ft_grim_reaper(void *ptr)
{
	t_data	*data;
	int		i;

	if (ptr == NULL)
		return (0);
	data = (t_data *) ptr;
	while (!ft_philo_over (data))
	{
		i = -1;
		while (++i < data->philoc)
		{
			if (ft_philo_time_exceeded (data->philos[i]))
			{
				ft_notify_state_changed (data->philos[i], STATE_DIED);
				return (0);
			}
		}
	}
	return (0);
}
