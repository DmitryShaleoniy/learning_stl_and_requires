#ifndef ITERATOR_H
#define ITERATOR_H

#include "OutOfRangeException.h"

template <class T_Deque>
class DequeIterator {
private:
	T_Deque* m_pos;
public:
	//конструкторы
	explicit DequeIterator(T_Deque* p_pos) : m_pos(p_pos) {}
	DequeIterator(T_Deque* p_pos, int p_ind) {
		if (p_ind<0 || (p_pos + p_ind) - 1 == nullptr)
		{
			throw OutOfRangeException();
		}
		m_pos = p_pos + p_ind;
	}

	DequeIterator& operator++() {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		++m_pos;
		return *this;
	}
	DequeIterator& operator--() {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		--m_pos;
		return *this;
	}

	DequeIterator operator++(int) {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		m_pos++;
		return *this;
	}

	DequeIterator operator--(int) {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		m_pos--;
		return *this;
	}

	T_Deque& operator*() const{
		if (m_pos == nullptr)
			throw OutOfRangeException();
		return *m_pos;
	}

	T_Deque& operator*() {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		return *m_pos;
	}

	auto operator - (const DequeIterator& p_other) {
		if (m_pos - 1 == nullptr)
			throw OutOfRangeException();
		return m_pos - p_other.m_pos;
	}

	bool operator==(const DequeIterator& p_other) const {	
		return m_pos == p_other.m_pos;
	}

	bool operator != (const DequeIterator & p_other) const {
		return m_pos != p_other.m_pos;
	}

	bool operator > (const DequeIterator& p_other) const {
		return m_pos > p_other.m_pos;
	}

	bool operator >= (const DequeIterator& p_other) const {
		return m_pos >= p_other.m_pos;
	}

	bool operator < (const DequeIterator& p_other) const {
		return m_pos < p_other.m_pos;
	}

	bool operator <= (const DequeIterator& p_other) const {
		return m_pos <= p_other.m_pos;
	}

	DequeIterator operator+ (int p_num) const {
		return DequeIterator(m_pos + p_num);
	}

	DequeIterator operator- (int p_num) const {
		return DequeIterator(m_pos - p_num);
	}

	DequeIterator& operator+= (int p_num) {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		m_pos += p_num;
		return *this;
	}

	DequeIterator& operator-= (int p_num) {
		if (m_pos - 1 == nullptr)
			throw OutOfRangeException();
		m_pos -= p_num;
		return *this;
	}

	T_Deque* operator->() const {
		if (m_pos == nullptr)
			throw OutOfRangeException();
		return m_pos;
	}

	const T_Deque& operator[](int p_num) const {
		if (p_num < 0)
		{
			throw OutOfRangeException();
		}
		return m_pos[p_num];
	}

	T_Deque& operator[](int p_num) {
		if (p_num < 0)
		{
			throw OutOfRangeException();
		}
		return m_pos[p_num];
	}

	explicit operator T_Deque* () {
		return m_pos;
	}
};

#endif 