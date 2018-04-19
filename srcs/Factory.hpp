/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 17:57:39 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/19 18:22:45 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

# include <iostream>
# include <vector>
// # include <exception>

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
};

#endif
