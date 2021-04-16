#define switchFloor1 0 
#define switchFloor2 2
#define switchFloor3 3

#define photocellFloor2 0 
#define photocellFloor3 1

#define steps 520 

#define stepperPin1  10
#define stepperPin2  11
#define stepperPin3  12
#define stepperPin4  13

#define delaytime 10   
#define A 4 
#define B 5 
#define C 6 
#define D 7 
#define E 8 
#define f 10 
#define G 9 
#define DP 11 

#define CC4 1 

int   ;
boolean firstRun = true;
int currentFloor = 1; 
long debounceTime = 200; 
int secondFloorReading = 0; 
int thirdFloorReading = 0;

byte numbers[3][8] = {{0,1,1,0,0,0,0,0},{1,1,0,1,1,0,1,0},{1,1,1,1,0,0,1,0}}; 

const int segments[8] = { A, B, C, D, E, f, G, DP }; 

void setup(){
  Serial.begin(9600); 
   
  pinMode(A, OUTPUT); 
  digitalWrite(A,LOW);
  pinMode(B, OUTPUT);
  digitalWrite(B,LOW);
  pinMode(C, OUTPUT);
  digitalWrite(C,LOW);
  pinMode(D, OUTPUT);
  digitalWrite(D,LOW);
  pinMode(E, OUTPUT);
  digitalWrite(E,LOW);
  pinMode(f, OUTPUT); 
  digitalWrite(f,LOW);
  pinMode(G, OUTPUT);
  digitalWrite(G,LOW);
  pinMode(DP, OUTPUT); 
  digitalWrite(DP,LOW);
   
  pinMode(CC4, OUTPUT); 
  digitalWrite(CC4,HIGH);  
   
  pinMode(switchFloor1, INPUT); 
  pinMode(switchFloor2, INPUT);
  pinMode(switchFloor3, INPUT);
   
  pinMode(stepperPin1, OUTPUT); 
  pinMode(stepperPin2, OUTPUT); 
  pinMode(stepperPin3, OUTPUT); 
  pinMode(stepperPin4, OUTPUT);
}

void loop(){    
    
  secondFloorReading = analogRead(photocellFloor2); 
  thirdFloorReading = analogRead(photocellFloor3);
   
  Serial.print("Analog reading (Second floor) = ");
  Serial.println(secondFloorReading);  
  Serial.print("Analog reading (Third floor) = ");
  Serial.println(thirdFloorReading); 
  delay(1000);
     
  if(secondFloorReading > 790 && thirdFloorReading > 790) 
  {

[u]    [b][color=red]setSegments(0, CC4); 
[/u]    currentFloor = 1; 
  } 
  else if(secondFloorReading < 750) 
  {
    [color=red][u]setSegments(1, CC4); 
    currentFloor = 2;
  }
  else if(thirdFloorReading < 750) 
{ 
setSegments(2, CC4); 
currentFloor = 3; 
} 

if(readSwitch(switchFloor1, debounceTime) == true && currentFloor != 1)
{ 
if(currentFloor == 2)
{ 
Serial.println("going down"); 
int numberOfSteps = steps+90; 
step_OFF(); 

while(numberOfSteps>0)
{ 
        backward(); 
        numberOfSteps -- ;   
      }
    }
    else if(currentFloor == 3){
       
       Serial.println("going down");
       int numberOfSteps = (steps*2)+80;
       step_OFF(); 
        
       while(numberOfSteps>0){
         backward(); 
         numberOfSteps -- ; 
       }
    }
    currentFloor = 1; 
    delay(1000);
  }
   

  if(readSwitch(switchFloor2, debounceTime) == true && currentFloor != 2){
     
    if(currentFloor == 1){
      Serial.println("going up");
      int numberOfSteps = steps+90;
      step_OFF(); 
       
      while(numberOfSteps>0){
        forward(); 
        numberOfSteps -- ; 
      }
    }
    else if(currentFloor == 3){
      Serial.println("going down");
      int numberOfSteps = steps+5;
      step_OFF(); 
       
      while(numberOfSteps>0){
        backward(); 
        numberOfSteps -- ; 
      }
    }
    currentFloor = 2; 
    delay(2000);
  }
   

  if(readSwitch(switchFloor3, debounceTime) == true && currentFloor != 3){ 
    if(currentFloor == 1){
      Serial.println("going up");
      int numberOfSteps = (steps*2)+80; 
      step_OFF(); 
         
      while(numberOfSteps>0){
        forward(); 
        numberOfSteps -- ; 
      }
    }
    else if(currentFloor == 2){
      Serial.println("going up");
      int numberOfSteps = steps+5;
      step_OFF(); 
         
      while(numberOfSteps>0){
        forward();
        numberOfSteps -- ; 
      }
    }
    currentFloor = 3; 
    delay(2000);
  }
  Serial.println(currentFloor);
  }