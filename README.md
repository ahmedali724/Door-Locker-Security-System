# Door Locker Security System

Welcome to the Door Locker Security System project! This system is designed to enhance door security using a password-based access control mechanism. 

## Table of Contents

- [Introduction](#introduction)
- [System Specifications](#system-specifications)
- [Architecture](#architecture)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Simulation Screenshot](#simulation-screenshot)

## Introduction

The Door Locker Security System is a project that utilizes two ATmega32 microcontrollers to provide secure door access through a password. It offers features such as password creation, password verification, door locking/unlocking, and user-friendly interaction via an LCD and a keypad.

## System Specifications

- Microcontroller 1 (Mc1):
  - HAL drivers: LCD and Keypad
  - MCAL drivers: GPIO, UART, Timer1

- Microcontroller 2 (Mc2):
  - HAL drivers: Buzzer, EEPROM, and DC-motor
  - MCAL drivers: GPIO, I2C, UART, Timer0_PWM, Timer1

## Architecture

The project follows a layered architecture model:
- Mc1 (HMI_ECU) handles user interaction and interface components.
- Mc2 (Control_ECU) manages the core system logic, including password verification and door control.

## Getting Started

To get started with the Door Locker Security System, you'll need the following hardware components:
- Two ATmega32 microcontrollers
- LCD and keypad for Mc1
- Buzzer, EEPROM, and DC-motor for Mc2

You'll also need to set up the development environment, including the required drivers and libraries.

## Usage

1. Creating a System Password
   - Follow the on-screen instructions to set up a system password.

2. Main Options
   - Use the main menu to select options like opening the door or changing the password.

3. Open Door
   - Enter the password to unlock the door securely.

4. Change Password
   - Choose this option to set a new system password.

5. Password Mismatch Handling
   - The system handles mismatched passwords, locking the system after multiple failed attempts.

## Simulation Screenshot
![image](https://github.com/ahmedali724/Door-Locker-Security-System/assets/111287464/8cb342f1-7611-4f39-8470-afc1ac956bac)

---

We hope this README file helps you understand and get started with the Door Locker Security System. If you have any questions or suggestions, please feel free to reach out to us.

Happy coding! 🚪🔒
