#include <Servo.h>

//simple leds
int bathroom = A0; //  a/b
int bedroom1 = A1; //  c/d
int bedroom2 = A2; // e/f  
int kitchen = A3; // g/h
int living = A4; // i/j
int parking = A5; //k/l
int storage = 2; //m/n

//window sensor this can be changed 
//once sensor I/O type detected
int window = 9;

//door servo
Servo servoMotor;
int door= 10; // o/p

//Analog rgb color led
int red = 3;
int green = 5;
int blue = 6;

long colorValue;

//handler for serial input
const byte numChars = 32;
char receivedChars[numChars];   

boolean newData = false;


void setup() {
  // put your setup code here, to run once:
  //start serial 
  Serial.begin(9600);

  //initialize led pins as output
  pinMode(bathroom, OUTPUT);
  pinMode(bedroom1, OUTPUT);
  pinMode(bedroom2, OUTPUT);
  pinMode(kitchen, OUTPUT);
  pinMode(living, OUTPUT);
  pinMode(parking, OUTPUT);
  pinMode(storage, OUTPUT);

  //read data from sensor (window state) 
  pinMode(window, INPUT);

  //attach servo to pin door
  servoMotor.attach(door);

  //set rgb led outputs
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  //delimiter to indicate arduinio is ready to recive data 
  while(!Serial);
  Serial.println("Ready");
  

}

void loop() {
  
  recvWithEndMarker();
  showNewData();
  handleSerialInput();
  windowHandler();
  
  if(colorValue > 0)
  {
    setColor(colorValue);
    }
 
   
}


//function to control main leds 
void handleSerialInput() {
 if (receivedChars) {
 long rChar = receivedChars[0];
 
 switch (rChar) {
    case 'a':
      digitalWrite(bathroom,HIGH);
      Serial.println("bath on");
      break;
      
    case 'b':
     digitalWrite(bathroom,LOW);
     Serial.println("bath off");
      break;
      
     case 'c':
      digitalWrite(bedroom1,HIGH);
      Serial.println("bedrrom1 on");
      
      break;
    case 'd':
     digitalWrite(bedroom1,LOW);
     Serial.println("bedrrom1 off");
      break;

      case 'e':
      digitalWrite(red,HIGH);
      
    
      Serial.println("bedrrom2 on"); 
      break;
    case 'f':
     digitalWrite(bedroom2,LOW);
   
     Serial.println("bedrrom2 off");
      break;

      case 'g':
      digitalWrite(kitchen,HIGH);
      Serial.println("kitchen on");
      
      break;
    case 'h':
     digitalWrite(kitchen,LOW);
     Serial.println("kitchen off");
      break;

      case 'i':
      digitalWrite(living,HIGH);
      Serial.println("living on");
      
      break;
    case 'j':
     digitalWrite(living,LOW);
     Serial.println("living off");
      break;

      case 'k':
      digitalWrite(parking,HIGH);
      Serial.println("parking on");
      
      break;
    case 'l':
     digitalWrite(parking,LOW);
     Serial.println("parking off");
      break;

      case 'm':
      digitalWrite(storage,HIGH);
      Serial.println("storage on");
      
      break;
    case 'n':
     digitalWrite(storage,LOW);
     Serial.println("storage off");
      break;

      case 'o':
       servoMotor.write(180);
       Serial.println("open Door");;
      
      break;
    case 'p':
      servoMotor.write(0);
      Serial.println("close door");
      break;

      default:
      colorValue = strtol(&receivedChars[1], (char **) '\0', 16);
      //Serial.println(colorValue, HEX);
      break;
      
      
      }
 }
}


void windowHandler()
{
  //this data shoud get from sensor 
  //int temp= digitalRead(window);
  int temp = random(255);
  // change fucntion according sensor value
  if(temp > 128)
  {
     Serial.println("wopen");
    }
    else{
       Serial.println("wclosed");
      }
  
  delay(1000);
  
}


void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        newData = false;
    }
}

void setColor(long color) {
  analogWrite(red, color >> 16);
  analogWrite(green, color >> 8 & 0xFF);
  analogWrite(blue, color & 0xFF);
  Serial.print("Led Color setted to ");
  Serial.println(color, HEX);
}
