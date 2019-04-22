//Chorus Chords v2
//By Andy Younie 20/04/2019
//Chords are based on Microwriter chords (see https://www.microsoft.com/buxtoncollection/a/pdf/Microwriter%20New%20Users%20Guide.pdf)

///////////////////////////////////////////////////////////////////
//Mostly working - need to work out how to pass key names like   //
//'KEY_DELETE' to the pressRelease function so that I can cancel //
//meta keys as appropriate.                                      //
//Some characters are not being sent correctly - e.g. €          //
///////////////////////////////////////////////////////////////////

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

int numKeys = 7; // The number of physical switches being used
int chord[] = {0, 0, 0, 0, 0, 0, 0}; // Make an empty array to hold the chord
int building = 0; // since we're not building a chord at the moment
int out = 0; // will hold the decimal representation of the chord
int key = 0; // the ascii code of the key we will type on the keyboard
// Meta Keys
int shift = 0; // have we pressed the SHIFT chord
int alt = 0; // have we pressed the ALT chord
int ctrl = 0; // have we pressed the CTRL chord
int win = 0; // have we pressed the WIN chord
// Modes
int mode2 = 0; // have we pressed second mode chord
int mode3 = 0; // have we pressed third mode chord
int mode4 = 0; // have we pressed fourth mode chord

#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3
#define BUTTON4_PIN 4
#define BUTTON5_PIN 5
#define BUTTON6_PIN 6
#define BUTTON7_PIN 7
#define LED1_PIN 8 // PIN for LED - 11 is the built in LED for testing purposes. I have connected a 3mm blue LED in series with a 220ohm Resistor between pin 8 and GND

       Bounce debouncer1 = Bounce(); // Instantiate a Bounce object
       Bounce debouncer2 = Bounce(); // Instantiate a Bounce object
       Bounce debouncer3 = Bounce(); // Instantiate a Bounce object
       Bounce debouncer4 = Bounce(); // Instantiate a Bounce object
       Bounce debouncer5 = Bounce(); // Instantiate a Bounce object
       Bounce debouncer6 = Bounce(); // Instantiate a Bounce object
       Bounce debouncer7 = Bounce(); // Instantiate a Bounce object 

       
//Functions here
void pressRelease(char keyToPress){
  Keyboard.press(keyToPress);
  Keyboard.release(keyToPress);
  if(shift == 1){//shift was on for a single character 
    Keyboard.release(KEY_LEFT_SHIFT);
    Serial.write("Shift Released");
    shift = 0; //shift is released, so set it back to 0
  }
    if(ctrl == 1){//ctrl was on for a single character 
    Keyboard.release(KEY_LEFT_CTRL);
    Serial.write("CTRL Released");
    ctrl = 0; //ctrl is released, so set it back to 0
  }
    if(alt == 1){//alt was on for a single character 
    Keyboard.release(KEY_LEFT_ALT);
    Serial.write("Alt Released");
    alt = 0; //alt is released, so set it back to 0
  }
    if(win == 1){//win was on for a single character 
    Keyboard.release(KEY_LEFT_GUI);
    Serial.write("Win Released");
    win = 0; //win is released, so set it back to 0
  }
    if(mode2 == 1){//mode2 was on for a single character 
    Serial.write("Mode2 Released");
    mode2 = 0; //mode2 is released, so set it back to 0
    digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
  }
    if(mode3 == 1){//mode3 was on for a single character 
    Serial.write("Mode3 Released");
    mode3 = 0; //mode3 is released, so set it back to 0
    digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
  }
    if(mode4 == 1){//mode4 was on for a single character 
    Serial.write("Mode4 Released");
    mode4 = 0; //mode2 is released, so set it back to 0
    digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
  }

}


//End of functions

