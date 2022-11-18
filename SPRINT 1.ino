                                                                 SPRINT 1

                                                 NELLAI COLLEGE OF ENGINEERING, MARUTHAKULAM

                                                       TEAM ID : PNT2022TMID50300


/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.

  OPEN THE SERIAL MONITOR TO VIEW THE OUTPUT >> 
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
unsigned long startMillis;
unsigned long currentMillis;
static int ButtonValueOld;
static float IntermitOutput;
static float IntermitOutput1;
static float Output_Hold;
static bool SchoolReached=false;
static bool SchoolCrossed=false;
const unsigned long period = 100;  //the value is a number of milliseconds
//100ms = 0.1seconds

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
}

// the loop routine runs over and over again forever:
void loop() 
{
  
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    Task_100ms();
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
}

void Task_100ms()
{
  // read the input on analog pin A0:
  int sensorValue = analogRead(A0);
  
  // read the input on Digital pin 4:
  int ButtonValue = digitalRead(4);

  //Map the senor value according to OUTPUT  
  int outputValue = map(sensorValue, 0, 1023, 0, 255);
  
  // change the analog out value If Button Pressed
  if(ButtonValue==HIGH)
  {
    if(outputValue>100)
    {
      if(ButtonValueOld==LOW)
      {
        Output_Hold = outputValue;
      }
      //Filtering the Output to 100
      
      //Output = Previous Output +((Destination value - Previous output)*Time step/Time constant)
      //Time step = 100ms = 0.1s; Time constant = 0.5s it can be increased or decreased depend on filtering speed
      
  	  Output_Hold = Output_Hold+((100-Output_Hold)*0.1/1);	
      
      SchoolReached = true;
      
      Serial.println(Output_Hold);
      
     }
    
    outputValue = Output_Hold;
   }
  
  if((ButtonValue==LOW && ButtonValueOld==HIGH && SchoolReached==true)||(SchoolCrossed==true))
  {
   	  if(ButtonValueOld==HIGH)
      {
        SchoolCrossed = true;
        SchoolReached = false;
      }	
      
  	  Output_Hold = Output_Hold+((outputValue-Output_Hold)*0.1/1);	
    
      if((outputValue - Output_Hold) <= 2 ) 
      {
    	//Serial.println((outputValue - Output_Hold));    
        SchoolCrossed = false;
      }
    outputValue = Output_Hold;
    
    Serial.println(Output_Hold);
  }
  
  ButtonValueOld = ButtonValue;
  
  
  
  //Serial.println(ButtonValue);
  analogWrite(3, outputValue);
}