/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpah <elpah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:22:42 by eobeng            #+#    #+#             */
/*   Updated: 2024/11/19 03:27:35 by elpah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void initial_init_philosopher(t_philo *philosopher)
{
    if (!philosopher)
        return;

    philosopher->id = 0;
    philosopher->number_of_philosophers = 0;
    philosopher->time_to_die = 0;
    philosopher->time_to_eat = 0;
    philosopher->time_to_sleep = 0;
    philosopher->number_of_eat_time = 0;
    philosopher->last_meal_time = 0;
    philosopher->left_fork = NULL;
    philosopher->right_fork = NULL;
}
void init_program(t_program *program, t_philo *philos)
{
    program->dead_flag = 0;
    program->philos = philos;
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);
}

int ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(500);
    return (0);
}

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
                 char **av)
{
    int i;

    i = 0;
    while (i < ft_atoi(av[1]))
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
        fill_phil(&philos[i], av);
        philos[i].start_time = get_current_time();
        philos[i].last_meal_time = get_current_time();
        philos[i].write_lock = &program->write_lock;
        philos[i].dead_lock = &program->dead_lock;
        philos[i].meal_lock = &program->meal_lock;
        philos[i].dead = &program->dead_flag;
        philos[i].left_fork = &forks[i];
        if (i == 0)
            philos[i].right_fork = &forks[philos[i].number_of_philosophers - 1];
        else
            philos[i].right_fork = &forks[i - 1];
        i++;
    }
}

int ft_isdigit(int i)
{
    return (i > 47 && i < 58);
}

int ft_atoi(char *s)
{
    int i;
    int res;
    int sign;

    i = 0;
    res = 0;
    sign = 1;
    while (s[i] == ' ' || ((s[i] > 8) && (s[i] < 14)))
        i++;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    while (ft_isdigit(s[i]))
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    return (sign * res);
}

void init_forks(pthread_mutex_t *forks, int philo_num)
{
    int i;

    i = 0;
    while (i < philo_num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

int thread_create(t_program *program, pthread_mutex_t *forks)
{
    pthread_t observer;
    int i;

    if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
        destory_all("Thread creation error", program, forks);
    i = 0;
    while (i < program->philos[0].number_of_philosophers)
    {
        if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
                           &program->philos[i]) != 0)
            destory_all("Thread creation error", program, forks);
        i++;
    }
    i = 0;
    if (pthread_join(observer, NULL) != 0)
        destory_all("Thread join error", program, forks);
    while (i < program->philos[0].number_of_philosophers)
    {
        if (pthread_join(program->philos[i].thread, NULL) != 0)
            destory_all("Thread join error", program, forks);
        i++;
    }
    return (0);
}

void destory_all(char *str, t_program *program, pthread_mutex_t *forks)
{
    int i;

    i = 0;
    if (str)
    {
        write(2, str, ft_strlen(str));
        write(2, "\n", 1);
    }
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->meal_lock);
    pthread_mutex_destroy(&program->dead_lock);
    while (i < program->philos[0].number_of_philosophers)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}

// Improved version of sleep function

int ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(500);
    return (0);
}

// Gets the current time in milliseconds

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
