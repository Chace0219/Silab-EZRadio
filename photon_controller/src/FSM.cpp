/*
	Description
*/

#include "FSM.h"

//FINITE STATE
State::State( void (*updateFunction)() ){
	userEnter = 0;
	userUpdate = updateFunction;
	userExit = 0;
}

State::State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() ){
	userEnter = enterFunction;
	userUpdate = updateFunction;
	userExit = exitFunction;
}

//what to do when entering this state
void State::enter(){
	if (userEnter){
		userEnter();
	}
}

//what to do when this state updates
void State::update(){
	if (userUpdate){
		userUpdate();
	}
}

//what to do when exiting this state
void State::exit(){
	if (userExit){
		userExit();
	}
}
//END FINITE STATE


//FINITE STATE MACHINE
FSM::FSM(State& current){
	needToTriggerEnter = true;
	currentState = nextState = &current;
	prevState = NULL;
	stateChangeTime = 0;
}

FSM& FSM::update() {
	//simulate a transition to the first state
	//this only happens the first time update is called
	if (needToTriggerEnter) {
		currentState->enter();
		needToTriggerEnter = false;
	} else {
		if (currentState != nextState){
			immediateTransitionTo(*nextState);
		}
		currentState->update();
	}
	return *this;
}

FSM& FSM::transitionTo(State& state){
	nextState = &state;
	stateChangeTime = millis();
	return *this;
}

FSM& FSM::immediateTransitionTo(State& state){
	currentState->exit();
	prevState = currentState;
	currentState = nextState = &state;
	currentState->enter();
	stateChangeTime = millis();
	return *this;
}

//return the current state
State& FSM::getCurrentState() {
	return *currentState;
}

State* FSM::getPrevState() {
	return prevState;
}

//check if state is equal to the currentState
boolean FSM::isInState( State &state ) const {
	if (&state == currentState) {
		return true;
	} else {
		return false;
	}
}

unsigned long FSM::timeInCurrentState() {
	return millis() - stateChangeTime;
}
//END FINITE STATE MACHINE
