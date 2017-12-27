#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

/*contains all the constants used in the game*/
#define SCREEN_WIDTH 1143
#define SCREEN_HEIGHT 768
#define HELI_WIDTH 144
#define HELI_HEIGHT 53
/*heli x_pos is 1/10th of original screen width*/
#define HELI_X_POS 114
/*default heli pos in y direction*/
#define HELI_Y_POS 184
/*gives change in pixels for one press*/
#define HELI_VELOCITY_UP 1
#define HELI_VELOCITY_DOWN -2
/*pixels moved per frame*/
#define MOVEMENT_PER_FRAME 9
#define SPRITE_DISTANCE 648
/*max limits to velocities*/
#define MAX_UPWARD_VELOCITY 10
#define MAX_DOWNWARD_VELOCITY -10

#endif /*CONSTANTS_H_INCLUDED*/
