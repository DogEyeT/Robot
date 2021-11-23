#include "variable.h"
#include "walk.h"
#include <math.h>

void spot(){
  walk_dir ='P';
  switch(walk_flag){
    case 0:
      xf3[RF] = FX;
      yf3[RF] = l1;
      zf3[RF] = FZ - 30 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
 
      xf3[LR] = RX;
      yf3[LR] = l1;
      zf3[LR] = RZ - 30 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      if(t >= 0.25){
        zf3[RF] = FZ - 30;
        zf3[LR] = RZ - 30;
        ulPreTime_Step = ulCurTime;
        walk_flag++;
      }
      break;


    case 1:
      xf3[LF] = FX;
      yf3[LF] = l1;
      zf3[LF] = FZ - 30 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      xf3[RR] = RX;
      yf3[RR] =  l1;
      zf3[RR] = RZ - 30 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      if(t >= 0.25){
        zf3[LF] = FZ - 30;
        zf3[RR] = RZ - 30;
        ulPreTime_Step = ulCurTime;
        walk_flag = 0;
        walk_dir = 0;
      }
      break;
  }
}

void start_straight(){
  walk_dir ='S';
  if(t> 0.25){
    t = 0.25;
    walk_flag = 1;
    ulPreTime_Step = ulCurTime;
  }
  //LF
  xf3[LF] = FX - 25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC))+ 25;
  yf3[LF] = l1;
  zf3[LF] = FZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
  
  //FR
  xf3[RF] = FX + 25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 25;
  yf3[RF] = l1;
  zf3[RF] = FZ - 30;
 
  //RL
  xf3[LR] = RX + 25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 25;
  yf3[LR] = l1;
  zf3[LR] = RZ  - 30;
  
  //RR
  xf3[RR] = RX - 25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
  yf3[RR] =  l1;
  zf3[RR] = RZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
   
}

void straight(){
  walk_dir ='S';
  if(walk_flag != 4 && walk_flag !=6){
    if( walk_flag >= 2){
      if(walk_flag == 2 && t >= 0.5){
        walk_flag = 3;
      }
      else if(walk_flag == 2 && ht >= 0.5){
        walk_flag = 5;
      }
      else if(walk_flag == 3 && t < 0.5){
        t = 0.0;
        ht = 0.5;
        walk_flag = 4;
      }
      else if(walk_flag == 5 && ht < 0.5){
        ht = 0.0; 
        t = 0.5;
        walk_flag = 6;
      }    
    }
    //LF
    xf3[LF] = FX - 50 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LF] = l1;
    zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[LF] = FZ - 30;
    }
  
    //FR
    xf3[RF] = FX - 50 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RF] = l1;
    zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[RF] = FZ - 30;
    }
   
    //RL
    xf3[LR] = RX - 50 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LR] = l1;
    zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[LR] = RZ - 30;
    }
  
    //RR
    xf3[RR] = RX - 50 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RR] =  l1;
    zf3[RR] = RZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[RR] = RZ - 30;
    }
  }

  else{    
    if(walk_flag == 4){
      if(ht < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        ht = 0;
        t = 0.5;
      }

    //LF
      xf3[LF] = FX - 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[LF] = l1;
      zf3[LF] = FZ + 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //FR
      xf3[RF] = FX - 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[RF] = l1;
      zf3[RF] = FZ - 30;
   
     //RL
      xf3[LR] = RX - 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[LR] = l1;
      zf3[LR] = RZ  - 30;

       //RR
      xf3[RR] = RX - 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[RR] =  l1;
      zf3[RR] = RZ + 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }

    else if(walk_flag == 6){
      if(t < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        t = 0.0;
        ht = 0.5;
      }

    //LF
      xf3[LF] = FX - 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[LF] = l1;
      zf3[LF] = FZ - 30;

      //FR
      xf3[RF] = FX - 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC) + 25);
      yf3[RF] = l1;
      zf3[RF] = FZ + 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
   
      //RL
      xf3[LR] = RX - 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[LR] = l1;
      zf3[LR] = RZ + 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

       //RR
      xf3[RR] = RX - 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 25;
      yf3[RR] =  l1;
      zf3[RR] = RZ - 30;

    }
    if(walk_flag == 0){
      ulPreTime_Step = ulCurTime;
      pre_walk_dir = 'S';
    }
  }
   
}

