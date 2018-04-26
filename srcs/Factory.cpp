/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:57:32 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/26 17:12:20 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operator.hpp"

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

char const		*Factory::invalidValue::what() const throw()
{
	return ("Invalid value for this specific type.");
}

char const		*Factory::assertNotTrue::what() const throw()
{
	return ("Assert instruction not true.");
}

char const		*Factory::stackEmpty::what() const throw()
{
	return ("Stack is empty can not proceed with the instruction.");
}

char const		*Factory::printInst::what() const throw()
{
	return ("Print instruction failed, type isn't INT8.");
}

char const		*Factory::operatorError::what() const throw()
{
	return ("Stack to small to be able to add/sub/mul/div/mod.");
}

IOperand const	*Factory::createInt8(std::string const &value) const
{
	// int nb = std::stoi(value);
	int nb;
	std::stringstream sstr;
	sstr << value;
	sstr >> nb;
	if (nb < -128 || nb > 127)
		throw Factory::invalidValue();
	return (new Operator<int8_t>(nb));
}

IOperand const	*Factory::createInt16(std::string const &value) const
{
	// int nb = std::stoi(value);
	int nb;
	std::stringstream sstr;
	sstr << value;
	sstr >> nb;
	if (nb < -32768 || nb > 32767)
		throw Factory::invalidValue();
	return (new Operator<int16_t>(nb));
}

IOperand const	*Factory::createInt32(std::string const &value) const
{
	int nb;
	std::stringstream sstr;
	sstr << value;
	sstr >> nb;
	if (nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max())
		throw Factory::invalidValue();
	return (new Operator<int32_t>(std::stoi(value)));
}

IOperand const	*Factory::createFloat(std::string const &value) const
{
	float nb;
	std::stringstream sstr;
	sstr << value;
	sstr >> nb;
	if (nb < (-1 * std::numeric_limits<float>::max()) || nb > std::numeric_limits<float>::max())
		throw Factory::invalidValue();
	return (new Operator<float>(std::stof(value)));
}

IOperand const	*Factory::createDouble(std::string const &value) const
{
	double nb;
	std::stringstream sstr;
	sstr << value;
	sstr >> nb;
	if (nb < (-1 * std::numeric_limits<double>::max()) || nb > std::numeric_limits<double>::max())
		throw Factory::invalidValue();
	return (new Operator<double>(std::stod(value)));
}

IOperand const	*Factory::createOperand(eOperandType type, std::string const & value ) const
{
	switch (type)
	{
		case Int8:
			return (createInt8(value));
		case Int16:
			return (createInt16(value));
		case Int32:
			return (createInt32(value));
		case Float:
			return (createFloat(value));
		default:
			return (createDouble(value));
	}
}

eOperandType	Factory::guesstype(std::string type) const
{
	if (type == "int8")
		return (Int8);
	else if (type == "int16")
		return (Int16);
	else if (type == "int32")
		return (Int32);
	else if (type == "float")
		return (Float);
	else
		return (Double);
}

void		Factory::push(eOperandType type, std::string value)
{
	this->_stack.push(createOperand(type, value));
}

void		Factory::assertt(std::string type, std::string value) const
{
	if (this->_stack.empty())
		throw Factory::stackEmpty();
	IOperand const *w = this->_stack.top();
	eOperandType typeNum = guesstype(type);

	switch (typeNum)
	{
		case 0:
		case 1:
		case 2:
			if ((typeNum != w->getType()) || (std::to_string(std::stoi(value)) != w->toString()))
				throw Factory::assertNotTrue();
			break;
		case 3:
			if ((typeNum != w->getType()) || (std::to_string(std::stof(value)) != w->toString()))
				throw Factory::assertNotTrue();
			break;
		default:
			if ((typeNum != w->getType()) || (std::to_string(std::stod(value)) != w->toString()))
				throw Factory::assertNotTrue();
			break;
	}
}

void		Factory::pop(void)
{
	if (this->_stack.empty())
		throw Factory::stackEmpty();
	this->_stack.pop();
}

