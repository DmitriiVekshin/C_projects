// Delay если без задержки и он = 0 То он конвертируется в 1. Delay_aproximate вернёт 0 если задержка будет меньше чем разница в цветах начальном и новом
// по сути это косяк только когда она меньше 255 так что для быстрого переключение прога непригода, пока что. ( Даже для задержки 0 или 1 )
// Для фикса нужно завести функцию Delay_aproximate_Fast_change которая будет расчитывать мини задержки и дописать циклы, для случая когда инкримент будет не единицей, хорошо что
// они сейчас представлены переменными,используй это, и напиши условие если Delay_aproximate вернёт 0 то тогда измени инкримент и всё.  

#define R_REDPIN 11 // right side ( motor driver , tapes)
#define R_GREENPIN 10
#define R_BLUEPIN 9
#define L_REDPIN 3 // left side ( motor driver , tapes)
#define L_GREENPIN 5
#define L_BLUEPIN 6
#define R_0_Mono 11 // right side ( motor driver , tapes)
#define R_1_Mono 10
#define L_0_Mono 3
#define L_1_Mono 5 // left side ( motor driver , tapes)
#define L_2_Mono 6




#include <Wire.h>

short int Brig_R_RED = 255;//Actual Brightness Right Red 
short int Brig_R_GREEN = 255;//Actual brightness Right Greed
short int Brig_R_BLUE = 255;//Actual brightness Right Blue
short int Brig_L_RED = 255;//Actual Brightness Left Red
short int Brig_L_GREEN = 255;//Actual Brightness Left Green
short int Brig_L_BLUE = 255;//Actual Brightness Left Blue
short int Brig_L_0_Mono = 255;//Actual Brightness Left zero one-light 
short int Brig_L_1_Mono = 255;//Actual Brightness Left first one-light
short int Brig_L_2_Mono = 255;//Actual Brightness Left second one-light
short int Brig_R_0_Mono = 255;//Actual Brightness Left zero one-light
short int Brig_R_1_Mono = 255;//Actual Brightness Left first one-light
const short int ERROR_PIN = 13;
const short int broadcast = 5;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    


void setup() {
     Serial.begin(9600);
     pinMode(ERROR_PIN, OUTPUT);
     digitalWrite( ERROR_PIN, LOW);
     Wire.begin(8);                // Поменять адресс, для других слееров!
     Wire.onReceive(receiveEvent);            
}

