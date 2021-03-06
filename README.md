# chorus
*My DIY chorded keyboard*

This will be a learning project for me. 

The plan is to:
* use a Teensy USB development board as the keyboard controller.
* use mechanical keyboard switches and keycaps for the buttons
* print a suitable case with my Anet A8 3D printer
* use chords based on those used on the MicroWriter AgendA (as I have used them previously)
* write as much of the code as I can myself
* investigate further improvements such as text expansion if memory constraints allow
* post schematics, 3d printer files, code, and build instructions

Get details of the build on my website [https://secreci.com/posts/20190414-chording-keyboard-part-1/](https://secreci.com/posts/20190414-chording-keyboard-part-1/)

**Parts list:**
* PLA filament for case
* Solid core hookup wire
* Solder
* 1 x Teensy 2.0 development board
* 7 x mx-style keyboard switches
* 6 x standard blank keycaps
* 1 x larger  blank keycap (e.g. shift)
* 1 x Mini-B USB cable
* 1 x 3mm LED
* 1 x 220ohm resistor


**Future development**
* Quieter, lighter switches - this is quite noisy and tiring to use - would be better with rubber switches, I think.
* ~~LEDs to show which mode the keyboard is in.~~ The 'all keys release all' chord helps cancel all pressed buttons.
  3mm LEDs arrived today (22/04/2019)
  
  LED Code added. LED is illuminated when we're not in 'mode 1'
  
* A timer to automatically cancel all held buttons if nothing is pressed in, say, 5 seconds.
* A chord to allow insertion of common word parts -ing, -ation, etc.
* The 3 thumb keys might be better rotated 90 degrees anticlockwise to make pressing 1 and 3 together easier.
* Amend the code to repeat when a chord is held down (e.g. for deleting multiple characters)
