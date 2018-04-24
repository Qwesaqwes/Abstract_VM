/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:52:01 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/24 21:13:57 by jichen-m         ###   ########.fr       */
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

template<typename T>
IOperand const	*Operator<T>::operator+(IOperand const &rhs)
{
	Factory		factory;

	eOperandType resulType = (this->getType() <= rhs.getType()) ? this->getType() : rhs.getType();
	if (resulType <= 2)
	{
		int intRes = std::stoi(this->toString()) + std::stoi(rhs.toString());
		return (factory.createOperand(resulType, std::to_string(intRes)));
	}
	else if (resulType == 3)
	{
		float floatRes = std::stof(this->toString()) + std::stof(rhs.toString());
		return (factory.createOperand(resulType, std::to_string(floatRes)));
	}
	else
	{
		double doubleRes = std::stod(this->toString()) + std::stod(rhs.toString());
		return (factory.createOperand(resulType, std::to_string(doubleRes)));
	}
}

// template<typename T>
// IOperand const	*Operator<T>::operator-(IOperand const &rhs)
// {
// 	(void)rhs;
// 	return (this);
// }
//
// template<typename T>
// IOperand const	*Operator<T>::operator*(IOperand const &rhs)
// {
// 	(void)rhs;
// 	return (this);
// }
//
// template<typename T>
// IOperand const	*Operator<T>::operator/(IOperand const &rhs)
// {
// 	(void)rhs;
// 	return (this);
// }
//
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
