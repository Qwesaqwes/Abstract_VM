/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:57:39 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/20 18:57:08 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

# include <iostream>
# include <vector>
# include <string>
# include "IOperand.hpp"
# include "Operand.hpp"
// # include <exception>
// # include <limits>

class	Factory
{
	public:
		Factory(void);
		Factory(Factory const &);
		~Factory(void);

		Factory		&operator=(Factory const &);

		void		fill_vectors(std::vector<std::string>);

	private:
		std::vector<std::string> _instruction;
		std::vector<std::string> _type;
		std::vector<std::string> _value;
		std::stack<IOperand const *> _stack;

		void			detec_inst(unsigned long);
		void			push(std::string, std::string) const;
		eOperandType	guesstype(std::string) const;

		IOperand const	*createOperand( eOperandType type, std::string const & value ) const;
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

};

#endif
