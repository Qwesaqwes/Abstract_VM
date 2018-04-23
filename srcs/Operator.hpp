/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:07:26 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/23 18:26:56 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

# include "IOperand.hpp"

template<typename T>
class Operator : public IOperand
{
	public:
		Operator<T>(void);
		Operator<T>(T);
		Operator<T>(Operator const &);
		~Operator<T>(void);

		Operator<T>			&operator=(Operator const &);

		IOperand const		*operator+(IOperand const &); // Sum
		// IOperand const		*operator-(IOperand const &); // Difference
		// IOperand const		*operator*(IOperand const &); // Product
		// IOperand const		*operator/(IOperand const &); // Quotient
		// IOperand const		*operator%(IOperand const &); // Modulo

		int					getPrecision(void) const;
		eOperandType		getType(void) const;
		std::string const	&toString(void) const;

	private:
		T	_value;
		std::string _valueString;
};


#endif
