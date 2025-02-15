import serial
import threading
from kivy.app import App
from kivy.clock import Clock
from kivy.uix.label import Label

# ✅ Ensure correct port name & settings
SERIAL_PORT = "/dev/tty.usbmodem2101"  # Change if needed
BAUD_RATE = 9600
TIMEOUT = 1

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=TIMEOUT)
except serial.SerialException as e:
    print(f"Error: Could not open serial port {SERIAL_PORT}. {e}")
    ser = None  # Prevent crashes if the port isn't available

latest_temp = "Waiting for data..."

def read_serial():
    global latest_temp
    while ser:  # ✅ Only run if serial is connected
        if ser.in_waiting > 0:
            try:
                data = ser.readline().decode("utf-8").strip()
                temp_values = data.split(",")

                # ✅ Ensure the data is valid
                if len(temp_values) == 2:
                    tempC, tempF = temp_values
                    latest_temp = f"Temperature:\n{tempC}°C | {tempF}°F"
                else:
                    latest_temp = "Invalid data received"
            except Exception as e:
                latest_temp = f"Error: {e}"

# ✅ Start reading serial in a separate thread
if ser:
    thread = threading.Thread(target=read_serial, daemon=True)
    thread.start()

class MyApp(App):
    def build(self):
        self.label = Label(text=latest_temp, font_size=40)
        Clock.schedule_interval(self.update_label, 1)  # ✅ Update every second
        return self.label    

    def update_label(self, dt):
        self.label.text = latest_temp  # ✅ Update label with new data

if __name__ == "__main__":
    MyApp().run()