void start_clk(){
 walk_dir ='C';
  if(t> 0.25){
    t = 0.25;
    walk_flag = 1;
    ulPreTime_Step = ulCurTime;
  }
  //LF
    xf3[LF] = FX + 6.25  - 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));;
    yf3[LF] = l1 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 6.25;
    zf3[LF] = FZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
      
  //FR
    xf3[RF] = FX + 6.25 - 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RF] = l1 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 6.25;
    zf3[RF] = FZ  - 30;
 
  //RL

    xf3[LR] = RX - 6.25 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));;
    yf3[LR] = l1 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 6.25;
    zf3[LR] = RZ  - 30;

  
  //RR
    xf3[RR] = RX - 6.25 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));;
    yf3[RR] = l1 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 6.25;
    zf3[RR] = RZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

}



void clk(){
  walk_dir = 'C';
  if(walk_flag != 4 && walk_flag !=6){
    if( walk_flag >= 2){
      if(walk_flag == 2 && t >= 0.5){
        walk_flag = 3;
      }
      else if(walk_flag == 2 && ht >= 0.5){
        walk_flag = 5;
      }
      else if(walk_flag == 3 && t < 0.5){
        t = 0.0;
        ht = 0.5;
        walk_flag = 4;
      }
      else if(walk_flag == 5 && ht < 0.5){
        ht = 0.0; 
        t = 0.5;
        walk_flag = 6;
      }    
    }
  
    //LF
    xf3[LF] = FX - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LF] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[LF] = FZ - 30;
    }
  
    //FR
    xf3[RF] = FX  + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RF] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[RF] = FZ - 30;
    }
   
    //RL
    xf3[LR] = RX - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LR] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[LR] = RZ - 30;
    }
  
    //RR
    xf3[RR] = RX + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RR] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RR] = RZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[RR] = RZ - 30;
    }
  }

  else{
    if(walk_flag == 4){
      t = 0;
      if(ht < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        ht = 0.0;
      }
    //LF
 
      xf3[LF] = FX - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
      yf3[LF] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[LF] = FZ + 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //RR
       xf3[RR] = RX + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
       yf3[RR] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
       zf3[RR] = RZ + 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }

    else if(walk_flag == 6){
      ht = 0;
      if(t < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        t = 0.0;
      }
      //FR
      xf3[RF] = FX + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      yf3[RF] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[RF] = FZ + 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
   
      //RL
      xf3[LR] = RX - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));;
      yf3[LR] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[LR] = RZ + 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }
    
    if(walk_flag == 0){
      ulPreTime_Step = ulCurTime;
      pre_walk_dir = 'C';
    }
  }
  
}

void start_anti_clk(){
 walk_dir ='A';
  if(t> 0.25){
    t = 0.25;
    walk_flag = 1;
    ulPreTime_Step = ulCurTime;
  }
  //LF
    xf3[LF] = FX - 6.25  + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LF] = l1 - 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 6.25;
    zf3[LF] = FZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
      
  //FR
    xf3[RF] = FX  - 6.25 + 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RF] = l1 - 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 6.25;
    zf3[RF] = FZ  - 30;
 
  //RL

    xf3[LR] = RX + 6.25 - 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LR] = l1 - 6.25 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 6.25;
    zf3[LR] = RZ  - 30;

  
  //RR
    xf3[RR] = RX + 6.25 - 6.25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));;
    yf3[RR] = l1 - 6.25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 6.25;
    zf3[RR] = RZ - 50 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

}


void anti_clk(){
 walk_dir = 'A';

  if(walk_flag != 4 && walk_flag !=6){
    if( walk_flag >= 2){
      if(walk_flag == 2 && t >= 0.5){
        walk_flag = 3;
      }
      else if(walk_flag == 2 && ht >= 0.5){
        walk_flag = 5;
      }
      else if(walk_flag == 3 && t < 0.5){
        t = 0.0;
        ht = 0.5;
        walk_flag = 4;
      }
      else if(walk_flag == 5 && ht < 0.5){
        ht = 0.0; 
        t = 0.5;
        walk_flag = 6;
      }    
    }
    //LF
    xf3[LF] = FX + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LF] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[LF] = FZ - 30;
    }
    
    //FR
    xf3[RF] = FX - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RF] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[RF] = FZ - 30;
    }
   
    //RL
    xf3[LR] = RX + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[LR] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[LR] = RZ - 30;
    }

    //RR
    xf3[RR] = RX - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    yf3[RR] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RR] = RZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[RR] = RZ - 30;
    }

  } 

