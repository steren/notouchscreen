/*
 * NoTouchScreenException.h
 *
 *  Created on: 18 déc. 2010
 *      Author: canard
 */

#ifndef NOTOUCHSCREENEXCEPTION_H_
#define NOTOUCHSCREENEXCEPTION_H_

#include <string>
#include <exception>

class NoTouchScreenException: public std::exception {
public:
	NoTouchScreenException();
	NoTouchScreenException(std::string iMessage);
	NoTouchScreenException(const NoTouchScreenException& iException);
	virtual ~NoTouchScreenException() throw();

	const std::string& getMessage() const;
	void print() const;

private:
	std::string m_message;
};

#endif /* NOTOUCHSCREENEXCEPTION_H_ */
