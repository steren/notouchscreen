/*
 * Fifo.cpp
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

template <typename T> Fifo<T>::Fifo(unsigned int iSize, T iInitObject)
: m_pointer(0), m_size(iSize)
{
	m_objects = new T[m_size];
	for(unsigned int i=0;i < m_size; i++)
	{
		m_objects[i] = iInitObject;
	}
}

template <typename T> Fifo<T>::~Fifo()
{
	delete[] m_objects;
}

template <typename T>
unsigned int Fifo<T>::size() const
{
	return m_size;
}

template <typename T>
T& Fifo<T>::getFirst() const
{
	return m_objects[m_pointer];
}

template <typename T>
T& Fifo<T>::getLast() const
{
	return m_objects[m_size - 1];
}

template <typename T>
T& Fifo<T>::get(unsigned int iIndex) const
{
	return m_objects[(iIndex + m_pointer) % m_size];
}

template <typename T>
void Fifo<T>::push(const T& obj)
{
	round();
	getFirst() = obj;
}

template <typename T>
void Fifo<T>::round()
{
	m_pointer = ++m_pointer % m_size;
}
