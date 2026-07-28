/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eobeng <eobeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:46:39 by eobeng            #+#    #+#             */
/*   Updated: 2024/11/14 20:07:09 by eobeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo *allocate_phil(int number_of_philosophers)
{
    t_philo  *philosophers;

    philosophers = malloc(sizeof(t_philo) * number_of_philosophers);
    if(!philosophers)
        return (NULL);
    return (philosophers);   
}