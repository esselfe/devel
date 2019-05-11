#ifndef STATE_H
#define STATE_H 1

#define STATE_MODE_ELEMENT    1
#define STATE_MODE_MEMORY     2

#define STATE_RENDER_ELEMENT  1
#define STATE_RENDER_FLAG     (1<<1)
#define STATE_RENDER_FLOOR    (1<<2)
#define STATE_RENDER_HUD      (1<<3)
#define STATE_RENDER_MEMORY   (1<<4)
#define STATE_RENDER_SKY      (1<<5)

extern unsigned long state, state_mode;

void StateInit(void);
void StateToggle(unsigned long state_mask);
void StateModeSet(unsigned long mode);

#endif /* STATE_H */

