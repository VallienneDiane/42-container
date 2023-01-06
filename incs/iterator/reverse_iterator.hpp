/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:50:04 by dvallien          #+#    #+#             */
/*   Updated: 2023/01/06 12:11:11 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include "iterator_traits.hpp"
#include "../vector/Vector.hpp"

namespace ft 
{
	template <class Iterator, class T >
	class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
		
		protected:
			Iterator _current;

		public:
			reverse_iterator(): _current() {}
			explicit reverse_iterator(iterator_type it): _current(it) {}
			explicit reverse_iterator(const reverse_iterator &other): _current(other.base()) {}
			reverse_iterator& operator=(const reverse_iterator &other) { _current = other.base(); return (*this); }
			~reverse_iterator(){}
			
			iterator_type base() const { return (_current); } //accesses the underlying iterator
			
			// ACCESSES AN ELEMENT BY INDEX
			reference operator[](int index) { return *(_current + index); }
			// ACCESSES TO POINTED-TO ELEMENT
			pointer operator->() const { return (_current); }
			reference operator*() const { return (*_current); }
			// INCREMENT OR DECREMENT THE ITERATOR
				//pre increment : returns a reference to the incremented object
				//post increment (int): returns a copy of the original, unincremented object
			reverse_iterator& operator++() { --_current; return (*this); }
			reverse_iterator& operator++(int) { reverse_iterator tmp = *this; --_current; return tmp;}
			reverse_iterator& operator+=(difference_type n) { return reverse_iterator(_current - n); }
			reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); }
			
			reverse_iterator& operator--() { _current++; return *this;}
			reverse_iterator& operator--(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
			reverse_iterator& operator-=( difference_type n) { return reverse_iterator(_current + n); }
			reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); }	
	};
	
	// COMPARISON OPERATORS
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	
	// template <typename Iterator>
	// bool operator!=(const reverse_iterator& other) const
	// {
	// 	return (_current != other->_current);
	// }
	
	// template <typename Iterator>
	// bool operator>=(const reverse_iterator &other) const
	// {
	// 	return (_current >= other->_current);
	// }
	
	// template <typename Iterator>
	// bool operator<=(const reverse_iterator &other) const
	// {
	// 	return (_current <= other->_current);
	// }
	
	// template <typename Iterator>
	// bool operator>(const reverse_iterator &other) const
	// {
	// 	return (_current > other->_current);
	// }
	
	// template <typename Iterator>
	// bool operator<(const reverse_iterator &other) const
	// {
	// 	return (_current < other->_current);
	// }
	

}
#endif
			