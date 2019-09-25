/*
 * state.h
 *
 *  Created on: Sep 23, 2019
 *      Author: albrechter
 */

#ifndef STATE_H_
#define STATE_H_

typedef enum{
    eState_IDLE,
    eState_BUSY,
    eState_COLLISION
}eState;

inline void transition_idle(void);
inline void transition_busy(void);
inline void transition_collision(void);

#endif /* STATE_H_ */
