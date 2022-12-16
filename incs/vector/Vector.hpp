/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vallienne <vallienne@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:45:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/12/16 18:08:51 by vallienne        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//////////////////////////////////////////////////////////////////////////////////////////
////// VECTOR IS A SEQUENCE CONTAINER AND KNOWN AS A DYNAMIC ARRAY OR ARRAY LIST ////////
////////////////////////////////////////////////////////////////////////////////////////

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

namespace ft 
{
	template <typename T, class Allocator = std::allocator<T> >
	
	class vector
	{
		private:
			typedef T			value_type;
			typedef	T&			reference;
			typedef	T const &	const_reference;
			typedef	size_t		size_type;
			Allocator 			alloc;
			value_type			*_arr;
			size_type			_size; 		// number of elements
			size_type			_capacity;	//size of allocated storage 
			
		public:
			vector(void): _size(0), _capacity(1) {};
			~vector(void) {};
			
			void	push_back(const value_type& value)
			{
				if (_size == 0)
				{
					_arr = alloc.allocate(_capacity);
					alloc.construct(_arr + _size, value);
					_size++;
				}
				else if(_size < _capacity)
				{
					alloc.construct(_arr + _size, value);
					_size++;
				}
				else if (_size == _capacity)
				{
					_capacity = _capacity * 2;
					move_arr(_capacity); // move array to deallocate old arr
					alloc.construct(_arr + _size, value);
					_size++;
				}
			}

			void	move_arr(size_type new_capacity)
			{
				value_type	*new_arr;

				new_arr = alloc.allocate(new_capacity);
				for(int i = 0; i < _size; i++)
				{
					alloc.construct(new_arr + i, _arr[i]);
					alloc.destroy(_arr + i);
				}
				alloc.destroy(_arr);
				alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_capacity = new_capacity;
			}

			void	pop_back(void)
			{
				_size--;
				alloc.destroy(_arr);
			}

			size_type capacity() const { return (_capacity); }

			bool empty() const
			{
				if(_size == 0)
					return (true);
				return (false);
			}

			size_type size() const { return (_size); }

			size_type max_size() const { return (alloc.max_size()); }

			reference at(size_type n)
			{
				if (n < 0 || n > _size)
					throw  std::out_of_range("Out of Range error");
				return (_arr[n]);
			}

			const_reference at (size_type n) const
			{
				if (n < 0 || n > _size)
					throw  std::out_of_range("Out of Range error");
				return (_arr[n]);
			}
			
			//////////////////////// OPERATORS /////////////////////////////
			T const & operator[](size_type n) const { return (_arr[n]); }
			T & operator[](size_type n) { return (_arr[n]); }
	};
}



#endif