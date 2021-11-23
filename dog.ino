/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#define _MAIN_

#include "dynamixel_driver.h"
#include "dynamixel_tool.h"
#include "dynamixel_item.h"
#include "dynamixel_workbench.h"
#include "walk.h"
#include "variable.h"
#include <math.h>
#include <Wire.h>



#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define RUN_RATE 100000

// in microseconds; should give 0.5Hz toggles
#define RIDAR 0x40
volatile unsigned int TimSec=0;
HardwareTimer Timer(1);


DynamixelWorkbench dxl_wb;
DynamixelDriver dxl_dv;

int delay_flag = 0;



int iTargetAngle[MAX_LEG_NUM][MAX_JOINT_NUM] = {{0,}, };
int iOffsetAngle[4][3] = {{0, 38 , -4 }, {0, 38, -4}, {0 ,38, -4 }, {0, 38, -4 }};
  
float bt_val;
bool btflag = 0;
bool dir_flag = 0;

double roll, pitch, yaw;
double a_roll, a_pitch, a_yaw;
int pp=0;
void setup() 
{
  Serial.begin(57600);
  Serial4.begin(115200);
  Serial2.begin(9600);
  Wire.begin();
  // while(!Serial); // Wait for Opening Serial Monitor

  const char *log;
  bool result = false;
  int i;

  uint16_t model_number = 0;

  
  walk_flag = 0;
  walk_dir = 0;
  ulPeriod_Step = 1000;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);

  for(i = 0; i < 12; i++)
  {
    
    result = dxl_wb.ping(i+1, &model_number, &log);
   
    result = dxl_wb.jointMode(i+1, 60, 0, &log);
    
  }
  for (int iLeg = 0 ; iLeg < 4 ; iLeg++)
  {
    for (int iAxis = 0 ; iAxis < 3 ; iAxis++)
    {
      switch(iLeg){
        case LF:
          switch(iAxis){
            case JOINT_1:
              iTargetAngle[LF][JOINT_1] = 185 - iOffsetAngle[LF][JOINT_1];
              break;
            case JOINT_2:
              iTargetAngle[LF][JOINT_2] = 270 + iOffsetAngle[LF][JOINT_2];
              break;
            case JOINT_3:
              iTargetAngle[LF][JOINT_3] = 180 - iOffsetAngle[LF][JOINT_3];
              break;
          }
          break;
        case RF:
          switch(iAxis){
            case JOINT_1:
              iTargetAngle[RF][JOINT_1] = 175 + iOffsetAngle[RF][JOINT_1];
              break;
            case JOINT_2:
              iTargetAngle[RF][JOINT_2] = 90 - iOffsetAngle[RF][JOINT_2];
              break;
            case JOINT_3:
              iTargetAngle[RF][JOINT_3] = 180 + iOffsetAngle[RF][JOINT_3];
              break;
          }
          break;
        case LR:
          switch(iAxis){
            case JOINT_1:
              iTargetAngle[LR][JOINT_1] = 175 + iOffsetAngle[LR][JOINT_1];
              break;
            case JOINT_2:
              iTargetAngle[LR][JOINT_2] = 90 - iOffsetAngle[LR][JOINT_2];
              break;
            case JOINT_3:
              iTargetAngle[LR][JOINT_3] = 180 + iOffsetAngle[LR][JOINT_3];
              break;
          }
          break;
        case RR:
          switch(iAxis){
            case JOINT_1:
              iTargetAngle[RR][JOINT_1] = 185 - iOffsetAngle[RR][JOINT_1];
              break;
            case JOINT_2:
              iTargetAngle[RR][JOINT_2] = 270 + iOffsetAngle[RR][JOINT_2];
              break;
            case JOINT_3:
              iTargetAngle[RR][JOINT_3] = 180 - iOffsetAngle[RR][JOINT_3];
              break;
          }
          break;
      }
      dxl_wb.ping(3*iLeg+iAxis+1, &model_number, &log);
      dxl_wb.jointMode(3*iLeg+iAxis+1, 60, 0, &log);
      dxl_wb.goalPosition(3*iLeg+iAxis+1, (int)iTargetAngle[iLeg][iAxis]);
      pre_pos[3*iLeg+iAxis] = iTargetAngle[iLeg][iAxis];
    }
  }

  delay(3000);
