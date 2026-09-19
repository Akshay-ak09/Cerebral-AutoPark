# Cerebral AutoPark

## Project Overview
Cerebral AutoPark is a PIC16F877A-based intelligent parallel parking assistant developed and simulated using Proteus. The system detects obstacles around the vehicle and controls the vehicle's movement and steering to demonstrate an automated parallel parking sequence.

## Features
- Automated parallel parking control
- Four-direction obstacle detection
- Two-wheel DC motor control
- Servo-based steering control
- 16x2 LCD status display
- Red and green LED indicators
- Real-time obstacle status
- PIC16F877A-based embedded control
- Proteus simulation

## Components Used
- PIC16F877A Microcontroller
- L293D Motor Driver
- 2 × DC Motors
- Hobby Servo Motor
- 4 × PULSE Sensor Models
- 16x2 LCD
- Green LED
- Red LED
- Buzzer
- 20 MHz Crystal
- 22 pF Capacitors
- 10 kΩ Resistor
- 10 kΩ Potentiometer
- 220 Ω LED Resistors
- +5V Power Supply
- 
## Pin Configuration
| Component | PIC16F877A Pin |
|---|---|
| LCD RS | RB0 |
| LCD EN | RB1 |
| LCD D4 | RB2 |
| LCD D5 | RB3 |
| LCD D6 | RB4 |
| LCD D7 | RB5 |
| Front Sensor | RC4 |
| Left Sensor | RC5 |
| Rear Sensor | RC6 |
| Right Sensor | RA1 |
| Servo Signal | RC2 |
| Motor 1 IN1 | RD0 |
| Motor 1 IN2 | RD1 |
| Motor 2 IN3 | RD2 |
| Motor 2 IN4 | RD3 |
| Green LED | RD4 |
| Red LED | RD5 |
| Buzzer | RC7 |

## Software Tools
- MPLAB X IDE
- XC8 Compiler
- Proteus 8 Professional
- GitHub

## System Architecture
'
             ┌─────────────────────┐
             │    PIC16F877A       │
             │   Main Controller   │
             └──────────┬──────────┘
                        │
        ┌───────────────┼────────────────┐
        │               │                │
        ▼               ▼                ▼
  PULSE Sensors     L293D Driver      Servo Motor
        │               │                │
        │               ▼                │
        │           DC Motors            │
        │                                │
        └────────────┬───────────────────┘
                     │
              ┌──────┴──────┐
              │             │
              ▼             ▼
           16x2 LCD       LED Indicators
           
## Working Principle
The four simulated sensor inputs provide obstacle information to the PIC16F877A. The microcontroller processes these inputs and controls the L293D motor driver and steering servo.

The DC motors provide vehicle movement while the servo controls the steering direction. The LCD displays the current operating state and the LEDs provide visual status indication.

The system demonstrates a sequential parallel-parking operation consisting of parking-space detection, controlled reverse movement, steering adjustment, obstacle checking, vehicle alignment, and parking completion.

## Circuit Diagram
<img width="1315" height="842" alt="image" src="https://github.com/user-attachments/assets/bd83fd86-4d40-44c9-ac0b-f656cafa7360" />

## Simulation Results
The complete system is simulated in Proteus using the PIC16F877A, L293D, DC motors, hobby servo, LCD, LEDs, and PULSE-based obstacle inputs.

## Future Improvements
Replace simulated PULSE inputs with real HC-SR04 ultrasonic sensors
Implement actual distance measurement in centimeters
Add PWM speed control
Improve parking-space detection
Implement adaptive steering control
Add real-time buzzer warnings
Build a physical prototype
Add wireless monitoring

## Author
Akshay S M
Electronics and Communication Engineering

