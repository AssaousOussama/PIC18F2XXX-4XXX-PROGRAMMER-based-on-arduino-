///**********************************************************************************************///
///                            >>  PIC18F2XXX/4XXX  PROGRAMMER  <<                               ///
///                                created by : Assaous Oussama                                  ///
///  programme description : this program is for programing the PIC18F2XXX/4XXX microcontroller  ///
///                                 date : 25/09/2020  19:36                                     ///
///**********************************************************************************************///

#include "BufferConfig.h"

#define ERASE  0
#define PROGM  1
#define CONFIG 2
#define IDV    3
#define EEPROG 4

#define VPP    2  
#define PGM    5 
#define PGC    4 
#define PGD    3 


char instBuffer,bitselect,comp;
int bitnumbr;
char buffin[100];
int i,j,k,p,z,addr,addrh,data;
int num;
int val,val1,val2;

bool WR =true;

void startLowProg();
void endprog();
void EraseDevice();
void program();
void eepromWrite();
void idWrite();
void configWrite();
void senddata(int,int,int);

void setup() {

  Serial.end();

  pinMode(VPP,OUTPUT);
  pinMode(PGM,OUTPUT);
  pinMode(PGC,OUTPUT);
  pinMode(PGD,OUTPUT);

  digitalWrite(VPP,LOW);
  digitalWrite(PGM,LOW);
  digitalWrite(PGC,LOW);
  digitalWrite(PGD,LOW);
  
  Serial.begin(57600);

}

void loop() {
 
i=0;


 if(Serial.available()  == 38 ) 
 {
  
   num = Serial.available();
   while (i < num )
   {  
    buffin[i] = Serial.read();
    i++;
   }

   
   if(buffin[0] == 'P' && buffin[1] == 'I' && buffin[2] == 'C' && buffin[3] == 'P' && buffin[4] == 'R' && buffin[5] == 'O' && buffin[6] == 'G' && buffin[7] == '!')
   {
     startLowProg();
     Serial.write("YESIAM");
   }
   if(buffin[0] == 'E' && buffin[1] == 'R' && buffin[2] == 'E' && buffin[3] == 'S' )
   {
     EraseDevice();
     Serial.write("DONE");
   }
   if(buffin[0] == 'P' && buffin[1] == 'R' && buffin[2] == 'O'  )
   {
     program();
     Serial.write("*OK*");
   }
   if(buffin[0] == 'U' && buffin[1] == 'S' && buffin[2] == 'I' && buffin[3] == 'D' )
   {
     idWrite();
     Serial.write("*OK*");
   }
   if(buffin[0] == 'E' && buffin[1] == 'E' && buffin[2] == 'P' && buffin[3] == 'R' )
   {
      eepromWrite();
     Serial.write("*OK*");
   }
   if(buffin[0] == 'C' && buffin[1] == 'O' && buffin[2] == 'N' && buffin[3] == 'F' && buffin[4] == 'I' && buffin[5] == 'G')
   {
     configWrite();
     Serial.write("*OK*");
   }
   if(buffin[0] == 'O' && buffin[1] == 'F' )
   {
     endprog();
     Serial.write("*OK*");
   }


   buffin[0] = 0x00;
   buffin[1] = 0x00;
   buffin[2] = 0x00;
   buffin[3] = 0x00;
   buffin[4] = 0x00;
   buffin[5] = 0x00;
   buffin[6] = 0x00;
   
 } 

}

///***************************************************///
///           FUNCTION : startLowProg                 ///
///          OUTPUT : start programming               ///
///***************************************************///

void startLowProg()
{
  digitalWrite(PGM,HIGH);
  delay(10);
  digitalWrite(VPP,HIGH);
  delay(2);
}
///***************************************************///

///***************************************************///
///               FUNCTION : endprog()                ///
///             OUTPUT :  end programming             ///                              
///***************************************************///
void endprog()
{
  digitalWrite(PGD,LOW);
  digitalWrite(PGC,LOW);
  delay(4);
  digitalWrite(VPP,LOW);
  delay(4);
  digitalWrite(PGM,LOW);   
  delay(1000);
  digitalWrite(VPP,HIGH);
}
//****************************************************///

///***************************************************///
///            FUNCTION : EraseDevice()               ///
///      OUTPUT : erase the holl device memory        ///
///***************************************************///
void EraseDevice()
{
  senddata(0,16,ERASE);
  digitalWrite(PGD,LOW);
  delay(5);
}
///***************************************************///

///***************************************************///
///               FUNCTION : program()                ///
///        OUTPUT : program the memory program        ///
///***************************************************///
void program()
{
  ProgramBuffer[3][1] = buffin[3];
  ProgramBuffer[5][1] = buffin[4];
  ProgramBuffer[7][1] = buffin[5];

  j=6;
  for(i = 9 ; i<=24 ; i++)
  {
    ProgramBuffer[i][0] = buffin[j+1];
    ProgramBuffer[i][1] = buffin[j];
    j+=2;
  }
  senddata(0,26,PROGM); 
}
///**************************************************///

///**************************************************///
///             FUNCTION : idWrite()                 ///
///     OUTPUT : write the id data to PIC18F         ///
///**************************************************///
void idWrite()
{
  j=8;
  for(p = 4 ; p<=11 ; p+=2)
  {
  idBuffer[j][0] = buffin[p] ;
  idBuffer[j][1] = buffin[p+1] ;
  j++;
  }
  senddata(0,13,IDV);
} 
///**************************************************///

