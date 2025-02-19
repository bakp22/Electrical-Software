import serial
import threading
from kivy.app import App
from kivy.clock import Clock
from kivy.uix.label import Label

# ✅ Ensure correct port name & settings
SERIAL_PORT = "/dev/tty.usbmodem2101"  # Change if needed
BAUD_RATE = 9600
TIMEOUT = 1
switch = False # initial state of Arduino 
isWater = False
latest_water = ""

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=TIMEOUT)
except serial.SerialException as e:
    print(f"Error: Could not open serial port {SERIAL_PORT}. {e}")
    ser = None  # Prevent crashes if the port isn't available

latest_temp = "Waiting for data..."


# read serial data from sensors 
def read_serial():
    global latest_temp
    while ser:  # while the serial is connected 
        if ser.in_waiting > 0: # if the data is positive 
            try:
                temp_data = ser.readline().decode("utf-8").strip() # read data from arduino output for temperature
                water_data = ser.readline().decode("utf-8").strip()
                temp_values = temp_data.split(",")
                water_value = water_data

                # Ensure the temperature data is valid
                if len(temp_values) == 2:
                    tempC, tempF = temp_values
                    latest_temp = f"Temperature:\n{tempC}°C | {tempF}°F"
                else:
                    latest_temp = "Invalid data received"

                # Ensure the water sensor data is valid and assign accordingly 
                # water level sensor data goes from 0 to 1023
                if isWater == False:
                    latest_water = "No Water Present"
                else:
                    latest_water = "Water Present"

                if 
                    
            except Exception as e:
                latest_temp = f"Error: {e}"

# Start reading serial in a separate thread
if ser:
    thread = threading.Thread(target=read_serial, daemon=True)
    thread.start()

# build App 
class MyApp(App):
    def build(self):
        self.label = Label(text=latest_temp, font_size=40)
        Clock.schedule_interval(self.update_label, 1)  # Update every second
        return self.label    

    def update_label(self, dt):
        self.label.text = latest_temp  # Update label with new data

if __name__ == "__main__":
    MyApp().run()
