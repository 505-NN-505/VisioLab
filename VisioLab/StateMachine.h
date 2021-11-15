#pragma once

#include <memory>
#include <stack>
#include "State.h"

namespace VisioLab {
	typedef std::unique_ptr<State> StateRef;

	class StateMachine {
	private:
		std::stack<StateRef> _states;	// stores the address of the states in the _states stack
		StateRef newState;
		bool _isRemoving, _isAdding, _isReplacing;
	public:
		StateMachine() :_isRemoving(0), _isAdding(0), _isReplacing(0) { }
		~StateMachine() {}

		// If isReplacing is true, the previous state will be replaced, else
		// the contents of the previous state will be saved while a new state is added on the top being
		// visible on the screen
		void AddState(StateRef newState, bool isReplacing = true);
		
		void RemoveState();

		// this function literally adds or removes states from the decision made
		// by AddState() or Remove(), basic stact push() or pop()
		void ProcessSateChanges();

		// returns the address of the current active state
		StateRef& getActiveState();
	};
}