///**************************************************///
///          FUNCTION : void eepromWrite()           ///
///      OUTPUT : program the EEPROM memory          ///
///**************************************************///
void eepromWrite()
{
  senddata(0,2,EEPROG);
  eeprombuffer[2][1] = buffin[5];
  eeprombuffer[4][1] = buffin[4];
  addr = buffin[5]; 
  addrh = buffin[4];
  for(p = 6 ; p<=38 ; p++)
  { 
    eeprombuffer[6][1] = buffin[p];
    senddata(2,10,EEPROG);
    
   while(WR)
   {
    senddata(10,14,EEPROG);
   } 
   
   WR =true;
   delayMicroseconds(200);
   if(addr == 0xff)
   {
      addrh++;
      addr = 0;
   }
   else  addr++;
   eeprombuffer[2][1] = addr; 
   eeprombuffer[4][1] = addrh; 
   senddata(14,15,EEPROG);   
  } 
}
///**************************************************///

///**************************************************///
///             FUNCTION : configWrite()             ///
///     OUTPUT : program the configuration bits      ///
///**************************************************///
void configWrite()
{
 senddata(0,6,CONFIG);
 j=0;
 for(p = 6 ; p <=18 ; p+=2)
 {
   configbuffer[6][1] = j;
   configbuffer[10][1] = j+1;
   configbuffer[8][1] = buffin[p];
   configbuffer[12][0] = buffin[p+1];
   senddata(6,14,CONFIG);
   j+=2;
 } 
}
///**************************************************///


///**************************************************///
///              FUNCTION : senddata()               ///
///       OUTPUT : send data to the PIC18F           ///
///**************************************************///
void senddata(int startbyte,int stopbyte,int bufselect)
{
  
for(j = startbyte ; j <stopbyte ; j++)
  {
    for(k=2;k>=0;k--)
    {
       bitselect = 0x1;

       switch(bufselect)
       {
         case ERASE :
         {
            instBuffer = EraseBufer[j][k];
         }
         break;
         case PROGM:
         {
            instBuffer = ProgramBuffer[j][k];
         }
         break;
         case CONFIG:
         {
            instBuffer = configbuffer[j][k];
         }
         break;
         case IDV : 
         {
            instBuffer = idBuffer[j][k];
         }
         break;
         case EEPROG :
         {
            instBuffer = eeprombuffer[j][k];
         }
         break;
       }

       if(k == 2)
       {
         bitnumbr = 4;
       }
        else
       {
         bitnumbr = 8;
       }

      for(i=0;i<bitnumbr;i++)
      {
       comp = 0x00;
       comp = bitselect & instBuffer ; 
       
        if(comp == bitselect)
        {
          digitalWrite(PGD,HIGH);
        }
        else if(comp == 0x00) {
          digitalWrite(PGD,LOW); 
        }

        if(bufselect == ERASE && j == (stopbyte-1) && i == 3 && k == 2 )
        {
          digitalWrite(PGC,HIGH);
          delayMicroseconds(10);
          digitalWrite(PGC,LOW);
          digitalWrite(PGD,LOW); 
          delay(6);
        }
        else if(bufselect == PROGM && j == (stopbyte-1) && i == 3 && k == 2 )
        {
          digitalWrite(PGC,HIGH);
          delay(2);
          digitalWrite(PGC,LOW);
          delayMicroseconds(500);
        }
        else if( bufselect == CONFIG && j == (stopbyte-1) && i == 3 && k == 2  && startbyte == 6)
        {
          digitalWrite(PGC,HIGH);
          delay(2);
          digitalWrite(PGC,LOW);
          delayMicroseconds(500);
        }
        else if( bufselect == IDV &&  j == (stopbyte-1) && i == 3 && k == 2 )
        {
          digitalWrite(PGC,HIGH);
          delay(2);
          digitalWrite(PGC,LOW);
          delayMicroseconds(500);
        }
        else if( bufselect == EEPROG &&  j == (stopbyte-1) && i == 7 && k == 1 && startbyte == 10)
        {    
          digitalWrite(PGC,HIGH);
          delayMicroseconds(10);
          digitalWrite(PGC,LOW);
          delayMicroseconds(10);
          digitalWrite(PGD,LOW);
          pinMode(PGD,INPUT);

             val1 =0x00;
             val = 0x00;
             val2 = 0x00;
          for(z= 0 ;z<8;z++)
          {
            val1 = val1 << 1;
            digitalWrite(PGC,HIGH);
            delayMicroseconds(10);
            digitalWrite(PGC,LOW);
            delayMicroseconds(10);
            val = digitalRead(PGD);
            val1 = val1 | val;          
          }
          val1 = val1 & 0x40;
          if(val1 == 0x00) 
          {
            WR = false ;
          }
          else 
          {
           WR = true ;
          }

          k= -1;
          pinMode(PGD,OUTPUT);
        }
        else
        {
          digitalWrite(PGC,HIGH);
          delayMicroseconds(10);
          digitalWrite(PGC,LOW);
          delayMicroseconds(10);
        }
         bitselect = bitselect << 1; 
      }
    }
  } 
}

///**************************************************///
