#include "test_sensor_manager.h"
#include "sensor_manager.h"
#include "ultra_sonic.h"
#include "common.h"

int echo_pins[NUM_SENSOR];
int trig_pins[NUM_SENSOR];
UltraSonic *p_sensors[NUM_SENSOR];
SensorManager *p_sensor_manager;

void setUp() {
   for (int i=0; i<NUM_SENSOR; i++) {
       echo_pins[i] = i + 1;
       trig_pins[i] = i + 11;
   }
   
   for (int i=0; i<NUM_SENSOR; i++) {
      p_sensors[i] = new UltraSonic(echo_pins[i], trig_pins[i]);
   }
   
   p_sensor_manager = new SensorManager(
      p_sensors[0], p_sensors[1], p_sensors[2],
      p_sensors[3]);
}

void testSensorManager() {
    setUp();
    p_sensor_manager->init();
    p_sensor_manager->update();
    bool isTrue = p_sensor_manager->isTooClose(TRUE);
    assert(!isTrue);
    isTrue = p_sensor_manager->isTooClose(FALSE);
    assert(!isTrue);
}