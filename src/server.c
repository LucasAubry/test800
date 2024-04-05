/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Laubry <aubrylucas.pro@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:36:50 by Laubry            #+#    #+#             */
/*   Updated: 2024/04/05 17:32:52 by laubry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	stock_and_print(char *tab, int *i, int len, int *bit, int boul)
{
	static int	x;

	x = 0;
	if (*bit == 7 && boul == 1)
	{
		tab[x++] = *i;
		*i = 0;
		*bit = -1;
	}
	if (x == len)
	{
		tab[++x] = '\0';
		ft_putendl_fd(tab, 1);
	}
}

void	ft_checkeur(int signal)
{
	static int	bit;
	static int	i;
	static int	boul = 0;
	static char	*tab;
	static int	len = -1;

	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	if (bit == 31 && boul == 0)
	{
		bit = 0;
		boul = 1;
		tab = malloc(i + 1);
		len = i;
		ft_printf("len : %d\n", len);
		i = 0;
		return ;
	}
	stock_and_print(tab, &i, len, &bit, boul);
	bit++;
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("pas d'arguments autorises");
		return (0);
	}
	pid = getpid();
	ft_printf("pid : %d\n", pid);
	signal(SIGUSR1, ft_checkeur);
	signal(SIGUSR2, ft_checkeur);
	while (1)
	{
		pause ();
	}
	return (0);
}
