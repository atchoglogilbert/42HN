/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:58:38 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/01 15:22:32 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

enum e_state	ft_state(int i)
{
	if (i == 0)
		return (STATE_EAT);
	else if (i == 1)
		return (STATE_SLEEP);
	return (STATE_THINK);
}

void	ft_sleep(t_data *data, int msecs)
{
	t_time	t1;
	t_time	t2;

	ft_get_time (data, &t1, TRUE);
	ft_get_time (data, &t2, TRUE);
	while (t2 - t1 < (t_time) msecs)
	{
		usleep (100);
		ft_get_time (data, &t2, TRUE);
	}
}

int	ft_error(t_data *data, enum e_errno err)
{
	data->err = err;
	return (EXIT_FAILURE);
}

static int	ft_put_philo_state(t_philo *philo, enum e_state state)
{
	char	**states;
	t_time	t;

	if (!(state >= 0 && state < STATE_C))
		return (FALSE);
	states = (char *[STATE_C]){"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};
	if (ft_philo_over (philo->data))
		return (FALSE);
	pthread_mutex_lock (philo->mutex_t_start);
	ft_get_time (philo->data, &t, TRUE);
	printf ("%llu\t%d %s\n", t - philo->data->t_start,
		philo->n, states[state]);
	pthread_mutex_unlock (philo->mutex_t_start);
	return (TRUE);
}

void	ft_notify_state_changed(t_philo *philo, enum e_state state)
{
	if (philo == NULL)
		return ;
	pthread_mutex_lock (philo->data->mutex_out);
	if (!ft_put_philo_state (philo, state))
	{
		pthread_mutex_unlock (philo->data->mutex_out);
		return ;
	}
	if (state == STATE_DIED)
	{
		pthread_mutex_lock (philo->data->mutex_philo_dead);
		philo->data->philo_died = TRUE;
		pthread_mutex_unlock (philo->data->mutex_philo_dead);
	}
	else if (state == STATE_EAT)
	{
		pthread_mutex_lock (philo->mutex_t_start);
		ft_get_time (philo->data, &(philo->t_start), FALSE);
		pthread_mutex_unlock (philo->mutex_t_start);
	}
	pthread_mutex_lock (philo->mutex_state);
	philo->state = state;
	pthread_mutex_unlock (philo->mutex_state);
	pthread_mutex_unlock (philo->data->mutex_out);
}