void setup() {
       debouncer1.attach(BUTTON1_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       debouncer2.attach(BUTTON2_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       debouncer3.attach(BUTTON3_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       debouncer4.attach(BUTTON4_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       debouncer5.attach(BUTTON5_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       debouncer6.attach(BUTTON6_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       debouncer7.attach(BUTTON7_PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
       
       debouncer1.interval(25); // Use a debounce interval of 25 milliseconds
       debouncer2.interval(25); // Use a debounce interval of 25 milliseconds
       debouncer3.interval(25); // Use a debounce interval of 25 milliseconds
       debouncer4.interval(25); // Use a debounce interval of 25 milliseconds
       debouncer5.interval(25); // Use a debounce interval of 25 milliseconds
       debouncer6.interval(25); // Use a debounce interval of 25 milliseconds
       debouncer7.interval(25); // Use a debounce interval of 25 milliseconds

       pinMode(LED1_PIN, OUTPUT); // initialize the digital pin as an output.
       //digitalWrite(LED1_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
       //digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
}

void loop() {

        debouncer1.update(); 
        debouncer2.update();
        debouncer3.update();
        debouncer4.update();
        debouncer5.update();
        debouncer6.update();
        debouncer7.update();
        
        int value1 = debouncer1.read();
        int value2 = debouncer2.read();
        int value3 = debouncer3.read();
        int value4 = debouncer4.read();
        int value5 = debouncer5.read();
        int value6 = debouncer6.read();
        int value7 = debouncer7.read();
               
        if ( value1 == HIGH && value2 == HIGH && value3 == HIGH && value4 == HIGH && value5 == HIGH && value6 == HIGH && value7 == HIGH ) {
                // all the buttons are released, do the sending stuff
                if (building == 1) {//check if we are building a chord
                        // convert the keys pressed from binary to a decimal number
                        int b = sq(numKeys + 1); //1st binary digit in the array is numkeys+1 squared (e.g 7 digits, first digit is 64 which is 8^2)
                        for (int i = 0; i < numKeys; i++) { // converting the array from bin to dec
                                out = out + (b * chord[i]);
                                b = b / 2; //divide b by 2 to get the value of the next binary number
                                // This might be better but needs to be tested, removes need for 'b' variable
                                //for (int i = 0; i < numkeys; i++){
                                //  out = sq(out) + chord[i] //
                                //}
                        }
                        Serial.write("Decimal chord is ");
                        Serial.print(out); // write the chord to serial
                        Serial.println(); // and a newline
            
                        //Check if a mode chord has been pressed
                        switch(out){
                        case 33: //fourth mode
                          Serial.write("Fourth Mode Pressed");
                          Serial.println(); // and a newline   
                          //cancel any other active modes
                          mode2 = 0;
                          mode3 = 0;
                          //handle this toggle
                          if (mode4 < 2) {
                                            mode4++;
                                        }else {
                                            mode4 = 0;
                                        }
                          if (mode4 > 0) {
                            digitalWrite(LED1_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                          } else {
                            digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
                          }
                          Serial.write("Mode4 is ");
                          Serial.print(mode4);
                          Serial.println(); // and a newline
                          break;
                          
                        case 38: //second mode
                          Serial.write("Second Mode Pressed");
                          Serial.println(); // and a newline
                          //cancel any other active modes
                          mode3 = 0;
                          mode4 = 0;
                          //handle this toggle
                          if (mode2 < 2) {
                                            mode2++;
                                        }else {
                                            mode2 = 0;
                                        }
                          if (mode2 > 0) {
                            digitalWrite(LED1_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                          } else {
                            digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
                          }
                          Serial.write("Mode2 is ");
                          Serial.print(mode2);
                          Serial.println(); // and a newline
                          break;
                          
                        case 47: //third mode
                          Serial.write("Third Mode Pressed");
                          Serial.println(); // and a newline
                          //cancel any other active modes
                          mode2 = 0;
                          mode4 = 0;
                          //handle this toggle
                          if (mode3 < 2) {
                                            mode3++;
                                        }else {
                                            mode3 = 0;
                                        }
                          if (mode3 > 0) {
                            digitalWrite(LED1_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
                          } else {
                            digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
                          }
                          Serial.write("Mode3 is ");
                          Serial.print(mode3);
                          Serial.println(); // and a newline
                        break;

                        case 127: //release all
                          Serial.write("Releaseall Chord Pressed");
                          Serial.println(); // and a newline
                          // release all keys
                          Keyboard.releaseAll(); 
                          //cancel all active modes
                          mode2 = 0;
                          mode3 = 0;
                          mode4 = 0;
                          shift = 0;
                          ctrl = 0;
                          alt = 0;
                          win = 0;
                          digitalWrite(LED1_PIN, LOW);   // turn the LED off (LOW is the voltage level)
                          break;
                          
                        }

                        // Check if a meta key has been pressed
                        switch(out){
                        case 32: //Shift
                          Serial.write("SHIFT Pressed");
                          Serial.println(); // and a newline   
                          //handle this toggle
                          if (shift < 2) { //shift can be 0, 1, or 2
                                            shift++;
                                        }else {
                                            shift = 0;
                                        }
                          Serial.write("SHIFT is ");
                          Serial.print(shift);
                          Serial.println(); // and a newline
                          break;
                          
                        case 52: //CTRL
                          Serial.write("CTRL Pressed");
                          Serial.println(); // and a newline
                          //handle this toggle
                          if (ctrl < 1) { //ctrl can be 0 or 1
                                            ctrl++;
                                        }else {
                                            ctrl = 0;
                                        }
                          Serial.write("CTRL is ");
                          Serial.print(ctrl);
                          Serial.println(); // and a newline
                          break;
                          
                        case 59: //WIN
                          Serial.write("WIN Pressed");
                          Serial.println(); // and a newline
                          //handle this toggle
                          if (win < 1) { // win can be 0 or 1
                                            win++;
                                        }else {
                                            win = 0;
                                        }
                          Serial.write("WIN is ");
                          Serial.print(win);
                          Serial.println(); // and a newline
                        break;

                        case 60: //ALT
                          Serial.write("ALT Pressed");
                          Serial.println(); // and a newline
                          //handle this toggle
                          if (alt < 1) { //alt can be 0 or 1
                                            alt++;
                                        }else {
                                            alt = 0;
                                        }
                          Serial.write("ALT is ");
                          Serial.print(alt);
                          Serial.println(); // and a newline
                        break;
                        }

                        //Apply the meta Keys
                        switch (shift){
                        case 0: Keyboard.release(KEY_LEFT_SHIFT); 
                                break;
                        case 1: Keyboard.press(KEY_LEFT_SHIFT);
                                break;
                        // case 2, Shift has already been pressed
                        }
                        switch (ctrl){
                        case 0: Keyboard.release(KEY_LEFT_CTRL); 
                                break;
                        case 1: Keyboard.press(KEY_LEFT_CTRL);
                                break;
                        // case 2, Ctrl has already been pressed
                        }
                        switch (alt){
                        case 0: Keyboard.release(KEY_LEFT_ALT); 
                                break;
                        case 1: Keyboard.press(KEY_LEFT_ALT);
                                break;
                        // case 2, Alt has already been pressed
                        }
                        switch (win){
                        case 0: Keyboard.release(KEY_LEFT_GUI); 
                                break;
                        case 1: Keyboard.press(KEY_LEFT_GUI);
                                break;
                        // case 2, Win has already been pressed
                        }
                                               
                        // lookup the key to send based on the chord
                        // Second mode - numbers and punctuation
                        if (mode2 > 0) {
                          Serial.write("We're in Mode2");
                          Serial.println(); // and a newline
                          switch (out){
                            case 1: pressRelease('6');
                                        break;
                            case 2: pressRelease('$');
                                        break;
                            case 3: pressRelease('7');
                                        break;
                            case 4: pressRelease('0');
                                        break;
                            case 5: pressRelease(')');
                                        break;
                            case 6: pressRelease('"');
                                        break;
                            case 7: pressRelease('8');
                                        break;
                            case 8: pressRelease('1');
                                        break;
                            case 9: pressRelease('&');
                                        break;
                            case 10: pressRelease('+');
                                        break;
                            case 12: pressRelease('*');
                                        break;
                            case 13: pressRelease('-');
                                        break;
                            case 14: pressRelease('.');
                                        break;
                            case 15: pressRelease('9');
                                        break;
                            case 16: pressRelease(' ');
                                        break;
                            case 17: pressRelease('#');
                                        break;
                            case 18: pressRelease('/');
                                        break;
                            case 19: pressRelease('=');
                                        break;
                            case 20: pressRelease('(');
                                        break;
                            case 21: pressRelease('%');
                                        break;
                            case 22: pressRelease('?');
                                        break;
                            case 23: pressRelease('!');
                                        break;
                            case 24: pressRelease('2');
                                        break;
                            case 25: pressRelease('£'); // this does not work
                                        break;
                            case 26: pressRelease(';');
                                        break;
                            case 27: pressRelease(':');
                                        break;
                            case 28: pressRelease('3');
                                        break;
                            case 29: pressRelease('@');
                                        break;
                            case 30: pressRelease('4');
                                        break;
                            case 31: pressRelease('5');
                                        break;
                            case 36: Keyboard.press(KEY_RETURN);
                                     Keyboard.release(KEY_RETURN);
                                     break;
                            case 39: Keyboard.press(KEY_BACKSPACE);
                                     Keyboard.release(KEY_BACKSPACE);
                                     break;
                            case 40: Keyboard.press(KEY_INSERT);
                                     Keyboard.release(KEY_INSERT);
                                     break;
                            case 42: Keyboard.press(KEY_TAB);
                                     Keyboard.release(KEY_TAB);
                                     break;
                            case 44: Keyboard.press(KEY_DELETE);
                                     Keyboard.release(KEY_DELETE);
                                     break;
                            case 49: Keyboard.press(KEY_PAGE_UP);
                                     Keyboard.release(KEY_PAGE_UP);
                                     break;
                            case 55: Keyboard.press(KEY_PAGE_DOWN);
                                      Keyboard.release(KEY_PAGE_DOWN);
                                      break;
                            case 113: Keyboard.press(KEY_UP_ARROW);
                                      Keyboard.release(KEY_UP_ARROW);
                                      break;
                            case 121: Keyboard.press(KEY_LEFT_ARROW);
                                      Keyboard.release(KEY_LEFT_ARROW);
                                      break;
                            case 122: Keyboard.press(KEY_RIGHT_ARROW);
                                      Keyboard.release(KEY_RIGHT_ARROW);
                                      break;
                            case 124: Keyboard.press(KEY_DOWN_ARROW);
                                      Keyboard.release(KEY_DOWN_ARROW);
                                      break;
                            }
                          } else {
                        
                          // Third mode - other printable characters
                          if (mode3 > 0) {
                            Serial.write("We're in Mode3");
                            Serial.println(); // and a newline
                              switch(out) {
                              case 1: pressRelease('_');
                                      break;
                              case 5: pressRelease('>');
                                      break;
                              case 6: pressRelease('^');
                                      break;
                              case 8: pressRelease('€'); //this does not work
                                      break;
                              case 13: pressRelease('~');
                                      break;
                              case 18: pressRelease('\\');
                                      break;
                              case 20: pressRelease('<');
                                      break;
                              case 24: pressRelease('|');
                                      break;
                              case 25: pressRelease('[');
                                      break;
                              case 26: pressRelease(']');
                                      break;
                              case 29: pressRelease('`');
                                      break;
                              }
                            } else {
            
                            // Fourth mode
                            if (mode4 > 0) {
                              Serial.write("We're in Mode4");
                              Serial.println(); // and a newline
                              switch(out) {
                              case 5: pressRelease('}');
                                      break;
                              case 20: pressRelease('{');
                                      break;
                              }
                            } else {
            
                              // First Mode
                              Serial.write("We're in Mode1");
                              Serial.println(); // and a newline
                              switch (out){
                                case 1: pressRelease('u');
                                        break;
                                case 2: pressRelease('s');
                                        break;
                                case 3: pressRelease('g');
                                        break;
                                case 4: pressRelease('o');
                                        break;
                                case 5: pressRelease('q');
                                        break;
                                case 6: pressRelease('n');
                                        break;
                                case 7: pressRelease('b');
                                        break;
                                case 8: pressRelease('e');
                                        break;
                                case 9: pressRelease('v');
                                        break;
                                case 10: pressRelease('t');
                                        break;
                                case 11: pressRelease(',');
                                        break;
                                case 12: pressRelease('a');
                                        break;
                                case 13: pressRelease('-');
                                        break;
                                case 14: pressRelease('.');
                                        break;
                                case 15: pressRelease('m');
                                        break;
                                case 16: pressRelease(' ');
                                        break;
                                case 17: pressRelease('h');
                                        break;
                                case 18: pressRelease('k');
                                        break;
                                case 19: pressRelease('j');
                                        break;
                                case 20: pressRelease('c');
                                        break;
                                case 21: pressRelease('z');
                                        break;
                                case 22: pressRelease('y');
                                        break;
                                case 23: pressRelease('x');
                                        break;
                                case 24: pressRelease('i');
                                        break;
                                case 25: pressRelease('l');
                                        break;
                                case 26: pressRelease('r');
                                        break;
                                case 27: pressRelease('w');
                                        break;
                                case 28: pressRelease('d');
                                        break;
                                case 29: pressRelease('\'');
                                        break;
                                case 30: pressRelease('f');
                                        break;
                                case 31: pressRelease('p');
                                        break;
                                case 36: Keyboard.press(KEY_RETURN);
                                         Keyboard.release(KEY_RETURN);
                                         break;
                                case 39: Keyboard.press(KEY_BACKSPACE);
                                         Keyboard.release(KEY_BACKSPACE);
                                         break;
                                case 40: Keyboard.press(KEY_INSERT);
                                         Keyboard.release(KEY_INSERT);
                                        break;
                                case 42: Keyboard.press(KEY_TAB);
                                         Keyboard.release(KEY_TAB);
                                        break;
                                case 44: Keyboard.press(KEY_DELETE);
                                         Keyboard.release(KEY_DELETE);
                                        break;
                                case 49: Keyboard.press(KEY_HOME);
                                         Keyboard.release(KEY_HOME);
                                        break;
                                case 55: Keyboard.press(KEY_END);
                                         Keyboard.release(KEY_END);
                                        break;
                                case 56: Keyboard.press(KEY_ESC);
                                         Keyboard.release(KEY_ESC);
                                        break;
                                case 113: Keyboard.press(KEY_UP_ARROW);
                                         Keyboard.release(KEY_UP_ARROW);
                                        break;
                                case 121: Keyboard.press(KEY_LEFT_ARROW);
                                         Keyboard.release(KEY_LEFT_ARROW);
                                        break;
                                case 122: Keyboard.press(KEY_RIGHT_ARROW);
                                         Keyboard.release(KEY_RIGHT_ARROW);
                                        break;
                                case 124: Keyboard.press(KEY_DOWN_ARROW);
                                         Keyboard.release(KEY_DOWN_ARROW);
                                        break;
                                }
                            }
                          }
                        }
                        Serial.write("got here");
                        Serial.println(); // and a newline


            
            building = 0; // we're no longer building a chord
            out = 0;
            for(int i=0;i<7;i++){ //Modify array and set all values back to 0
                   chord[i] = 0; 
                   }

                                }
                        }
        else
        {// Update the array - this only adds key presses, it doesn't remove any which have been released. The chord consists of all keys which have been pressed since the last tine none were pressed.

                if (value1 == LOW){chord[0] = 1;}
                if (value2 == LOW){chord[1] = 1;}
                if (value3 == LOW){chord[2] = 1;}
                if (value4 == LOW){chord[3] = 1;}
                if (value5 == LOW){chord[4] = 1;}
                if (value6 == LOW){chord[5] = 1;}
                if (value7 == LOW){chord[6] = 1;}
    
                // we're building a chord so
                building = 1;
        }
}