else{
    if(walk_flag == 4){
      t = 0;
      if(ht < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        ht = 0.0;
      }
      //LF
      xf3[LF] = FX + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
      yf3[LF] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[LF] = FZ + 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //RR
      xf3[RR] = RX - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
      yf3[RR] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[RR] = RZ + 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }
    else if(walk_flag == 6){
      ht = 0;
      if(t < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        t = 0.0;
      }

      //FR
      xf3[RF] = FX - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      yf3[RF] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[RF] = FZ + 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
   
      //RL
      xf3[LR] = RX + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      yf3[LR] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
      zf3[LR] = RZ + 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }
    if(walk_flag == 0){
      ulPreTime_Step = ulCurTime;
      pre_walk_dir = 'A';
    }
 }
}

void start_left_side(){
 walk_dir ='L';
  if(t> 0.25){
    t = 0.25;
    walk_flag = 1;
    ulPreTime_Step = ulCurTime;
  }
  //LF
  xf3[LF] = FX;
  yf3[LF] = l1 - 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
  zf3[LF] = FZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
  
  //FR
  xf3[RF] = FX;
  yf3[RF] = l1 - 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
  zf3[RF] = FZ - 30;
 
  //RL
  xf3[LR] = RX;
  yf3[LR] = l1 + 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
  zf3[LR] = RZ  - 30;
  
  //RR
  xf3[RR] = RX;
  yf3[RR] =  l1 + 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;;
  zf3[RR] = RZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
}


void left_side(){
  walk_dir = 'L';
  if(walk_flag != 4 && walk_flag != 6){
    if( walk_flag >= 2){
      if(walk_flag == 2 && t >= 0.5){
        walk_flag = 3;
      }
      else if(walk_flag == 2 && ht >= 0.5){
        walk_flag = 5;
      }
      else if(walk_flag == 3 && t < 0.5){
        t = 0;
        ht = 0.5;
        walk_flag = 4;
      }
      else if(walk_flag == 5 && ht < 0.5){
        ht = 0; 
        t = 0.5;
        walk_flag = 6;
      }    
    }

    //LF
    xf3[LF] = FX;
    yf3[LF] = l1 - 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[LF] = FZ - 30;
    }
  
    //FR
    xf3[RF] = FX;
    yf3[RF] = l1 + 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[RF] = FZ - 30;
    }

   
    //RL
    xf3[LR] = RX;
    yf3[LR] = l1 - 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[LR] = RZ - 30;
    }
  
    //RR
    xf3[RR] = RX;
    yf3[RR] = l1 + 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RR] = RZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[RR] = RZ - 30;
    }

  }

  else{
    if(walk_flag == 4){
      if(ht < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        ht = 0.0;
        t = 0.5;
      }
     //LF
      xf3[LF] = FX;
      yf3[LF] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[LF] = FZ- 30;

      //FR
      xf3[RF] = FX;
      yf3[RF] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
   
      //RL
      xf3[LR] = RX;
      yf3[LR] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //RR
      xf3[RR] = RX;
      yf3[RR] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[RR] = RZ - 30;
    }

    else if(walk_flag == 6){
      if(t < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        t = 0.0;
        ht = 0.5;
      }
       //LF
      xf3[LF] = FX;
      yf3[LF] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //FR
      xf3[RF] = FX;
      yf3[RF] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[RF] = FZ  - 30;
   
      //RL
      xf3[LR] = RX;
      yf3[LR] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[LR] = RZ - 30;

      //RR
      xf3[RR] = RX;
      yf3[RR] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[RR] = RZ  - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }
    
    if(walk_flag == 0){
      ulPreTime_Step = ulCurTime;
      pre_walk_dir = 'L';
    }
  }
  
}

