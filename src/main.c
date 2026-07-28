/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpah <elpah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:13:57 by eobeng            #+#    #+#             */
/*   Updated: 2024/11/23 00:40:47 by elpah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void *fill_phil(char **av, t_philo *philo)
{
	if (!philo)
		return;

	philo->number_of_philosophers = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->number_of_eat_time = ft_atoi(av[5]);
	else
		philo->number_of_eat_time = -1;
	return;
}

int check_valid_input(int ac, char **av)
{
	int i;
	int j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("invalid number of arguments"), 0);
	while (av[i] != NULL)
	{
		if (av[i][0] == '\0')
			return (printf("Error: Argument %d is empty.\n", i), 0);
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]))
				return (printf("Error: Argument %d contains invalid characters.\n", i), 0);
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (printf("Error: Number of philosophers should not be more than 200"), 0);

	return (1);
}

int main(int ac, char **av)
{
	t_philo *philosophers;
	t_program program;
	pthread_mutex_t forks[200];

	philosophers = allocate_phil(ft_atoi(av[1]));

	if (!philosophers)
		return (EXIT_FAILURE);

	if (check_valid_input)
	{
		return (1);
		init_program(&program, philosophers);
		init_forks(forks, ft_atoi(av[1]));
		init_pldshilos(philosophers, &program, forks, av);
		thread_create(&program, forks);
		destory_all(NULL, &program, forks);
		return (0);
	}
}
