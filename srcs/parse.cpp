/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:29:37 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/17 16:31:17 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

Parse::Parse(void)
{
	store_commands("this is nothing");
	return;
}
Parse::Parse(std::string file_name)
{
	store_commands(file_name);
	return;
}
Parse::Parse(Parse const &src)
{
	*this = src;
	return;
}
Parse::~Parse(void) {return;}

const char	*Parse::notfile::what(void) const throw()
{
	return ("File not found.");
}

const char	*Parse::notExitInstruction::what(void) const throw()
{
	return ("Not exit instruction at the end.");
}

const char	*Parse::unknowInstruction::what(void) const throw()
{
	return ("Unknow instruction.");
}

const char	*Parse::unknowSyntax::what(void) const throw()
{
	return ("Error Syntax.");
}

Parse		&Parse::operator=(Parse const &rhs)
{
	this->_content = rhs._content;
	return (*this);
}

void	Parse::check_values(std::string type, std::string value, int line) const
{
	int point = 0;
	std::string arrayFtype[2] = { "float", "double" };

	if ((std::find(std::begin(arrayFtype), std::end(arrayFtype), type) != std::end(arrayFtype)) && value.find(".") == std::string::npos)
		throw Parse::unknowSyntax(line);
	for (std::string::iterator it = value.begin(); it != value.end(); it++)
	{
		if (value[0] == '-')
			continue;
		if (*it == '.' && point != 1 && (std::find(std::begin(arrayFtype), std::end(arrayFtype), type) != std::end(arrayFtype)))
		{
			point = 1;
			continue;
		}
		if (!(isdigit(*it)))
			throw Parse::unknowSyntax(line);
	}
}

void	Parse::check_type(std::string inst, std::string value, int line) const
{
	std::size_t pos = value.find("(");
	std::size_t pos2 = value.find(")");
	std::string array_type[5] = { "int8", "int16", "int32", "float", "double" };

	if (((inst != "push" && inst != "assert") && value != "0") || ((inst == "push" || inst == "assert") && value == "0"))
		throw Parse::unknowSyntax(line);
	else if (pos != std::string::npos)
	{
		std::string type = value.substr(0, pos);
		std::cout << type << std::endl;		//need to erase
		if ((std::find(std::begin(array_type), std::end(array_type), type) != std::end(array_type)) && pos2 != std::string::npos)
		{
			std::string	nb = value.substr(pos + 1, pos2 - pos - 1);
			std::cout << nb << std::endl;	//need to erase
			check_values(type, nb, line);
		}
		else
			throw Parse::unknowSyntax(line);
	}
	else
	{
		if ((inst != "push" && inst != "assert") && value == "0")
			goto end;
		throw Parse::unknowSyntax(line);
	}
	end: {}
}

void	Parse::check_instruction(void) const
{
	std::string inst;
	std::string	value;
	std::size_t pos;
	std::string array_inst[11] = { "push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit" };

	if (this->_content.back() != "exit")
		throw Parse::notExitInstruction();
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
			throw Parse::unknowInstruction(i);
		check_type(inst, value, i);	//check value, if not okey throw exception
	}
}

void	Parse::store_commands(std::string str)
{
	std::ifstream ifs(str.c_str());
	try
	{
		if (ifs)
		{
			for(std::string line; std::getline(ifs,line);)			//store each line in container Vector<std::string>
				this->_content.push_back(line);
			check_instruction();
			remove_comment();
		}
		else if (str == "this is nothing")
		{
			while (str != ";;")
			{
				getline(std::cin, str);
				this->_content.push_back(str);
			}
			this->_content.pop_back();
			check_instruction();
			remove_comment();
		}
		else
			throw Parse::notfile();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void	Parse::remove_comment(void)
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

std::vector<std::string>	Parse::getVector(void) const
{
	return (this->_content);
}
