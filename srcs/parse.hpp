/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 18:29:29 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/27 16:08:20 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <fstream>
# include <iostream>
# include <vector>

class	Parse
{
	public:
		Parse(void);
		Parse(std::string);
		Parse(Parse const &);
		~Parse(void);

		Parse	&operator=(Parse const &);

	private:
		std::vector<std::string> _content;

		void	store_commands(std::string);
		void	remove_comment(void);
		void	remove_comment_inline(void);
		void	check_instruction(std::ofstream &) const;
		void	check_type(std::string, std::string, int, std::ofstream &) const;
		void	check_values(std::string, std::string, int, std::ofstream &) const;
		void	check_exit_inst(std::ofstream &) const;
		bool	fill_content(std::string, std::ofstream &);
};

#endif
