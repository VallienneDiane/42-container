/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:45:19 by dvallien          #+#    #+#             */
/*   Updated: 2023/01/10 16:46:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include "./reverse_iterator.hpp"
#include "./iterator_vector.hpp"
#include "./iterator_traits.hpp"
#include "./is_integral.hpp"
#include "./equal.hpp"
#include "./enable_if.hpp"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////---------------------------- VECTOR IS A SEQUENCE CONTAINER AND KNOWN AS A DYNAMIC ARRAY ------------------------------------- /////////
////// sequence containers refer to a group of container class templates in STL of C++ that implement storage of _current elements	 /////////
////// deque and list are also sequence container																					/////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ft 
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T																							value_type;
			typedef Allocator																					allocator_type;
    		typedef typename Allocator::size_type       														size_type;
    		typedef typename Allocator::difference_type 														difference_type;
			typedef	typename Allocator::reference																reference;
			typedef	typename Allocator::const_reference															const_reference;
    		typedef typename Allocator::pointer         														pointer;
    		typedef typename Allocator::const_pointer   														const_pointer;
			typedef typename ft::my_iterator<value_type, difference_type, pointer, reference>					iterator;
			typedef typename ft::my_iterator<value_type, difference_type, const_pointer, const_reference>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>														reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>												const_reverse_iterator;

		private:
			Allocator			_alloc;
			value_type			*_arr;
			size_type			_size; 		//number of elements
			size_type			_capacity;	//size of allocated storage
			
		public:
			explicit vector(const allocator_type& alloc = allocator_type()): _size(0), _capacity(1), _alloc(alloc) {} //default constructor
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(n), _alloc(alloc) //fill constructor
			{
				_arr = _alloc.allocate(_capacity);
				for(int i = 0; i < n; i++)
					_alloc.construct(_arr + i, val);
			}
			template <class InputIterator> 
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::isIntegral<InputIterator>::value, InputIterator>::type = NULL): _alloc(alloc) //range constructor
			{
//to do		
			}
			vector(const vector &x) { *this = x; }	//copy constructor
			~vector(void) {} //destructor

			vector & operator=(const vector &src) { _size = src._size; _capacity = src._capacity; return (*this); };
			reference operator[](size_type n) { return (_arr[n]); }
			const_reference operator[](size_type n) const { return (_arr[n]); }
	
			////////////////////////////////////    VECTOR MEMBER FUNCTIONS   ////////////////////////////////////////////
			////////   ASSIGN    //////////
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				size_type	dist = 0;

				for(InputIterator tmp = first; tmp != last; tmp++)
				{
					dist++;
					_size++;
				}
				_capacity = dist;					
				_arr = _alloc.allocate(_capacity);
				for(InputIterator tmp = first; tmp != last; tmp++)
				{
					if(dist < _size)
					{
						for(int i = 0; i < dist; i++)
							_alloc.construct(_arr + i, *tmp);
						for(int j = dist; j < _size; j++)
							_alloc.destroy(_arr + j);
						_size = dist;
					}
					else if(dist > _capacity)//if capacity too low reallocate
					{
						reserve(dist);
						_size = _capacity;
					}
				}
			}
			void assign(size_type n, const value_type& val)
			{
				try
				{
					if(n < _size)//if size smaller than n, suppr the extra
					{
						for(int i = 0; i < n; i++)
							_alloc.construct(_arr + i, val);
						for(int j = n; j < _size; j++)
							_alloc.destroy(_arr + j);
						_size = n;
					}
					else if(n > _capacity)//if capacity too low reallocate
					{
						reserve(n);
						_size = _capacity;
					}
				}
				catch(const std::length_error& e)
				{
					throw std::length_error("vector");
				}
			}
			////////   AT    //////////
			reference at(size_type n)
			{
				if (n < 0 || n > _size)
					throw  std::out_of_range("vector");
				return (_arr[n]);
			}
			const_reference at (size_type n) const
			{
				if (n < 0 || n > _size)
					throw  std::out_of_range("vector");
				return (_arr[n]);
			}
			////////   BACK    //////////
			reference back() { return (_arr[_size - 1]); }
			const_reference back() const { return (_arr[_size - 1]); }
			////////   BEGIN    //////////
			iterator begin() { return iterator(_arr); }
			const_iterator begin() const { return iterator(_arr); }
			////////   CAPACITY    //////////
			size_type capacity() const { return (_capacity); }
			////////   CLEAR    //////////
			void clear()
			{
				_alloc.destroy(_arr);
				_alloc.deallocate(_arr, _capacity);
				_size = 0;
			}
			////////   EMPTY   //////////
			bool empty() const
			{
				if(_size == 0)
					return (true);
				return (false);
			}
			////////   END   //////////
			iterator end() { return iterator(_arr + _size); }
			const_iterator end() const { return iterator(_arr + _size); }
			////////   ERASE    //////////
			// iterator erase (iterator position)
			// {
			// 	_alloc.destroy(_arr[position]);
			// 	_size--;
			// 	for(size_type i = position; i < _arr.end(); i++)
			// 	{
					
			// 	}					
			// }
			
			// iterator erase (iterator first, iterator last)
			// {
			// 	for(iterator tmp = first; tmp != last; tmp++)
			// 	{
			// 		_alloc.destroy(_arr[tmp]);
			// 		_size--;
			// 	}
			// }
			////////   FRONT   //////////
			reference front(){ return (_arr[0]); }
			const_reference front() const { return (_arr[0]); }
			////////   GET ALLOCATOR    //////////
			allocator_type get_allocator() const { return (this->_alloc); }
			////////   INSERT    //////////
// iterator insert(iterator position, const value_type& val);
// void insert(iterator position, size_type n, const value_type& val);
// void insert(iterator position, InputIterator first, InputIterator last);
			////////   MAX SIZE    //////////
			size_type max_size() const { return (_alloc.max_size()); }
			////////   POP BACK    //////////
			void pop_back()
			{
				if (_size > 0)
				{
					_size--;
					_alloc.destroy(_arr[_size - 1]);
				}
			}
			////////   PUSH BACK    //////////
			void	push_back(const value_type& value)
			{
				if (_size == 0)
				{
					_arr = _alloc.allocate(_capacity);
					_alloc.construct(_arr + _size, value);
					_size++;
				}
				else if(_size < _capacity)
				{
					_alloc.construct(_arr + _size, value);
					_size++;
				}
				else if (_size == _capacity)
				{
					_capacity = _capacity * 2;
					move_arr(_capacity); // move array to deallocate old arr
					_alloc.construct(_arr + _size, value);
					_size++;
				}
			}

			void	move_arr(size_type new_capacity)
			{
				value_type	*new_arr;

				new_arr = _alloc.allocate(new_capacity);
				for(int i = 0; i < _size; i++)
				{
					_alloc.construct(new_arr + i, _arr[i]);
					_alloc.destroy(_arr + i);
				}
				_alloc.destroy(_arr);
				_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_capacity = new_capacity;
			}
			////////   RBEGIN   //////////
			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
			////////   REND   //////////
			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };
			
			////////   RESERVE   //////////
			void reserve (size_type new_cap)
			{
				if(new_cap > _capacity)
				{
					if(new_cap > max_size())
						throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
					_capacity = new_cap;
					_arr = _alloc.allocate(_capacity);
				}
			}
			////////   RESIZE   //////////
			void resize (size_type n, value_type val = value_type())
			{
				value_type	*new_arr;
				size_type	new_capacity;
				
				try
				{
					if (n == _size)
						return ;
					else if(n < _size)
					{
						new_capacity = _capacity;
						new_arr = _alloc.allocate(new_capacity);
						for(int i = 0; i < n; i++)
						{
							_alloc.construct(new_arr + i, _arr[i]);						
							_alloc.destroy(_arr + i);
						}
						_alloc.destroy(_arr);
						_alloc.deallocate(_arr, _capacity);
						_arr = new_arr;
						_size = n;
					}
					else if (n > _size)
					{
						if (n > _capacity)
							new_capacity = n;
						else
							new_capacity = _capacity;
						new_arr = _alloc.allocate(new_capacity);
						for(int i = 0; i < _size; i++)
							_alloc.construct(new_arr + i, _arr[i]);
						for(int i = _size; i < n; i++)
						{
							_alloc.construct(new_arr + i, val);
							_size++;
						}
					}
					_capacity = new_capacity;
				}
				catch(const std::bad_alloc& e)
				{
					throw ;
				}
				catch(const std::length_error& e)
				{
					throw std::length_error("vector");
				}
			}	
			////////   SIZE   //////////
			size_type size() const { return (_size); }
			////////   SWAP   //////////
			void swap (vector& x)
			{
				vector tmp;
				
				tmp = *this;
				*this = x;
				x = tmp;
			}				
	};
}

#endif