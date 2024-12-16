# DIY ESP32 RC Car

<p align="center">
  <img src="https://github.com/user-attachments/assets/6951ceae-68d6-404f-8ec2-f7391fd4ea73" width=80% height=80%>
</p>

<h1>Introduction</h1>
Using skills we gained through EE 3752 labs and lectures, my partner and I decided to apply our arm assembly knowledge to microcontrollers and create a fully functional RC car and controller powered by the ESP32. This project connects to ARM assembly and microprocessors by applying embedded system principles like GPIO/ADC handling, I/O, and real time communication. Skills we used in the labs including registers, loops, low-level debugging, and I/O helped us design and fabricate a functional project using the ESP32. This project is very important because it allowed us to take what we learned in class, and apply to a real world application. This connection is like what one would see in a job where you must think outside of the box using your technical skills to solve an issue. 

<h1>Background Information and Design Process</h1>
When we decided to take on this project, we started researching and deciding on what we need to make the RC car reliable, low cost, and fully functional. We chose the ESP32 microcontroller as our processor due to low cost, form factor, adaptability, and Bluetooth and Wi-Fi capabilities. The Xtensa dual-core 32-bit LX6 microprocessor, operating at 240 MHz adds a lot of capability compared to a normal Arduino UNO. The ESP32 also includes peripherals we need without having to buy WI-FI/Bluetooth modules to interface between the car and transmitter externally.

<p align="center">
  <img src="https://github.com/user-attachments/assets/470659e3-7c37-4c92-a527-d3784f4c23a6" width=30% height=30%>
</p>
<!-- -->
Our first iteration of the prototype involved a toy RC car kit on Amazon for our base. 
<p align="center">
  <img src="https://github.com/user-attachments/assets/bde1481d-7040-47d4-9698-8d4adb611554" width=30% height=30%>
</p>

Our goal was to have a finished RC car kit that we can place all our electronics on so we would not have to design a chassis. To get this iteration working, we would have to buy an ESP32, and two H-bridge motor drivers for steering and throttle. For the controller we wanted to use a phone app and use ESP32’s Bluetooth capability to control the RC car. This iteration would have worked fine for the scope of this project, but after seeing how fast we would finish the project we came up with a new idea. We wanted to take the RC car a step further and make a faster, more durable, and more custom RC car with a fabricated controller. 
<!-- -->
After research on Thingiverse, we settled on the platform called Carduino V2 and applied our own electronic design using the ESP32 Microcontroller and a brushless motor system. This design did not include any code files so this made it a perfect opportunity to design a system from scratch.


