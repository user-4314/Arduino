#include <LiquidCrystal.h>
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);// select the pins used on the LCD panel
byte Row=0, Col=0;
int speakerPin = D3;
char notes[] = "gccfddcdefggggccfddcegge ";// 依照簡譜的順序，填入代表的音符，空白代表休止符
unsigned long beats[] = {1,1,2,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,2,4};// 決定每個音階的拍子，注意這邊用 unsigned long 所以拍子只能是正整數
int length = sizeof(notes);// 利用 sizeof()，算出總共要多少音符
int tempo = 300;// 決定一拍多長，這邊一拍 300 ms
unsigned long recordbeats[15] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//紀錄要錄音下來的譜
int count = 0;  //紀錄錄下來的音到底長度有多長
//判斷到時候要發出的音到底是要高、中、低哪種音階
bool high = false;
bool middle = false;
bool low = false;

void setup() {
  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)                                   
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)  // (A, B, C, D) is correct.
  //Pin left to right :R1 R2 R3 R4 C1 C2 C3 C4

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  lcd.begin(16, 2);              // start the library
  
  pinMode(speakerPin, OUTPUT);
} 

void loop() {
  // put your main code here, to run repeatedly:
  byte keyindex=0;
  //if key is pressed in the first round scan, 
  //then call keyscan() again to check if the key pressed in first round is actually pressed 
  if(keyscan()==true) 
  {
    keyindex=(Row-1)*4+Col;
    delay(5);
      if (keyindex==1){
              //當按下button 1後在lcd上顯示do
              lcd.setCursor(0,0);
              lcd.print("Do");
              if(high){
                //當判斷到需要發出high的音階時就發出高音do
                tone(speakerPin,1046, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1046;//把高音do的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音do
                tone(speakerPin,523, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=523;//把中音do的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音do
                tone(speakerPin,262, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=262;//把低音do的頻率存到record的陣列
                count++;//record的長度+1
              }
            }
            if( keyindex == 2){
              //當按下button 2後在lcd上顯示re
              lcd.setCursor(0,0);
              lcd.print("Re");
              if(high){
                //當判斷到需要發出high的音階時就發出高音re
                tone(speakerPin,1175, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1175;//把高音re的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音re
                tone(speakerPin,587, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=587;//把中音re的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音re
                tone(speakerPin,294, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=294;//把低音re的頻率存到record的陣列
                count++;//record的長度+1
              }
            }
            if( keyindex == 3){
              //當按下button 3後在lcd上顯示mi
              lcd.setCursor(0,0);
              lcd.print("Mi");
              if(high){
                //當判斷到需要發出high的音階時就發出高音mi
                tone(speakerPin,1318, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1318;//把高音mi的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音mi
                tone(speakerPin,659, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=659;//把中音mi的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音mi
                tone(speakerPin,330, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=330;//把低音mi的頻率存到record的陣列
                count++;//record的長度+1
              }
            }  
            if( keyindex == 5){
              //當按下button 4後在lcd上顯示fa
              lcd.setCursor(0,0);
              lcd.print("Fa");
              if(high){
                //當判斷到需要發出high的音階時就發出高音fa
                tone(speakerPin,1397, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1397;//把高音fa的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音fa
                tone(speakerPin,698, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=698;//把中音fa的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音fa
                tone(speakerPin,349, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=349;//把低音fa的頻率存到record的陣列
                count++;//record的長度+1
              }
            }
            if( keyindex == 6){
              //當按下button 5後在lcd上顯示so
              lcd.setCursor(0,0);
              lcd.print("So");
              if(high){
                //當判斷到需要發出high的音階時就發出高音so
                tone(speakerPin,1568, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1568;//把高音so的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音so
                tone(speakerPin,784, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=784;//把中音so的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音so
                tone(speakerPin,392, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=392;//把低音so的頻率存到record的陣列
                count++;//record的長度+1
              }
            }
            if(keyindex == 7){
              //當按下button 6後在lcd上顯示la
              lcd.setCursor(0,0);
              lcd.print("La");
              if(high){
                //當判斷到需要發出high的音階時就發出高音la
                tone(speakerPin,1760, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1760;//把高音la的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音la
                tone(speakerPin,880, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=880;//把中音la的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音la
                tone(speakerPin,440, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=440;//把低音la的頻率存到record的陣列
                count++;//record的長度+1
              }
            }
            if(keyindex == 9){
              //當按下button 7後在lcd上顯示si
              lcd.setCursor(0,0);
              lcd.print("Si");
              if(high){
                //當判斷到需要發出high的音階時就發出高音si
                tone(speakerPin,1976, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=1976;//把高音si的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(middle){
                //當判斷到需要發出middle的音階時就發出中音si
                tone(speakerPin,988, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=988;//把中音si的頻率存到record的陣列
                count++;//record的長度+1
              }
              if(low){
                //當判斷到需要發出low的音階時就發出低音si
                tone(speakerPin,494, 300);
                delay(300);
                noTone(speakerPin);
                recordbeats[count]=494;//把低音si的頻率存到record的陣列
                count++;//record的長度+1
              }
            }
            
       if(keyindex == 4){
          //當按下button A後在lcd上顯示high
          lcd.clear();
          lcd.setCursor(12,0);
          lcd.print("High");
          //把音階的判斷調成high
          high = true;
          middle = false;
          low = false;
       }
       
       if(keyindex == 8){
          //當按下button B後在lcd上顯示middle
          lcd.clear();
          lcd.setCursor(10,0);
          lcd.print("Middle");
          //把音階的判斷調成middle
          high = false;
          middle = true;
          low = false;  
       }
       
       if(keyindex == 12){
          //當按下button C後在lcd上顯示low
          lcd.clear();
          lcd.setCursor(13,0);
          lcd.print("Low");
          //把音階的判斷調成low
          high = false;
          middle = false;
          low = true;  
       }
    }

  if(!digitalRead(BUTTON1)){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Recording");
    //當按下button BT1後把存的陣列位子移到第一格開始做存取的動作
    count=0;
  }
  
  if(!digitalRead(BUTTON2)){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("No Recording");
    //當按下button BT2後在存的陣列句尾補上零代表結束符號
    recordbeats[count]=0;
  }
  
  if(!digitalRead(BUTTON3)){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Playing");
    //當按下button BT3後把剛剛存在陣列裡的音符一個一個發音出來
    for (int i = 0; i < count; i++) {
      if (recordbeats[i] == 0)
        delay(400); // rest
      else {
        tone(speakerPin, recordbeats[i], tempo);
        delay(tempo);
        noTone(speakerPin);
      }
      delay(tempo/10);// 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
    }
  }
  
  if(!digitalRead(BUTTON4)){
    //當按下button BT4後把預先寫在陣列裡的音符一個一個發音出來
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Little bee");
    lcd.setCursor(0,1);
    lcd.print("Playing a Song.");
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ')// 如果是空白的話，不撥放音樂
        delay(400); // rest
      else 
        playNote(speakerPin,notes[i], beats[i] * tempo);// 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
      delay(tempo/10);// 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
    }
  }
}
void playNote(int OutputPin, char note, unsigned long duration) {
   
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 261, 294, 330, 349, 392, 440, 494, 523 };

  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}

void playNote2(int OutputPin, char note, unsigned long duration) {
   // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 523, 587, 659, 698, 784, 880, 988, 1046 };


    // 播放音符對應的頻率(中音)
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
  //下方的 delay() 及 noTone ()，測試過後一定要有這兩行，整體的撥放出來的東西才不會亂掉，可能是因為 Arduino 送出tone () 頻率後會馬上接著執行下個指令，不會等聲音播完，導致撥出的聲音混合而亂掉
      delay(duration);
      noTone(OutputPin);
    }
  }
}

void playNote3(int OutputPin, char note, unsigned long duration) {
   // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1046, 1175, 1318, 1397, 1568, 1760, 1976,2092 };

  // 播放音符對應的頻率(高音)
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
  //下方的 delay() 及 noTone ()，測試過後一定要有這兩行，整體的撥放出來的東西才不會亂掉，可能是因為 Arduino 送出tone () 頻率後會馬上接著執行下個指令，不會等聲音播完，導致撥出的聲音混合而亂掉
      delay(duration);
      noTone(OutputPin);
    }
  }
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
      Col=1;Row=1;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
       digitalWrite(A0, HIGH);
      Col=1;Row=4;
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
      Col=2;Row=1;
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=4;
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
      Col=3;Row=1;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=2;
      keypressed = true;
      return(keypressed);
  }  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=4;
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
      Col=4;Row=1;
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=4;
      keypressed = true;
      return(keypressed);
  }
  return(false);
}
