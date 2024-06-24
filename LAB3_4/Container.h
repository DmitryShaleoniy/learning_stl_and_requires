#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <algorithm>
#include <initializer_list>
#include "Iterator.h"
#include "OutOfRangeException.h"
#include "IncompatibleDimException.h"

template<class _DataType>
class Deque {
private:
	int m_dim;
	int m_cap;
	_DataType* m_data;
	_DataType* m_beg;

	void resize(int num) {
		if (num < 0) {
			throw IncompatibleDimException();
		}
		_DataType* new_data = new _DataType[num + 10];
		/*for (int i = 0; i < num + 10; i++) {
			new (&new_data[i]) _DataType();
		}*/

		for (int i = 0; i < m_dim; i++) {
			new_data[i + 5] = m_beg[i];
		}

		delete[] m_data;
		m_data = new_data;
		m_beg = m_data + 5;
		m_cap = num + 10;

	}

	void resize_front(int num) {
		if (num < 0) {
			throw IncompatibleDimException();
		}
		_DataType* new_data = new _DataType[num];
		int i = 0;
		/*for (i; i < num - m_dim; i++) {
			new (&new_data[i]) _DataType();
		}*/
		for (int j = 0; j < std::min(num, m_dim); j++) {
			new_data[i] = m_data[j];
			i++;
		}
		delete[] m_data;
		m_data = new_data;
		m_dim = num;
	}

public:
	using Iterator = DequeIterator<_DataType>;
	//конструкторы
	Deque() : m_dim(0), m_cap(0), m_data(nullptr), m_beg(nullptr)/*, m_end(nullptr)*/ {}

	explicit Deque(int p_dim) : m_dim(p_dim), m_cap(p_dim + 10) {
		if (p_dim < 0) {
			throw IncompatibleDimException();
		}
		m_data = new _DataType[m_cap];
		/*for (int i = 0; i < m_cap; i++) {
			new (&m_data[i]) _DataType();
		}*/
		m_beg = m_data + 5;
	}

	template<class IteratorName>
	Deque(IteratorName p_beg, IteratorName p_end) : m_dim(p_end - p_beg), m_cap(m_dim + 10) {
		if (m_dim < 0) {
			throw IncompatibleDimException();
		}
		m_data = new _DataType[m_cap];
		/*for (int i = 0; i < m_cap; i++) {
			new (&m_data[i]) _DataType();
		}*/
		m_beg = m_data + 5;
		for (int i = 0; p_beg != p_end; i++) {
			m_beg[i] = *p_beg;
			p_beg++;
		}

	}

	Deque(int p_dim, const _DataType& p_dat) : m_dim(p_dim), m_cap(m_dim + 10) {
		if (m_dim < 0) {
			throw IncompatibleDimException();
		}
		m_data = new _DataType[m_cap];
		/*for (int i = 0; i < m_cap; i++) {
			new (&m_data[i]) _DataType();
		}*/
		m_beg = m_data + 5;
		std::fill_n(m_beg, m_dim, p_dat);
	}

	Deque(std::initializer_list<_DataType> p_list) : m_dim(p_list.size()), m_cap(m_dim + 10) {
		if (m_dim < 0) {
			throw IncompatibleDimException();
		}
		m_data = new _DataType[m_cap];
		/*for (int i = 0; i < m_cap; i++) {
			new (&m_data[i]) _DataType();
		}*/
		m_beg = m_data + 5;
		std::copy(p_list.begin(), p_list.end(), m_beg);
	}

	Deque(const Deque& p_other) : m_dim(p_other.m_dim), m_cap(p_other.m_cap) {
		m_data = new _DataType[m_cap];
		/*for (int i = 0; i < m_cap; i++) {
			new (&m_data[i]) _DataType();
		}*/

		Iterator iter1 = p_other.begin();
		Iterator iter(p_other.m_data);
		int i = 0;
		while (iter != iter1) {
			iter++;
			i++;
		}
		m_beg = m_data + i;
		Iterator iter2 = p_other.end();

		for (int i = 0; iter1 != iter2; i++) {
			m_beg[i] = *iter1;
			iter1++;
		}
	}

	Deque(Deque&& p_other) : m_dim(p_other.m_dim), m_data(p_other.m_data), m_cap(p_other.m_cap), m_beg(p_other.m_beg) { //конструктор переноса
		p_other.m_dim = 0;
		p_other.m_cap = 0;
		p_other.m_beg = nullptr;
		p_other.m_data = nullptr;
	}

	~Deque() { //деструктор
		delete[] m_data;
	}

	//функции операции

