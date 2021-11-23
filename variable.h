#ifdef _MAIN_
	#ifndef __VARIABLE_EXT__
		#define __VARIABLE_EXT__
	#endif
#else
	#ifndef __VARIABLE_EXT__
		#define __VARIABLE_EXT__	extern
	#endif
#endif

__VARIABLE_EXT__ double xf3[4];
__VARIABLE_EXT__ double yf3[4];
__VARIABLE_EXT__ double zf3[4];

__VARIABLE_EXT__ double x3;
__VARIABLE_EXT__ double y3;
__VARIABLE_EXT__ double z3;

__VARIABLE_EXT__ double xf1;
__VARIABLE_EXT__ double yf1;
__VARIABLE_EXT__ double zf1;

__VARIABLE_EXT__ double fr_1;
__VARIABLE_EXT__ double fr_2;
__VARIABLE_EXT__ double fr_3;

__VARIABLE_EXT__ double fl_1;
__VARIABLE_EXT__ double fl_2;
__VARIABLE_EXT__ double fl_3;

__VARIABLE_EXT__ double f1;
__VARIABLE_EXT__ double f2;
__VARIABLE_EXT__ double f3;

__VARIABLE_EXT__ double rr_1;
__VARIABLE_EXT__ double rr_2;
__VARIABLE_EXT__ double rr_3;

__VARIABLE_EXT__ double rl_1;
__VARIABLE_EXT__ double rl_2;
__VARIABLE_EXT__ double rl_3;

__VARIABLE_EXT__ double r1;
__VARIABLE_EXT__ double r2;
__VARIABLE_EXT__ double r3;

__VARIABLE_EXT__ double pre_pos[12];
__VARIABLE_EXT__ double next_pos[12];

__VARIABLE_EXT__ unsigned long ulPeriod_Step;
__VARIABLE_EXT__ unsigned long ulPreTime_Step;
__VARIABLE_EXT__ unsigned long ulPreTime;
__VARIABLE_EXT__ unsigned long ulCurTime;
__VARIABLE_EXT__ double t;
__VARIABLE_EXT__ double ht;

__VARIABLE_EXT__ int walk_flag;
__VARIABLE_EXT__ char walk_dir;
__VARIABLE_EXT__ char pre_walk_dir;

__VARIABLE_EXT__ short FrontV_Dist;
__VARIABLE_EXT__ short FrontH_Dist;
__VARIABLE_EXT__ short Right_Dist;
__VARIABLE_EXT__ short Rear_Dist;
__VARIABLE_EXT__ short Left_Dist;