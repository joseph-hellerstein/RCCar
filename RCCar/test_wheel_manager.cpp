#include "wheel_manager.h"
#include "test_wheel_manager.h"
#include "wheel.h"
#include "common.h"

int dira_pins[NUM_WHEEL];
int dirb_pins[NUM_WHEEL];
int enable_pins[NUM_WHEEL];
Wheel *p_wheels[NUM_WHEEL];
WheelManager *p_wheel_manager;

void setupTest() {
   for (int i=0; i<NUM_WHEEL; i++) {
       dira_pins[i] = i + 1;
       dirb_pins[i] = i + 11;
       enable_pins[i] = i + 21;
   }
   
   for (int i=0; i<NUM_WHEEL; i++) {
      p_wheels[i] = new Wheel(dira_pins[i],
            dirb_pins[i], enable_pins[i]);
   }
   
   p_wheel_manager = new WheelManager(
      p_wheels[0], p_wheels[1], p_wheels[2],
      p_wheels[3]);
}

void testWheelManager() {
    setupTest();
    p_wheel_manager->init();
    /* goForward */
    p_wheel_manager->goForward();
    bool isTrue = TRUE;
    for (int i = 0; i<NUM_WHEEL; i++){
        isTrue = p_wheels[i]->isForward && isTrue;
    }
    assert(isTrue);
    /* goBackwards */
    p_wheel_manager->goBackwards();
    bool isFalse = FALSE;
    for (int i = 0; i<NUM_WHEEL; i++){
        isFalse = p_wheels[i]->isForward || isFalse;
    }
    assert(!isFalse);
    /* Stop */
    p_wheel_manager->stop();
    isTrue = TRUE;
    for (int i = 0; i<NUM_WHEEL; i++){
        isTrue = (p_wheels[i]->getSpeed() == SPEED_STOP)
              && isTrue;
    }
    assert(isTrue);
}