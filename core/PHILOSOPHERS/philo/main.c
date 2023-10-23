/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:57:10 by katchogl          #+#    #+#             */
/*   Updated: 2022/12/31 16:37:10 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_pthreads_create(t_data *data)
{
	int	i;

	if (data == NULL || data->philos == NULL)
		return (ft_error (data, ERR_NULL_POINTER));
	i = -1;
	while (++i < data->philoc)
	{
		if (data->philos[i]->pthread == NULL)
			return (ft_error (data, ERR_NULL_POINTER));
		if (pthread_create (data->philos[i]->pthread, NULL,
				ft_philo_routine, data->philos[i]) != 0)
			return (ft_error (data, ERR_PTHREADS_CREATE_FAIL));
	}
	return (0);
}

static int	ft_pthread_mutexes_init(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->philoc)
		if (pthread_mutex_init (data->mutexes[i], NULL) != 0
			|| pthread_mutex_init (data->philos[i]->mutex_state, NULL) != 0
			|| pthread_mutex_init (data->philos[i]->mutex_t_start
				, NULL) != 0)
			return (ft_error (data, ERR_MUTEXES_INIT_FAIL));
	if (pthread_mutex_init (data->mutex_philo_dead, NULL) != 0
		|| pthread_mutex_init (data->mutex_out, NULL) != 0
		|| (data->n_m_eat != -1
			&& pthread_mutex_init (data->mutex_eatc, NULL) != 0))
		return (ft_error (data, ERR_MUTEXES_INIT_FAIL));
	return (0);
}

static int	ft_pthreads_join(t_data *data)
{
	int		i;

	ft_grim_reaper (data);
	i = -1;
	while (++i < data->philoc)
		if (pthread_join (*(data->philos[i]->pthread), NULL) != 0)
			return (ft_error (data, ERR_PTHREADS_JOIN_FAIL));
	return (0);
}

static int	ft_parse(t_data *data, int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (ft_error (data, ERR_INVALID_ARGSC));
	i = 0;
	while (++i < argc)
		if (!ft_isint (argv[i], -1))
			return (ft_error (data, ERR_INVALID_ARG));
	data->philoc = ft_atoi (argv[1]);
	data->t_die = ft_atoi (argv[2]);
	data->t_eat = ft_atoi (argv[3]);
	data->t_sleep = ft_atoi (argv[4]);
	if (argc == 6)
		data->n_m_eat = ft_atoi (argv[5]);
	if (data->philoc < 1)
		return (ft_error (data, ERR_INVALID_PHILOC));
	else if (data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0
		|| (argc == 6 && data->n_m_eat < 0))
		return (ft_error (data, ERR_INVALID_ARG));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_initdata (&data) != 0 || ft_parse (data, argc, argv) != 0
		|| ft_initphilos (data) != 0
		|| ft_initmutexes (data) != 0
		|| ft_pthread_mutexes_init (data) != 0
		|| ft_get_time (data, &(data->t_start), TRUE) != 0
		|| ft_pthreads_create (data) != 0
		|| ft_pthreads_join (data) != 0)
		return (ft_free (data));
	return (ft_free (data));
}
