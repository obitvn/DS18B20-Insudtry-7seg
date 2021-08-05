/**
******************************************************************************
* @file    Project/main.c 
* @author  MCD Application Team
* @version V2.2.0
* @date    30-September-2014
* @brief   Main program body
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
*
* Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
* You may not use this file except in compliance with the License.
* You may obtain a copy of the License at:
*
*        http://www.st.com/software_license_agreement_liberty_v2
*
* Unless required by applicable law or agreed to in writing, software 
* distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************
*/ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "DS18x20.h"


volatile uint32_t f_cpu;
volatile uint32_t time_keeper=0;
int dem=0;

uint16_t time_update_temp;
volatile uint8_t count_time, start=0;

uint8_t mode; 
uint16_t set_time_minute;
float set_temp_max, set_temp_min;

uint32_t count_ms_time, count_ms_minute;
volatile uint8_t count_led;
float temp_ds18b20, now_temp;

uint16_t min;
uint16_t max;
uint16_t int_temp;


void quet_led(uint8_t number)
{     
  
  if(number==0)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
  }
  else if(number==1)
  {
    GPIO_WriteHigh(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
  }
  else if(number==2)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteLow(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
  }
  else if(number==3)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
  }
  else if(number==4)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteHigh(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
  }
  else if(number==5)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
  }
  else if(number==6)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteLow(GPIOC, GPIO_PIN_4); //E
  }
  else if(number==7)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2); //G
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
  }
  else if(number==8)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteLow(GPIOC, GPIO_PIN_4); //E 
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
  }
  else if(number==9)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteLow(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteLow(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteLow(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteLow(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteLow(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
  }
  else
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_4); //E
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1); //DP
    GPIO_WriteHigh(GPIOD, GPIO_PIN_0); //A
    GPIO_WriteHigh(GPIOC, GPIO_PIN_7); //B
    GPIO_WriteHigh(GPIOC, GPIO_PIN_3); //F
    GPIO_WriteHigh(GPIOC, GPIO_PIN_6); //C
    GPIO_WriteHigh(GPIOC, GPIO_PIN_5); //D
    GPIO_WriteHigh(GPIOC, GPIO_PIN_2); //G
  }
  
}



static void clk_config_16MHz_hsi(void)
{
  /* De-initialized clock control */
  CLK_DeInit();
  /* Enable HSE */
  CLK_HSECmd(ENABLE);
  /* Wait until HSE has been ready */
  while(CLK_GetFlagStatus(CLK_FLAG_HSERDY) != SET);
  /* Switch clock source to HSE and disable HSI (Auto mode) */
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
  /* Wait until HSE is chosen as SYSCLK Source */
  while(CLK_GetSYSCLKSource() != CLK_SOURCE_HSE);
  /* Stop clock switch */
  CLK_ClockSwitchCmd(DISABLE);
  /* Prescale of SYSCLK Source as 1 (not divided) */
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
}






void delay_using_timer4_init(void)
{
  TIM4_TimeBaseInit(TIM4_PRESCALER_128,124);//1ms if fMaster=16Mhz
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
  
  enableInterrupts();
  TIM4_Cmd(DISABLE);
}

void delay_isr(void)
{
  if(TIM4_GetITStatus(TIM4_IT_UPDATE)==SET)
  {
    if(time_keeper!=0)
    {
      time_keeper--;
    }
    else
    {
      /* Disable Timer to reduce power consumption */
      TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
    }
    TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
  }
}


void delay_ms(uint32_t time)
{
  time_keeper=time;
  
  /* Reset Counter Register value */
  TIM4->CNTR = (uint8_t)(0);
  
  /* Enable Timer */
  TIM4->CR1 |= TIM4_CR1_CEN;
  
  while(time_keeper);
}

