///////////////////////////////////////////////////////////
//  TypeAction.h
//  Implementation of the Class TypeAction
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef TYPEACTION_H
#define TYPEACTION_H

/**
 * This type says if the action is desire or comes from emotional action. This is
 * important when is necessary to resolve which parameters has more presedence in
 * the moment to change parameters
 */
enum TypeAction
{
	TypeActionUnknown,
	/**
	 * This action has trajectory parameters
	 */
	TypeActionTrajectory,
	/**
	 * This action has speak parameters
	 */
	TypeActionSpeak
};
#endif
