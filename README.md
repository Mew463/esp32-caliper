# Summary
This project adds bluetooth functionality to an ordinary set of calipers with an embedded ESP32 C3. It's main purpose was to speed up CAD Development with it's ability to automatically enter numbers into OnShape.
![](https://github.com/Mew463/esp32-caliper/blob/main/images/caliperdemo.gif)

It features a built in 150mAh battery and a USB C interface for charging/uploading code. 


This is meant to be a direct replacement for the GROSS solution that you could just buy for the inexpensive price of $100:
![](https://github.com/Mew463/esp32-caliper/blob/main/images/grossexistingsolution.png)


# Features
- Realtime battery reporting
- Two User buttons 
    - Button1 enters numbers and then presses Enter
    - Button2 enters numbers and then inserts a space so that the user can add tolerance
- Neopixel indicator (States: Bluetooth pairing, Connected, Button 1 or 2 Pressed, Entering deep sleep)
- 20 day standby time or 2hr usage time 
- Charge light
- Snap-on PCB Case

# Decoding the Caliper Data
[Calipers Used](https://www.amazon.com/Neiko-01407A-Electronic-Digital-Stainless/dp/B000GSLKIW/ref=sr_1_1_sspa?crid=24I6FXWO3H5A4&keywords=neiko+caliper&qid=1678232283&sprefix=neiko+calip%2Caps%2C243&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExQ0FaOFdNMVQ3TTImZW5jcnlwdGVkSWQ9QTA2ODI2NTAyUTFQWVNNVFVCQkZNJmVuY3J5cHRlZEFkSWQ9QTAyNTI0MDAzRERQVjZMWVAxWTExJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

## Soldering Wires
My old caliper's data output port looked like this:
 
![](https://github.com/Mew463/esp32-caliper/blob/main/images/old%20caliper%20data%20port.png) 

Unfortunately I broke the old caliper during this project and had to buy a brand new version of my old caliper. Sometime in the span of 3 years, it seemed that the data output port changed to be adapted for a female micro usb (though there wasn't one soldered on the caliper's pcb).

The smaller pads made it more painful to solder wires to, but it was doable.

With an oscilloscope, I probed each pad to determine which was the clock, data, and ground line.

## Logic converter
Because the Caliper's logic level is 1.5v but the ESP32 is 3v3, I needed to use a logic converter. V1 and V3 use the transistor circuit below which shifts and inverts the clock and data lines coming from the caliper. V2 used a IC level shifter which didn't work at all for some unknown reason. 

![](https://github.com/Mew463/esp32-caliper/blob/main/images/logic%20converter.png) Logic converter

## Data protocol
Like many other people who have decoded their caliper, I discovered that there are 24 bits sent out by the caliper:

The bit at index[0] is always 1.

Bits from index[1] - index[15] signify the value with the LCB being first.

Index[21] signifies a negative number.

My old caliper had one bit to indicate the unit, but my new caliper did not have this bit (? idk why).

# Creation
## KiCAD
Designed in KiCAD 6.0. Bought from Mouser and manufactured by JLCPCB. I assembled them by hand.

![](https://github.com/Mew463/esp32-caliper/blob/main/images/esp32%20caliper.jpg)

![](https://github.com/Mew463/esp32-caliper/blob/main/images/blinkypcbs.gif)

## CAD
![](https://github.com/Mew463/esp32-caliper/blob/main/images/Onshape%20Rendering.png)

[CAD](https://cad.onshape.com/documents/368abd500c875635f19a3005/w/ab7db60efad03bd7d6054350/e/1cf117eaa5e9ddddb41ff0d8?renderMode=0&uiState=6407caa931dacb56d467d292)

# Summary 
This project took like 40 hours and 3 revisions of pcbs.
If you really want a bluetooth caliper just buy one premade, it'll save you a lot of headache. Otherwise this is a fun intro-to-embedded project.

[Premade bluetooth calipers](https://www.amazon.com/iGaging-Electronic-Absolute-Bluetooth-Connectivity/dp/B0716B8Q99/ref=sr_1_3?crid=NPXC9LKMF29V&keywords=bluetooth+caliper&qid=1678232538&s=hi&sprefix=bluetooth+calip%2Ctools%2C187&sr=1-3)