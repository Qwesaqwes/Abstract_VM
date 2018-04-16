/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:21:36 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/12 18:28:53 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERATOR_H
# define IOPERATOR_H

class IOperator
{
	public:
		virtual ~IOperand( void ) {}

		virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
		virtual eOperandType getType( void ) const = 0; // Type of the instance

		virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
		virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
		virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
		virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
		virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo

		virtual std::string const & toString( void ) const = 0; // String representation of the instance
};

#endif