void start_right_side(){
 walk_dir ='R';
  if(t> 0.25){
    t = 0.25;
    walk_flag = 1;
    ulPreTime_Step = ulCurTime;
  }
  //LF
  xf3[LF] = FX;
  yf3[LF] = l1 + 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
  zf3[LF] = FZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
  
  //FR
  xf3[RF] = FX;
  yf3[RF] = l1 + 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
  zf3[RF] = FZ - 30;
 
  //RL
  xf3[LR] = RX;
  yf3[LR] = l1 - 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
  zf3[LR] = RZ  - 30;
  
  //RR
  xf3[RR] = RX;
  yf3[RR] =  l1 - 12.5 * cos(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;;
  zf3[RR] = RZ - 50 * sin(4 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
}


void right_side(){
 walk_dir = 'R';

  if(walk_flag != 4 && walk_flag !=6){
   if( walk_flag >= 2){
      if(walk_flag == 2 && t >= 0.5){
        walk_flag = 3;
      }
      else if(walk_flag == 2 && ht >= 0.5){
        walk_flag = 5;
      }
      else if(walk_flag == 3 && t < 0.5){
        t = 0;
        ht = 0.5;
        walk_flag = 4;
      }
      else if(walk_flag == 5 && ht < 0.5){
        ht = 0; 
        t = 0.5;
        walk_flag = 6;
      }    
    }
    //LF
    xf3[LF] = FX;
    yf3[LF] = l1 + 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[LF] = FZ - 30;
    }
    
    //FR
    xf3[RF] = FX;
    yf3[RF] = l1 - 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[RF] = FZ - 30;
    }
   
    //RL
    xf3[LR] = RX;
    yf3[LR] = l1 + 25 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(t >= 0.5){
      zf3[LR] = RZ - 30;
    }

    //RR
    xf3[RR] = RX;
    yf3[RR] = l1 - 25 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC));
    zf3[RR] = RZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
    if(ht >= 0.5){
      zf3[RR] = RZ - 30;
    }

  } 

else{
    if(walk_flag == 4){
      if(ht < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        ht = 0.0;
        t = 0.5;
      }
      //LF
      xf3[LF] = FX;
      yf3[LF] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[LF] = FZ- 30;

      //FR
      xf3[RF] = FX;
      yf3[RF] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[RF] = FZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;
   
      //RL
      xf3[LR] = RX;
      yf3[LR] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[LR] = RZ - 80 * sin(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //RR
      xf3[RR] = RX;
      yf3[RR] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[RR] = RZ - 30;

    }
    else if(walk_flag == 6){
      if(t < 0.5){
        walk_flag = 0;
        walk_dir = 'P';
        t = 0.0;
        ht = 0.5;
      }
      //LF
      xf3[LF] = FX;
      yf3[LF] = l1 + 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[LF] = FZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

      //FR
      xf3[RF] = FX;
      yf3[RF] = l1 - 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) + 12.5;
      zf3[RF] = FZ - 30;
   
      //RL
      xf3[LR] = RX;
      yf3[LR] = l1 + 12.5 * cos(2 * M_PI * t / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[LR] = RZ - 30;

      //RR
      xf3[RR] = RX;
      yf3[RR] = l1 - 12.5 * cos(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 12.5;
      zf3[RR] = RZ - 80 * sin(2 * M_PI * ht / (ulPeriod_Step * _1MSEC_TO_1SEC)) - 30;

    }
    if(walk_flag == 0){
      ulPreTime_Step = ulCurTime;
      pre_walk_dir = 'R';
    }
 }
}

void way(){
 
    if(walk_dir == 'S' || walk_flag == 0)
    {
      if(walk_flag == 0){
        start_straight();
      }
      else{
        straight();
      }
    }
   
}

void clk_way(){
 
    if(walk_dir == 'C' || walk_flag == 0)
    {
      if(walk_flag == 0){
        start_clk();
      }
      else{
        clk();
      }
    }
   
}

void anti_clk_way(){
 
    if(walk_dir == 'A' || walk_flag == 0)
    {
      if(walk_flag == 0){
        start_anti_clk();
      }
      else{
        anti_clk();
      }
    }
   
}
