/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:52:01 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/25 18:34:50 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operator.hpp"
#include "Factory.hpp"

template<typename T>
Operator<T>::Operator(void) {return ;}

template<typename T>
Operator<T>::Operator(T value) : _value(value), _valueString(std::to_string(value))
{
	return ;
}

template<typename T>
Operator<T>::Operator(Operator const &src)
{
	*this = src;
	return ;
}

template<typename T>
Operator<T>::~Operator(void) {return ;}

template<typename T>
Operator<T>		&Operator<T>::operator=(Operator const &rhs)
{
	this->_value = rhs._value;
	this->_valueString = rhs._valueString;
	return (*this);
}

char const		*overflow::what(void) const throw()
{
	return ("Arithmetic value Overflow.");
}

char const		*underflow::what(void) const throw()
{
	return ("Arithmetic value Underflow.");
}

char const		*undifinedBehavior::what(void) const throw()
{
	return ("Can not Div or Mod by 0.");
}

template<typename T>
T			checkFlow(eOperandType type, T value1, T value2, int typeOp)
{
	T value = 0;

	switch (type)
	{
		case 0:
			if (typeOp == 0) value = ((value1 + value2) < -128) ? throw underflow() : (((value1 + value2) > 127) ? throw overflow() : (value1 + value2));
			else if (typeOp == 1) value = ((value1 - value2) < -128) ? throw underflow() : (((value1 - value2) > 127) ? throw overflow() : (value1 - value2));
			else value = ((value1 * value2) < -128) ? throw underflow() : (((value1 * value2) > 127) ? throw overflow() : (value1 * value2));
			return (value);
		case 1:
			if (typeOp == 0) value = ((value1 + value2) < -32768) ? throw underflow() : (((value1 + value2) > 32767) ? throw overflow() : (value1 + value2));
			else if (typeOp == 1) value = ((value1 - value2) < -32768) ? throw underflow() : (((value1 - value2) > 32767) ? throw overflow() : (value1 - value2));
			else value = ((value1 * value2) < -32768) ? throw underflow() : (((value1 * value2) > 32767) ? throw overflow() : (value1 * value2));
			return (value);
		case 2:
			if (typeOp == 0) value = ((value1 + value2) < std::numeric_limits<int>::min()) ? throw underflow() : (((value1 + value2) > std::numeric_limits<int>::max()) ? throw overflow() : (value1 + value2));
			else if (typeOp == 1) value = ((value1 - value2) < std::numeric_limits<int>::min()) ? throw underflow() : (((value1 - value2) > std::numeric_limits<int>::max()) ? throw overflow() : (value1 - value2));
			else value = ((value1 * value2) < std::numeric_limits<int>::min()) ? throw underflow() : (((value1 * value2) > std::numeric_limits<int>::max()) ? throw overflow() : (value1 * value2));
			return (value);
		case 3:
			if (typeOp == 0) value = ((value1 + value2) < std::numeric_limits<float>::min()) ? throw underflow() : (((value1 + value2) > std::numeric_limits<float>::max()) ? throw overflow() : (value1 + value2));
			else if (typeOp == 1) value = ((value1 - value2) < std::numeric_limits<float>::min()) ? throw underflow() : (((value1 - value2) > std::numeric_limits<float>::max()) ? throw overflow() : (value1 - value2));
			else value = ((value1 * value2) < std::numeric_limits<float>::min()) ? throw underflow() : (((value1 * value2) > std::numeric_limits<float>::max()) ? throw overflow() : (value1 * value2));
			return (value);
		default:
			if (typeOp == 0) value = ((value1 + value2) < std::numeric_limits<double>::min()) ? throw underflow() : (((value1 + value2) > std::numeric_limits<double>::max()) ? throw overflow() : (value1 + value2));
			else if (typeOp == 1) value = ((value1 - value2) < std::numeric_limits<double>::min()) ? throw underflow() : (((value1 - value2) > std::numeric_limits<double>::max()) ? throw overflow() : (value1 - value2));
			else value = ((value1 * value2) < std::numeric_limits<double>::min()) ? throw underflow() : (((value1 * value2) > std::numeric_limits<double>::max()) ? throw overflow() : (value1 * value2));
			return (value);
	}
}

