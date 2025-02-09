#include "string.h"
#include "as5047p.h"
#include "imitate_spi.h"
#include "cmd.h"
AS5047P wheel_x,wheel_y;
float diameter_x=52.50,diameter_y=52.50;

float limit_in_180(float value){
  while(value>180)
  value -= 360;
  while(value<-180)
  value += 360;
  return value;
}
float limit_in_360(float value){
  while(value>360)
  value -= 360;
  while(value<-360)
  value += 360;
  return value;
}
float delta_limit_in_360(float value){
  while(value>180)
  value -= 360;
  while(value<-180)
  value += 360;
  return value;
}
uint16_t as5047p_Get_Position_x(){
  uint8_t readBuffer[2]={1,1};
  //uint8_t writeBuffer1[2]={0x40,0x01};
  uint8_t writeBuffer2[2]={0xff,0xff};
  ispi1_write_read(writeBuffer2, readBuffer,2);
  uint16_t position=(uint16_t)((readBuffer[0]&0x3f)*256+readBuffer[1]);
  return position;
}
uint16_t as5047p_Get_Position_y(){
  uint8_t readBuffer[2]={1,1};
  // uint8_t writeBuffer1[2]={0x40,0x01};
  uint8_t writeBuffer2[2]={0xff,0xff};
  ispi3_write_read(writeBuffer2, readBuffer,2);
  uint16_t position=(uint16_t)((readBuffer[0]&0x3f)*256+readBuffer[1]);
  return position;
}
void as5047p_init(){
  memset(&wheel_x,0,sizeof(AS5047P));
  memset(&wheel_y,0,sizeof(AS5047P));
 
  wheel_x.zero_position = as5047p_Get_Position_x()*360/16384; 
  wheel_x.last_position = wheel_x.zero_position;
  wheel_x.now_position = wheel_x.zero_position;
  
  wheel_y.zero_position = as5047p_Get_Position_y()*360/16384; 
  wheel_y.last_position = wheel_y.zero_position;
  wheel_y.now_position = wheel_y.zero_position;
  uprintf("as5047p init done\r\n");
}

void Get_Basic_x(){

  //now_position 
  wheel_x.now_position = (float)as5047p_Get_Position_x()*360/16384; 
  //now_speed 
  wheel_x.now_speed = wheel_x.now_position - wheel_x.last_position;  
  while(wheel_x.now_speed > 180)
    wheel_x.now_speed-=360;
  while(wheel_x.now_speed < -180)
    wheel_x.now_speed+=360;  
  //now_speed
  wheel_x.circlesum += wheel_x.now_speed;
  //angle计算
  if(wheel_x.now_position<wheel_x.zero_position){
    wheel_x.now_angle = wheel_x.now_position + 360 - wheel_x.zero_position;}
  else{ 
    wheel_x.now_angle = wheel_x.now_position - wheel_x.zero_position;}
  //circlesum计算
  if((wheel_x.circlesum>360)){
    wheel_x.now_circlenum +=1;
    wheel_x.circlesum =wheel_x.circlesum - 360;
  }  
  if((wheel_x.circlesum<-360)){
    wheel_x.now_circlenum -=1;
    wheel_x.circlesum =wheel_x.circlesum + 360;
  }  
}
void Get_Basic_y(){
  //now_position 
  wheel_y.now_position = (float)as5047p_Get_Position_y()*360/16384; 
  //now_speed 
  wheel_y.now_speed = wheel_y.now_position - wheel_y.last_position;  
  while(wheel_y.now_speed > 180)
    wheel_y.now_speed-=360;
  while(wheel_y.now_speed < -180)
    wheel_y.now_speed+=360;  
  //now_speed
  wheel_y.circlesum += wheel_y.now_speed;
  //angle计算
  if(wheel_y.now_position<wheel_y.zero_position){
    wheel_y.now_angle = wheel_y.now_position + 360 - wheel_y.zero_position;}
  else{
    wheel_y.now_angle = wheel_y.now_position - wheel_y.zero_position;}
  //circlesum计算
  if((wheel_y.circlesum>360)){
    wheel_y.now_circlenum +=1;
    wheel_y.circlesum =wheel_y.circlesum - 360;
  }  
  if((wheel_y.circlesum<-360)){
    wheel_y.now_circlenum -=1;
    wheel_y.circlesum =wheel_y.circlesum + 360;
  }   
}

void Get_Wheel_x(){
  Get_Basic_x();
  float cnt = wheel_x.now_speed/360;
  wheel_x.delta_distance= (float)3.1415926 * diameter_x * cnt ;
  // wheel_x.full_distance= 3.1415926 * diameter_x * (wheel_x.now_circlenum + wheel_x.circlesum/360);
  wheel_x.full_distance += wheel_x.delta_distance;
  //last变量赋值
  wheel_x.last_position = wheel_x.now_position;
  wheel_x.last_angle = wheel_x.now_angle;
  wheel_x.last_circlenum = wheel_x.now_circlenum;
}

void Get_Wheel_y(){
  Get_Basic_y();
  float cnt = wheel_y.now_speed/360;
  wheel_y.delta_distance= 3.1415926 * diameter_y * cnt ;
  // wheel_y.full_distance= 3.1415926 * diameter_y * (wheel_y.now_circlenum + limit_in_360(wheel_y.circlesum)/360);
  wheel_y.full_distance += wheel_y.delta_distance;
  //last变量赋值
  wheel_y.last_position = wheel_y.now_position;
  wheel_y.last_angle = wheel_y.now_angle;
  wheel_y.last_circlenum = wheel_y.now_circlenum;
}

void Show_Wheel_x()
{
  uprintf("**************xwheel************\r\n");
  uprintf("zero_position=%f\r\n",wheel_x.zero_position); 
  uprintf("now_position=%f\r\n",wheel_x.now_position); 
  uprintf("last_position=%f\r\n",wheel_x.last_position); 
  uprintf("now_speed=%f\r\n",wheel_x.now_speed); 
  uprintf("now_angle=%f\r\n",wheel_x.now_angle); 
  uprintf("last_angle=%f\r\n",wheel_x.last_angle); 
  uprintf("circlesum=%f\r\n",wheel_x.circlesum); 
  uprintf("now_circlenum=%d\r\n",wheel_x.now_circlenum); 
  uprintf("last_circlenum=%d\r\n",wheel_x.last_circlenum); 
  uprintf("delta_distance=%f\r\n",wheel_x.delta_distance); 
  uprintf("**************xwheel************\r\n");
}
void Show_Wheel_y()
{
  uprintf("**************ywheel************\r\n");
  uprintf("zero_position=%f\r\n",wheel_y.zero_position); 
  uprintf("now_position=%f\r\n",wheel_y.now_position); 
  uprintf("last_position=%f\r\n",wheel_y.last_position); 
  uprintf("now_speed=%f\r\n",wheel_y.now_speed); 
  uprintf("now_angle=%f\r\n",wheel_y.now_angle); 
  uprintf("last_angle=%f\r\n",wheel_y.last_angle); 
  uprintf("circlesum=%f\r\n",wheel_y.circlesum); 
  uprintf("now_circlenum=%d\r\n",wheel_y.now_circlenum); 
  uprintf("last_circlenum=%d\r\n",wheel_y.last_circlenum); 
  uprintf("delta_distance=%f\r\n",wheel_y.delta_distance); 
  uprintf("**************ywheel************\r\n");
}