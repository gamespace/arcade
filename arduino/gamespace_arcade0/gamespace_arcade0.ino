const int pin_switch = 2;
const int pin_button_count = 8;
const int pin_button_min = 3;
const int pin_button_max = pin_button_min + pin_button_count;
const char keys[] = { 'a', 'd', 'w', 's', ' ', 'n', 'm' , ' '};  // SPACE as a start button, for example for a money slot

// FEEDBACK
const int pin_led    =13;
const int multi_stop =100;          // time multiplier for the LED if keyboard is not running
const int multi_run  = 50;          // time multiplier for the LED if keyboard is running

int ledVal, ledCounter = 0;

// MOUSE
const int pin_mouse_sense = 12;
const int pin_x   = 0;  // A0
const int pin_y   = 1;  // A1

// Copy paste from JoystickMouseControl
int range = 12;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;  

int mouseX,mouseY;

void setup()
{
  pinMode( pin_switch, INPUT_PULLUP );
  
  pinMode(pin_led, OUTPUT);

  for( int i=pin_button_min; i<pin_button_max; ++i )
  {
    pinMode( i, INPUT_PULLUP );
  }
  Keyboard.begin();
  Mouse.begin();
}

void loop()
{
  int stateSwitch = digitalRead( pin_switch );
  
  if( stateSwitch == HIGH )
  {
    int mouseSwitch == digitalRead( pin_mouse_sense );
    if( mouseSwitch == HIGH ){
      mouseX = readAxis(pin_x);
      mouseY = readAxis(pin_y);
      mouse.move( mouseX, mouseX, 0 );
    }

    for( int i=pin_button_min; i<pin_button_max; ++i )
    {
      int buttonState = digitalRead( i );
      
      //Serial.print( "button" );
      //Serial.println( i );
      
      if( buttonState == LOW )
      {
        Keyboard.write( keys[ i - pin_button_min ] );
      }
    }

    if(ledCounter==multi_run)
    {
      ledVal = !ledVal;
      digitalWrite(pin_led, ledVal);
      ledCounter = 0;
    }
    else
    {
      ledCounter++;
    }
  }
  else // stateSwitch == LOW
  {
    if(ledCounter= multi_stop)
    {
      ledVal = !ledVal;
      digitalWrite(pin_led, ledVal);
      ledCounter = 0;
    }
    else
    {
      ledCounter++;
    }
  }

  delay(10);
}

/*
  from JoystickMouseControl

  reads an axis (0 or 1 for x or y) and scales the
 analog input range to a range from 0 to <range>
 */

int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the
  // rest position threshold,  use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;
}


