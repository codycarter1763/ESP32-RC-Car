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

<p align="center">
  <img src="https://github.com/user-attachments/assets/86cd66bf-c84b-4a6c-9319-b676c02f4dc9" width=60% height=60%>
</p>

With the use of a personal 3D printer, we were able to fabricate our own parts without relying on our college’s printers. 
<!-- -->
When we started developing this prototype, we first had trouble with the brushless motor and ESC interface with the ESP32 board. Getting a signal going to the ESC was tricky, the motor would power on and begin beeping in 1 second intervals. Per the instructions for the motor indicated to us that it wasn’t receiving a control signal from the board. Further troubleshooting indicated that the problem was the ESC was waiting for certain throttle calibration steps involving full, low, and neutral throttle. Once we built that functionality into our code, we were able to interface and control the ESC. Thankfully, the steering servo worked right away, it gave us no issues since no calibration is needed. 

<h1>Parts List</h1>
•	2x ESP32<br>
•	1000kv A2212 Brushless Motor 30 amp ESC combo<br>
•	2s 7.4 Volt LIPO<br>
•	SG90 Servos<br>
•	8x12x3.5 Bearings<br>
•	A959 Tire<br>
•	Screws<br>
•	Joysticks and Wires<br>
•	Headers<br>
•	2x Blue LEDs<br>
•	100 Ohm resistor<br>
•	2x Clear White LEDs (For Headlights)<br>
•	68 Ohm resistor<br>

<h1>Chassis Construction</h1>
Chassis construction was relatively simple, the instructions provided with the Carduino 3Dprint files were fairly thorough. The build was broken down into 3 sections; base, steering rack, and rear assembly. <br>
<br>
The rear assembly went together first, this component holds in 4 bearings which support the rear axle and reduce friction when its powered. The brushless motor sits on a mount above the rear assembly, it powers a gear that connects to the rear axle providing motion for the vehicle. The entire construction is held together by 20 M3x10 screws. The rear assembly also supports the wing. The entire assembly is held onto the base with 2 screws forming a hinge-like mechanism, this functions as the suspension for the rear wheels.<br>
<br>
The steering rack was slightly more complex. Each wheel is held by a hub that can rotate left or right depending on the servo mounted in the middle, the hubs are connected to suspension arms that allow for up-and-down movement. Tension is provided to both the front and rear suspension via a set of rubber bands tightly bound around hooks on the suspension arms. <br>
<br>
The base is one single piece with a series of pegs that hold in the battery and the ESP32 board itself. Overall, the chassis went together decently well, the print didn’t include threads for the screws, this made it troublesome to screw everything together as we didn’t have a drill or any other means of forming our own threads. The chassis proved very sturdy and without fault during our testing, it has apt space for all the wiring and saved us a lot of time during the build since we didn’t have to fabricate our own chassis from the ground up. <br>
<br>

<h1>Circuit Design</h1>
For our RC car, this was the circuit diagram that we made that shows our wiring.

