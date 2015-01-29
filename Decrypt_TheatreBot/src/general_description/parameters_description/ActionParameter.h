///////////////////////////////////////////////////////////
//  ActionParameter.h
//  Implementation of the Class ActionParameter
//  Created on:      01-abr-2014 05:53:23 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef ACTIONPARAMETER_H
#define ACTIONPARAMETER_H

#include "Parameter.h"

/**
 * This class is an special class to send the parameters of the actions.
 * 
 * This class is added to allow following modifications of the parameters.
 * 
 * Specific methods and variables could be added, at the begining is the same as
 * its father class just to test
 */
class ActionParameter : public Parameter
{

public:
	ActionParameter();
	virtual ~ActionParameter();

};
#endif // !defined(EA_657D027D_F5F8_478d_910E_DEE0B5E6CFCB__INCLUDED_)
