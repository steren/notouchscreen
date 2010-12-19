/*
 * Fifo.cpp
 *
 *  Created on: 16 déc. 2010
 *      Author: canard
 */

template <typename T> Fifo<T>::Fifo(unsigned int iSize, T iInitObject)
{
	m_objects = new T[iSize];
	for(unsigned int i=0;i < iSize; i++)
	{
		m_pointers.push_back(i);
		m_objects[i] = iInitObject;
	}
}

template <typename T> Fifo<T>::~Fifo()
{
	delete[] m_objects;
}

template <typename T>
unsigned int Fifo<T>::size()
{
	return m_pointers.size();
}

template <typename T>
T& Fifo<T>::getFirst() const
{
	return m_objects[m_pointers.front()];
}

template <typename T>
T& Fifo<T>::getLast() const
{
	return m_objects[m_pointers.back()];
}

template <typename T>
T& Fifo<T>::get(unsigned int iIndex) const
{
	return m_objects[ (iIndex + m_pointers.front()) % m_pointers.size() ];
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
	m_pointers.push_front(m_pointers.back());
	m_pointers.pop_back();
}
