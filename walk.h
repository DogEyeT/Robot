#ifndef WALK_H_
#define WALK_H_

#define _1MSEC_TO_1SEC 0.001
#define _1SEC_TO_1MSEC 1000

enum _COORD
{
 COORD_X,
 COORD_Y,
 COORD_Z,
 MAX_COORD_NUM
};
enum _LEG
{
 LF,
 RF,
 LR,
 RR,
 MAX_LEG_NUM
};
enum _JOINT
{
 JOINT_1,
 JOINT_2,
 JOINT_3,
 MAX_JOINT_NUM
};


#define FX 0
#define FZ 380
#define RX 0
#define RZ 380
#define H 500

#define l1 55
#define l2 240
#define l3 48
#define l4 215

extern void spot();

extern void start_straight();
extern void straight();

extern void clk();
extern void anti_clk();

extern void left_side();
extern void right_side();

extern void way();
extern void clk_way();
extern void anti_clk_way();

#endif /*WALK_H_*/