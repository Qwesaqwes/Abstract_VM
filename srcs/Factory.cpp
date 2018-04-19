/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:57:32 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/19 19:46:53 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"

Factory::Factory(void) {return;}

Factory::Factory(Factory const &src)
{
	*this = src;
	return;
}

Factory::~Factory(void) {return;}

Factory		&Factory::operator=(Factory const &rhs)
{
	this->_instruction = rhs._instruction;
	this->_type = rhs._type;
	this->_value = rhs._value;
	return (*this);
}

void		Factory::fill_vectors(std::vector<std::string> content)
{
	std::size_t pos_inst;
	std::size_t pos_type;
	std::size_t pos_value;

	for (unsigned long i = 0; i < content.size(); i++)
	{
		pos_inst = content[i].find(" ");
		pos_type = content[i].find("(");
		pos_value = content[i].find(")");

		this->_instruction.push_back(content[i].substr(0, pos_inst));
		if (pos_inst == std::string::npos)
		{
			this->_type.push_back("0");
			this->_value.push_back("0");
		}
		else
		{
			this->_type.push_back(content[i].substr(pos_inst + 1, pos_type - pos_inst - 1));
			this->_value.push_back(content[i].substr(pos_type + 1, pos_value - pos_type - 1));
		}
	}
	// for(unsigned long i = 0; i < this->_instruction.size(); i++)	 //need to delete
	// {
	// 	std::cout << "inst: " << this->_instruction[i] << std::endl;
	// 	std::cout << "type: " << this->_type[i] << std::endl;
	// 	std::cout << "value: " << this->_value[i] << std::endl << std::endl;
	// }
}
