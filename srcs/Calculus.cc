/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calculus.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:48:09 by jichen-m          #+#    #+#             */
/*   Updated: 2018/04/24 19:53:26 by jichen-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Calculus.hpp"

Calculus::Calculus(void) {return;}

Calculus::Calculus(Calculus const &src)
{
	*this = src;
	return;
}

Calculus::~Calculus(void) {return;}

Calculus	&Calculus::operator=(Calculus const &rhs)
{
	//.....
	(void)rhs;
	return (*this);
}

void	Calculus::add(void)
{
		if (this->_stack.size() < 2)
			throw Factory::operatorError();
		IOperand const *firstOp = this->_stack.top();
		this->_stack.pop();
		IOperand const *secondOp = this->_stack.top();
		this->_stack.pop();

		IOperand const *res = firstOp + secondOp;
		this->_stack.push(res);

		// eOperandType resulType = (firstOp->getType() <= secondOp->getType()) ? firstOp->getType() : secondOp->getType();
		// // if (resulType <= 2)
		// // {
		// // 	int res = std::stoi(firstOp->toString()) + std::stoi(secondOp->toString());
		// // 	push(resulType, std::to_string(res));
		// // }
		// // else if (resulType == 3)
		// // {
		// // 	float res = std::stof(firstOp->toString()) + std::stof(secondOp->toString());
		// // 	push(resulType, std::to_string(res));
		// // }
		// // else
		// // {
		// // 	double res = std::stod(firstOp->toString()) + std::stod(secondOp->toString());
		// // 	push(resulType, std::to_string(res));
		// // }
		// switch (resulType)
		// {
		// 	case 0:
		// 	case 1:
		// 	case 2:
	    //
		// 		break;
		// 	case 3:
		// 		float res = std::stof(firstOp->toString()) + std::stof(secondOp->toString());
		// 		push(resulType, std::to_string(res));
		// 		break;
		// 	default:
		// 		double res = std::stod(firstOp->toString()) + std::stod(secondOp->toString());
		// 		push(resulType, std::to_string(res));
		// 		break;
		// }

}
