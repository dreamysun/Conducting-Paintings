#define waterlight 2
#define menlight 3
#define mountainlight 4

#define alight 5
#define blight 6
#define clight 7

#define IR_1 8 
#define IR_2 9 
#define IR_3 10 

#define Leftswitch A4
#define Rightswitch A5

int xVal;
int yVal;
int zVal;
int samples = 10;

int lightvalue = 400;

int kai_1 = 0;
int kai_2 = 0;
int kai_3 = 0;

int IR_1_State = 0,IR_1_lastState = 0;
int IR_2_State = 0,IR_2_lastState = 0;
int IR_3_State = 0,IR_3_lastState = 0;

int Leftswitch_Value;
int Rightswitch_Value;
int Page_State = 0;

//message given to max
int Zero = 0;
int One  = 1;    //ir1
int Two  = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(waterlight,OUTPUT);
  pinMode(menlight,OUTPUT);
  pinMode(mountainlight,OUTPUT);

  pinMode(alight,OUTPUT);
  pinMode(blight,OUTPUT);
  pinMode(clight,OUTPUT);
  
  pinMode(IR_1,INPUT);
  pinMode(IR_2,INPUT);
  pinMode(IR_3,INPUT);

  pinMode(Leftswitch, INPUT);
  pinMode(Rightswitch,INPUT);
  
  Serial.begin(9600);

}

void loop() {
  IR_1_State = digitalRead(IR_1);
  IR_2_State = digitalRead(IR_2);
  IR_3_State = digitalRead(IR_3);
  Leftswitch_Value = analogRead(Leftswitch);
  Rightswitch_Value = analogRead(Rightswitch);

  if (Leftswitch_Value >lightvalue && Rightswitch_Value > lightvalue){
    Page_State = 0;
  } else {
      if (Leftswitch_Value <= lightvalue){
          Page_State = 1;
      }

      if (Rightswitch_Value <= lightvalue){
          Page_State = 2;
      }  
  }

if (Page_State == 0){
  
  //Send Three '0' to Max
  Serial.print(Zero,DEC);
  Serial.print(" ");
  Serial.print(Zero,DEC);
  Serial.print(" ");
  Serial.print(Zero,DEC);
  Serial.print(" ");
  
  //Set Three Swtich to off
  kai_1 = false;
  kai_2 = false;
  kai_3 = false;
  
  // Turn off all led
  digitalWrite(alight,LOW);
  digitalWrite(blight,LOW);
  digitalWrite(clight,LOW);
  digitalWrite(waterlight,LOW);
  digitalWrite(menlight,LOW);
  digitalWrite(mountainlight,LOW);
  
}
 
else{

//IR1   Send data in 1st Slot to Max
  if (IR_1_State && !IR_1_lastState) {
    kai_1 = !kai_1;
    delay(20);
  } 
    IR_1_lastState = IR_1_State;

  if(!kai_1){
    digitalWrite(waterlight,LOW);
    digitalWrite(alight,LOW);
    Serial.print(Zero,DEC);
    Serial.print(" ");
  } else if(kai_1){
          if(Page_State == 1){ 
                digitalWrite(waterlight,HIGH);
                Serial.print(One,DEC); 
                Serial.print(" ");
          } else if( Page_State == 2 ){
                digitalWrite(alight,HIGH);
                Serial.print(Two,DEC);
                Serial.print(" ");
          }
    
  }

  //IR2       Send data in 2nd Slot to Max
  if (IR_2_State && !IR_2_lastState) {
    kai_2 = !kai_2;
    delay(20);
  } 
    IR_2_lastState = IR_2_State;
    
  if(!kai_2){
    digitalWrite(menlight,LOW);
    digitalWrite(blight,LOW);
    
    Serial.print(Zero,DEC);
    Serial.print(" ");
    
  } else if(kai_2){
          if(Page_State == 1){
                digitalWrite(menlight,HIGH);          
                Serial.print(One,DEC); 
                Serial.print(" ");
          } else if( Page_State == 2 ){
                digitalWrite(blight,HIGH);           
                Serial.print(Two,DEC);
                Serial.print(" ");
          }
  }


  //IR3         Send data in 3rd Slot to Max
  if (IR_3_State && !IR_3_lastState) {
    kai_3 = !kai_3;
    delay(20);
  } 
    IR_3_lastState = IR_3_State;
    
  if(!kai_3){
    
    digitalWrite(mountainlight,LOW);
    digitalWrite(clight,LOW);
    
    Serial.print(Zero,DEC);
    Serial.print(" ");
  } else if(kai_3){
          if(Page_State == 1){ 
                digitalWrite(mountainlight,HIGH);
                Serial.print(One,DEC); 
                Serial.print(" ");
          } else if( Page_State == 2 ){
                digitalWrite(clight,HIGH);  
                Serial.print(Two,DEC);
                Serial.print(" ");
          }
  }  
}

//Accelorometer Send data in 4th,5th,6th slot to Max
for (int i=0; i<samples; i++){
  xVal += analogRead(A0);
  yVal += analogRead(A1);
  zVal += analogRead(A2);
  }
  xVal /= samples;
  yVal /= samples;
  zVal /= samples;
 /////////////////change 315 and 400 below
 ///////////////// to whatever your raw value are
  xVal = map(xVal, 315, 400, 0, 255);
  xVal = constrain(xVal, 0, 255);
  yVal = map(yVal, 315, 400, 0, 255);
  yVal = constrain(yVal, 0, 255);
  zVal = map(zVal, 315, 400, 0, 255);
  zVal = constrain(zVal, 0, 255);


  Serial.print(xVal);
  Serial.print(" ");
  Serial.print(yVal);
  Serial.print(" ");
  Serial.println(zVal);
  Serial.print(" ");
  delay(50);
  Serial.print("\r");

}