void display_temp(float temp)
{
  float dis_temp;
  dis_temp = temp*10; 
  GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
  uint8_t a, b, c;
  a = (int)dis_temp/100;
   b= (int)dis_temp%100/10;
   c=(int)dis_temp%10;
  if(count_led>2) count_led=0; //da quet het led
  if(count_led==0)
  {
    quet_led(20); //clear led
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
    GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
    GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
    GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
    
    quet_led(a);
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    GPIO_WriteHigh(GPIOD, GPIO_PIN_3); //2
    count_led++;
    //break;
  }
  else if(count_led==1)
  {
    quet_led(20); //clear led
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
    GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
    GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
    
    GPIO_WriteLow(GPIOC, GPIO_PIN_1);
    quet_led(b);
    GPIO_WriteHigh(GPIOD, GPIO_PIN_2); //3
    GPIO_WriteLow(GPIOC, GPIO_PIN_1);
    count_led++;
    //break;
  }
  else if(count_led==2)
  {
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
    quet_led(20); //clear led
    GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
    GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
    GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
    GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
    //GPIO_WriteLow(GPIOC, GPIO_PIN_1);
    quet_led(c);
    //GPIO_WriteLow(GPIOC, GPIO_PIN_1);
    GPIO_WriteHigh(GPIOD, GPIO_PIN_1); //4
    count_led++;
    
    //break;
  }
}

void display_time(uint16_t time)
{
 
  
  switch (count_time)
  {
  case 0:
    {
      GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
      
      GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
      GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
      GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
      GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
      quet_led(20); //clear led
      GPIO_WriteHigh(GPIOD, GPIO_PIN_4); //2
      quet_led(time/1000);
      count_time++;
      break;
    }
  case 1:
    {
      GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
      
      GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
      GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
      GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
      GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
      quet_led(20); //clear led
      GPIO_WriteHigh(GPIOD, GPIO_PIN_3); //2
      quet_led(time%1000/100);
      count_time++;
      break;
    }
  case 2:
    {
      GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
      
      GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
      GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
      GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
      GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
      quet_led(20); //clear led
      GPIO_WriteHigh(GPIOD, GPIO_PIN_2); //3
      quet_led((time%100/10));
      count_time++;
      break;
    }
  case 3:
    {
      GPIO_WriteHigh(GPIOC, GPIO_PIN_1);
      
      GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
      GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
      GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
      GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
      quet_led(20); //clear led
      GPIO_WriteHigh(GPIOD, GPIO_PIN_1); //4
      quet_led((time%10));
      count_time++;
      break;
    }
  }
}

void blynk_wait()
{
  GPIO_WriteHigh(GPIOD, GPIO_PIN_1); //4
  GPIO_WriteHigh(GPIOD, GPIO_PIN_2); //3
  GPIO_WriteHigh(GPIOD, GPIO_PIN_3); //1
  GPIO_WriteHigh(GPIOD, GPIO_PIN_4); //2
  GPIO_WriteLow(GPIOC, GPIO_PIN_2); //G
  delay_ms(100);
  GPIO_WriteLow(GPIOD, GPIO_PIN_1); //4
  GPIO_WriteLow(GPIOD, GPIO_PIN_2); //3
  GPIO_WriteLow(GPIOD, GPIO_PIN_3); //1
  GPIO_WriteLow(GPIOD, GPIO_PIN_4); //2
  quet_led(20); //clear led
}

void control_relay_temp(float temp_min, float temp_max, float real_temp)
{
  min =(uint16_t) temp_min*10;
  max = (uint16_t) temp_max*10;
  int_temp = (uint16_t) real_temp*10;
  if(max>int_temp)
  {
    if(int_temp>min)
      GPIO_WriteHigh(GPIOD, GPIO_PIN_6);
    else
      GPIO_WriteLow(GPIOD, GPIO_PIN_6);
  }
  else GPIO_WriteLow(GPIOD, GPIO_PIN_6);
}

void control_relay_time(uint32_t set_time, uint32_t time_now)
{
  if(set_time>time_now)
  {
    GPIO_WriteHigh(GPIOD, GPIO_PIN_7);
  }
  else
  {
    GPIO_WriteLow(GPIOD, GPIO_PIN_7);
    
  }
}



void timer2_init(void)
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_128,124);//1ms if fMaster=16Mhz
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);
  TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);
  enableInterrupts();
  TIM2_Cmd(ENABLE);
}

void wirte_flash_set_temp_max(float temp) // luu nhiet do
{
  uint16_t write_temp=0;
  write_temp = temp*10;
  //FLASH_DeInit();
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_TPROG);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  
  FLASH_EraseByte(0x4006);
  FLASH_ProgramByte(0x4006,(write_temp/100));
  
  FLASH_EraseByte(0x4007);
  FLASH_ProgramByte(0x4007,(write_temp%100/10));
  
  FLASH_EraseByte(0x4008);
  FLASH_ProgramByte(0x4008,(write_temp%10));
  
  FLASH_Lock(FLASH_MEMTYPE_PROG);
}

