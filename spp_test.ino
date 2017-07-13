 
  
// include the library code:
#include <LiquidCrystal.h>
  
#define START_CMD_CHAR '*'
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'
#define CMD_DIGITALWRITE 10
#define CMD_ANALOGWRITE 11
#define CMD_TEXT 12
#define CMD_READ_ARDROID 13
#define MAX_COMMAND 20  
#define MIN_COMMAND 10  
#define IN_STRING_LENGHT 40
#define MAX_ANALOGWRITE 255
#define PIN_HIGH 3
#define PIN_LOW 2

LiquidCrystal MyLCD(12, 11, 5, 4, 3, 2); // Definining LCD.
//  char data = 0;                //Variable for storing received data

String inText;
  
  void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(13, OUTPUT);        //Sets digital pin 13 as output pin

   MyLCD.begin(16, 2); // Initializing 16X2 LCD.
   MyLCD.home(); // Home location : 0,0 
   MyLCD.print("BT testing"); // Print on LCD.
   MyLCD.setCursor(0, 1);
   MyLCD.print("16x2 LCD init...");
   delay(2000);
    MyLCD.home();   // Cursor set to 0,0
  MyLCD.print("Command from mobile");
 
   
}

void loop() {
 MyLCD.clear();  // Clearing LCD
 MyLCD.setCursor(0,1); 
  
     // Setting cursor 2nd row first column
  int ard_command = 0;
  int pin_num = 0;
  int pin_value = 0;

  char get_char = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  get_char = Serial.read();
  if(get_char == '1')  {          //Checks whether value of data is equal to 1 
      digitalWrite(13, HIGH);  //If value is 1 then LED turns ON
        MyLCD.print("LED ON");  // Printing counter value.
           Serial.println("LED ON");
        delay(1000);     
    } else if(get_char == '0')    {   //Checks whether value of data is equal to 0
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF
        MyLCD.print("LED OFF");  // Printing counter value.
   Serial.println("LED OFF");
  delay(1000);     
    }else if (get_char == START_CMD_CHAR) {
      Serial.println("got start command char");
 // parse incoming command type
  ard_command = Serial.parseInt(); // read the command
  // 1) GET TEXT COMMAND FROM ARDROID
  if (ard_command == CMD_TEXT){   
    inText =""; //clears variable for new input   
  String str =  Serial.readStringUntil(END_CMD_CHAR);
  Serial.println(str);
  set_digitalwrite(str);
    }
  }
}
void set_digitalwrite(String text){
   Serial.print(text);        //Print Value inside data in Serial monitor
        MyLCD.print(text);  // Printing counter value.
 delay(1000);   
    if(text == "1")  {          //Checks whether value of data is equal to 1 
      digitalWrite(13, HIGH);  //If value is 1 then LED turns ON
    } else if(text == "0")    {   //Checks whether value of data is equal to 0
      digitalWrite(13, LOW);   //If value is 0 then LED turns OFF    
    }
        
}


