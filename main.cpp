/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:17:01 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/17 16:09:13 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./srcs/Parse.hpp"



int main(int ac, char **av)
{
	if (ac == 2)
	{
		Parse	Parse(av[1]);


		std::vector<std::string> content;
		content = Parse.getVector();
		std::cout << std::endl;
		for(unsigned long i = 0; i < content.size(); i++)
		{
			std::cout << content[i] << std::endl;
		}
	}
	else
	{
		Parse	Parse;


		std::vector<std::string> content;
		content = Parse.getVector();
		std::cout << std::endl;
		for(unsigned long i = 0; i < content.size(); i++)
		{
			std::cout << content[i] << std::endl;
		}
	}



	return (0);
}

/*only for display need to erase later*/
