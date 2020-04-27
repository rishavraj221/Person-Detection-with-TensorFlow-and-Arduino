# Person-Detection-with-TensorFlow-and-Arduino

With this project we use TensorFlow Lite library, we can flash tiny machine learning models on an Arduino to detect humans from a camera.

My basic purpose is to analyze which, why and how things are used in this project along with the code...

Hardware components

* 1 Arduino Nano 33 BLE Sense
* 1 Arducam Mini 2MP
* 1 Adafruit Micro-Lipo Charger
* 1 Adafruit Lithium Ion Polymer Battery
	
Software apps and online services

* TensorFlow
* Arduino IDE	

Hand tools and fabrication machines

* Breadboard, 170 Pin	
* Premium Female/Male Extension Jumper Wires, 40 x 6" (150mm)	

One of the exciting aspects of running machine learning models on embedded hardware is the ability to use low power devices with greater contextual awareness to trigger high energy devices only when it is valuable to do so.

To learn more about this vision, check out Pete Warden's blog.

As a proof-of-concept, we want to use the low-power Arduino Nano 33 BLE Sense and an ArduCam Mini 2MP, along with the TensorFlow Lite library, to trigger a relay to turn on/off when a person is recognized.

Basic wiring

Follow the following wiring diagram to connect your Arduino Nano 33 BLE Sense to the ArduCam Mini 2MP. This diagram also shows how to add a lipo battery after you've flashed the Arduino.

Flashing the model

A few examples of tiny models have been released on the official TensorFlow repo, the micro_speech model being the most widely shown example. We wanted to flash the vision (person_detection) demo, however as of the time of this post being written, not all of the resources are available. From the micro_speech example, we saw that these Arduino zip packages were being stored in the same place as Google's nightly TensorFlow builds. When you navigate to this link, you'll see a document tree with links to all kinds of nightly builds:

Doing a quick word search through the document tree, we were able to locate the missing package! (Update: TF team is working on updating the missing link)

Download this package link and rename it to person_detection.zip. This will be the package we upload as a library to our Arduino IDE as the official instructions describe.

After uploading this zip package, we want to make a couple more modifications for things to run smoothly. With your text editor of choice, find where the Arduino library installed and open the library.properties file for editing

Change the first line that declares the name of the library to TensorFlowLite:person_detection.

This makes it visible in the Arduino IDE examples menu. Finally, navigate to the examples/ directory in the same place and rename the subdirectory to person_detection. All these changes resolve the necessary differences to get the demo running.

From here, you can follow the official instructions to download the libraries for the ArduCam and JPEG decoding.

To run the example, navigate to Files -> Examples -> TensorflowLite:person_detection and select the person_detection sample script. Make sure you have your Arduino BLE 33 sense connected to your computer and it has been selected for flashing on the Arduino IDE. Flash the example and it should start up immediately. The on board LED will flash blue to indicate that an image has been captured and inference has been completed. The light will turn red if it did not detect a human and turn green when it has. Inference takes ~19 seconds since the person detection model is fairly large for the device.

Using the Arduino as a Smart Switch

Microcontrollers are very energy efficient, some being able to operate on coin cell batteries for years! With recent efforts to minimize machine learning models to run on embedded devices, we can build smart "switches" that can be invoked to power or trigger other devices that need more power to operate. With this person detection model running on the Arduino BLE sense, we can trigger a high energy consuming device like a Donkeycar using the sombrero shield. We'll use a relay connected to the Arduino and switch it on/off depending on inference results.

Wire up the relay, pi, and arduino following the wiring diagram below:

Now simply add a few lines to the person_detection.ino example to look at the inference results and switch the relay.

Extending our Smart Switch using BLE

There may be situations where a high powered device could benefit from logic inferred elsewhere. For example, say you wanted a power hungry rover to start up when a person is detected in another section of a large warehouse. A way to extend the perception of our smart relay switch is through BLE.

BLE is a low power consuming wireless communication protocol designed to send small amounts of data. In this example, we set up an Arduino Nano 33 BLE Sense with the ArduCam attached to it as a control, sending a high alert when a person is detected. In the person_detection script, along with other BLE initialization steps, we add the logic to send a high alert when the person_score is high enough.

A second Arduino Nano 33 BLE Sense will serve as a peripheral device that will listen for that alert and switch a relay attached to it.

Thank you
