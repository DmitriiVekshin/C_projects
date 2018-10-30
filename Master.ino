#include <Wire.h>


void Permanent_Light_RGB();
void Permanent_Light_One_Light();
void Blinking_Light_RGB();
void Blinking_Light_One_Light();



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
const short int ERROR_PIN = 13;
short int type_of_tape; // 1 - One-light, 0 - RGB 
short int blinking; // 1 - blinking mod, 0 - permanent light mod




//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup(){
  Wire.begin();
  Serial.begin(9600);
  pinMode(ERROR_PIN, OUTPUT);
  digitalWrite( ERROR_PIN, LOW);
  
}



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop(){
  if (Serial.available())
   {    
   type_of_tape = (Serial.read() );
   
   if(Serial.read() != ':'){
   digitalWrite( ERROR_PIN, HIGH);
    }
    
   blinking = (Serial.read() );
   
   if(Serial.read() != ':'){
   digitalWrite( ERROR_PIN, HIGH);
    }
    
   if(blinking == 0 && type_of_tape == 0){
    Permanent_Light_RGB();
    }
   
  else if(blinking == 0 && type_of_tape == 1){
   Permanent_Light_One_Light ();   
   }

  else if(blinking == 1 && type_of_tape == 0){
   Blinking_Light_RGB();   
   }

  else if(blinking == 1 && type_of_tape == 0){
   Blinking_Light_One_Light();   
   }
   }
   
   delay(1);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Permanent_Light_RGB (){
      Wire.beginTransmission(Serial.read());  // received ADDRESS of device and start transmitting
          Wire.write(0); // mod flag
          
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read());  // Number of RGB led tape on ARDUINO slaver , 0 - left, 1 - right 

      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);            
            }
      
      Wire.write(Serial.read()); // Send red color;
          
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
                  
      Wire.write(Serial.read()); // Send green color;
          
          
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // Send blue color;

      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // delay before ligth on new color ( expected a time in 0.1 sec)
      
      
     
      Wire.endTransmission();    // stop transmitting
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Permanent_Light_One_Light(){
      Wire.beginTransmission(Serial.read());  // received ADDRESS of device and start transmitting
          Wire.write(1); // mod flag
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read());  // Number MOTOR DRIVER , 0 - left, 1 - right 
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // Number of tape;
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // Tapes brightness ;
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }

      
      Wire.write(0); // Flag for one-light case
           
      Wire.write(Serial.read()); // delay before ligth on new color ( expected a time in 0.1 sec)
      
      Wire.endTransmission();    // stop transmitting
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Blinking_Light_RGB (){
      Wire.beginTransmission(Serial.read());  // received ADDRESS of device and start transmitting
          Wire.write(2); // mod flag
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read());  // Number of RGB tape on ARDUINO slaver , 0 - left , 1 - right
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(0); // flag for RGB case
      
      Wire.write(Serial.read()); // Delay before light off;  ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // Time without light ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // Delay before light on ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
      
      Wire.write(Serial.read()); // Time with light ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
       
      Wire.write(Serial.read()); // Quantity of blinks
      Wire.endTransmission();    // stop transmitting
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Blinking_Light_One_Light(){
      Wire.beginTransmission(Serial.read());  // received ADDRESS of device and start transmitting
          Wire.write(3); // mod flag 
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
          
      Wire.write(Serial.read());  // Number of MOTOR DRIVER on ARDUINO slaver , 0 - left , 1 - right
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
            
      Wire.write(Serial.read()); // Choosing of device ( expected a number of the tape 0 - 2 for left motor and 0 - 1 for right)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
           
      Wire.write(Serial.read()); // Delay before light off; 1st byte ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
           
      Wire.write(Serial.read()); // Time without light  ( expected a time in 0.1 sec)  
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
           
      Wire.write(Serial.read()); // Delay before light on ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
            
      Wire.write(Serial.read()); // Time with light ( expected a time in 0.1 sec)
      
          if(Serial.read() != ':'){
            Wire.endTransmission();
            digitalWrite( ERROR_PIN, HIGH);
            }
          
      Wire.write(Serial.read()); // Quantity of blinks
      Wire.endTransmission();    // stop transmitting
}

 
