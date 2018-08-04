# Pie Pebble Watchface

This is is a minimalistic watchface for the Pebble smartwatch that shows the hour as a pie segment.

![Photo of actual watch](pics/photo.jpg)

The background is a pie segment that goes from from 12:00 to where the hour hand of a regular watch would be. This pie segment is blue for AM (00:00-11:59) and red for PM (12:00-23:59). The minute is indicated by a white minute hand that extends from the center to the edge of the watch.

![Mockup showing 12:32](pics/14-41.jpg)

![Mockup showing 00:00](pics/00-00.jpg)
![Mockup showing 13:51](pics/13-51.jpg)
![Mockup showing 16-09](pics/16-09.jpg)
![Mockup showing 18:00](pics/18-00.jpg)
![Mockup showing 19:32](pics/19-32.jpg)

All colors and the width of the minute hand are configurable through the configuration dialog on your phone.

![Screenshot of configuration dialog](pics/config.png)

![AM white, PM blue, hand black, width 9](pics/white-blue-black-9.jpg)
![AM black, PM green, hand yellow, width 33](pics/black-green-yellow-33.jpg)
![AM purple, PM pink, hand yellow, width 7](pics/purple-pink-yellow-7.jpg)
![AM white, PM black, hand red, width 13](pics/white-black-red-13.jpg)
![AM dark gray, PM gray, hand light gray, width 3](pics/dgray-gray-lgray-3.jpg)

To install the watchface on your Pebble, upload `pie.pbw` using the Pebble app on your smartphone, or build and install the watchface with the Pebble SDK as described on https://developer.rebble.io/developer.pebble.com/tutorials/watchface-tutorial/part1/index.html.

Planned future changes:

* Battery low indicator.
* Bluetooth down indicator.
* Selection of predefined color schemes.
* Upload to Rebble store.

---
*Wolfram Rösler • wolfram@roesler-ac.de • https://gitlab.com/wolframroesler • https://twitter.com/wolframroesler • https://www.linkedin.com/in/wolframroesler/*
