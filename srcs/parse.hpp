/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:29:29 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/16 17:41:37 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <iostream>
# include <fstream>
# include <vector>
# include <exception>
# include <string>
# include <algorithm>

class	parse
{
	public:
		parse(void);
		parse(std::string);
		parse(parse const &);
		~parse(void);

		parse	&operator=(parse const &);

		void	store_commands(std::string);
		void	remove_comment(void);
		void	check_content(void) const;
		void	check_values(std::string, std::string, int) const;

		std::vector<std::string>	getVector(void) const;

	private:
		std::vector<std::string> _content;

		class	notfile : public std::exception		//exception if file doesn't exist
		{
			public:
				notfile(void) {};
				notfile(notfile const &) {};
				virtual ~notfile(void) throw() {};

				notfile		&operator=(notfile const &);

				virtual const char	*what(void) const throw();
		};

		class	notExitInstruction : public std::exception		//exception if exit instruction no at the end
		{
			public:
				notExitInstruction(void) {};
				notExitInstruction(notExitInstruction const &) {};
				virtual ~notExitInstruction(void) throw() {};

				notExitInstruction		&operator=(notExitInstruction const &);

				virtual const char	*what(void) const throw();
		};

		class	unknowInstruction : public std::exception		//exception if unknow instruction
		{
			public:
				unknowInstruction(void) {};
				unknowInstruction(unknowInstruction const &) {};
				virtual ~unknowInstruction(void) throw() {};

				unknowInstruction		&operator=(unknowInstruction const &);

				virtual const char	*what(void) const throw();
		};

		class	unknowSyntax : public std::exception		//exception if unknow instruction
		{
			public:
				unknowSyntax(void) {};
				unknowSyntax(unknowSyntax const &) {};
				virtual ~unknowSyntax(void) throw() {};

				unknowSyntax		&operator=(unknowSyntax const &);

				virtual const char	*what(void) const throw();
		};
};

#endif