/*
  pre_pos[0] = fl_1[6];
  pre_pos[1] = fl_2[6];
  pre_pos[2] = fl_3[6];

  pre_pos[3] = fr_1[0];
  pre_pos[4] = fr_2[0];
  pre_pos[5] = fr_3[0];

  pre_pos[6] = rl_1[0];
  pre_pos[7] = rl_2[0];
  pre_pos[8] = rl_3[0];

  pre_pos[9] = rr_1[6];
  pre_pos[10] = rr_2[6];
  pre_pos[11] = rr_3[6];
  
*/ 

  ulCurTime = millis();
}
void loop()
{
  const char *log;
  bool result;
  uint16_t model_number;
  if(Serial2.available()){
    
    bt_val = bt();
  }
  Rider();

  
  if(ulCurTime - ulPreTime_Step >= ulPeriod_Step){
    ulPreTime_Step = ulCurTime;
    if(delay_flag > 0)
      delay_flag --;
  }
  ulCurTime = millis();

  
  t = (double)((ulCurTime - ulPreTime_Step) % ulPeriod_Step) * _1MSEC_TO_1SEC;
  ht = (double)((ulCurTime + 500 - ulPreTime_Step) % ulPeriod_Step) * _1MSEC_TO_1SEC;
  /*SerialUSB.print(walk_dir);
  SerialUSB.print("/");
  SerialUSB.print(walk_flag);
  SerialUSB.print("/");
  
  SerialUSB.print(FrontV_Dist);
  SerialUSB.print("/");
  SerialUSB.println(FrontH_Dist);*/
  if(!btflag){
    pp++;
    Serial.println(yaw);
  }
  if(btflag){
    Serial.print(bt_val);
    Serial.print("-");
    Serial.print(yaw);
    Serial.print("=");
    Serial.println(bt_val - yaw);
  if(walk_dir == 'P'){
      spot();
      if(walk_dir == 0)
        delay_flag = 2;
  }
  else if(delay_flag){
    ;
  }
  else{
    if((abs(bt_val - yaw) > 20.0) && (abs(bt_val - yaw) < 340.0)&& (dir_flag == 1)){
      if(abs(bt_val - yaw) <= 180.0){
        if(bt_val > yaw){
         if(walk_dir == 'C' || walk_flag == 0)
         {
           clk_way();
         }
         else{
           if(walk_flag == 1)
             walk_flag = 2;
             
           if(walk_dir == 'A'){
             anti_clk();
           }
           else{
             way();
             Serial.println(walk_dir);
           }
         
         }     
        }
        else{
         if(walk_dir == 'A' || walk_flag == 0)
         {
           anti_clk_way();
         }
         else{
           if(walk_flag == 1)
             walk_flag = 2;
           
           if(walk_dir == 'C'){
             clk();
           }
           else{
             way();
             Serial.println(walk_dir);
           }
         }
        }
      }
      else{
        if(bt_val > yaw){
         if(walk_dir == 'A' || walk_flag == 0)
         {
           anti_clk_way();
         }
         else{
           if(walk_flag == 1)
             walk_flag = 2;
             
           if(walk_dir == 'C'){
             clk();
           }
           else{
             way();
             Serial.println(walk_dir);
           }
         
         }     
        }
        else{
         if(walk_dir == 'C' || walk_flag == 0)
         {
           clk_way();
         }
         else{
           if(walk_flag == 1)
             walk_flag = 2;
           
           if(walk_dir == 'A'){
             anti_clk();
           }
           else{
             way();
             Serial.println(walk_dir);
           }
         }
        }
      }
     }
     else{
      if((walk_dir != 'C' && walk_dir != 'A') || walk_flag == 0)
      {
        way();
        Serial.println(walk_dir);
      }
      else if(dir_flag == 1){
        if(walk_dir == 'C'){
          clk();
          if((bt_val >= 5.0 && bt_val - yaw <= 5.0) || (bt_val < 5 && yaw - bt_val > 355.0)){
          //if(bt_val < yaw ){
            walk_flag = 2;
            /*SerialUSB.print("/");
            SerialUSB.print(yaw);
            SerialUSB.println("/");*/
          }
        }
        else if(walk_dir == 'A'){
          anti_clk();
          if((bt_val <= 355.0 && yaw - bt_val <= 5.0) || (bt_val > 355.0 && bt_val - yaw > 355.0)){
          //if(yaw < bt_val){
            walk_flag = 2;
            dir_flag = 0;
            /*SerialUSB.print("/");
            SerialUSB.print(yaw);
            SerialUSB.println("/");*/
          }
        }
      }
      else{
        if(walk_dir == 'C')
          clk_way();
        else if(walk_dir == 'A')
          anti_clk_way();

        if(walk_dir == 0){
          dir_flag = 0;
        }
      }
     }
   }
    /*SerialUSB.print(walk_dir);
    SerialUSB.print("//");
    SerialUSB.println(walk_flag);*/
  
   for(int i = 0; i < MAX_LEG_NUM; i++){
    double x3 = xf3[i];
    double y3 = yf3[i];
    double z3 = zf3[i];
    ConvertAngle(i, &y3, &z3);
    
    switch(i){
      case LF:
      case RF:
        f1 = (atan(y3 / z3) - asin(l1 / sqrt(y3*y3 + z3*z3)));
        yf1 = y3 - l1 * cos(f1);
        zf1 = z3 + l1 * sin(f1);
        f3 = asin((x3 * x3 + y3 * y3 + z3 * z3 - (l1*l1 + l2*l2 + l3*l3 + l4*l4)) / (2 * l2 * sqrt(l3*l3 + l4*l4))) - asin(l3 / sqrt(l3*l3 + l4*l4));
        f2 = -atan(x3 / sqrt(yf1*yf1 + zf1*zf1)) + acos((l2 + l3*cos(f3) + l4*sin(f3))/sqrt(x3*x3 + yf1*yf1 + zf1*zf1));

        if(i == RF){
          fr_1 = (175 - f1 * 180 / M_PI);
          fr_2 = (90 - f2 * 180 / M_PI);
          fr_3 = (180 - f3 * 180 / M_PI);
        }
        else{
          fl_1 = (185 + f1 * 180 / M_PI);
          fl_2 = (270 + f2 * 180 / M_PI);
          fl_3 = (180 + f3 * 180 / M_PI);
        }
        break;
      
      case LR:
      case RR:
   
        r1 = atan(y3 / z3) - asin(l1 / (sqrt(y3*y3 + z3*z3)));
        yf1 = y3 - l1 * cos(r1);
        zf1 = z3 + l1 * sin(r1);
        r3 = asin((x3 * x3 + y3 * y3 + z3 * z3 - (l1*l1 + l2*l2 + l3*l3 + l4*l4)) / (2 * l2 * sqrt(l3*l3 + l4*l4))) - asin(l3 / sqrt(l3*l3 + l4*l4));
        r2 = atan(x3 / sqrt(yf1*yf1 + zf1*zf1)) + acos((l2 + l3*cos(r3) + l4*sin(r3))/sqrt(x3*x3 + yf1*yf1 + zf1*zf1));

        if(i == RR){
          rr_1 = (185 + r1 * 180 / M_PI);
          rr_2 = (270 + r2 * 180 / M_PI);
          rr_3 = (180  + r3 * 180 / M_PI); 
        }
        else{
          rl_1 = (175 - r1 * 180 / M_PI);
          rl_2 = (90 - r2 * 180 / M_PI);
          rl_3 = (180 - r3 * 180 / M_PI);   
        }
    }
   }

   next_pos[0] = fl_1;
   next_pos[1] = fl_2;
   next_pos[2] = fl_3;

   next_pos[3] = fr_1;
   next_pos[4] = fr_2;
   next_pos[5] = fr_3;

   next_pos[6] = rl_1;
   next_pos[7] = rl_2;
   next_pos[8] = rl_3;
  
   next_pos[9] = rr_1;
   next_pos[10] = rr_2;
   next_pos[11] = rr_3;
  
  
   result |= dxl_wb.writeRegister((uint8_t)1, "Profile_Velocity", (int32_t)( abs(next_pos[0] - pre_pos[0])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)2, "Profile_Velocity", (int32_t)( abs(next_pos[1] - pre_pos[1])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)3, "Profile_Velocity", (int32_t)( abs(next_pos[2] - pre_pos[2])/(1.374 * (ulCurTime - ulPreTime))),&log);
  
   result |= dxl_wb.writeRegister((uint8_t)4, "Profile_Velocity", (int32_t)( abs(next_pos[3] - pre_pos[3])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)5, "Profile_Velocity", (int32_t)( abs(next_pos[4] - pre_pos[4])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)6, "Profile_Velocity", (int32_t)( abs(next_pos[5] - pre_pos[5])/(1.374 * (ulCurTime - ulPreTime))),&log);
  
   result |= dxl_wb.writeRegister((uint8_t)7, "Profile_Velocity", (int32_t)( abs(next_pos[6] - pre_pos[6])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)8, "Profile_Velocity", (int32_t)( abs(next_pos[7] - pre_pos[7])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)9, "Profile_Velocity", (int32_t)( abs(next_pos[8] - pre_pos[8])/(1.374 * (ulCurTime - ulPreTime))),&log);
  
   result |= dxl_wb.writeRegister((uint8_t)10, "Profile_Velocity", (int32_t)( abs(next_pos[9] - pre_pos[9])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)11, "Profile_Velocity", (int32_t)( abs(next_pos[10] - pre_pos[10])/(1.374 * (ulCurTime - ulPreTime))),&log);
   result |= dxl_wb.writeRegister((uint8_t)12, "Profile_Velocity", (int32_t)( abs(next_pos[11] - pre_pos[11])/(1.374 * (ulCurTime - ulPreTime))),&log);
   if(result == false){
    for(int i = 0; i< 12; i++){
      result = dxl_wb.ping(i+1, &model_number, &log);
      result = dxl_wb.jointMode(i+1,(int32_t)( abs(next_pos[11] - pre_pos[11])/(1.374 * (ulCurTime - ulPreTime))) , 0, &log);
      Serial.println("e");
    }
    return;
   }
   
   dxl_wb.goalPosition(1, (int)next_pos[0]);
   dxl_wb.goalPosition(2, (int)next_pos[1]);
   dxl_wb.goalPosition(3, (int)next_pos[2]);
  
   dxl_wb.goalPosition(4, (int)next_pos[3]);
   dxl_wb.goalPosition(5, (int)next_pos[4]);
   dxl_wb.goalPosition(6, (int)next_pos[5]);
  
   dxl_wb.goalPosition(7, (int)next_pos[6]);
   dxl_wb.goalPosition(8, (int)next_pos[7]);
   dxl_wb.goalPosition(9, (int)next_pos[8]);
  
   dxl_wb.goalPosition(10, (int)next_pos[9]);
   dxl_wb.goalPosition(11, (int)next_pos[10]);
   dxl_wb.goalPosition(12, (int)next_pos[11]);
  
  
  
   for(int i = 0; i< 12; i++){
    pre_pos[i] = next_pos[i];
  
   }
  }
  ulPreTime = ulCurTime;
  
}
float bt(){
  char buf[6];
  int flag = 3;
  int j = 0;
  Serial.println("==============================================");
  for(int i = 0; flag != 2 && j < 50; j++){
    if(Serial2.available()){
      buf[i] = Serial2.read();
      if(buf[i] == '.'){
        flag = 0;
      }
      else if(flag < 2) flag++;
      i++;
    }
    delay(1);
  }
  if(!btflag){
    Timer.pause();
    // Set up period
    Timer.setPeriod(RUN_RATE); // in microseconds
    // Set up an interrupt on channel 1
    Timer.attachInterrupt(imu);
    // Refresh the timer's count, prescale, and overflow
    Timer.refresh();
    // Start the timer counting
    Timer.resume();
  }
  btflag = 1;
  dir_flag = 1;
  Serial.println(j);
  Serial.println("===================================================");
  return atof(buf);
}

