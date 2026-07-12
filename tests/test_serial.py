import serial
import time

PORT = "COM6"
BAUDRATE = 115200

try:
    print("Connecting to", PORT)

    ser = serial.Serial(PORT, BAUDRATE, timeout=2)

    print("Device connected on", PORT)

    # Trigger Arduino reset through DTR
    ser.dtr = False
    time.sleep(0.2)
    ser.dtr = True

    # Wait for Arduino boot
    time.sleep(2)

    print("\nSerial console ready")
    print("Type commands and press ENTER")
    print("Type EXIT to close\n")

    while True:
        command = input("> ")

        if command.upper() == "EXIT":
            break

        # Send command to Arduino
        ser.write((command + "\n").encode())

        time.sleep(0.2)

        print("Answer:")

        while ser.in_waiting:
            response = ser.readline().decode(errors="ignore").strip()
            if response:
                print(response)

    ser.close()

    print("Disconnected from", PORT)

except Exception as e:
    print("Error:", e)