void		Factory::dump(void) const
{
	 std::stack<IOperand const *> tmp = this->_stack;

	 while(!tmp.empty())
	{
		IOperand const *w = tmp.top();
		switch (w->getType())
		{
			case 0:
				std::cout <<"\033[1;31m" << w->toString() << "\033[0m" << std::endl;
				break;
			case 1:
				std::cout <<"\033[1;33m" << w->toString() << "\033[0m" << std::endl;
				break;
			case 2:
				std::cout <<"\033[1;36m" << w->toString() << "\033[0m" << std::endl;
				break;
			case 3:
				std::cout <<"\033[1;37m" << w->toString() << "\033[0m" << std::endl;
				break;
			default:
				std::cout <<"\033[1;35m" << w->toString() << "\033[0m" << std::endl;
				break;
		}
		// std::cout <<"\033[1;31m" << w->toString() << "\033[0m" << std::endl;
		tmp.pop();
	}
}

bool		Factory::print(void) const
{
	if (this->_stack.empty())
		throw Factory::stackEmpty();
	IOperand const *w = this->_stack.top();
	if (w->getType() != 0)
		throw Factory::printInst();
	int integer = std::stoi(w->toString());
	if (integer > 32 && integer < 127)
		std::cout << static_cast<char>(integer);
	else
	{
		std::cout << "Not posible to interpret the value to ASCII." << std::endl;
		return false;
	}
	return true;
}

void		Factory::add(void)
{
	if (this->_stack.size() < 2)
		throw Factory::operatorError();
	IOperand const *firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *secondOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *res = *firstOp + *secondOp;
	this->_stack.push(res);
}

void		Factory::sub(void)
{
	if (this->_stack.size() < 2)
		throw Factory::operatorError();
	IOperand const *firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *secondOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *res = *firstOp - *secondOp;
	this->_stack.push(res);
}

void		Factory::mul(void)
{
	if (this->_stack.size() < 2)
		throw Factory::operatorError();
	IOperand const *firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *secondOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *res = *firstOp * *secondOp;
	this->_stack.push(res);
}

void		Factory::divv(void)
{
	if (this->_stack.size() < 2)
		throw Factory::operatorError();
	IOperand const *firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *secondOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *res = *firstOp / *secondOp;
	this->_stack.push(res);
}

void		Factory::mod(void)
{
	if (this->_stack.size() < 2)
		throw Factory::operatorError();
	IOperand const *firstOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *secondOp = this->_stack.top();
	this->_stack.pop();
	IOperand const *res = *firstOp % *secondOp;
	this->_stack.push(res);
}

bool		Factory::detec_inst(unsigned long i)
{
	if (this->_instruction[i] == "push")
		push(guesstype(this->_type[i]), this->_value[i]);
	else if (this->_instruction[i] == "assert")
		assertt(this->_type[i], this->_value[i]);
	else if (this->_instruction[i] == "pop")
		pop();
	else if (this->_instruction[i] == "dump")
		dump();
	else if (this->_instruction[i] == "print")
		{if (!print()) return false;}
	else if (this->_instruction[i] == "mod")
		mod();
	else if (this->_instruction[i] == "add")
		add();
	else if (this->_instruction[i] == "sub")
		sub();
	else if (this->_instruction[i] == "mul")
		mul();
	else if (this->_instruction[i] == "div")
		divv();
	else
		return false;
	return true;
}

void		Factory::fill_vectors(std::vector<std::string> content)
{
	std::size_t pos_inst;
	std::size_t pos_type;
	std::size_t pos_value;

	std::cout <<"\033[1;31mINT8\033[0m" << std::endl;
	std::cout <<"\033[1;33mINT16\033[0m" << std::endl;
	std::cout <<"\033[1;36mINT32\033[0m" << std::endl;
	std::cout <<"\033[1;37mFLOAT\033[0m" << std::endl;
	std::cout <<"\033[1;35mDOUBLE\033[0m" << std::endl << std::endl << std::endl;
	for (unsigned long i = 0; i < content.size(); ++i)
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
		if (!detec_inst(i))
			break;
	}
	// for(unsigned long i = 0; i < this->_instruction.size(); i++)	 //need to delete
	// {
	// 	std::cout << "inst: " << this->_instruction[i] << std::endl;
	// 	std::cout << "type: " << this->_type[i] << std::endl;
	// 	std::cout << "value: " << this->_value[i] << std::endl << std::endl;
	// }

	// std::cout << std::endl;
	// while(!this->_stack.empty())
	// {
	// 	IOperand const *w = this->_stack.top();
	// 	std::cout << w->toString() << " ";
	// 	std::cout << w->getType() << std::endl;
	// 	this->_stack.pop();
	// }
}
