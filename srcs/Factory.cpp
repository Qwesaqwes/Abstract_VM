/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:57:32 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/23 21:24:11 by jichen-m         ###   ########.fr       */
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

char const		*Factory::invalidValue::what() const throw()
{
	return ("Invalid Value for this specific type.");
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
	return ("Stack to small to ADD.");
}

IOperand const	*Factory::createInt8(std::string const &value) const
{
	int nb = std::stoi(value);
	if (nb < -128 || nb > 127)
		throw Factory::invalidValue();
	return (new Operator<int8_t>(nb));
}

IOperand const	*Factory::createInt16(std::string const &value) const
{
	int nb = std::stoi(value);
	if (nb < -32.768 || nb > 32.767)
		throw Factory::invalidValue();
	return (new Operator<int16_t>(nb));
}

IOperand const	*Factory::createInt32(std::string const &value) const
{
	int nb = std::stoi(value);
	if (nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max())
		throw Factory::invalidValue();
	return (new Operator<int32_t>(nb));
}

IOperand const	*Factory::createFloat(std::string const &value) const
{
	float nb = std::stof(value);
	if (nb < std::numeric_limits<float>::min() || nb > std::numeric_limits<float>::max())
		throw Factory::invalidValue();
	return (new Operator<float>(nb));
}

IOperand const	*Factory::createDouble(std::string const &value) const
{
	double nb = std::stod(value);
	if (nb < std::numeric_limits<double>::min() || nb > std::numeric_limits<double>::max())
		throw Factory::invalidValue();
	return (new Operator<double>(nb));
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
		std::cout << w->toString() << std::endl;
		tmp.pop();
	}
}

void		Factory::print(void) const
{
	if (this->_stack.empty())
		throw Factory::stackEmpty();
	IOperand const *w = this->_stack.top();
	if (w->getType() != 0)
		throw Factory::printInst();
	int integer = std::stoi(w->toString());
	if (integer > 32 && integer < 127)
		std::cout << static_cast<char>(integer) << std::endl;
	else
		std::cout << "Not posible to interpret the value to ASCII." << std::endl;
}

void		Factory::add(void)
{
	if (this->_stack.size() < 2)
		throw Factory::operatorError()
	IOperand const *firstOp = this->_stack.top();
	this->_stack.pop()
	IOperand const *secondOp = this->_stack.top();
	this->_stack.pop()
	eOperandType resulType = (firstOp->getType() <= secondOp->getType()) ? firstOp->getType() : secondOp->getType();
	if (resulType <= 2)
	{
		
	}

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
		print();
	else if (this->_instruction[i] == "exit")
		return false;
	else if (this->_instruction[i] == "add")
		add();
	return true;
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
		if (!detec_inst(i))
		{
			std::cout << "Exit instruction called." << std::endl;
			break;
		}
	}
	// for(unsigned long i = 0; i < this->_instruction.size(); i++)	 //need to delete
	// {
	// 	std::cout << "inst: " << this->_instruction[i] << std::endl;
	// 	std::cout << "type: " << this->_type[i] << std::endl;
	// 	std::cout << "value: " << this->_value[i] << std::endl << std::endl;
	// }

	// while(!this->_stack.empty())
	// {
	// 	IOperand const *w = this->_stack.top();
	// 	std::cout << w->toString() << " ";
	// 	std::cout << w->getType() << std::endl;
	// 	this->_stack.pop();
	// }
}