void loop() {
     delay(100);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    


void receiveEvent(int howMany) {
 
  short int mod = Wire.read();    // receive byte as an integer ( choose mod 0 - permament RGB, 1 - permament One-light, 2 - blinking RGB, 3 - blinking one-light)
  
    switch ( mod ) {
        case 0:          
            Perm_Light_RGB(Wire.read(), Wire.read(), Wire.read(), Wire.read(), Wire.read());
            break;
        case 1:
            Perm_Light_One_light(Wire.read(), Wire.read(), Wire.read(), Wire.read());
            break;
        case 2:
            Blinking_RGB(Wire.read(), Wire.read(), Wire.read(), Wire.read(), Wire.read(), Wire.read());
            break;
        case 3:
            Blinking_One_light(Wire.read(), Wire.read(), Wire.read(), Wire.read(), Wire.read(), Wire.read(), Wire.read());
            break;
        default:
            digitalWrite( ERROR_PIN, HIGH);
    }
    
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    

void Perm_Light_RGB ( short int Tape, short int New_Red, short int New_Green, short int New_Blue, short int Del){
    Del = Convert_To_milisec(Del);
    short int inc_RED, inc_GREEN, inc_BLUE;
      if(Tape == 0){
          short int cyc_per_color_change_Red = Delay_aproximate( Brig_L_RED, New_Red, Del);
          if(cyc_per_color_change_Red == 0){
                       inc_RED = Inc_aproximate( Brig_L_RED, New_Red, Del);

          }
          else{
                      inc_RED = (cyc_per_color_change_Red >= 0 ? 1 : -1);

          }
          short int cyc_per_color_change_Green = Delay_aproximate( Brig_L_GREEN, New_Green, Del);
          if(cyc_per_color_change_Green == 0){
                        inc_GREEN = Inc_aproximate( Brig_L_GREEN, New_Green, Del);

          }
          else{
                      inc_GREEN = (cyc_per_color_change_Green >= 0 ? 1 : -1);

          }
          short int cyc_per_color_change_Blue = Delay_aproximate( Brig_L_BLUE, New_Blue, Del);
          if(cyc_per_color_change_Blue == 0){
                       inc_BLUE = Inc_aproximate( Brig_L_BLUE, New_Blue, Del);

          }
          else{
                      inc_BLUE = (cyc_per_color_change_Blue >= 0 ? 1 : -1);

          }
         

    for( int i = 1; i <= Del; i++){
          if(i%cyc_per_color_change_Red == 0){
              Brig_L_RED = Brig_L_RED + inc_RED; 
              analogWrite(L_REDPIN, Brig_L_RED);
          }
          if(i%cyc_per_color_change_Green == 0){
              Brig_L_GREEN = Brig_L_GREEN + inc_GREEN;
              analogWrite(L_GREENPIN, Brig_L_GREEN);
          }
          if(i%cyc_per_color_change_Blue == 0){
              Brig_L_BLUE = Brig_L_BLUE + inc_BLUE;
              analogWrite(L_BLUEPIN, Brig_L_BLUE);
          }    
      delay(1);
    }
}
      if(Tape == 1){
          short int cyc_per_color_change_Red = Delay_aproximate( Brig_R_RED, New_Red, Del);
          if(cyc_per_color_change_Red == 0){
                       inc_RED = Inc_aproximate( Brig_R_RED, New_Red, Del);

          }
          else{
                      inc_RED = (cyc_per_color_change_Red >= 0 ? 1 : -1);

          }
          short int cyc_per_color_change_Green = Delay_aproximate( Brig_R_GREEN, New_Green, Del);
          if(cyc_per_color_change_Green == 0){
                        inc_GREEN = Inc_aproximate( Brig_R_GREEN, New_Green, Del);

          }
          else{
                      inc_GREEN = (cyc_per_color_change_Green >= 0 ? 1 : -1);

          }
          short int cyc_per_color_change_Blue = Delay_aproximate( Brig_R_BLUE, New_Blue, Del);
          if(cyc_per_color_change_Blue == 0){
                       inc_BLUE = Inc_aproximate( Brig_R_BLUE, New_Blue, Del);

          }
          else{
                      inc_BLUE = (cyc_per_color_change_Blue >= 0 ? 1 : -1);

          }

      for( int i = 1; i <= Del; i++){
            if(i%cyc_per_color_change_Red == 0){
                Brig_R_RED = Brig_R_RED + inc_RED; 
                analogWrite(R_REDPIN, Brig_R_RED);
             }
            if(i%cyc_per_color_change_Green == 0){
                Brig_R_GREEN = Brig_R_GREEN + inc_GREEN;
                analogWrite(R_GREENPIN, Brig_R_GREEN);
            }
            if(i%cyc_per_color_change_Blue == 0){
                Brig_R_BLUE = Brig_R_BLUE + inc_BLUE;
                analogWrite(R_BLUEPIN, Brig_R_BLUE);
            }
          if(Wire.read() == 255 ){break;}     
          delay(1);
         }

 

}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    

void Perm_Light_One_light ( short int Driver, short int Tape, short int New_Brightness, short int Del){
      Del = Convert_To_milisec(Del);
      short int cyc_per_color_change;
  short int inc;
  if(Driver == 0){
         if(Tape == 0){
           cyc_per_color_change = Delay_aproximate( Brig_L_0_Mono, New_Brightness, Del);
         if(cyc_per_color_change == 0){
             inc = Inc_aproximate( Brig_L_0_Mono, New_Brightness, Del);
             }
          else{
              inc = (cyc_per_color_change >= 0 ? 1 : -1);
          }
                
               for( int i = 1; i <= Del; i++){
                      if(i%cyc_per_color_change == 0 ){
                            Brig_L_0_Mono = Brig_L_0_Mono + inc; 
                            analogWrite(L_0_Mono, Brig_L_0_Mono);
                       }     
                       delay(1); 
                 }
          }
          else if(Tape == 1){
                cyc_per_color_change = Delay_aproximate( Brig_L_1_Mono, New_Brightness, Del);
                if(cyc_per_color_change == 0){
                inc = Inc_aproximate( Brig_L_1_Mono, New_Brightness, Del);
                  }
               else{
                 inc = (cyc_per_color_change >= 0 ? 1 : -1);
               }
                 
                for( int i = 0; i <= Del; i++){
                       if(i%cyc_per_color_change == 0 ){
                             Brig_L_1_Mono = Brig_L_1_Mono + inc; 
                             analogWrite(L_1_Mono, Brig_L_1_Mono);
                      }     
                      if(Wire.read() == 255 ){break;} 
                      delay(1); 
                }
            }
         else if(Tape == 2){
               cyc_per_color_change = Delay_aproximate( Brig_L_2_Mono, New_Brightness, Del);
               if(cyc_per_color_change == 0){
             inc = Inc_aproximate( Brig_L_2_Mono, New_Brightness, Del);
             }
          else{
              inc = (cyc_per_color_change >= 0 ? 1 : -1);
          }
   
               for( int i = 0; i <= Del; i++){
                       if(i%cyc_per_color_change == 0 ){
                             Brig_L_2_Mono = Brig_L_2_Mono + inc; 
                             analogWrite(L_2_Mono, Brig_L_2_Mono);
                       }     
                       if(Wire.read() == 255 ){break;} 
                       delay(1); 
                       }
               }

  }


  if(Driver == 1){
       if(Tape == 0){
             cyc_per_color_change = Delay_aproximate( Brig_R_0_Mono, New_Brightness, Del);
             if(cyc_per_color_change == 0){
             inc = Inc_aproximate( Brig_R_0_Mono, New_Brightness, Del);
             }
              else{
              inc = (cyc_per_color_change >= 0 ? 1 : -1);
            }
   
       for( int i = 0; i <= Del; i++){
              if(i%cyc_per_color_change == 0 ){
                   Brig_R_0_Mono = Brig_R_0_Mono + inc; 
                   analogWrite(R_0_Mono, Brig_R_0_Mono);
              }     
              delay(1); 
              }
      }
   
    else if(Tape == 1){
           cyc_per_color_change = Delay_aproximate( Brig_R_1_Mono, New_Brightness, Del);
              if(cyc_per_color_change == 0){
               inc = Inc_aproximate( Brig_R_1_Mono, New_Brightness, Del);
               }
              else{
              inc = (cyc_per_color_change >= 0 ? 1 : -1);
          }
   
       for( int i = 0; i <= Del; i++){
            if(i%cyc_per_color_change == 0 ){
                 Brig_R_1_Mono = Brig_R_1_Mono + inc; 
                 analogWrite(R_1_Mono, Brig_R_1_Mono);
             }     
              if(Wire.read() == 255 ){break;} 
              delay(1); 
       }
    }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    

void Blinking_RGB (short int Tape, short int Delay_Off, short int Time_State_Off, short int Delay_On, short int Time_State_On, short int Quantity){
  Delay_Off = Convert_To_milisec(Delay_Off);
  Time_State_Off = Convert_To_milisec(Time_State_Off);
  Delay_On = Convert_To_milisec(Delay_On); 
  Time_State_On = Convert_To_milisec(Time_State_On); 
  short int inc_R_Off;
short int inc_G_Off;
short int inc_B_Off;
short int inc_R_On;
short int inc_G_On;
short int inc_B_On;
  
  if(Tape == 0){
short int cyc_per_color_change_Red_Off = Delay_aproximate( Brig_L_RED, 255, Delay_Off);
short int cyc_per_color_change_Green_Off = Delay_aproximate( Brig_L_GREEN, 255, Delay_Off);
short int cyc_per_color_change_Blue_Off = Delay_aproximate( Brig_L_BLUE, 255, Delay_Off);
short int cyc_per_color_change_Red_On = Delay_aproximate( 255, Brig_L_RED, Delay_On);
short int cyc_per_color_change_Green_On = Delay_aproximate( 255, Brig_L_GREEN, Delay_On);
short int cyc_per_color_change_Blue_On = Delay_aproximate( 255, Brig_L_BLUE, Delay_On);
if(cyc_per_color_change_Red_Off == 0){
                       inc_R_Off = Inc_aproximate( Brig_L_RED, 255, Delay_Off);

          }
          else{
                      inc_R_Off = (cyc_per_color_change_Red_Off >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Green_Off == 0){
                        inc_G_Off = Inc_aproximate( Brig_L_GREEN, 255, Delay_Off);

          }
          else{
                      inc_G_Off = (cyc_per_color_change_Green_Off >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Blue_Off == 0){
                       inc_B_Off = Inc_aproximate( Brig_L_BLUE, 255, Delay_Off);

          }
          else{
                      inc_B_Off = (cyc_per_color_change_Blue_Off >= 0 ? 1 : -1);

          }



 if(cyc_per_color_change_Red_On == 0){
                       inc_R_On = Inc_aproximate( 255, Brig_L_RED, Delay_On);

          }
          else{
                      inc_R_On = (cyc_per_color_change_Red_On >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Green_On == 0){
                        inc_G_On = Inc_aproximate( 255, Brig_L_GREEN, Delay_On);

          }
          else{
                      inc_G_On = (cyc_per_color_change_Green_On >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Blue_On == 0){
                       inc_B_On = Inc_aproximate( 255, Brig_L_BLUE, Delay_On);

          }
          else{
                      inc_B_On = (cyc_per_color_change_Blue_On >= 0 ? 1 : -1);

          }
short int temp_R = Brig_L_RED;
short int temp_G = Brig_L_GREEN;
short int temp_B = Brig_L_BLUE; 
for( int i = 0; i < Quantity; i++){


delay(Time_State_On);

for( int i = 0; i <= Delay_Off; i++){
  if(i%cyc_per_color_change_Red_Off==0){
    temp_R = temp_R + inc_R_Off; 
    analogWrite(L_REDPIN, temp_R);
  }
  if(i%cyc_per_color_change_Green_Off==0){
     temp_G = temp_G + inc_G_Off;
    analogWrite(L_GREENPIN, temp_G);
  }
  if(i%cyc_per_color_change_Blue_Off==0){
    temp_B = temp_B + inc_B_Off;
    analogWrite(L_BLUEPIN, temp_B);
  }     
delay(1);
}

delay( Time_State_Off );

for( int i = 0; i <= Delay_On; i++){
  if(i%cyc_per_color_change_Red_On==0){
    temp_R = temp_R + inc_R_On; 
    analogWrite(L_REDPIN, temp_R);
  }
  if(i%cyc_per_color_change_Green_On==0){
     temp_G = temp_G + inc_G_On;
    analogWrite(L_GREENPIN, temp_G);
  }
  if(i%cyc_per_color_change_Blue_On==0){
    temp_B = temp_B + inc_B_On;
    analogWrite(L_BLUEPIN, temp_B);
  }     
delay(1);
}

  if(Wire.read() == 255 ){break;}
}
}



  if(Tape == 1){
short int cyc_per_color_change_Red_Off = Delay_aproximate( Brig_R_RED, 255, Delay_Off);
short int cyc_per_color_change_Green_Off = Delay_aproximate( Brig_R_GREEN, 255, Delay_Off);
short int cyc_per_color_change_Blue_Off = Delay_aproximate( Brig_R_BLUE, 255, Delay_Off);
short int cyc_per_color_change_Red_On = Delay_aproximate( 255, Brig_R_RED, Delay_On);
short int cyc_per_color_change_Green_On = Delay_aproximate( 255, Brig_R_GREEN, Delay_On);
short int cyc_per_color_change_Blue_On = Delay_aproximate( 255, Brig_R_BLUE, Delay_On);
 if(cyc_per_color_change_Red_Off == 0){
                       inc_R_Off = Inc_aproximate( Brig_R_RED, 255, Delay_Off);

          }
          else{
                      inc_R_Off = (cyc_per_color_change_Red_Off >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Green_Off == 0){
                        inc_G_Off = Inc_aproximate( Brig_R_GREEN, 255, Delay_Off);

          }
          else{
                      inc_G_Off = (cyc_per_color_change_Green_Off >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Blue_Off == 0){
                       inc_B_Off = Inc_aproximate( Brig_R_BLUE, 255, Delay_Off);

          }
          else{
                      inc_B_Off = (cyc_per_color_change_Blue_Off >= 0 ? 1 : -1);

          }



 if(cyc_per_color_change_Red_On == 0){
                       inc_R_On = Inc_aproximate( 255, Brig_R_RED, Delay_On);

          }
          else{
                      inc_R_On = (cyc_per_color_change_Red_On >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Green_On == 0){
                        inc_G_On = Inc_aproximate( 255, Brig_R_GREEN, Delay_On);

          }
          else{
                      inc_G_On = (cyc_per_color_change_Green_On >= 0 ? 1 : -1);

          }
          
          if(cyc_per_color_change_Blue_On == 0){
                       inc_B_On = Inc_aproximate( 255, Brig_R_BLUE, Delay_On);

          }
          else{
                      inc_B_On = (cyc_per_color_change_Blue_On >= 0 ? 1 : -1);

          }

short int temp_R = Brig_R_RED;
short int temp_G = Brig_R_GREEN;
short int temp_B =Brig_R_BLUE; 
for( int i = 0; i < Quantity; i++){


delay(Time_State_On);

for( int i = 0; i <= Delay_Off; i++){
  if(i%cyc_per_color_change_Red_Off==0){
    temp_R = temp_R + inc_R_Off; 
    analogWrite(R_REDPIN, temp_R);
  }
  if(i%cyc_per_color_change_Green_Off==0){
     temp_G = temp_G + inc_G_Off;
    analogWrite(R_GREENPIN, temp_G);
  }
  if(i%cyc_per_color_change_Blue_Off==0){
    temp_B = temp_B + inc_B_Off;
    analogWrite(R_BLUEPIN, temp_B);
  }     
delay(1);
}

delay( Time_State_Off );

for( int i = 0; i <= Delay_On; i++){
  if(i%cyc_per_color_change_Red_On==0){
    temp_R = temp_R + inc_R_On; 
    analogWrite(R_REDPIN, temp_R);
  }
  if(i%cyc_per_color_change_Green_On==0){
     temp_G = temp_G + inc_G_On;
    analogWrite(R_GREENPIN, temp_G);
  }
  if(i%cyc_per_color_change_Blue_On==0){
    temp_B = temp_B + inc_B_On;
    analogWrite(R_BLUEPIN, temp_B);
  }     
delay(1);
}

}
}


}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    

void Blinking_One_light (short int Driver, short int Tape, short int Delay_Off, short int Time_State_Off, short int Delay_On, short int Time_State_On, short int Quantity){
  
  short int cyc_per_color_change_Off;
  short int cyc_per_color_change_On;
  short int temp_Brig;
  short int temp_Pin;
  
  Delay_Off = Convert_To_milisec(Delay_Off);
  Time_State_Off = Convert_To_milisec(Time_State_Off);
  Delay_On = Convert_To_milisec(Delay_On); 
  Time_State_On = Convert_To_milisec(Time_State_On);
 
 
 if(Driver == 0){
   if(Tape == 0){
  cyc_per_color_change_Off = Delay_aproximate( Brig_L_0_Mono, 255, Delay_Off);
  cyc_per_color_change_On = Delay_aproximate( 255, Brig_L_0_Mono, Delay_On);
  temp_Brig = Brig_L_0_Mono;
  temp_Pin = L_0_Mono;
  
   }
   else if(Tape == 1){
  cyc_per_color_change_Off = Delay_aproximate( Brig_L_1_Mono, 255, Delay_Off);
  cyc_per_color_change_On = Delay_aproximate( 255, Brig_L_1_Mono, Delay_On);
  temp_Brig = Brig_L_1_Mono;
  temp_Pin = L_1_Mono;
   }

   else if(Tape == 2){
  cyc_per_color_change_Off = Delay_aproximate( Brig_L_2_Mono, 255, Delay_Off);
  cyc_per_color_change_On = Delay_aproximate( 255, Brig_L_2_Mono, Delay_On);
  temp_Brig = Brig_L_2_Mono;
  temp_Pin = L_2_Mono;
   }
   
short int inc_Off;
short int inc_On;

          if(cyc_per_color_change_Off == 0){
             inc_Off = Inc_aproximate( temp_Brig, 255, Delay_Off);
             }
          else{
              inc_Off = (cyc_per_color_change_Off >= 0 ? 1 : -1);
          }
          if(cyc_per_color_change_On == 0){
             inc_On = Inc_aproximate( 255, temp_Brig, Delay_On);
             }
          else{
              inc_On = (cyc_per_color_change_On >= 0 ? 1 : -1);
          }

for( int i = 0; i < Quantity; i++){


delay(Time_State_On);

for( int i = 0; i <= Delay_Off; i++){
  if(i%cyc_per_color_change_Off==0){
    temp_Brig = temp_Brig + inc_Off; 
    analogWrite(temp_Pin, temp_Brig);
  }     
delay(1);
}

delay( Time_State_Off );

for( int i = 0; i <= Delay_On; i++){
  if(i%cyc_per_color_change_On==0){
    temp_Brig = temp_Brig + inc_On; 
    analogWrite(temp_Pin, temp_Brig);
  }
 
delay(1);
}

}
}



 if(Driver == 1){
   if(Tape == 0){
  cyc_per_color_change_Off = Delay_aproximate( Brig_R_0_Mono, 255, Delay_Off);
  cyc_per_color_change_On = Delay_aproximate( 255, Brig_R_0_Mono, Delay_On);
  temp_Brig = Brig_R_0_Mono;
  temp_Pin = R_0_Mono;
  
   }
   else if(Tape == 1){
  cyc_per_color_change_Off = Delay_aproximate( Brig_R_1_Mono, 255, Delay_Off);
  cyc_per_color_change_On = Delay_aproximate( 255, Brig_R_1_Mono, Delay_On);
  temp_Brig = Brig_R_1_Mono;
  temp_Pin = R_1_Mono;
   }


short int inc_Off;
short int inc_On;

          if(cyc_per_color_change_Off == 0){
             inc_Off = Inc_aproximate( temp_Brig, 255, Delay_Off);
             }
          else{
              inc_Off = (cyc_per_color_change_Off >= 0 ? 1 : -1);
          }
          if(cyc_per_color_change_On == 0){
             inc_On = Inc_aproximate( 255, temp_Brig, Delay_On);
             }
          else{
              inc_On = (cyc_per_color_change_On >= 0 ? 1 : -1);
          }


for( int i = 0; i < Quantity; i++){


delay(Time_State_On);

for( int i = 0; i <= Delay_Off; i++){
  if(i%cyc_per_color_change_Off==0){
    temp_Brig = temp_Brig + inc_Off; 
    analogWrite(temp_Pin, temp_Brig);
  }     
delay(1);
}

delay( Time_State_Off );

for( int i = 0; i <= Delay_On; i++){
  if(i%cyc_per_color_change_On==0){
    temp_Brig = temp_Brig + inc_On; 
    analogWrite(temp_Pin, temp_Brig);
  }
 
delay(1);
}

  if(Wire.read() == 255 ){break;}
}
}


}



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    



int Delay_aproximate (  short int Actual_Color,  short int New_Color,  int del){
      short int diff = New_Color - Actual_Color;
      short int cyc_per_color = del / diff;      
      return cyc_per_color;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------    
int Inc_aproximate (  short int Actual_Color,  short int New_Color,  int del){
      short int diff = New_Color - Actual_Color;
      short int inc_per_cycle =  diff / del ;      
      return inc_per_cycle;
}

int Convert_To_milisec ( int to_convert){
      return (to_convert == 0 ? 1 : to_convert * 100);
}
