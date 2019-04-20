//Chorus Chords v2
//By Andy Younie 20/04/2019
//Based on Microwriter chords

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>
int numKeys = 7 // The number of physical switches being used

              int chord[] = {} // Make an empty array to hold the chord

for(int i=0; i<numKeys; i++) { //Define the Button Pins, and initially populate chord array
#define BUTTON[i+1] _PIN [i+1] //define button pins (#define BUTTON1_PIN 1, #define BUTTON2_PIN 2, etc.)
        chord[i] = 0 // populate chord array with the correct number of 0's
}

int building = 0; // since we're not building a chord at the moment
int out = 0; // will hold the decimal representation of the chord
int key = 0; // the ascii code of the key we will type on the keyboard
// Meta Keys
int shift = 0; // have we pressed the SHIFT chord
int alt = 0; // have we pressed the ALT chord
int ctrl = 0; // have we pressed the CTRL chord
int win = 0; // have we pressed the WIN chord
int mode2 = 0; // have we pressed second mode chord
int mode3 = 0; // have we pressed third mode chord
int mode4 = 0; // have we pressed fourth mode chord

for(int i=1; i<=numkeys; i++) {
        Bounce debouncer[i] = Bounce(); // Instantiate a Bounce object (debouncer1, debouncer2, etc.)
}

