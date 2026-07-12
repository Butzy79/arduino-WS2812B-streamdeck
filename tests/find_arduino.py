import serial.tools.list_ports

print("Serial USB Ports:\n")

porte = list(serial.tools.list_ports.comports())

if not porte:
    print("No port")
else:
    for p in porte:
        print("Port:", p.device)
        print("Name :", p.description)
        print("USB  :", p.hwid)
        print("---")