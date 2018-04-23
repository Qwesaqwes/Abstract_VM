/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:52:01 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/23 18:34:44 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operator.hpp"

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