void imu()
{
  float deg[3];
  
  readSerial(deg);
  a_roll += deg[0];
  roll = deg[0];
  a_pitch += deg[1];
  pitch = deg[1];
  yaw = deg[2] + 180.0;
}

void ConvertAngle(int iLeg, double *y, double *z){
  
  switch(iLeg){
    case LF:
    case RF:
      *z = *z - 0.5 * H * sin(a_pitch * PI / 1800.0);
      break;
    case LR:
    case RR:
      *z = *z + 0.5 * H * sin(a_pitch * PI / 1800.0);
      break;
  }
    switch(iLeg){
    case LF:
    case LR:
      *z = *z - 0.5 * H * sin(a_roll * PI / 1800.0);
      //*y = *y - *z * sin(roll * PI / 180);
      break;
    case RF:
    case RR:
      *z = *z + 0.5 * H * sin(a_roll * PI / 1800.0);
      //*y = *y + *z * sin(roll * PI / 180);
      break;
  }
  if(*z > 430)  *z = 430;
  else if(*z < 200) *z = 200;
  if(*y > 200) *y = 200;
  else if(*y < -200) *y = -200;
}

void readSerial(float *deg)
{
  String str = "";
  char cTemp;
  int count = 0;
  while(1){
    while(!Serial4.available()) delay(1);
    if(Serial4.read() == '*') break;
  }
    
   while(1)
   {
      while(!Serial4.available()) delay(1);
      cTemp = Serial4.read();
      if(cTemp == '\r'){
        *(deg+count) = str.toFloat();
        continue;
      }
      else if(cTemp == ','){
        *(deg+count) = str.toFloat();
        str = "";
        count ++;
        continue;
      }
      else if(cTemp == '\n')  break;
      str.concat(cTemp);
   }
}


void Rider(){
  Wire.requestFrom(RIDAR, 10);

  while(!Wire.available());

  FrontV_Dist = ((Wire.read() & 0xFF) << 8) | (Wire.read() & 0xFF);
  FrontH_Dist = ((Wire.read() & 0xFF) << 8) | (Wire.read() & 0xFF);
  Right_Dist = ((Wire.read() & 0xFF) << 8) | (Wire.read() & 0xFF);
  Rear_Dist = ((Wire.read() & 0xFF) << 8) | (Wire.read() & 0xFF);
  Left_Dist = ((Wire.read() & 0xFF) << 8) | (Wire.read() & 0xFF);  
  
  /*SerialUSB.print(FrontV_Dist);
  SerialUSB.print("/");
  SerialUSB.print(FrontH_Dist);
  SerialUSB.print("/");
  SerialUSB.print(Right_Dist);
  SerialUSB.print("/");
  SerialUSB.print(Rear_Dist);
  SerialUSB.print("/");
  SerialUSB.println(Left_Dist);*/
}
