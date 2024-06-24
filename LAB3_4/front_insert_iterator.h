#ifndef FRONT_UNSERT_ITERATOR_H
#define FRONT_UNSERT_ITERATOR_H

#include <iostream>
#include "Container.h"

template<class _DataType>
class front_insert_iterator_deq {
private:
	Deque<_DataType>* m_cont;
public:
    front_insert_iterator_deq(Deque <_DataType>& p_cont) : m_cont(&p_cont) {}

    front_insert_iterator_deq& operator*() {
        return *this;
    }

    front_insert_iterator_deq& operator=(const _DataType& value) {
        m_cont->pushFront(value);
        return *this;
    }

    front_insert_iterator_deq& operator=(_DataType&& value) {
        m_cont->pushFront(std::move(value));
        return *this;
    }

    constexpr front_insert_iterator_deq& operator++() {
        return *this;
    }

    constexpr front_insert_iterator_deq operator++(int) {
        return *this;
    }

    constexpr front_insert_iterator_deq& operator--() {
        return *this;
    }

    constexpr front_insert_iterator_deq operator--(int) {
        return *this;
    }

    bool operator == (const front_insert_iterator_deq& p_other) const {
        return (m_cont == p_other.m_cont);
    }

    bool operator != (const front_insert_iterator_deq& p_other) const {
        return (m_cont != p_other.m_cont);
    }

};

#endif