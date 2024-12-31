import serial
ser = serial.Serial('/dev/ttyS0',115200,timeout=1)

while True:
	if ser.in_waiting > 0:
		line =ser.readline().decode('utf-8').rstrip()
		print("Received:", line)
