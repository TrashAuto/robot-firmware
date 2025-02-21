// Movement state definitions
#define Stop 0
#define Left 1
#define Forwards 2
#define Backwards 3
#define Right 4

// Movement function prototypes
void move_left(uint8_t angle);
void move_forwards(uint8_t distance);
void move_backwards(uint8_t distance);
void move_right(uint8_t angle);
void movement(void)