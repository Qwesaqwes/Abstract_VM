/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:07:26 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/25 20:47:49 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_T
# define OPERATOR_T

# include "IOperand.hpp"
# include <exception>
# include <limits>
# include <math.h>

template<typename T>
class Operator : public IOperand
{
	public:
		Operator<T>(void);
		Operator<T>(T);
		Operator<T>(Operator const &);
		~Operator<T>(void);

		Operator<T>			&operator=(Operator const &);

		IOperand const		*operator+(IOperand const &) const; // Sum
		IOperand const		*operator-(IOperand const &) const; // Difference
		IOperand const		*operator*(IOperand const &) const; // Product
		IOperand const		*operator/(IOperand const &) const; // Quotient
		IOperand const		*operator%(IOperand const &) const; // Modulo

		int					getPrecision(void) const;
		eOperandType		getType(void) const;
		std::string const	&toString(void) const;

	private:
		T	_value;
		std::string _valueString;
};

template<typename T>
T		checkFlow(eOperandType, T, T, int);

class	overflow : public std::exception		//exception if overflow
{
	public:
		overflow(void) {};
		overflow(overflow const &) {};
		virtual ~overflow(void) throw() {};

		overflow		&operator=(overflow const &);

		virtual const char	*what(void) const throw();
};

class	underflow : public std::exception		//exception if underflow
{
	public:
		underflow(void) {};
		underflow(underflow const &) {};
		virtual ~underflow(void) throw() {};

		underflow		&operator=(underflow const &);

		virtual const char	*what(void) const throw();
};

class	undifinedBehavior : public std::exception		//exception if div or mod by 0
{
	public:
		undifinedBehavior(void) {};
		undifinedBehavior(undifinedBehavior const &) {};
		virtual ~undifinedBehavior(void) throw() {};

		undifinedBehavior		&operator=(undifinedBehavior const &);

		virtual const char	*what(void) const throw();
};

#include "Operator.cc"

#endif
