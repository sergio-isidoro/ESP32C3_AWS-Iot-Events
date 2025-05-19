# 🔥 **Automated Control System with AWS IoT Events Integration**

This project implements an automated control system that integrates the ESP32 with AWS IoT Events for real-time event detection, device monitoring, and automated actions. It uses AWS IoT Core, SNS for notifications, and IoT Events for seamless event management based on sensor data.

---

## 🌟 **Features**

- **AWS IoT Integration:** Connects ESP32 with AWS IoT Core for secure communication and data handling.
- **IoT Events Detection:** Monitors IoT device states and triggers events based on conditions like location changes or system malfunctions.
- **Automated Notifications:** Sends real-time alerts via Amazon SNS when specific events are detected.
  
### **Device State Monitoring**

- Monitors device location and temperature.
- Detects state changes (e.g., entering or leaving a predefined area).
  
### **Automated Event Handling**

- Automatically triggers actions like sending notifications or activating other AWS services.
  
---

## 🛠️ **Hardware Pin Mapping**

| **Pin** | **Function**           |
|:-------:|:----------------------:|
| D1      | Output LED             |
| D2      | Button Input           |

---

## 📚 **Code Overview**

- **Setup Phase:** Initializes Wi-Fi and MQTT connection to AWS IoT, including device certificates for secure communication.
  
### **Loop Functions**

- **Event Monitoring:** Checks for button presses and updates device state (e.g., temperature changes).
- **MQTT Communication:** Publishes sensor data to AWS IoT Core and subscribes to device shadow updates.
- **AWS IoT Events Integration:** Sends events to AWS IoT Events when specific conditions (e.g., location change) are met.
- **Real-Time Notifications:** Sends email alerts via Amazon SNS when certain events are triggered.

---

## 🚀 **How to Use**

1. **Initial Setup:** Connect the ESP32 to your Wi-Fi and configure AWS IoT Core credentials.
2. **Device Registration:** Register your device in AWS IoT Core and configure policies and certificates.
3. **Event Configuration:** Use AWS IoT Events to define event detection logic and configure automatic actions.
4. **Operation:** Monitor device states and receive notifications in real-time when events occur.
5. **Testing:** Test the setup by pressing the button to simulate temperature changes or state transitions.

---

## 🎯 **Applications**

This system can be adapted for various IoT applications such as:

- **Automated asset monitoring:** Track devices and trigger actions based on specific states (e.g., low battery, location change).
- **Smart alerts:** Set up real-time alerts for system malfunctions or state changes.
- **Industrial IoT solutions:** Manage and monitor devices in a factory or warehouse environment.

---

## 📸 **Photos**

![ESP32C3_PinOut](https://github.com/user-attachments/assets/6acbe8f2-9935-40ed-a314-100a2d607c5e)
![wokwi](https://github.com/user-attachments/assets/5ddce3f7-f39f-466d-986b-3478c4b40cd3)
![AWS_Iot](https://github.com/user-attachments/assets/c8b79e2a-0eac-41ed-8128-dca047f3f329)

## Github link

[Automated_Control_System_with_AWS_IoT_Events](https://github.com/manoper93/ESP32C3_AWS-Iot-Events)
