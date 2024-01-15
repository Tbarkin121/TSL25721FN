#ifndef _LIGHTSNS_H
#define _LIGHTSNS_H

void lightsns_initialize(void);
void lightsns_check(void);

/**
 * @brief Detects an light sense event. 
 */
void lightsns_event(void);

#endif //_LIGHTSNS_H
