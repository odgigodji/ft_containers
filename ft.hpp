//
// Created by Nelson Amerei on 10/30/21.
//

#pragma once

#include <iostream>

namespace ft
{
/*******************************************************************************
*______________________________Enable_if_______________________________________*
*******************************************************************************/
#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
template<bool B, class T = void>
	struct    enable_if {};

template<class T>
	struct    enable_if<true, T> { typedef T type; };
#endif

/*******************************************************************************
*____________________________Iterator_traits___________________________________*
*******************************************************************************/
#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
template<class Category, class T>
	struct   	iterator_traits {
		typedef 	T				 value_type;
		typedef 	value_type*      pointer;
		typedef 	value_type&      reference;
		typedef 	ptrdiff_t        difference_type;
		typedef 	Category		 iterator_category;
	};
#endif

/*******************************************************************************
*____________________________Reverse_iterator__________________________________*
*******************************************************************************/
#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
template<class Iter>
	struct    reverse_iterator {
		typedef Iter										iterator_type;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::iterator_category	iterator_category;
	};
#endif

/*******************************************************************************
*______________________________Equal_compare___________________________________*
*******************************************************************************/
#ifndef EQUAL_HPP
# define EQUAL_HPP
template<class InputIt1, class InputIt2>
bool    equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	for ( ; first1 != last1; ++first1, ++first2) {
		if (*first1 != *first2)
			return false;
	}
	return true;
}
#endif

/*******************************************************************************
*__________________________Lexicographical_compare_____________________________*
*******************************************************************************/
#ifndef LEXICOGRAPHICAL_HPP
# define LEXICOGRAPHICAL_HPP
template<class InputIt1, class InputIt2>
bool	lexicographical_compare (InputIt1 first1, InputIt1 last1, InputIt2 first2,
								 InputIt2 last2) {
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1) { return false; }
		else if (*first1 < *first2) { return true; }
		++first1;
		++first2;
	}
	return (first2 != last2);
}
template<class InputIt1, class InputIt2, class Compare>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
								InputIt2 last2, Compare comp)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void)++first2 )
	{
		if (comp(*first1, *first2)) { return true; }
		if (comp(*first2, *first1)) { return false; }
	}
	return (first1 == last1) && (first2 != last2);
}
#endif

/*******************************************************************************
*_________________________________Is_integral__________________________________*
*******************************************************************************/

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP
template <class T>
		struct is_integral : public std::integral_constant<bool, __is_integral(T)>
#endif

/*******************************************************************************
*__________________________Other _____________________________*
*******************************************************************************/
//							/*    PAIR    */
//							template<class _T1, class _T2>
//									struct pair
//											{
//										typedef _T1    first_type;
//										typedef _T2    second_type;
//
//										first_type    first;
//										second_type    second;
//
//										/*    CONSTRUCTORS    */
//
//										/*    default constructor    */
//										pair() : first(first_type()), second(second_type()) {}
//
//										/*    filling    constructor    */
//										pair(const first_type &x, const second_type &y) : first(x), second(y) {}
//
//										/*    converting constructor    */
//										template<class _U1, class _U2>
//												pair(const pair<_U1, _U2> &p) : first(p.first), second(p.second) {}
//
//												/*    copy constructor    */
//												pair(const pair &other) { *this = other; }
//
//												/*    ASSIGNMENT OPERATOR    */
//												pair&    operator = (const pair &other)
//														{
//													if (this != &other)
//													{
//														first = other.first;
//														second = other.second;
//													}
//													return *this;
//														}
//											};

///*    MAKE PAIR    */
//template<class _T1, class _T2>
//		pair<_T1, _T2>    make_pair(_T1 t, _T2 u) { return pair<_T1, _T2>(t, u); }
//
{};
//
//		/*    CONTAINER PROTOTYPES    */
//		template <    class _T,
//				class _Allocator = std::allocator<_T> >
//						class vector;
//
//		template <    class _T,
//				class _Container = vector<_T> >
//						class stack;
//
//		template <    class _Key,
//				class _T,
//						class _Compare = std::less<_Key>,
//								class _Allocator = std::allocator<pair<const _Key, _T> > >
//										class map;
};
