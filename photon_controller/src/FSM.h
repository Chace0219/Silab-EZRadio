/* Created By Yang */
/*
||
|| @file 	FSM.h
|| @version	1.9
|| @author	Yang
||
|| @description : state machine
||
*/

#ifndef FSM_H
#define FSM_H

#include "application.h"

#define NO_ENTER (0)
#define NO_UPDATE (0)
#define NO_EXIT (0)

//define the functionality of the states
class State {
	public:
		State( void (*updateFunction)() );
		State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );
		//State( byte newId, void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );

		//void getId();
		void enter();
		void update();
		void exit();
	private:
		//byte id;
		void (*userEnter)();
		void (*userUpdate)();
		void (*userExit)();
};

//define the finite state machine functionality
class FSM {
	public:
		FSM(State& current);

		FSM& update();
		FSM& transitionTo( State& state );
		FSM& immediateTransitionTo( State& state );

		State& getCurrentState();
		State* getPrevState();
		boolean isInState( State &state ) const;

		unsigned long timeInCurrentState();

	private:
		bool 	needToTriggerEnter;
		State* 	currentState;
		State* 	nextState;
		State* 	prevState;
		unsigned long stateChangeTime;
};

#endif
