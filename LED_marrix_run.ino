#define NUM 16 // 首先定義LED的數目
int leds[NUM] = {
  D0, D1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15
};

// 將每個腳位模式設為OUTPUT
void setup() {               
  for(int i = 0; i < NUM; i++){
    pinMode(leds[i], OUTPUT);
  }    
}

void loop() {
  
    func(0xC003);
    delay(500);
    func(0x300C);
    delay(500);
    func(0x0C30);
    delay(500);
    func(0x03C0);
    delay(500);
    func(0x0000);
    delay(500);
    func(0x0180);
    delay(500);
    func(0x0240);
    delay(500);
    func(0x0420);
    delay(500);
    func(0x0810);
    delay(500);
    func(0x1008);
    delay(500);
    func(0x2004);
    delay(500);
    func(0x4002);
    delay(500);
    func(0x8001);
    delay(500);
}
void func(int num){
  unsigned int mask =0b1<<15;
   for(int i=0;i<16;i++){
       if((num&mask)>>(15-i) == 1){
          digitalWrite(leds[i], LOW);
        }
        else{
          digitalWrite(leds[i], HIGH);
        }
        mask>>=1;
    }
}
