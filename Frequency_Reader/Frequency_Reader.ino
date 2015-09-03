unsigned const int AVARRSIZE = 15, LED = 13;

long cycles[AVARRSIZE];
int cyclesCount = 0;
long average = 0;

unsigned long pulseTimerInit, pulseTimerDiff, updateTimerInit, updateTimerDiff;



void setup(){
  pinMode(LED, OUTPUT);
   updateTimerInit = millis();

  attachInterrupt(0, _HighPulse, RISING); // 0 = pin 2

  Serial.begin(9600);
  delay(500);
}

void loop(){
   updateTimerDiff = millis() - updateTimerInit;

   if (updateTimerDiff > 1000){
      _GetAverageFreq();
      if (average > 6000){
        digitalWrite(LED, HIGH); 
      }
      else{
        digitalWrite(LED, LOW);        
      }
      Serial.println(average);
      updateTimerInit = millis();
   }
}

void _HighPulse(){
   unsigned long currentTimer = micros();

   pulseTimerDiff = currentTimer - pulseTimerInit;

   pulseTimerInit = currentTimer;
  
   cycles[cyclesCount] = pulseTimerDiff;
   
   cyclesCount++;
   
   if (cyclesCount > (AVARRSIZE-1)){
      cyclesCount = 0;
   }
}

int _GetAverageFreq(){
   double tempFreq = 0, aveTime, aveFreq;
   long sumTimes = 0;
   int i = 0;
   
   for (i = 0; i < AVARRSIZE; i++){
      sumTimes = (long)sumTimes + (long)cycles[i];
   }

   aveTime = double((long)sumTimes / (long)AVARRSIZE);

   average = long(float(1000000.0) / float(aveTime));    
}
//********************************Delete upon reading***********************************************************//
// This is from Jesse Graham..Testing comments and playing around. Feel Free to delete out whomever reads this  //
// Hi jesse.  I was very confused when I saw this.  I'm glad you got it working.  //
//********************************Delete upon reading***********************************************************//


