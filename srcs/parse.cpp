/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:29:37 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/27 17:18:53 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"
#include "Factory.hpp"

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

Parse		&Parse::operator=(Parse const &rhs)
{
	this->_content = rhs._content;
	return (*this);
}

void	Parse::check_values(std::string type, std::string value, int line, std::ofstream &outfile) const
{
	int point = 0;
	std::string arrayFtype[2] = { "float", "double" };

	if ((std::find(std::begin(arrayFtype), std::end(arrayFtype), type) != std::end(arrayFtype)) && value.find(".") == std::string::npos)
		outfile << "In line: " << line + 1 << " Unknow Value." << std::endl;
	for (std::string::iterator it = value.begin(); it != value.end(); it++)
	{
		if (*(value.begin()) == '-')
			continue;
		if (*it == '.' && point != 1 && (std::find(std::begin(arrayFtype), std::end(arrayFtype), type) != std::end(arrayFtype)))
		{
			point = 1;
			continue;
		}
		if (!(isdigit(*it)))
			outfile << "In line: " << line + 1 << " Unknow Value." << std::endl;
	}
}

void	Parse::check_type(std::string inst, std::string value, int line, std::ofstream &outfile) const
{
	std::size_t pos = value.find("(");
	std::size_t pos2 = value.find(")");
	std::string array_type[5] = { "int8", "int16", "int32", "float", "double" };

	if (((inst != "push" && inst != "assert") && value != "0") || ((inst == "push" || inst == "assert") && value == "0"))
		outfile << "In line: " << line + 1 << " Unknow Type" << std::endl;
	else if (pos != std::string::npos)
	{
		std::string type = value.substr(0, pos);
		if ((std::find(std::begin(array_type), std::end(array_type), type) != std::end(array_type)) && pos2 != std::string::npos)
		{
			std::string	nb = value.substr(pos + 1, pos2 - pos - 1);
			check_values(type, nb, line, outfile);
		}
		else
			outfile << "In line: " << line + 1 << " Unknow Type" << std::endl;
	}
	else
	{
		if ((inst != "push" && inst != "assert") && value == "0")
			goto end;
		outfile << "In line: " << line + 1 << " Unknow Type" << std::endl;
	}
	end: {}
}

void	Parse::check_instruction(std::ofstream &outfile) const
{
	std::string inst;
	std::string	value;
	std::size_t pos;
	std::string array_inst[11] = { "push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit" };

	for(unsigned long i = 0; i < this->_content.size(); ++i)
	{
		if (this->_content[i][0] == ';' || this->_content[i].empty())		//skip comments or if line is empty
			continue ;
		pos = this->_content[i].find(" ");
		inst = (pos != std::string::npos) ? this->_content[i].substr(0, pos) : this->_content[i].substr(0);	//store instruction
		value = (pos != std::string::npos) ? this->_content[i].substr(pos + 1) : "0";						//store value, if not, store a "0"
		value = (value[0] == ';') ? "0" : value;
		if (std::find(std::begin(array_inst), std::end(array_inst), inst) == std::end(array_inst))		//check if instruction exist
		{
			outfile << "In line: " << i + 1 << " Unknow Instruction." << std::endl;
			continue;
		}
		check_type(inst, value, i, outfile);	//check value, if not okey throw exception
	}
}

void	Parse::check_exit_inst(std::ofstream &outfile) const
{
	bool	exit_good = false;

	for (unsigned long i = 0; i < this->_content.size(); i++)
		if (this->_content[i].find("exit") != std::string::npos) exit_good = true;
	if (!exit_good)
		outfile << "Not Exit instruction." << std::endl;//throw Parse::notExitInstruction();
}

bool	Parse::fill_content(std::string str, std::ofstream &outfile)
{
	std::ifstream	ifs(str.c_str());
	if (ifs)
		for(std::string line; std::getline(ifs,line);) this->_content.push_back(line);		//store each line in container Vector<std::string>
	else if (str == "this is nothing")
	{
		while (str != ";;")
		{
			getline(std::cin, str);
			this->_content.push_back(str);	//store each line in container Vector<std::string>
		}
		this->_content.pop_back();
	}
	else
		outfile << "File not found." << std::endl; return false;//throw Parse::notfile();
	return true;
}

void	Parse::remove_comment(void)
{
	for(unsigned long i = 0; i < this->_content.size(); ++i)
	{
		if (this->_content[i][0] == ';' || this->_content[i].empty())		//erase element from vector if ';' is at the beginning
		{
			this->_content.erase(this->_content.begin() + i);
			i = -1;
			continue;
		}
	}
}

void	Parse::remove_comment_inline(void)
{
	for(unsigned long i = 0; i < this->_content.size(); i++)
	{
		std::size_t found = this->_content[i].find_first_of(";");
		if (found != std::string::npos && found != 0)
		{
			if (this->_content[i][found - 1] == ' ')
				found -= 1;
			this->_content[i].erase(found);						//erase string when ';' start
		}
	}
}

void	Parse::store_commands(std::string str)
{
	Factory			*factory = new Factory();
	std::string		fileName = "Error.txt";

	std::ofstream outfile (fileName);
	if (fill_content(str, outfile)) goto notfile;
	remove_comment_inline();
	check_instruction(outfile);		//check if instruction, type and value are okey
	remove_comment();			//if all okey remove comments
	check_exit_inst(outfile);
	outfile.close();
	notfile:;
	std::ifstream fileEmpty;
	std::stringstream concatenate;
	concatenate << "./" << fileName;
	fileEmpty.open(concatenate.str(), std::ios::binary);
	fileEmpty.seekg(0, std::ios::end);
	if (fileEmpty.tellg() == 0)
	{
		remove((concatenate.str()).c_str());
		try {factory->fill_vectors(this->_content);}
		catch(std::exception &e) {std::cout << e.what() << std::endl;}
	}
	else
		std::cout << "Error, Logs in Error.txt." << std::endl;
	delete factory;
}
