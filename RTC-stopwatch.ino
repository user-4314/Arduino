// include the library code:
#include <LiquidCrystal.h>
#include <RTC.h>
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* Change these values to set the current initial time */
//設定當前時間
const byte seconds = 55;
const byte minutes = 20;
const byte hours = 14;
const byte day = 20; 
int sh,sm,ss,h=0,m=0,s=0,count=0;
void setup() {
     // set up the LCD's number of columns and rows
     lcd.begin(16, 2);
     RTC.settime(day,hours, minutes, seconds);
     RTC.startcounting();
     // set the time and start counting
}

void loop() {
     //印出今天的日期
 lcd.setCursor(0, 0);
     lcd.print("11/30   ");
     //印出設定的時間
     sh=RTC.gethours();
     if(sh>9)//如果不足兩位數就在前面補0
      lcd.print(sh);
     else{
      lcd.print("0");
      lcd.print(sh);
     }
     lcd.print(":");
     sm=RTC.getminutes();
     if(sm>9) //如果不足兩位數就在前面補0
      lcd.print(sm);
     else{
      lcd.print("0");
      lcd.print(sm);
     }
     lcd.print(":");
      ss=RTC.getseconds();
     if(ss>9) //如果不足兩位數就在前面補0
      lcd.print(ss);
     else{
      lcd.print("0");
      lcd.print(ss);
     }
     
     if(!digitalRead(BUTTON1))
    {   //開啟計時器
        lcd.setCursor(0, 1);
        lcd.print("00:00:00StopWatch");
        h=0;m=0;s=0; //把碼表歸零
    }  
    if(!digitalRead(BUTTON2))
    {	 //把碼表歸零
        lcd.setCursor(0, 1);
        lcd.print("00:00:00StopWatch");
        h=0;m=0;s=0; 
    } 
    if(!digitalRead(BUTTON3))
    {	 //關閉碼表功能
        lcd.setCursor(0, 1);
        lcd.print("                ");
    }  
    if(!digitalRead(BUTTON4))
    {
        count++;//判斷是否有按下BUTTON4
        if(count%2==1){//假如有按下BUTTON4就開始計時
          for(int i=0;i<6;i++){
          lcd.setCursor(0, 1);
		  //印出碼表的時間
          if(h>9) //如果不足兩位數就在前面補0
            lcd.print(h);
          else{
            lcd.print("0");
            lcd.print(h);
          }
          lcd.print(":");
          if(m>9) //如果不足兩位數就在前面補0
            lcd.print(m);
          else{
            lcd.print("0");
            lcd.print(m);
          }
          lcd.print(":");
          if(s>9) //如果不足兩位數就在前面補0
            lcd.print(s);
          else{
            lcd.print("0");
            lcd.print(s);
          }
          lcd.print("Counting");//顯示碼表正在計時的提示字串
          s++;//每過一秒就讓紀錄秒的參數+1
          if(s>60){//秒超過60就進位
            s=0;
            m++;
          }
          if(m>60){ //分超過60就進位
            m=0;
            h++;
          } 
          delay(1000);
          } 
        }
        else{//當再次按下BUTTON4就停止計時
          s--;
          lcd.setCursor(0, 1);
		  //印出碼表的時間
          if(h>9) //如果不足兩位數就在前面補0
            lcd.print(h);
          else{
            lcd.print("0");
            lcd.print(h);
          }
          lcd.print(":");
          if(m>9) //如果不足兩位數就在前面補0
            lcd.print(m);
          else{
            lcd.print("0");
            lcd.print(m);
          }
          lcd.print(":");
          if(s>9) //如果不足兩位數就在前面補0
            lcd.print(s);
          else{
            lcd.print("0");
            lcd.print(s);
          }
          lcd.print("    Stop");//顯示碼表停止計時的提示字串
        }
    }    
     delay(1000);
}
