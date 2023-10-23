/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:53:02 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/31 16:29:18 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_initphilos(t_data *data)
{
	int		i;

	if (data == NULL)
		return (ft_error (data, ERR_NULL_POINTER));
	data->philos = (t_philo **) malloc (data->philoc * sizeof (t_philo *));
	if (data->philos == NULL)
		return (ft_error (data, ERR_MALLOC_FAIL));
	i = -1;
	while (++i < data->philoc)
	{
		data->philos[i] = (t_philo *) malloc (sizeof (t_philo));
		if (data->philos[i] == NULL)
			return (ft_error (data, ERR_MALLOC_FAIL));
		data->philos[i]->n = i + 1;
		data->philos[i]->data = data;
		data->philos[i]->pthread = (pthread_t *) malloc (sizeof (pthread_t));
		if (data->philos[i]->pthread == NULL)
			return (ft_error (data, ERR_MALLOC_FAIL));
		data->philos[i]->state = STATE_UNDEF;
		data->philos[i]->mutex_state = NULL;
		data->philos[i]->t_start = 0;
		data->philos[i]->mutex_t_start = NULL;
	}
	return (0);
}

static int	ft_initmutexespl(t_data *data)
{
	if (data == NULL)
		return (ft_error (data, ERR_NULL_POINTER));
	data->mutex_out = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
	data->mutex_philo_dead = (pthread_mutex_t *) malloc
		(sizeof (pthread_mutex_t));
	if (data->n_m_eat != -1)
		data->mutex_eatc = (pthread_mutex_t *) malloc
			(sizeof (pthread_mutex_t));
	if (data->mutex_out == NULL || data->mutex_philo_dead == NULL
		|| (data->n_m_eat != -1 && data->mutex_eatc == NULL))
		return (ft_error (data, ERR_MALLOC_FAIL));
	return (0);
}

int	ft_initmutexes(t_data *data)
{
	int	i;

	if (data == NULL)
		return (ft_error (data, ERR_NULL_POINTER));
	data->mutexes = (pthread_mutex_t **) malloc
		(data->philoc * sizeof (pthread_mutex_t *));
	if (data->mutexes == NULL)
		return (ft_error (data, ERR_MALLOC_FAIL));
	i = -1;
	while (++i < data->philoc)
	{
		data->mutexes[i] = (pthread_mutex_t *) malloc
			(sizeof (pthread_mutex_t));
		if (data->mutexes[i] == NULL)
			return (ft_error (data, ERR_MALLOC_FAIL));
		data->philos[i]->mutex_state = (pthread_mutex_t *) malloc
			(sizeof (pthread_mutex_t));
		data->philos[i]->mutex_t_start = (pthread_mutex_t *) malloc
			(sizeof (pthread_mutex_t));
		if (data->philos[i]->mutex_state == NULL
			|| data->philos[i]->mutex_t_start == NULL)
			return (ft_error (data, ERR_MALLOC_FAIL));
	}
	return (ft_initmutexespl (data));
}

int	ft_initdatapl(t_data **data)
{
	if (data == NULL || *data == NULL)
		return (ft_error (*data, ERR_NULL_POINTER));
	(*data)->philoc = -1;
	(*data)->t_die = -1;
	(*data)->t_eat = -1;
	(*data)->t_sleep = -1;
	(*data)->n_m_eat = -1;
	(*data)->t_start = 0;
	(*data)->philo_died = FALSE;
	(*data)->err = EXIT_SUCCESS;
	(*data)->eatc = 0;
	(*data)->philos = NULL;
	(*data)->mutexes = NULL;
	(*data)->mutex_out = NULL;
	(*data)->mutex_philo_dead = NULL;
	(*data)->mutex_eatc = NULL;
	return (0);
}

int	ft_initdata(t_data **data)
{
	if (data == NULL)
		return (ft_error (*data, ERR_NULL_POINTER));
	*data = (t_data *) malloc (sizeof (t_data));
	if (*data == NULL)
		return (ft_error (*data, ERR_MALLOC_FAIL));
	return (ft_initdatapl (data));
}
