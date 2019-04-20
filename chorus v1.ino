// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2

#include <Bounce2.h>
#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3
#define BUTTON4_PIN 4
#define BUTTON5_PIN 5
#define BUTTON6_PIN 6
#define BUTTON7_PIN 7

int chord[] = {0, 0, 0, 0, 0, 0, 0}; //default 7 button chord, all zeros
int building = 0; // since we're not building a chord at the moment
int out = 0;
int key = 0; // the key we will type on the keyboard
int shift = 0; // have we pressed the shift key to capitalise the next letter?

Bounce debouncer1 = Bounce(); // Instantiate a Bounce object
Bounce debouncer2 = Bounce(); // Instantiate a Bounce object
Bounce debouncer3 = Bounce(); // Instantiate a Bounce object
Bounce debouncer4 = Bounce(); // Instantiate a Bounce object
Bounce debouncer5 = Bounce(); // Instantiate a Bounce object
Bounce debouncer6 = Bounce(); // Instantiate a Bounce object
Bounce debouncer7 = Bounce(); // Instantiate a Bounce object

void setup() { // This should be done with a for loop
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
  }
  
void loop() {
// Update the Bounce instances - should do this with a for loop.
   debouncer1.update(); 
   debouncer2.update();
   debouncer3.update();
   debouncer4.update();
   debouncer5.update();
   debouncer6.update();
   debouncer7.update();
   
// Get the values - should do this with a for loop (maybe the same loop as above?
   int value1 = debouncer1.read();
   int value2 = debouncer2.read();
   int value3 = debouncer3.read();
   int value4 = debouncer4.read();
   int value5 = debouncer5.read();
   int value6 = debouncer6.read();
   int value7 = debouncer7.read();
  
   if ( value1 == HIGH && value2 == HIGH && value3 == HIGH && value4 == HIGH && value5 == HIGH && value6 == HIGH && value7 == HIGH ) {
    // all the buttons are released, do the sending stuff
    if (building == 1){//check if we are building a chord
   // convert the keys pressed from binary to a decimal number
       int b = 64; //1st binary digit in the array is worth 64
       for (int i = 0; i <= 6; i++) { // build the 7 digit output, converting from bin to dec
       out = out + (b * chord[i]);
       b = b / 2; //divide b by 2 to get the value of the next column
       }
      Serial.print(out); // write the chord to serial for debugging purposes
      Serial.println(); // and a newline

// lookup the key to send based on the chord
switch(out){
  case 1: key = 117; break; //u
  case 2: key = 115; break; //s
  case 3: key = 103; break; //g
  case 4: key = 111; break; //o
  case 5: key = 113; break; //q
  case 6: key = 110; break; //n
  case 7: key = 98; break;  //b
  case 8: key = 101; break; //e
  case 9: key = 118; break; //v
  case 10: key = 116; break; //t
  case 12: key = 97; break; //a
  case 15: key = 109; break; //m
  case 16: key = 32; break; //space  - would be good if this could repeat while held
  case 17: key = 104; break; //h
  case 18: key = 107; break; //k
  case 19: key = 106; break; //j
  case 20: key = 99; break; //c
  case 21: key = 122; break; //z
  case 22: key = 121; break; //y
  case 23: key = 120; break; //x
  case 24: key = 105; break; //i
  case 25: key = 108; break; //l
  case 26: key = 114; break; //r
  case 27: key = 119; break; //w
  case 28: key = 100; break; //d
  case 30: key = 102; break; //f
  case 31: key = 112; break; //p
  case 32: shift = shift ^ 1; break;   //Toggle the shift variable. Probably better to send the shift key (129) using keyboard.press and do a keyboard.release or releaseall after sending the next key.

// Numbers - check how Microwriter did it, I've forgotten!
  case 33: key = 49; break; //   0100001 1 binary 1 with the second thumb key held 
  case 34: key = 50; break; //   0100010 2 binary 2 with the second thumb key held 
  case 35: key = 51; break; //   0100011 3 binary 3 with the second thumb key held 
  case 36: key = 52; break; //   0100100 4 binary 4 with the second thumb key held 
  case 37: key = 53; break; //   0100101 5 binary 5 with the second thumb key held 
  case 38: key = 54; break; //   0100110 6 binary 6 with the second thumb key held 
  case 39: key = 55; break; //   0100111 7 binary 7 with the second thumb key held 
  case 40: key = 56; break; //   0101000 8 binary 8 with the second thumb key held 
  case 41: key = 57; break; //   0101001 9 binary 9 with the second thumb key held 
  case 42: key = 48; break; //   0101010 0 binary 10 with the second thumb key held 
 
 // Other keys to add: see https://web.archive.org/web/20060806154015/http://www.bellaire.demon.co.uk/page15.gif
  // Modifiers
  // CTRL - 0110100 key = 128 (kinda like a 'c' but with two thumb buttons) should be 'sticky' to allow other modifiers to be added
  // WIN - 0111011 key = 131 (kinda like a 'w' but with two thumb buttons) should be 'sticky' to allow other modifiers to be added
  // ALT - 0111100 key = 130 (kinda like a 'a' but with two thumb buttons) should be 'sticky' to allow other modifiers to be added
  
  // Special Keys
  // TAB - 0111010 key = 179 (kinda like a 't' but with two thumb buttons)
  // ESC - 0111000 key = 177 (kinda like a 'e' but with two thumb buttons)
  // HOME - 0110001 key = 210 (kinda like a 'h' but with two thumb buttons)
  // END - 0110111 key = 213 (kinda like a 'd' but with two thumb buttons)
  // DEL - check what Microwriter used  key = 212 - would be good if this could repeat while held
  // BACKSPACE - check what Microwriter used  key = 178  - would be good if this could repeat while held
  // RETURN - check what Microwriter used  key = 176  - would be good if this could repeat while held
  // UPARROW key = 218
  // DOWNARROW key = 217
  // LEFTARROW key = 216
  // RIGHTARROW key = 215
 
  // Punctuation
  // . - 0001110 key = 46 (I think this is the Microwriter code, 3 middle fingers)
  // , key = 44
  // ? - should this just be 'shift' + '/'? key = 63
  // ! - should this just be 'shift' + '1'? key = 33
  // " - should this just be 'shift' + '2'? key = 34
  // £ - should this just be 'shift' + '3'? key = (no ascii number!)
  // $ - should this just be 'shift' + '4'? key = 36
  // % - should this just be 'shift' + '5'? key = 37
  // ^ - should this just be 'shift' + '6'? key = 94
  // & - should this just be 'shift' + '7'? key = 38
  // * - should this just be 'shift' + '8'? key = 42
  // ( - should this just be 'shift' + '9'? key = 40
  // ) - should this just be 'shift' + '0'? key = 41
  // - key = 45
  // = key = 61
  // _  - should this just be 'shift' + '-'? key = 95
  // +  - should this just be 'shift' + '='? key = 43
  // [  key = 91
  // ]  key = 93
  // { - should this just be 'shift' + '['? key = 123
  // } - should this just be 'shift' + ']'? key = 125
  // < - should this just be 'shift' + ','? key = 60
  // > - should this just be 'shift' + '.'? key = 62
  // ; key = 59
  // : - should this just be 'shift' + ';'? key = 58
  // ' key = 44
  // @ - should this just be 'shift' + '''? key = 64
  // # key = 35
  // ~ - should this just be 'shift' + '#'? key = 126
  // ` key = 96
  // \ key = 92
  // | - should this just be 'shift' + '\'? | key = 124
  // € - this might be tricky, it's KEY_RIGHT_ALT (134) and '4' (36)
  // REPEAT LAST KEY - a nice simple key combination to repeat the previous character?
 default: key = 0; break; // if an unknown key combination is pressed, set the key to 0, 'null'
}

if(shift == 1 &&  out != 32){key = key - 32; shift = 0;} // capitals are the ascii number for the lowercase letter minus 32. This might cause some problems with punctuation later. See comment against Case 32 above
        Keyboard.write(key); // send the key
        key = 0; // set the key to ascii null
      //  Serial.print(key);
      out = 0; // reset the output after writing it.
      //Serial.print(out);
      for(int i=0;i<7;i++){ //Modify array and set all values back to 0
       chord[i] = 0; 
       }
      int chord[] = {0, 0, 0, 0, 0, 0, 0}; // reset chord ready for the next one
      building = 0; // we're no longer building a chord 
      }
   }
   else
   {
    // one or more buttons are pressed
    // add all pressed buttons to the array - this could probably be another loop.
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
