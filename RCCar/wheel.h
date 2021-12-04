#define SPEED_STOP 0
#define SPEED_LOW 100
#define SPEED_MED 200
#define SPEED_HIGH 255

class Wheel {
    public:
        int dira_pin;
        int dirb_pin;
        int enable_pin;  // Motor is enabled
        bool isForward;  // Current direction
        int speed;

        Wheel(int dira_pin, int dirb_pin, int enable_pin);
        void init();
        void goForward();
        void goBackwards();
        void setSpeed(int speed);
        int getSpeed();
        void stop();
};