![IMG_0156](https://github.com/user-attachments/assets/5d7e8b3b-462d-43d8-bf1f-4d98ec546435)
<br>
<br>
For our LEDs, we used Ohm’s law to calculate what resistors we needed to use to prevent the LED from burning out.

![Picture3](https://github.com/user-attachments/assets/3f11d578-1db9-494b-bed1-f2a8b39744b4)
<br>
<br>
<br>

Our project was gladly sponsored by PCBWay. PCBWay has provided professional solutions to students and electronics enthusiasts, and we believe that their sponsorship would be essential to easy and reliable construction of ESP32 breakout boards for the car and controller. Such boards will allow for removability in case of ESP32 failure or programming, as well as options for different pin assignments. With this breakout board, we could apply to more projects as an easy and reliable way to add a more permanent setup for the ESP32. It’s an honor to share the results with the PCBWay community and contribute our project to their platform.  <br>
 <br>
We have not received our circuit boards yet, since the arrival date is after the project due date. But the linked photo below is a simulation of what the final product will look like. 
![image](https://github.com/user-attachments/assets/3253581c-9c10-4329-aa81-215169151ca1)

<p align="center">
  <img src="https://github.com/user-attachments/assets/922f5bfa-00ec-41fb-b49f-0a670eb609c0" width=60% height=60%>
</p>

<h1>Code Overview</h1>
Below is a state chart that we wrote up to be able to clearly see the function of the code for specific parts of the program execution. 

![image](https://github.com/user-attachments/assets/034f1b49-b5cd-4133-9cdb-ade744da563b)



<h1>Testing and Design Improvements</h1>
•	During the debugging process, we added various serial monitor outputs at critical parts of the code to see logically why our code was not working. Such techniques, for example, were used to discover what values our joysticks outputted when we moved them. <br> 
•	During our prototyping, we first used WI-FI connectivity for communication between the car and controller. Due to noticeable input lag, we decided to use Bluetooth as the latency is 1-3ms. The disadvantage is the decreased range, but for the safety and reliable use of the system we opted for Bluetooth. <br>
•	During testing, there were cases where the RC car would run away when there was a controller disconnection. As a result, we added in logic to always check for connection from the controller before each iteration. If there was no connection, the ESP32 would send a neutral throttle PWM value to prevent the car from running away.  <br>
•	One issue we ran into was the A959 tires we used non compatible rims to work with our design. After printing out the supplied rims on the Carduino V2 instructions, the rims were slightly too small to fit the tires. So, we made the rim a 2mm bigger diameter on each side and add a small bit of material to the screw hole using a CAD program to account for the screw hole being slightly bigger after increasing rim size.   <br>

![image](https://github.com/user-attachments/assets/da2fb5a0-11fb-4ca5-ac39-c66fc258a920)

![image](https://github.com/user-attachments/assets/ad0e6fde-88fa-4c57-a480-fd4c085cdc19)

•	After prototyping, we fabricated PCB boards to attach our ESP32 with a more permanent and compact form factor. Our intent was to use headers to allow the ESP32 to be removable in case of failure or future programming.  <br>

![image](https://github.com/user-attachments/assets/4846177c-f0c9-4013-8f2a-3e4a42b3a4ea)

![image](https://github.com/user-attachments/assets/88c2840a-fe1a-4b4b-96e8-0aa3ce133bfd)

<h1>Future Design Improvements</h1>
Through the fabrication of the RC car, we found some limitations to our design involving the electronics. Some improvements and solutions we saw to implement in the future are included below.<br>
<br>
•	The ESC we used to control our motor and power the ESP32 is used for drone and plane applications and does not come with reverse and brakes by default. Through much trial and error, we could not program our ESC according to the instructions to add the reverse and braking capability. Our solution would be to buy a dedicated ESC for an RC car, like this.<br>
<br>
•	The range of the ESP32’s Bluetooth is limited as it’s about 30-40 feet in open air compared to hobby grade RC vehicle ranges can span thousands of feet to even kilometers. One way we could fix this limitation is add additional radio transmission hardware such as the NRF24L01+PA+LNA Wireless Transceiver which would increase our range to thousands of feet with very minimal controller latency of 1 to 3ms. This board can adapt very easily through the ESP32 using libraries.<br>
<br>
o	Another solution to increase range would be to use the HopeRF RFM95/96 transceiver system to increase our range to multiple kilometers with low latency. Though for the scope of our project an RC car is not going to need that range normally.<br> 
<br>
•	We found a design online for a shell for our transmitter to house our electronics. The finished ESP32 PCB board we fabricated did not fit completely in our shell. We did not have time for this project, but in the future, we could modify the CAD design and make the controller wider to house our electronics.<br> 
<br>
•	We did not have time before the presentation, but we plan on submitting our project to PCBWay to get a circuit board sponsored very soon. PCBWay very regularly sponsors students and makers around the world to complete their projects with very professional and reliable circuit boards. <br>
<br>
•	Another improvement would be a proper body for the car. This would aid greatly in protecting the fragile internal components of the vehicle against obstacles and collisions.<br>
<br>

![image](https://github.com/user-attachments/assets/268fb4e1-940e-4fca-8bbd-fa290401c4eb)

•	Another area that could use improvement would be the steering rack, the arms that connect to the servo are stiff and grind against the screw holding the assembly together. One side tends to stick to the screw during compression of the suspension, which could limit steering in the immediate time after a jump. A way to fix this is to use ball ends with a threaded rod, such designs are used on hobby grade RCs to alleviate pressure and grinding through varying suspension travel positions. <br>
<br>
![image](https://github.com/user-attachments/assets/76af9d91-d513-41b4-8225-0ff1ed69636b)
<br>
<h1>Conclusion</h1>
Overall, this was a very challenging but fun project that was very beneficial in applying our lab knowledge to a real-world application. This project connected to ARM assembly and microprocessors by applying embedded system principles like GPIO/ADC handling, I/O, and real time communication. This project took a lot of trial and error to get the car working safely and reliably but using skills we used in the labs involving low level debugging we were able to get a solution. This connection is like what one would see in a job where you must apply prior knowledge to solve an issue. In the future we hope to develop this RC car to be even more reliable and useable and see where this sort of idea can take us.  <br>
<br>
Thanks again to PCBWay for their proud support for our project. PCBWay has provided professional solutions to students and electronics enthusiasts, and we are happy to share what we’ve been building to the PCBWay community and LSU. 


