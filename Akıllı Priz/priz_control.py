from pyHS100 import SmartPlug

# Prizin IP adresini ve portunu belirtin
plug_ip = "192.168.1.100"  # Prizin IP adresini buraya girin
plug_port = 9999  # Prizin portunu buraya girin

# Priz nesnesini oluşturun
plug = SmartPlug(plug_ip, plug_port)

# Prizin enerji tüketimini alın
energy = plug.get_emeter_realtime()

# Enerji tüketimi bilgisini yazdırın
print("Akım (A):", energy["current"])
print("Gerilim (V):", energy["voltage"])
print("Güç (W):", energy["power"])
print("Toplam Enerji Tüketimi (kWh):", energy["total"])