void wirte_flash_set_temp_min(float temp) // luu nhiet do
{
  uint16_t write_temp=0;
  write_temp = temp*10;
  //FLASH_DeInit();
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_TPROG);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  
  FLASH_EraseByte(0x4000);
  FLASH_ProgramByte(0x4000,(write_temp/100));
  
  FLASH_EraseByte(0x4001);
  FLASH_ProgramByte(0x4001,(write_temp%100/10));
  
  FLASH_EraseByte(0x4002);
  FLASH_ProgramByte(0x4002,(write_temp%10));
  
  FLASH_Lock(FLASH_MEMTYPE_PROG);
}

void wirte_flash_set_time(uint16_t time) // luu nhiet do
{
  
  //FLASH_DeInit();
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_TPROG);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  
  FLASH_EraseByte(0x4003);
  FLASH_ProgramByte(0x4003,(time/100));
  
  FLASH_EraseByte(0x4004);
  FLASH_ProgramByte(0x4004,(time%100/10));
  
  FLASH_EraseByte(0x4005);
  FLASH_ProgramByte(0x4005,(time%10));
  
  FLASH_Lock(FLASH_MEMTYPE_PROG);
}

void read_flash_set_temp_min() // doc nhiet do da luu trong flash
{
  uint8_t tram, chuc, donvi;
  set_temp_min=0; 
  tram=FLASH_ReadByte(0x4000);
  chuc=FLASH_ReadByte(0x4001);
  donvi=FLASH_ReadByte(0x4002);
  set_temp_min=tram*10+chuc+donvi*0.1;
}
void read_flash_set_temp_max() // doc nhiet do da luu trong flash
{
  uint8_t tram, chuc, donvi;
  set_temp_max=0; 
  tram=FLASH_ReadByte(0x4006);
  chuc=FLASH_ReadByte(0x4007);
  donvi=FLASH_ReadByte(0x4008);
  set_temp_max=tram*10+chuc+donvi*0.1;
}

void read_flash_set_time() // doc nhiet do da luu trong flash
{
  uint8_t tram, chuc, donvi;
  set_time_minute=0; 
  tram=FLASH_ReadByte(0x4003);
  chuc=FLASH_ReadByte(0x4004);
  donvi=FLASH_ReadByte(0x4005);
  set_time_minute=tram*100+chuc*10+donvi;
}

void Scan_Button()
{
  if(start)
  {
    if((GPIO_ReadInputData(GPIOB) & GPIO_PIN_7)==0x00) //MODE
    {
      while((GPIO_ReadInputData(GPIOB) & GPIO_PIN_7)==0x00);
      mode++;
      if(mode>6) mode=0;
    }
    if((GPIO_ReadInputData(GPIOB) & GPIO_PIN_6)==0x00) //UP
    {
      //while((GPIO_ReadInputData(GPIOB) & GPIO_PIN_6)==0x00);
      if(mode==1) //set_temp
      {
        set_temp_max = set_temp_max + 0.1;
        if(set_temp_max>80) set_temp_max=0;
      }
      else if(mode==3)
      {
        set_temp_min = set_temp_min + 0.1;
        if(set_temp_min>80) set_temp_min=0;
      }
      else if (mode==5)
      {
        set_time_minute=set_time_minute+1;
        if(set_time_minute>300) set_time_minute=0;
      }
      delay_ms(180);
    }
    if((GPIO_ReadInputData(GPIOB) & GPIO_PIN_3)==0x00) //DOWN
    {
      //while((GPIO_ReadInputData(GPIOB) & GPIO_PIN_3)==0x00);
      if(mode==1) //set_temp
      {
        set_temp_max = set_temp_max - 0.1;
        if(set_temp_max<0) set_temp_max=80;
      }
      else if(mode==3)
      {
        set_temp_min = set_temp_min - 0.1;
        if(set_temp_min<0) set_temp_min=80;
      }
      else if (mode==5)
      {
        set_time_minute=set_time_minute-1;
        if(set_time_minute>300) set_time_minute=0;
      }
      delay_ms(180);
    }
  }
  if((GPIO_ReadInputData(GPIOB) & GPIO_PIN_1)==0x00) //START
  {
    while((GPIO_ReadInputData(GPIOB) & GPIO_PIN_1)==0x00);
    quet_led(20); //clear led
    count_ms_time = 0;
    count_ms_minute = 0;
    start=1;
  }
  if((GPIO_ReadInputData(GPIOB) & GPIO_PIN_2)==0x00) //STOP
  {
    while((GPIO_ReadInputData(GPIOB) & GPIO_PIN_2)==0x00);
    quet_led(20); //clear led
    start=0;
  }
  if((GPIO_ReadInputData(GPIOB) & GPIO_PIN_0)==0x00) //LIGHT
  {
    while((GPIO_ReadInputData(GPIOB) & GPIO_PIN_0)==0x00);
    GPIO_WriteReverse(GPIOD, GPIO_PIN_5);
  }
  
}

