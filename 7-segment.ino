/* Define shift register pins used for seven segment display */
#define LATCH_DIO D15   
#define CLK_DIO D14
#define DATA_DIO 2        // D2 is OK, too
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

/* Segment byte maps for numbers 0 to 9 , A, b , C*/ // MSB: dp g f e d c b a :LSB
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71,0X0};
const byte DP = 0x80;   // Digit Point
/* Byte maps to select digit 1 to 4 */ // E: 1110  D: 1101  B: 1011   7: 0111    // the 0's place
const byte SEGMENT_SELECT[] = {0x0E,0x0D,0x0B,0x07};   // {0xFE,0xFD,0xFB,0xF7};  is OK, too.
byte  RecordFourBits[5]={16,16,16,16,16} ;//讓一開始的陣列不顯示任何東西
byte Row=0, Col=0;

void setup ()
{
    /* Set DIO pins to outputs */
    pinMode(LATCH_DIO,  OUTPUT);
    pinMode(CLK_DIO,  OUTPUT);
    pinMode(DATA_DIO, OUTPUT);
    pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)                                   
    pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
    pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
    pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
    pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
    pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
    pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
    pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)  // (A, B, C, D) is correct.

    digitalWrite(A0,HIGH);
    digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
}

/* Main program */
void loop()
{   
    byte keyindex=0;
    if ((keyscan()==true) && (keyindex=(Col-1)*4+(Row-1))){
        //把按的數字存放到陣列裡面
        RecordFourBits[1] = RecordFourBits[2];
        RecordFourBits[2] = RecordFourBits[3];
        RecordFourBits[3] = RecordFourBits[4];
        RecordFourBits[4] = keyindex;
 
        digitalWrite(A0,LOW);
        digitalWrite(A1,LOW);
        digitalWrite(A2,LOW);
        digitalWrite(A3,LOW);

        delay(300);
    }
    //顯示當前陣列所存的四位數字
    WriteNumberToSegment(0 , RecordFourBits[1]);
    WriteNumberToSegment(1 , RecordFourBits[2]);
    WriteNumberToSegment(2 , RecordFourBits[3]);
    WriteNumberToSegment(3 , RecordFourBits[4]);
    
    //從左跑到右的跑馬燈
    if(!digitalRead(BUTTON4)){  //個別數字從左到右
       for(int i=4;i>=1;i--){ 
          for(int j=0;j<4;j++){ 
              WriteNumberToSegment(j , RecordFourBits[i]);
              delay(500);
          }
       }
       for(int i=0; i<500; i++){  //顯示四位數字
          WriteNumberToSegment(0 , RecordFourBits[1]);
          WriteNumberToSegment(1 , RecordFourBits[2]);
          WriteNumberToSegment(2 , RecordFourBits[3]);
          WriteNumberToSegment(3 , RecordFourBits[4]);
       }
    } 
    //從右跑到左的跑馬燈
    if(!digitalRead(BUTTON1)){  //個別數字從右到左
       for(int i=1;i<=4;i++){ 
          for(int j=3;j>=0;j--){ 
               WriteNumberToSegment(j , RecordFourBits[i]);
               delay(500);
          }
      }
       for(int i=0; i<500; i++){  //顯示四位數字
         WriteNumberToSegment(0 , RecordFourBits[1]);
         WriteNumberToSegment(1 , RecordFourBits[2]);
         WriteNumberToSegment(2 , RecordFourBits[3]);
         WriteNumberToSegment(3 , RecordFourBits[4]);
       }
    }    
}

/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void WriteNumberToSegment(byte Segment, byte Value)
{
    digitalWrite(LATCH_DIO, LOW);
    // The following order cannot be changed. MAP first and then SELECT.
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);        
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );

    digitalWrite(LATCH_DIO,HIGH);
}

bool keyscan( )
{
  Row=0;Col=0;
  bool keypressed = false;
  //scan col1
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=1;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=0
      //SW1 button的值是0->WriteNumberToSegment(3, 0)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=2;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=1
      //SW4 button的值是1->WriteNumberToSegment(3, 1)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=3;
      keypressed = true;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=2
      //SW7 button的值是2->WriteNumberToSegment(3, 2)
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
       digitalWrite(A0, HIGH);
      Col=1;Row=4;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=3
      //SW16 button的值是3->WriteNumberToSegment(3, 3)
      keypressed = true;
      return(keypressed);
  }
  //scan col 2  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=1;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=4
      //SW2 button的值是4->WriteNumberToSegment(3, 4)
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=2;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=5
      //SW5 button的值是5->WriteNumberToSegment(3, 5)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=3;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=6
      //SW8 button的值是6->WriteNumberToSegment(3, 6)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=4;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=7
      //SW0 button的值是7->WriteNumberToSegment(3, 7)
      keypressed = true;
      return(keypressed);
  }

  //scan col 3  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=1;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=8
      //SW3 button的值是8->WriteNumberToSegment(3, 8)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=2;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=9
      //SW6 button的值是9->WriteNumberToSegment(3, 9)
      keypressed = true;
      return(keypressed);
  }  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=3;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=10
      //SW9 button的值是10->WriteNumberToSegment(3, 10)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=4;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=11
      //SW17 button的值是3->WriteNumberToSegment(3, 11)
      keypressed = true;
      return(keypressed);
  }
  
  //scan col 4  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=1;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=12
      //SW10 button的值是12->WriteNumberToSegment(3, 12)
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=2;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=13
      //SW11 button的值是13->WriteNumberToSegment(3, 13)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=3;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=14
      //SW12 button的值是14->WriteNumberToSegment(3, 14)
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=4;//帶入main loop的function的算式keyindex=(Col-1)*4+(Row-1)=15
      //SW13 button的值是15->WriteNumberToSegment(3, 15)
      keypressed = true;
      return(keypressed);
  }
  return(false);
}
