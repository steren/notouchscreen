/*
 * Fifo.h
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

#ifndef FIFO_H_
#define FIFO_H_


/**
 * Any object buffer class
 *
 * T must be copiable. The ctor need an init object in order to
 * allocate the needed memory.
 */
template <typename T> class Fifo {
public:
	Fifo(unsigned int iSize, T iInitObject);
	virtual ~Fifo();

	unsigned int size() const;

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

	unsigned int m_size;
	unsigned int m_pointer;
	T * m_objects;
};

#include "Fifo.cpp"

#endif /* FIFO_H_ */
