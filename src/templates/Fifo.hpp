/*
 * Fifo.h
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <list>

template <typename T> class Fifo {
public:
	Fifo(unsigned int iSize, T iInitObject);
	virtual ~Fifo();

	unsigned int size();

	T& getFirst() const;
	T& getLast() const;
	T& get(unsigned int iIndex) const;

	void push(const T&);

private:
	Fifo(const Fifo&);
	Fifo& operator= (const Fifo&);

	void round();
	Fifo(const T&);
	T& operator= (const T&);

	std::list<unsigned int> m_pointers;
	T * m_objects;
};

#include "Fifo.cpp"

#endif /* FIFO_H_ */
