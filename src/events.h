#ifndef EVENTS_H
#define EVENTS_H 1

#define MOD_NONE    0
#define MOD_CTRL    1
#define MOD_CAPS    (1<<1)
#define MOD_ALT2     (1<<2)

extern unsigned int mods, mouse_hold, show_keys, warping;
extern unsigned long motion_time_last;

void EventsInit (void);
void EventsCheck (void);

#endif /* EVENTS_H */