void Control_Mode()
{
  if(start==1)
  {

    if (mode==2)
    {
      wirte_flash_set_temp_max(set_temp_max);
      mode=3;
    }
    else if (mode==4)
    {
      wirte_flash_set_temp_min(set_temp_min);
      mode=5;
    }
    else if (mode==6)
    {
      wirte_flash_set_time(set_time_minute);
      quet_led(20); //clear led
      mode=0;
    }
  }
}

void INT_timer2()
{
  if(TIM2_GetITStatus(TIM2_IT_UPDATE)==SET)
  {
    if(start)
    {
      if(count_ms_time>59)
      {
        count_ms_time=0;
        count_ms_minute++;
      }
      
    if(mode==0)
    {
      display_temp(now_temp);
    }
    else if(mode==1) // Set temp max
    {
      display_temp(set_temp_max);
    }
    else if (mode==3) // Set temp min
    {
     display_temp(set_temp_min);
    }
    else if (mode==5)
    {
      display_time(set_time_minute);
    }
      time_update_temp++;
      if(count_time>3) count_time=0;
      if((time_update_temp>999)&&(start==1))
      {
        if(mode==0) 
        {
          now_temp = (float) DS18x20_ReadTemp()*0.0625f;
        }
        count_ms_time++;
        time_update_temp=0;
        
      } 
    }  
    TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
  }
  
}


void main(void)
{
  clk_config_16MHz_hsi();
  //nut nhan
  GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT); //MODE
  GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT); //UP
  GPIO_Init(GPIOB, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT); //DOWN
  GPIO_Init(GPIOB, GPIO_PIN_2, GPIO_MODE_IN_PU_NO_IT); //STOP
  GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT); //START
  GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_PU_NO_IT); //LIGHT
  // ANODE LED
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST); //LED1
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST); //LED2
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST); //LED3
  GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST); //LED4
  // LED 7SEG
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_HIGH_FAST); //a
  GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_FAST); //b
  GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_HIGH_FAST); //c
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST); //d
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST); //e
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST); //f
  GPIO_Init(GPIOC, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST); //g
  GPIO_Init(GPIOC, GPIO_PIN_1, GPIO_MODE_OUT_PP_HIGH_FAST); //DP
  // relay
  GPIO_Init(GPIOD, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST); //RELAY SSR A
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST); //RELAY SSR B
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST); //RELAY LIGHT
  //DS18B20 PA3
  GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);
  ITC_SetSoftwarePriority(ITC_IRQ_TIM2_OVF,ITC_PRIORITYLEVEL_3);
  ITC_SetSoftwarePriority(ITC_IRQ_TIM4_OVF,ITC_PRIORITYLEVEL_1);
  read_flash_set_temp_max();
  read_flash_set_temp_min();
  read_flash_set_time();
  delay_using_timer4_init();
  timer2_init();
  enableInterrupts();
  while (1)
  {

    Scan_Button();
    Control_Mode();
    if(start)
    {
     control_relay_temp(set_temp_min, set_temp_max, temp_ds18b20);
     control_relay_time(set_time_minute, count_ms_minute);
    }
    else
    {
      quet_led(20); //clear led
      if(mode==0)
      {
        blynk_wait();
      }
      GPIO_WriteLow(GPIOD, GPIO_PIN_7); //3
      GPIO_WriteLow(GPIOD, GPIO_PIN_6); //1
    }
    
  }
  
}

#ifdef USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
