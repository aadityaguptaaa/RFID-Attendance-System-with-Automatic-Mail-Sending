# 📌 RFID Attendance System with Google Sheets & Automatic Email Sending

This project is a **Smart Attendance System** developed as part of my **Computer Organization and Architecture (COA) project**. It records attendance using **RFID technology**, stores data in **Google Sheets**, and **sends automated email reports** with attendance data.



## 📖 Table of Contents
- [🚀 Features](#-features)
- [🛠️ Hardware & Software Requirements](#%EF%B8%8F-hardware--software-requirements)
  - [🔧 Hardware Components](#-hardware-components)
  - [🖥️ Software & Tools](#%EF%B8%8F-software--tools)
- [🛠️ Circuit Diagram](#%EF%B8%8F-circuit-diagram)
- [🔧 Installation & Setup](#-installation--setup)
  - [1️⃣ Hardware Setup](#1️⃣-hardware-setup)
  - [2️⃣ Google Sheets & Apps Script Setup](#2️⃣-google-sheets--apps-script-setup)
  - [3️⃣ Arduino & NodeMCU Code](#3️⃣-arduino--nodemcu-code)
- [🔧 How It Works](#-how-it-works)
- [📂 Cloning the Repository](#-cloning-the-repository)
- [📜 License](#-license)
- [🤝 Contributions](#-contributions)
- [📧 Contact](#-contact)



## 🚀 Features
- 📍 **RFID-based attendance marking**
- 📊 **Data stored in Google Sheets**
- 📧 **Automatic send email reports to faculty**
- 🔔 **Daily scheduled email triggers**
- 🖥️ **Web-based data access**



## 🛠️ Hardware & Software Requirements

### 🔧 **Hardware Components**
- **NodeMCU ESP8266** (WiFi microcontroller)
- **RFID Reader Module (MFRC522)**
- **16x2 I2C LCD Display**
- **Buzzer** (for alert sound)
- **Jumper Wires**
- **Power Supply (5V)**




### 🖥️ **Software & Tools**
- **Google Apps Script** (for automation)
- **Google Sheets** (for storing attendance data)
- **Arduino IDE** (for coding NodeMCU)
- **SMTP Mail API** (for sending emails)
- **Wi-Fi Connectivity**



## 🛠️ Circuit Diagram
![image](https://github.com/user-attachments/assets/609efff1-af40-4e35-b8ea-a532d852c1e6)



## 🔧 Installation & Setup

### 1️⃣ **Hardware Setup**
1. Connect **RFID module** to **NodeMCU** according to the circuit diagram.
2. Connect **LCD display** via **I2C**.
3. Attach **Buzzer** for alerts.

### 2️⃣ **Google Sheets & Apps Script Setup**
1. Create a **Google Sheet** with columns: `Date`, `Time`, `Name`.
2. Open **Google Apps Script** and paste the provided script.
3. Replace `SpreadsheetApp.openById('YOUR_SHEET_ID')` with your **Google Sheet ID**.
4. Deploy the script as a **web app** (`doGet` function will handle data entry).
5. Set a **time-based trigger** to schedule email reports daily.

### 3️⃣ **Arduino & NodeMCU Code**
1. Upload the **Arduino Sketch** to **NodeMCU**.
2. Ensure the correct **Wi-Fi SSID & Password** are entered.
3. The system will read **RFID tags** and send data to **Google Sheets**.



## 🔧 How It Works
1. **Scan an RFID card** - The system records attendance.
2. **Data is sent to Google Sheets** - Time and Name are stored.
3. **Daily email reports** are sent to faculty.



## 📂 Cloning the Repository
To clone this repository and set up the project on your system, run the following command:
```sh
 git clone https://github.com/aadityaguptaaa/RFID-Attendance-System-with-Automatic-Mail-Sending.git
```
Navigate into the project directory:
```sh
 cd RFID-Attendance-System-with-Automatic-Mail-Sending
```


## 📜 License
This project is **open-source** under the **MIT License**.


## 🤝 Contributions
We welcome contributions! To contribute:
1. **Fork** the repository.
2. Create a **new branch** (`feature-branch`)
3. Commit your **changes** and push.
4. Open a **Pull Request**.



## 📧 Contact
For queries, contact: `aadityavidit@gmail.com`

