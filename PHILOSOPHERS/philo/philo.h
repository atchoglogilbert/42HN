/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 02:18:03 by katchogl          #+#    #+#             */
/*   Updated: 2023/01/01 15:23:59 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0

enum e_state {
	STATE_UNDEF = -1,
	STATE_TAKEN_FORK,
	STATE_EAT,
	STATE_SLEEP,
	STATE_THINK,
	STATE_DIED,
	STATE_C
};
enum e_errno {
	ERR_MALLOC_FAIL,
	ERR_NULL_POINTER,
	ERR_INVALID_PHILOC,
	ERR_INVALID_ARGSC,
	ERR_INVALID_ARG,
	ERR_PTHREADS_CREATE_FAIL,
	ERR_MUTEXES_INIT_FAIL,
	ERR_PTHREADS_JOIN_FAIL,
	ERR_GTIME_FAIL,
	ERR_C
};
typedef long long unsigned	t_time;
typedef int					t_pthread_mutex_index;
typedef struct s_data		t_data;
typedef struct s_philo
{
	int				n;
	t_data			*data;
	pthread_t		*pthread;
	enum e_state	state;
	pthread_mutex_t	*mutex_state;
	t_time			t_start;
	pthread_mutex_t	*mutex_t_start;
}	t_philo;
typedef struct s_data
{
	int				philoc;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_m_eat;
	t_time			t_start;
	int				philo_died;
	enum e_errno	err;
	int				eatc;
	t_philo			**philos;
	pthread_mutex_t	**mutexes;
	pthread_mutex_t	*mutex_out;
	pthread_mutex_t	*mutex_philo_dead;
	pthread_mutex_t	*mutex_eatc;
}	t_data;
int				ft_initdata(t_data **data);
int				ft_initphilos(t_data *data);
int				ft_initmutexes(t_data *data);
void			*ft_grim_reaper(void *ptr);
int				ft_free(t_data *data);
int				ft_lock(t_data *data, pthread_mutex_t *mutex);
void			ft_sleep(t_data *data, int msecs);
void			*ft_philo_routine(void *ptr);
int				ft_philo_over(t_data *data);
int				ft_philo_time_exceeded(t_philo *philo);
void			ft_notify_state_changed(t_philo *philo, enum e_state state);
int				ft_get_time(t_data *data, t_time *time, int msec);
int				ft_error(t_data *data, enum e_errno err);
enum e_state	ft_state(int i);
int				ft_unlock(pthread_mutex_t *mutex, pthread_mutex_t *mutex2);
int				ft_atoi(const char *str);
int				ft_isint(char *s, int i);
#endif