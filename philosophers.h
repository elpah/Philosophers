#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
    int id;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_eat_time;

    int eating;
    int meals_eaten;

    size_t start_time;
    size_t last_meal_time;

    pthread_t thread;

    int *dead;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
} t_philo;

typedef struct s_program
{
    int dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
    t_philo *philos;
} t_program;

void initial_init_philosopher(t_philo *philosopher);
int ft_atoi(char *s);
int ft_isdigit(int i);
void *fill_phil(char **av, t_philo *philo);
void init_program(t_program *program, t_philo *philos);
void init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **av);
void *monitor(void *pointer);
void *philo_routine(void *pointer);
size_t get_current_time(void);
void destory_all(char *str, t_program *program, pthread_mutex_t *forks);

#endif