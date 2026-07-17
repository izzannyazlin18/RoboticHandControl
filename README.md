# 🤖 5-Finger Robotic Hand Control System

An Arduino-based embedded application that maps human finger movements to a 5-digit robotic or prosthetic hand. The system reads analog inputs from individual flex sensors, processes the data through an Exponential Moving Average (EMA) low-pass filter to eliminate sensor jitter, and translates the filtered signals into precise servo motor angles.

## 📂 Project Structure

* `RoboticHandControl.ino` - Core Arduino sketch containing pin configurations, signal filtering algorithms, and servo mapping logic.
* `README.md` - Documentation and setup guide.

## 🛠️ Hardware Architecture

### System Pins & Components
* **Microcontroller:** Arduino Uno (or compatible board)
* **Actuators:** 5x Servo Motors (Pins: 2, 3, 4, 5, 6)
* **Sensors:** 5x Flex Sensors (Pins: A0, A1, A2, A3, A4)

 [Human Glove]                       [Robotic Hand]
 Flex Sensors  ──(Analog Input)──> Arduino ──(PWM Output)──> Servos
  (A0 - A4)                                                   (Pin 2 - 6)

## 🧠 Key Software Features

### 1. Signal Conditioning (Low-Pass Filter)
Flex sensors are inherently noisy due to mechanical shifting and electrical variance. To prevent the servo motors from twitching or jittering, a real-time Exponential Moving Average (EMA) filter is applied to the raw data:

$$\text{filteredFlex}[i] = (\alpha \times \text{raw}) + ((1 - \alpha) \times \text{filteredFlex}[i])$$

With a tuning factor of $\alpha = 0.1$, the system prioritizes smooth, natural-looking motor transitions over raw, erratic sensor spikes.

### 2. Custom Hardware Calibration
Because individual flex sensors have varying material tolerances and baseline resistances, the code utilizes unique tracking arrays (`flexMin` and `flexMax`) to define the specific boundary range for each finger:

```cpp
int flexMin[5] = {130, 130, 400, 150, 950}; // Sensor reading when fully bent
int flexMax[5] = {950, 600, 150, 950, 180}; // Sensor reading when flat
```
The application uses these thresholds to cleanly map the incoming signal to a full 0° to 180° rotational arc for the servos via the standard `map()` and `constrain()` functions.


### 🚀 How to Run the Project

1. Open `RoboticHandControl.ino` in the Arduino IDE.
2. Connect your Arduino board to your computer via USB.
3. Ensure the `Servo.h` library is included (comes default with the IDE).
4. Verify and upload the sketch to your board.
5. Open the Serial Monitor at `9600` baud to view real-time filtered flex sensor outputs.
