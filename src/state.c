#include <stdio.h>

#include "state.h"

unsigned long state, state_mode;

void StateInit(void) {
	state = STATE_RENDER_ELEMENT | STATE_RENDER_FLAG | STATE_RENDER_FLOOR |
		STATE_RENDER_HUD | STATE_RENDER_SKY;
	state_mode = STATE_MODE_ELEMENT;
}

void StateToggle(unsigned long state_mask) {
	state ^= state_mask;
}

void StateModeSet(unsigned long mode) {
	// Unload current mode
	switch(state_mode) {
	case STATE_MODE_ELEMENT:
		StateToggle(STATE_RENDER_ELEMENT);
		StateToggle(STATE_RENDER_FLAG);
		break;
	case STATE_MODE_MEMORY:
		StateToggle(STATE_RENDER_MEMORY);
		break;
	}	
	
	state_mode = mode;
	
	// Load the new mode
	switch(mode) {
	case STATE_MODE_ELEMENT:
		StateToggle(STATE_RENDER_ELEMENT);
		StateToggle(STATE_RENDER_FLAG);
		break;
	case STATE_MODE_MEMORY:
		StateToggle(STATE_RENDER_MEMORY);
		break;
	}
}

