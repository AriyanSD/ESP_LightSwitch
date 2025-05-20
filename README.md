💡 Project Overview: Network-Controlled Room Lamp with Optional RF Remote
Transform your room lamp into a smart device controllable over your local network. By hosting a simple web interface on an ESP8266 or ESP32, you can toggle the lamp on and off using any web browser. Additionally, integrate an RF receiver module to allow control via a traditional RF remote.

🔧 Key Features
Web-Based Control: Access the lamp's control interface by entering the ESP's IP address into your browser.

RF Remote Integration: Optional support for RF receivers enables lamp control using standard RF remotes.

Flexible HTML Hosting: Serve the control interface by either embedding HTML directly into your code or storing it separately using SPIFFS.

📁 Hosting HTML with SPIFFS
Storing your HTML files separately using SPIFFS (SPI Flash File System) keeps your code cleaner and allows for easier updates.
For Arduino IDE 1.x Users:

Install the SPIFFS Uploader Plugin:

For ESP8266: [Install ESP8266 Filesystem Uploader in Arduino IDE](https://randomnerdtutorials.com/install-esp8266-filesystem-uploader-arduino-ide/)

For ESP32: [Install ESP32 Filesystem Uploader in Arduino IDE](https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)

Upload to SPIFFS:

In the Arduino IDE, go to Tools > ESP8266 Sketch Data Upload or ESP32 Sketch Data Upload.

This will upload the contents of the data folder to your ESP's flash memory


For Arduino IDE 2.x Users:

As of now, the SPIFFS uploader plugin is not directly compatible with Arduino IDE 2.x. It's recommended to use Arduino IDE 1.x for uploading files to SPIFFS. You can have both versions installed simultaneously without conflicts.


The index.html file served by the ESP provides a user-friendly interface to control the lamp. By accessing the ESP's IP address in a browser, users can toggle the lamp's state with a simple click.



🧰 Components Required
NodeMCU (ESP8266)

RF Receiver Module (e.g., 433MHz)

Relay Module (for controlling the lamp)

Lamp or LED + resistor (optional for testing)

Breadboard and Jumper Wires

Power Supply (via USB or 5V adapter)

🔌 Wiring Description
| ESP8266 Pin    | Connected To                | Purpose                      |
| -------------- | --------------------------- | ---------------------------- |
| **D1 (GPIO5)** | Relay IN                    | Control lamp (LED output)    |
| **D2 (GPIO4)** | RF Receiver OUT             | Detect signal from RF remote |
| **3V3**        | RF Receiver VCC             | Power RF receiver            |
| **GND**        | RF Receiver GND + Relay GND | Common ground                |
| **VIN**        | Relay VCC                   | Power relay (if 5V relay)    |


⚠️ Note: Use a transistor + flyback diode if you’re driving a mechanical relay directly and it draws more than the ESP’s pin can handle. You can also use a logic convertor but transitor should be fine

⚡ Relay Wiring (to control the lamp)
If you’re controlling a lamp connected to AC mains, follow strict safety precautions and preferably use an opto-isolated relay module.

COM of the relay → Live wire from AC

NO (Normally Open) → Live wire to lamp

Neutral wire connects directly to the lamp

For safety, don’t work with mains AC unless you're experienced. You can test your circuit with a 5V LED strip or a low-voltage lamp first.
