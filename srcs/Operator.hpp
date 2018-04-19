/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:07:26 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/18 20:46:32 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

# include "./srcs/IOperator.hpp"

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class Operator : public IOperator
{
	public:
		Operator(void);
		Operator(Operator const &);
		~Operator(void);

		Operator	&operator=(Operator const &);

		IOperand const * operator+(IOperand const &); // Sum
		IOperand const * operator-(IOperand const &); // Difference
		IOperand const * operator*(IOperand const &); // Product
		IOperand const * operator/(IOperand const &); // Quotient
		IOperand const * operator%(IOperand const &); // Modulo

		int					getPrecision(void);
		eOperandType		getType(void);
		std::string const	&toString(void);

	private:
		
};


#endif
