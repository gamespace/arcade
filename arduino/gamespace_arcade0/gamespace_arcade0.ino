const int pin_switch = 2;
const int pin_button_count = 7;
const int pin_button_min = 3;
const int pin_button_max = pin_button_min + pin_button_count;
const char keys[] = { 'a', 'd', 'w', ' ', 'n', 'm' };

void setup()
{
  pinMode( pin_switch, INPUT_PULLUP );
  
  for( int i=pin_button_min; i<pin_button_max; ++i )
  {
    pinMode( i, INPUT_PULLUP );
  }
}

void loop()
{
  int stateSwitch = digitalRead( pin_switch );
  if( stateSwitch == HIGH )
  {
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
  }
}

