
#include <LiquidCrystal.h>
//#include<serLCD.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int x;
int iteration = 0;
float freq;
int thr =  10000;

#define MAXN 55

int a[MAXN];
int R[MAXN] = { 0 };
int lf =0;
String notbuf;
int bufferSize = 0;
boolean firstMax = false;

void setup(){
  //analog mic input
  pinMode(A3, INPUT);
  //set pins as outputs
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(1,OUTPUT);

cli();//stop interrupts

lcd.begin(16, 2);
Serial.begin(9600);

//set timer1 interrupt
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1khz increments
  OCR1A = 2000;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 for 8 prescaler
  TCCR1B |= (1 << CS11);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


sei();//allow interrupts

}


ISR(TIMER1_COMPA_vect)
{
  
 iteration++;
 
    //Serial.println(iteration);
  a[bufferSize] = analogRead(A3);//read the value of A0
 // Serial.print(data[buffersize]);//print the value
 // Serial.print("-");
  bufferSize++;
  if(bufferSize == MAXN-1 )
  {
    //Serial.println();
     bufferSize = 0;
  }
 }




void loop()
{
  
  if(iteration > MAXN-1)
  {
    //Serial.println("iteration");
    cli();
    iteration =0;
    Serial.print("R[i]");

    //-------autoCorrelation----------
    for (int i=0;i<MAXN - 1;i++)
    {
      for(int j=1;j<MAXN- 1 ;j++)
      {
      if (j>= i)
      R[i] += a[j] * a[j-i]; 
      }
      Serial.print(R[i]);
      Serial.print("-");
    }
    Serial.println();

    for (int i=1;i<MAXN - 1;i++)
    {
      if (!firstMax && R[i]>thr ){ find_freq(i);}
    }
    firstMax = false;
    for (int i=0;i<MAXN - 1;i++)
    {
      R[i] =0;
    }

}
if(iteration == 0) 
{
  sei();
}

}



void find_freq(int i)
  {
    
    freq = 1/(i * 0.001);
    firstMax = true;
    /* Serial.print("Flag   ");
     Serial.println(freq);*/
    find_note(freq);
    Serial.print(notbuf);
    lcd.print(notbuf);
    if(lf == 0 ){lcd.setCursor(0,0); //row 0
    lf++;
    }
    else if(lf == 1 ){
      lcd.setCursor(0,1); // row 1
    lf =0;}
//        sei();
  }

  void find_note(float f)
  {
    
    if(f < 92.50){
      notbuf = ("F2     ");
      
    }
    else if(f < 98.00){
      notbuf = ("F#2/Gb2");
      
    }
    else if(f < 103.83){
      notbuf = ("G2     ");
      
    }
    else if(f < 110.00){
      notbuf = ("G#2/Ab2");
      
    }else if(f < 116.54){
      notbuf = ("A2     ");
    }else if(f < 123.47){
      
      notbuf = ("A#2/Bb2");
      
    }else if(f <  130.81){
      notbuf = ("B2     ");
    }else if(f < 138.59){
      
      notbuf = ("C3     ");
    }else if(f < 146.83){
      
      notbuf = ("C#3/Db3");
      
    }else if(f < 155.56){
      
      notbuf = ("D3     ");
    }else if(f < 164.81){
      
      notbuf = ("D#3/Eb3");
    }else if(f < 174.61){
      
      notbuf = ("E3     ");
    }else if(f < 185.00){
      
      notbuf = ("F3     ");
    }else if(f < 196.00){
      
      notbuf = ("F#3/Gb3");
    }else if(f < 207.65){
      
      notbuf = ("G3     ");
    }else if(f< 220.00){
      
      notbuf = ("G#3/Ab3");
    }else if(f < 233.08){
      
      notbuf = ("A3     ");
    }else if(f < 246.94){
      notbuf = ("A#3/Bb3");
    }else if(f < 261.63){
      notbuf = ("B3     ");
    }else if(f < 277.18){
      notbuf = ("c4     ");
    }else if(f < 293.66){
      notbuf = ("C#4/Db4");
    }else if(f < 311.13){
      notbuf = ("D4     ");
    }else if(f <  329.63){
      notbuf = ("D#4/Eb4");
    }else if(f < 349.23){
      notbuf = ("E4     ");
    }else if( f <369.99){
      notbuf = ("F4     ");}
  }  






