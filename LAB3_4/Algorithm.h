#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <iterator>
#include <concepts>
#include "Iterator.h"
#include "front_insert_iterator.h"

template<class _Iter>
concept _iterator = requires(_Iter a, _Iter b) {
	{ ++a } -> std::same_as<_Iter&>;
	{ a++ } -> std::same_as<_Iter>;

	{ --a } -> std::same_as<_Iter&>;
	{ a-- } -> std::same_as<_Iter>;

	{ *a } -> std::same_as<std::iter_reference_t<_Iter>>;
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

template<class _Iter, class Func>
concept LambdaReq = requires(Func lambda, _Iter it) {
	lambda(*it);
};

template<class _Iter, class Func>
concept PredicateReq = requires(Func pred, _Iter it) {
	{ pred(*it) } -> std::convertible_to<bool>;
};

template <class _Iter, class Func>
requires _iterator<_Iter>&& PredicateReq<_Iter, Func>
_Iter findIf(_Iter beg, _Iter end, Func pred) {
	while (beg != end) {
		if (pred(*beg))
			break;
		beg++;
	}
	return beg;
};

template <class _Iter>
requires _iterator<_Iter>
_Iter minElement(_Iter beg, _Iter end) {
	_Iter result = beg;
	beg++;
	while (beg != end) {
		if (*beg < *result) {
			result = beg;
		}
		beg++;
	}
	return result;
}

template <class _Iter>
requires _iterator<_Iter>
_Iter maxElement(_Iter beg, _Iter end) {
	_Iter result(beg);
	beg++;
	while (beg != end) {
		if (*beg > *result) {
			result = beg;
		}
		beg++;
	}
	return result;
}

template<class _Iter, class Func>
requires _iterator<_Iter> && LambdaReq<_Iter, Func>
void forEach(_Iter beg, _Iter end, Func op) {
	while (beg != end) {
		op(*beg);
		beg++;
	}
};

template <class _Iter>
requires _iterator<_Iter>
void Sort(_Iter beg, _Iter end) {
	while (beg != end)
	{
		std::iter_swap(beg, minElement(beg, end));
		++beg;
	}
};

template <class _Iter, class _OtherIter, class Func>
requires _iterator<_Iter>&& PredicateReq<_Iter, Func> && _iterator<_OtherIter>
_OtherIter copyIf(_Iter sourceBeg, _Iter sourceEnd, _OtherIter destBeg, Func pred) {
	while (sourceBeg != sourceEnd) {
		if (pred(*sourceBeg)) {
			*destBeg = *sourceBeg;
			destBeg++;
		}
		sourceBeg++;
	}
	return destBeg;
};

#endif