/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:17:01 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/27 18:33:06 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/Parse.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
		Parse	Parse(av[1]);
	else
		Parse	Parse;
	return (0);
}
