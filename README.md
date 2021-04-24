# TemperatureV2
A POE powered ethernet temperature sensor with two probes.

I wanted to be able to monitor temperatures in various locations
in my server rooms.  Most products on the market were designed
around having a head unit that you plug probes into.  This 
doesn't work for me since the locations I want to monitor have
a fair bit of distance between them.  My solution is a POE 
powered unit with two attached sensors.  I can put them anywhere
without concerning myself with power availability.

## Hardware
The system is based on an Adafruit Feather M0 Basic paired with
a Silicognition PoE FeatherWing and two DS18B20 sensors on leads.

The setup is extremely simple.  The FeatherWing gets attached 
to the M0, including the SDA and SCL pins.  A single 4.7k 
resistor ties pin 5 or 6 to 3v3 and the data lead of both sensors.

This setup costs about $50, and even spending that on each unit
I want to deploy, it still costs less than the commercial
solutions.

## Enclosure
To protect the unit we need an enclosure.  The enclosure needs
to be able to release about 1W of heat from the PoE components.

The enclosure included can easily accomplish that and exposes
the USB port for reprogramming (or external power).  The battery
connector is not exposed in this enclosure.

## Software
Based on some Arduino libraries, the included software manages
the sensors and serves up a very basic webpage.

You may notice this is V2.  V1 was considerably larger based 
on an Arduino.  It produced more heat, and the firmware had to
be altered for each unit to program the MAC address.  Since the
FeatherWing includes a globally unique MAC address, we don't 
need to change the firmware for each unit.

Since this is V2, I wanted to maintain backwards compatibility
with V1.  That's not hard, it just means that the root request
"/" can only return temperatures T1 and T2.  I added a second
endpoint "/v" which returns the MAC address (serial number) and
version of the software in addition to the temperatures.

In production, you'll want to setup DHCP reservations for the
sensors so that they are always where you expect.

## Bugs
None that I know of. However, you cannot power cycle the DS18B20
sensors rapidly.  Because of that, if the unit loses power for
less than a second it may not be able to locate one or both of
the sensors when it boots back up.  In production this shouldn't
happen, but I was able to produce the issue several times during
development by quickly unplugging and plugging back in to reset
the hardware.

## License
Copyright (C) 2021 Beau Barker

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
