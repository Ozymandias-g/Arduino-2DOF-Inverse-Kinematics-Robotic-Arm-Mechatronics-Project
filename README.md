# 2-DOF Robotic Arm with Inverse Kinematics

## 📌 Project Overview
This repository contains my first-semester project for the **Introduction to Mechatronics Engineering** class. It is a 2-Degree-of-Freedom (2-DOF) robotic arm that calculates its joint angles using inverse kinematics to reach specified (x, y) coordinates.

## 🚀 Technologies Used
*   **Hardware:** Arduino, 2x Servo Motors
*   **Software:** Arduino IDE (C++), SolidWorks
*   **Manufacturing:** 3D Printing
*   **Core Concepts:** Inverse Kinematics, Coordinate Mapping

## ⚙️ How It Works
*   **Mechanical Design:** The robotic arms and motor cabin were fully designed from scratch in SolidWorks and manufactured using a 3D printer.
*   **Kinematics:** The system takes `(x, y)` Cartesian coordinates via serial input. It calculates the hypotenuse distance to the target and applies the Law of Cosines to determine the elbow angle. The shoulder angle is determined using `atan2` to account for height and elbow bending.
*   **Control:** The mathematical angles (in radians) are converted to degrees and mapped specifically to safely drive the servo motors without exceeding mechanical limits. 

## 🔧 Setup & Usage
1. Connect the shoulder servo to Pin 9 and the elbow servo to Pin 10 on your Arduino.
2. Upload the `.ino` code.
3. Open the Arduino Serial Monitor (Baud rate: 9600).
4. Send coordinates in the format `x,y` (e.g., `36,0` or `15,15`) and press Enter.
