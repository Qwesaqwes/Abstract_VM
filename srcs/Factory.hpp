/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:57:39 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/27 18:36:13 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

# include <vector>
# include <string>
# include "IOperand.hpp"
# include <stack>
# include <sstream>

class	Factory
{
	public:
		Factory(void);
		Factory(Factory const &);
		~Factory(void);

		Factory		&operator=(Factory const &);

		void		fill_vectors(std::vector<std::string>);
		IOperand const	*createOperand(eOperandType type, std::string const & value) const;

	private:
		std::vector<std::string> _instruction;
		std::vector<std::string> _type;
		std::vector<std::string> _value;
		std::stack<IOperand const *> _stack;

		bool			detec_inst(unsigned long);
		eOperandType	guesstype(std::string) const;

		void			push(eOperandType, std::string);
		void			assertt(std::string, std::string) const;
		void			pop(void);
		void			dump(void) const;
		bool			print(void) const;
		void			add(void);
		void			sub(void);
		void			mul(void);
		void			divv(void);
		void			mod(void);


		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

		class	invalidValue : public std::exception		//exception if value not correspond type
		{
			public:
				invalidValue(void) {};
				invalidValue(invalidValue const &) {};
				virtual ~invalidValue(void) throw() {};

				invalidValue		&operator=(invalidValue const &);

				virtual const char	*what(void) const throw();
		};

		class	assertNotTrue : public std::exception		//exception if assert inst not true
		{
			public:
				assertNotTrue(void) {};
				assertNotTrue(assertNotTrue const &) {};
				virtual ~assertNotTrue(void) throw() {};

				assertNotTrue		&operator=(assertNotTrue const &);

				virtual const char	*what(void) const throw();
		};

		class	stackEmpty : public std::exception		//exception if stack is empty
		{
			public:
				stackEmpty(void) {};
				stackEmpty(stackEmpty const &) {};
				virtual ~stackEmpty(void) throw() {};

				stackEmpty		&operator=(stackEmpty const &);

				virtual const char	*what(void) const throw();
		};

		class	printInst : public std::exception		//exception if instruction print error
		{
			public:
				printInst(void) {};
				printInst(printInst const &) {};
				virtual ~printInst(void) throw() {};

				printInst		&operator=(printInst const &);

				virtual const char	*what(void) const throw();
		};

		class	operatorError : public std::exception		//exception if operateur not posible
		{
			public:
				operatorError() {};
				operatorError(operatorError const &) {};
				virtual ~operatorError(void) throw() {};

				operatorError		&operator=(operatorError const &);

				virtual const char	*what(void) const throw();
		};
};

#endif