template<typename T>
IOperand const	*Operator<T>::operator+(IOperand const &rhs) const
{
	Factory		factory;

	eOperandType resulType = (this->getType() >= rhs.getType()) ? this->getType() : rhs.getType();
	if (resulType <= 2)
	{
		int intRes = checkFlow(resulType, std::stoi(this->toString()), std::stoi(rhs.toString()), 0);
		return (factory.createOperand(resulType, std::to_string(intRes)));
	}
	else if (resulType == 3)
	{
		float floatRes = checkFlow(resulType, std::stof(this->toString()), std::stof(rhs.toString()), 0);
		return (factory.createOperand(resulType, std::to_string(floatRes)));
	}
	else
	{
		double doubleRes = checkFlow(resulType, std::stod(this->toString()), std::stod(rhs.toString()), 0);
		return (factory.createOperand(resulType, std::to_string(doubleRes)));
	}
}

template<typename T>
IOperand const	*Operator<T>::operator-(IOperand const &rhs) const
{
	Factory		factory;

	eOperandType resulType = (this->getType() >= rhs.getType()) ? this->getType() : rhs.getType();
	if (resulType <= 2)
	{
		int intRes = checkFlow(resulType, std::stoi(this->toString()), std::stoi(rhs.toString()), 1);
		return (factory.createOperand(resulType, std::to_string(intRes)));
	}
	else if (resulType == 3)
	{
		float floatRes = checkFlow(resulType, std::stof(this->toString()), std::stof(rhs.toString()), 1);
		return (factory.createOperand(resulType, std::to_string(floatRes)));
	}
	else
	{
		double doubleRes = checkFlow(resulType, std::stod(this->toString()), std::stod(rhs.toString()), 1);
		return (factory.createOperand(resulType, std::to_string(doubleRes)));
	}
}

template<typename T>
IOperand const	*Operator<T>::operator*(IOperand const &rhs) const
{
	Factory		factory;

	eOperandType resulType = (this->getType() >= rhs.getType()) ? this->getType() : rhs.getType();
	if (resulType <= 2)
	{
		int intRes = checkFlow(resulType, std::stoi(this->toString()), std::stoi(rhs.toString()), 2);
		return (factory.createOperand(resulType, std::to_string(intRes)));
	}
	else if (resulType == 3)
	{
		float floatRes = checkFlow(resulType, std::stof(this->toString()), std::stof(rhs.toString()), 2);
		return (factory.createOperand(resulType, std::to_string(floatRes)));
	}
	else
	{
		double doubleRes = checkFlow(resulType, std::stod(this->toString()), std::stod(rhs.toString()), 2);
		return (factory.createOperand(resulType, std::to_string(doubleRes)));
	}
}

template<typename T>
IOperand const	*Operator<T>::operator/(IOperand const &rhs) const
{
	Factory		factory;

	eOperandType resulType = (this->getType() >= rhs.getType()) ? this->getType() : rhs.getType();
	if (resulType <= 2)
	{
		int intRes = (std::stoi(rhs.toString()) == 0) ? throw undifinedBehavior() : std::stoi(this->toString()) / std::stoi(rhs.toString());
		return (factory.createOperand(resulType, std::to_string(intRes)));
	}
	else if (resulType == 3)
	{
		float floatRes = (std::stof(rhs.toString()) == 0) ? throw undifinedBehavior() : std::stof(this->toString()) / std::stof(rhs.toString());
		return (factory.createOperand(resulType, std::to_string(floatRes)));
	}
	else
	{
		double doubleRes = (std::stod(rhs.toString()) == 0) ? throw undifinedBehavior() : std::stod(this->toString()) / std::stod(rhs.toString());
		return (factory.createOperand(resulType, std::to_string(doubleRes)));
	}
}

// template<typename T>
// IOperand const	*Operator<T>::operator%(IOperand const &rhs)
// {
// 	(void)rhs;
// 	return (this);
// }
//
template<typename T>
std::string const	&Operator<T>::toString(void) const
{
	return (this->_valueString);
}

/*------Template especialization------*/
template<>
eOperandType	Operator<int8_t>::getType(void) const {return (Int8);}
template<>
int				Operator<int8_t>::getPrecision(void) const {return (Int8);}

template<>
eOperandType	Operator<int16_t>::getType(void) const {return (Int16);}
template<>
int				Operator<int16_t>::getPrecision(void) const {return (Int16);}

template<>
eOperandType	Operator<int32_t>::getType(void) const {return (Int32);}
template<>
int				Operator<int32_t>::getPrecision(void) const {return (Int32);}

template<>
eOperandType	Operator<float>::getType(void) const {return (Float);}
template<>
int				Operator<float>::getPrecision(void) const {return (Float);}

template<>
eOperandType	Operator<double>::getType(void) const {return (Double);}
template<>
int				Operator<double>::getPrecision(void) const {return (Double);}