void setup() {
        for(int i=1; i<=numkeys; i++) {
                debouncer[i].attach(BUTTON[i] _PIN,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
                debouncer[i].interval(25); // Use a debounce interval of 25 milliseconds
        }
}
void loop() {
        for(int i=1; i<=numkeys; i++) {
                debouncer[i].update(); // Update the Bounce instance
                int value[i] = debouncer[i].read // Get the value
        }
        //
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
                        Serial.print(out); // write the chord to serial
                        Serial.println(); // and a newline
						
						//Check if a mode chord has been pressed
						switch(out){
						case 33: //fourth mode
							//cancel any other active modes
							mode2 = 0;
							mode3 = 0;
							//handle this toggle
							if (mode4 < 2) {
                                mode4++;
                            }else {
                                mode4 = 0;
                            }
						case 38: //second mode
							//cancel any other active modes
							mode3 = 0;
							mode4 = 0;
							//handle this toggle
							if (mode2 < 2) {
                                mode2++;
                            }else {
                                mode2 = 0;
                            }
						case 47: //third mode
							//cancel any other active modes
							mode2 = 0;
							mode4 = 0;
							//handle this toggle
							if (mode3 < 2) {
                                mode3++;
                            }else {
                                mode3 = 0;
                            }
						}
						
                        // lookup the key to send based on the chord
						// Second mode - numbers and punctuation
						if (mode2 > 0) {
							switch(out) {
							case 1: key = 54; break; //6
							case 2: key = 36; break; //$
							case 3: key = 55; break; //7
							case 4: key = 48; break; //0
							case 5: key = 41; break; //)
							case 6: key = 34; break; //"
							case 7: key = 56; break; //8
							case 8: key = 49; break; //1
							case 9: key = 38; break; //&
							case 10: key = 43; break; //+
							case 12: key = 42; break; //*
							case 13: key = 45; break; //-
							case 14: key = 46; break; //.
							case 15: key = 57; break; //9
							case 16: key = 32; break; //space
							case 17: key = 35; break; //#
							case 18: key = 47; break; ///
							case 19: key = 61; break; //=
							case 20: key = 40; break; //(
							case 21: key = 37; break; //%
							case 22: key = 63; break; //?
							case 23: key = 33; break; //!
							case 24: key = 50; break; //2
							case 25: key = 156; break; //£
							case 26: key = 59 ; break; //;
							case 27: key = 58; break; //:
							case 28: key = 51; break; //3
							case 29: key = 64; break; //@
							case 30: key = 52; break; //4
							case 31: key = 53; break; //5
							case 36: key = 176; break; //RETURN
							case 39: key = 178; break //BACKSPACE
							case 40: key = 209; break //INSERT
							case 42: key = 179; break //TAB
							case 44: key = 212; break //DELETE
							case 49: key = 211; break //PgUp
							case 55: key = 214; break //PgDn
							case 113: key = 218; break //UP
							case 121: key = 216; break; //LEFT
							case 122: key = 215; break; //RIGHT
							case 124: key = 217; break //DOWN
							default: key = 0; break; // if an unknown key combination is pressed, set the key to 0, 'null'
							}
						} else {
						
							// Third mode - other printable characters
							if (mode3 > 0) {
								switch(out) {
								case 1: key = 95; break; //_
								case 5: key = 62; break; //>
								case 6: key = 94; break; //^
								case 8: key = 0; break; //€ **Need to work out how to send this**
								case 13: key = 126; break; //~
								case 18: key = 92; break; //\
								case 20: key = 60; break; //<
								case 24: key = 124; break; //|
								case 25: key = 91; break; //[
								case 26: key = 93 ; break; //]
								case 29: key = 96; break; //`
								default: key = 0; break; // if an unknown key combination is pressed, set the key to 0, 'null'
								}
							} else {

								// Fourth mode
								if (mode4 > 0) {
									switch(out) {
									case 5: key = 125; break; //}
									case 20: key = 123; break; //{
									default: key = 0; break; // if an unknown key combination is pressed, set the key to 0, 'null'
								} else {

									// First Mode
									switch(out) {
									case 1: key = 117; break; //u
									case 2: key = 115; break; //s
									case 3: key = 103; break; //g
									case 4: key = 111; break; //o
									case 5: key = 113; break; //q
									case 6: key = 110; break; //n
									case 7: key = 98; break; //b
									case 8: key = 101; break; //e
									case 9: key = 118; break; //v
									case 10: key = 116; break; //t
									case 11: key = 44; break; //,
									case 12: key = 97; break; //a
									case 13: key = 45; break; ; //-
									case 14: key = 46; break; ; //.
									case 15: key = 109; break; //m
									case 16: key = 32; break; //space
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
									case 29: key = 39; break; //'
									case 30: key = 102; break; //f
									case 31: key = 112; break; //p
									case 32: key = 0; break; //SHIFT Pressed - handled below
									case 36: key = 176; break; //RETURN
									case 39: key = 178; break; //BACKSPACE
									case 40: key = 209; break; //INSERT
									case 42: key = 179; break //TAB
									case 44: key = 212; break //DELETE
									case 49: key = 210; break; //HOME
									case 52: key = 0; break; //CTRL Pressed - handled below
									case 55: key = 213; break; //END
									case 56: key = 177; break; //ESC
									case 59: key = 0; break; //WIN Pressed - handled below
									case 60: key = 0; break; //ALT Pressed - handled below
									case 113: key = 218; break //UP
									case 121: key = 216; break; //LEFT
									case 122: key = 215; break; //RIGHT
									case 124: key = 217; break //DOWN
									// REPEAT LAST KEY - a nice simple key combination to repeat the previous character?
									default: key = 0; break; // if an unknown key combination is pressed, set the key to 0, 'null'
									}
								}
							}
						}
						
						//Meta Keys
                        if (out == 32) { //shift was pressed
                                if (shift < 2) {  // make shift lockable
                                        shift++;
                                }else {
                                        shift = 0;
                                }
                        }
                        if (out == 52) { //ctrl was pressed
                                if (ctrl < 1) {
                                        ctrl++;
                                }else {
                                        ctrl = 0;
                                }
                        }
                        if (out == 60) { //alt was pressed
                                if (alt < 1) {
                                        alt++;
                                }else {
                                        alt = 0;
                                }
                        }
                        if (out == 59) { //win was pressed
                                if (win < 1) {
                                        win++;
                                }else {
                                        win = 0;
                                }
                        }

                        // Apply Meta Keys if necessary
                        switch (shift) {
                        case 0: keyboard.release(129); break;
                        case 1: keyboard.press(129); break;
                        case 2: keyboard.press(129); break;
                        }
                        switch (ctrl) {
                        case 0: keyboard.release(128); break;
                        case 1: keyboard.press(128); break;
                        }
                        switch (alt) {
                        case 0: keyboard.release(130); break;
                        case 1: keyboard.press(130); break;
                        }
                        switch (win) {
                        case 0: keyboard.release(131); break;
                        case 1: keyboard.press(131); break;
                        }
                        if (key > 0) {
                                Keyboard.write(key); // send the key
                                key = 0; // set the key to ascii null
                                //  Serial.print(key);
                                out = 0; // reset the output after writing it.
                                //Serial.print(out);
                                for(int i=0; i<numKeys; i++) { //Modify array and set all values back to 0
                                        chord[i] = 0;
                                }
                                building = 0; // we're no longer building a chord

                                // Remove Meta Keys if necessary
                                switch (shift) {
                                case 1: keyboard.release(129); break;
                                shift = 0;
                                }
                                switch (ctrl) {
                                case 1: keyboard.release(128); break;
                                ctrl = 0;
                                }
                                switch (alt) {
                                case 1: keyboard.release(130); break;
                                alt = 0;
                                }
                                switch (win) {
                                case 1: keyboard.release(131); break;
                                win = 0;
                                }
                        }
                }
        }
        else
        {
                // one or more buttons are pressed
                // add all pressed buttons to the array
                for(int i=1; i<=numKeys; i++) {
                        if (value[i] == LOW) {chord[i-1] = 1;}
                }
                // we're building a chord so
                building = 1;
        }
}
