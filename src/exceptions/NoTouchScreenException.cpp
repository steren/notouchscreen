/*
 * NoTouchScreenException.cpp
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#include "NoTouchScreenException.h"

#include <iostream>

NoTouchScreenException::NoTouchScreenException() : std::exception(), m_message("")
{
}

NoTouchScreenException::NoTouchScreenException(std::string iMessage) : std::exception(), m_message(iMessage)
{
}

NoTouchScreenException::NoTouchScreenException(const NoTouchScreenException& iException) : std::exception()
{
	m_message = iException.m_message;
}

NoTouchScreenException::~NoTouchScreenException() throw () {
}

const std::string& NoTouchScreenException::getMessage() const
{
	return m_message;
}

void NoTouchScreenException::print() const
{
	std::cerr << "NoTouchScreenException: " << m_message << std::endl;
}
