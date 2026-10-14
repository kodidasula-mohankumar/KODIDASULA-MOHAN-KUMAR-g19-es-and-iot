 int input[]={2,3,4,5,6,7,8,9};
void setup(){
  for(int i=0;i<8;i++){
      pinMode(input[i],OUTPUT);
    }
}
  void loop(){
   for(int num = 0; num <= 30; num++)
    {
        int tens = num / 10;
        int units = num % 10; 
       // Units display (pins 2,3,4,5)
        digitalWrite(input[0], tens & 1);
        digitalWrite(input[1], (tens >> 1) & 1);
        digitalWrite(input[2], (tens >> 2) & 1);
        digitalWrite(input[3], (tens >> 3) & 1);
        // Tens display (pins 6,7,8,9)
        digitalWrite(input[4], units & 1);
        digitalWrite(input[5], (units >> 1) & 1);
        digitalWrite(input[6], (units>> 2) & 1);
        digitalWrite(input[7], (units>> 3) & 1);
        delay(1000);
   }
}
