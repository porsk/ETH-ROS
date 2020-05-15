## Exercise 4
The goal of this exercise was use the node what I implemented in Exercise 2 & 3 and add a service server that can
start/stop the robot. This functionality could be used as an emergency stop. Also, as an optional task I created a separate node that stops the robot after a crash has occurred with the stop service. For this, I plotted and analysed the data of the IMU
under the topic `/imu/data` with `rqt_multiplot` and developed a method to detect a crash.


## Notes
- Ploted X/Y linear acceleration values from `/imu/data` using rqt_multiplot durign a crash: `xy_acc_crash.png`

## Result demonstration

[![Exercise 5 - Stop after crash](https://img.youtube.com/vi/JgRXXXy2rrs/0.jpg)](https://youtu.be/JgRXXXy2rrs)
[![Exercise 5 - Start stop service](https://img.youtube.com/vi/0r4_La7vw2g/0.jpg)](https://youtu.be/0r4_La7vw2g)