# Summary
This project adds bluetooth functionality to an ordinary set of calipers with an embedded ESP32 C3. It's main purpose was to speed up CAD Development with it's ability to automatically enter numbers into OnShape.

It features a built in 150mAh battery and a USB C interface for charging/uploading code. 

![](https://github.com/Mew463/esp32-caliper/blob/main/esp32%20caliper.jpg)

This was meant to be a direct replacement for the GROSS solution that you could just buy:
![](gross image)


# Features
- Breakaway PCB Design
- Two User buttons 
    - One enters numbers and then presses Enter
    - Other enters numbers and then inserts a space so that the user can add tolerance
- Neopixel indicator (States: Bluetooth pairing, Connected, Button 1 or 2 Pressed, Entering deep sleep)
- 20 day standby time or 2hr usage time 
- Charge light
- Snap-on PCB Case

# Decoding the Caliper Data
![Calipers Used](https://www.amazon.com/Neiko-01407A-Electronic-Digital-Stainless/dp/B000GSLKIW/ref=sr_1_1_sspa?crid=24I6FXWO3H5A4&keywords=neiko+caliper&qid=1678232283&sprefix=neiko+calip%2Caps%2C243&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExQ0FaOFdNMVQ3TTImZW5jcnlwdGVkSWQ9QTA2ODI2NTAyUTFQWVNNVFVCQkZNJmVuY3J5cHRlZEFkSWQ9QTAyNTI0MDAzRERQVjZMWVAxWTExJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

Old port configuration: 
![]() 



# Creation
Designed in KiCAD 6.0 and I bought everything from Mouser
![CAD](https://cad.onshape.com/documents/368abd500c875635f19a3005/w/ab7db60efad03bd7d6054350/e/1cf117eaa5e9ddddb41ff0d8?renderMode=0&uiState=6407caa931dacb56d467d292)

![](https://github.com/Mew463/esp32-caliper/blob/main/blinkypcbs.gif)

# Summary 
TBH if you really want a bluetooth caliper just buy one premade, it'll save you a lot of headache. This project probably took me like 60 hrs and 3 revisions of pcbs.

https://www.amazon.com/iGaging-Electronic-Absolute-Bluetooth-Connectivity/dp/B0716B8Q99/ref=sr_1_3?crid=NPXC9LKMF29V&keywords=bluetooth+caliper&qid=1678232538&s=hi&sprefix=bluetooth+calip%2Ctools%2C187&sr=1-3