## Exercise
The goal of this exercise was to work with data that was recorded on a real Husky robot. The
recorded bag file contained sensor measurements from wheel odometry, inertial
measurement unit (IMU) and laser scanner. The task was to use this raw sensor data to
localize the robot with a provided state estimation node that implements an extended
Kalman filter (EKF). To see the results, I plotted the output of the localization node using rqt Multiplot and
visualized the laser data in RViz.

## Notes
- Recorded and plotted the x/y plane of the simulated Husky using rqt_multiplot: `simulated_husky.png`
- Ploted the x/y plane of the recorded Husky using rqt_multiplot: `recorded_husky.png`

## Result demonstration

[![Exercise 4 DEMO](https://img.youtube.com/vi/5KdlKruCI6k/0.jpg)](https://youtu.be/5KdlKruCI6k)