/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:29:37 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/16 18:49:01 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

parse::parse(void)
{
	store_commands("this is nothing");
	return;
}
parse::parse(std::string file_name)
{
	store_commands(file_name);
	return;
}
parse::parse(parse const &src)
{
	*this = src;
	return;
}
parse::~parse(void) {return;}

const char	*parse::notfile::what(void) const throw()
{
	return ("File not found.");
}

const char	*parse::notExitInstruction::what(void) const throw()
{
	return ("Not exit instruction at the end.");
}

const char	*parse::unknowInstruction::what(void) const throw()
{
	return ("Unknow instruction.");
}

const char	*parse::unknowSyntax::what(void) const throw()
{
	return ("Error Syntax.");
}

parse		&parse::operator=(parse const &rhs)
{
	this->_content = rhs._content;
	return (*this);
}

void	parse::check_values(std::string inst, std::string value, int line) const
{
	std::size_t pos = value.find("(");
	std::size_t pos2 = value.find(")");
	std::string array_type[5] = { "int8", "int16", "int32", "float", "double" };

	if (((inst != "push" && inst != "assert") && value != "0") || ((inst == "push" || inst == "assert") && value == "0"))
	{
		std::cout << "In line: " << line + 1 << " ";
		throw parse::unknowSyntax();
	}
	else if (pos != std::string::npos)
	{
		std::string type = value.substr(0, pos);
		std::cout << type << std::endl;
		if ((std::find(std::begin(array_type), std::end(array_type), type) != std::end(array_type)) && pos2 != std::string::npos)
		{
			std::string	nb = value.substr(pos + 1, pos2 - pos - 1);

		}
		else
		{
			std::cout << "In line: " << line + 1 << " ";
			throw parse::unknowSyntax();
		}

	}
	else
	{
		if ((inst != "push" && inst != "assert") && value == "0")
			goto end;
		std::cout << "In line: " << line + 1 << " ";
		throw parse::unknowSyntax();
	}
	end: {}
}

void	parse::check_content(void) const
{
	std::string inst;
	std::string	value;
	std::size_t pos;
	std::string array_inst[11] = { "push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit" };

	if (this->_content.back() != "exit")
		throw parse::notExitInstruction();
	for(unsigned long i = 0; i < this->_content.size(); i++)
	{
		if (this->_content[i][0] == ';' || this->_content[i].empty())		//skip comments or if line is empty
			continue ;
		pos = this->_content[i].find(" ");
		inst = (pos != std::string::npos) ? this->_content[i].substr(0, pos) : this->_content[i].substr(0);	//store instruction
		value = (pos != std::string::npos) ? this->_content[i].substr(pos + 1) : "0";						//store value if not store a "0"
		value = (value[0] == ';') ? "0" : value;
		std::cout <<inst << " " << value << std::endl; //need to delete after all good
		if (std::find(std::begin(array_inst), std::end(array_inst), inst) == std::end(array_inst))		//check if instruction exist
		{
			std::cout << "In line: " << i + 1 << " ";
			throw parse::unknowInstruction();
		}
		check_values(inst, value, i);	//check value, if not okey throw exception
	}
}

void	parse::store_commands(std::string str)
{
	std::ifstream ifs(str.c_str());
	try
	{
		if (ifs)
		{
			for(std::string line; std::getline(ifs,line);)			//store each line in container Vector<std::string>
				this->_content.push_back(line);
			// remove_comment();
			check_content();
		}
		else if (str == "this is nothing")
		{
			while (str != ";;")
			{
				getline(std::cin, str);
				this->_content.push_back(str);
			}
			// remove_comment();
			check_content();
		}
		else
		{
			throw parse::notfile();
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void	parse::remove_comment(void)
{
	for(unsigned long i = 0; i < this->_content.size(); i++)
	{
		if (this->_content[i][0] == ';' || this->_content[i].empty())		//erase element from vector if ';' is at the beginning
		{
			this->_content.erase(this->_content.begin() + i);
			i = -1;
			continue;
		}
		std::size_t found = this->_content[i].find_first_of(";");
		if (found != std::string::npos)
		{
			if (this->_content[i][found - 1] == ' ')
				found -= 1;
			this->_content[i].erase(found);						//erase string when ';' start
		}
	}
}

std::vector<std::string>	parse::getVector(void) const
{
	return (this->_content);
}
