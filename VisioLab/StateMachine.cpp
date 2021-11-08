#include "StateMachine.h"

namespace VisioLab {
	void StateMachine::AddState(StateRef newState, bool isReplacing) {
		this->_isAdding = true;
		this->_isReplacing = isReplacing;
		this->newState = std::move(newState);
	}
	void StateMachine::RemoveState() {
		this->_isRemoving = true;
	}
	void StateMachine::ProcessSateChanges() {
		if (this->_isRemoving && !this->_states.empty()) {
			this->_states.pop();
			if (!_states.empty()) {
				this->_states.top()->Resume();
			}
			this->_isRemoving = false;
		}
		else if (this->_isAdding) {
			if (!this->_states.empty()) {
				if (this->_isReplacing) {			// for example, the menu screen will be replaced when we
					this->_states.pop();			// select the ds. we must discard the state
				}
				else {
					this->_states.top()->Pause();	// the virtual function from state will perform the task	
				}									// in the derived classes, eg PauseState
			}
			this->_states.push(std::move(this->newState));	// move stores one object from another object efficiently
			this->_states.top()->Init();			// initialize whatever the state is on the top
			this->_isAdding = false;
		}
	}
	StateRef& StateMachine::getActiveState() {
		return this->_states.top();
	}
}