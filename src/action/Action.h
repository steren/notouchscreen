/*
 * Action.h
 *
 *  Created on: 21 déc. 2010
 *      Author: canard
 */

#ifndef ACTION_H_
#define ACTION_H_

#include <boost/shared_ptr.hpp>

class Action {
public:
	Action();

	virtual ~Action();
	virtual void Fire();

private:
	Action(const Action&);
	Action& operator=(const Action&);

};

typedef boost::shared_ptr<Action> Action_var;

#endif /* ACTION_H_ */
