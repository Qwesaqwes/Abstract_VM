/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculus.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:47:54 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/24 16:02:10 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULUS_H
# define CALCULUS_H

// #include "Factory.hpp"
# include <iostream>

class Calculus
{
	public:
		Calculus(void);
		Calculus(Calculus const &);
		~Calculus(void);

		Calculus	&operator=(Calculus const &);

		void			add(void);

	private:
};

#endif