	Deque& operator= (const Deque& p_other) {
		if (this != &p_other) {
			delete[] m_data;
			m_dim = p_other.m_dim;
			m_cap = p_other.m_cap;
			m_data = new _DataType[m_cap];
			/*for (int i = 0; i < m_cap; i++) {
				new (&m_data[i]) _DataType();
			}*/
			Iterator iter1 = p_other.begin();
			Iterator iter(p_other.m_data);
			int i = 0;
			while (iter != iter1) {
				iter++;
				i++;
			}
			m_beg = m_data + i;
			Iterator iter2 = p_other.end();

			for (int i = 0; iter1 != iter2; i++) {
				m_beg[i] = *iter1;
				iter1++;
			}
		}
		return *this;
	}

	Deque& operator= (Deque&& p_moved) {
		if (this == &p_moved)
			return (*this);
		delete[] m_data;
		m_dim = p_moved.m_dim;
		m_data = p_moved.m_data;
		m_beg = p_moved.m_beg;
		m_cap = p_moved.m_cap;

		p_moved.m_cap = 0;
		p_moved.m_dim = 0;
		p_moved.m_beg = nullptr;
		p_moved.m_data = nullptr;
		return (*this);
	}

	const _DataType& operator[] (int p_ind) const { //для чтения
		if (p_ind < 0 || p_ind >= m_dim)
			throw OutOfRangeException();
		return m_beg[p_ind];
	}

	_DataType& operator[] (int p_ind) { //для записи
		if (p_ind < 0 || p_ind >= m_dim)
			throw OutOfRangeException();
		return m_beg[p_ind];
	}

	//методы

	_DataType& at(int idx) {
		if (idx < 0 || idx >= m_dim) {
			throw OutOfRangeException();
		}
		return m_beg[idx];
	}

	const _DataType& at(int idx) const {
		if (idx < 0 || idx >= m_dim) {
			throw OutOfRangeException();
		}
		return m_beg[idx];
	}

	Iterator begin() const {
		return Iterator(m_beg);
	}

	Iterator end() const {
		return Iterator(m_beg, m_dim);
	}

	void pushBack(const _DataType& elem) {
		if (m_beg + m_dim - 1 == m_data + m_cap - 1)
			resize(m_dim + 1);
		*(end()) = elem;
		m_dim++;
	}

	void pushBack(_DataType&& elem) {
		if (m_beg + m_dim - 1 == m_data + m_cap - 1)
			resize(m_dim + 1);
		*(end()) = std::move(elem);
		m_dim++;
	}

	void popBack() {
		if (m_dim < 1) {
			throw IncompatibleDimException();
		}
		m_dim--;
	}

	void pushFront(const _DataType& elem) {
		if (m_beg == m_data) {
			resize(m_dim + 1);
		}
		m_beg--;
		*(m_beg) = elem;
		m_dim++;
	}

	void pushFront(_DataType&& elem) {
		if (m_beg == m_data) {
			resize(m_dim + 1);
		}
		m_beg--;
		*(m_beg) = std::move(elem);
		m_dim++;
	}


	void popFront() {
		if (m_dim < 1) {
			throw IncompatibleDimException();
		}
		m_beg++;
		m_dim--;
	}

	Iterator insert(Iterator pos, const _DataType& elem) {
		if (m_dim == m_cap) {
			int g = 0;
			while (begin() + g != pos)
				g++;
			resize(m_dim + 1);
			pos = begin() + g;
		}
		m_dim++;

		Iterator swap = begin() - 1;
		if (m_beg == m_data) {
			swap = end() - 1;
			while (swap != pos) {
				*(swap) = *(swap - 1);
				swap--;
			}
		}
		else {
			m_beg--;
			while (swap + 1 != pos) {
				*(swap) = *(swap + 1);
				swap++;
			}
		}
		*(swap) = elem;
		return swap;
	}

	Iterator insert(Iterator pos, _DataType&& elem) {
		if (m_dim == m_cap) {
			resize(m_dim + 1);
		}
		m_dim++;

		Iterator swap = begin() - 1;
		if (m_beg == m_data) {
			swap = end() - 1;
			while (swap != pos) {
				*(swap) = *(swap - 1);
				swap--;
			}
		}
		else {
			m_beg--;
			while (swap + 1 != pos) {
				*(swap) = *(swap + 1);
				swap++;
			}
		}
		*(swap) = std::move(elem);
		return swap;
	}

	template<class IteratorName>
	Iterator insert(Iterator pos, IteratorName beg, IteratorName end) {
		int i = 0;
		while (beg != end) {
			pos = insert(pos, *beg);
			beg++;
			pos++;
			i++;
		}
		return pos - i;
	}

	Iterator erase(Iterator pos) {
		Iterator ret = pos + 1;
		while (pos != begin()) {
			*(pos) = *(pos - 1);
			pos--;
		}
		m_dim--;
		m_beg++;

		return ret;
	}

	bool empty() const {
		return m_dim == 0;
	}

	int size() const {
		return m_dim;
	}

	void clear() {
		delete[] m_data;
		m_data = nullptr;
		m_beg = nullptr;
		m_dim = 0;
		m_cap = 0;
	}
};

#endif