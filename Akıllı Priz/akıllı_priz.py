import pandas as pd
from pyHS100 import SmartPlug
from datetime import datetime
from time import sleep

def main():
    # Excel dosyasının adı ve konumu
    excel_filename = "veriler3.xlsx"

    # Akıllı prizin IP adresi
    plug_ip = "192.168.137.65"

    # DataFrame sütunları
    columns = ["Tarih", "Saat", "Gerilim (V)", "Akım (A)", "Güç (W)", "Toplam Tüketim (kWh)"]

    # Excel dosyasını oluştur ve ilk satırı yaz
    df = pd.DataFrame(columns=columns)
    df.to_excel(excel_filename, index=False)

    while True:
        try:
            # Akıllı prizden veri al
            plug = SmartPlug(plug_ip)
            data = plug.get_emeter_realtime()

            # Verileri düzenle
            voltage = data["voltage_mv"] / 1000  # Gerilim (V)
            current = data["current_ma"] / 1000  # Akım (A)
            power = data["power_mw"] / 1000      # Güç (W)
            total_energy = data["total_wh"] / 1000  # Toplam tüketim (kWh)

            # Şu anki tarih ve saat
            now = datetime.now()
            date = now.strftime("%d/%m/%Y")  # Gün/Ay/Yıl
            time = now.strftime("%H:%M:%S")  # Saat:Dakika:Saniye

            # Verileri anlamlı formatta yazdır
            print(f"Veriler:")
            print(f"  Gerilim: {voltage:.3f} V")
            print(f"  Akım: {current:.3f} A")
            print(f"  Güç: {power:.3f} W")
            print(f"  Toplam Tüketim: {total_energy:.3f} kWh")

            # Veriyi bir DataFrame'e dönüştür
            new_data = pd.DataFrame({"Tarih": [date], "Saat": [time], "Gerilim (V)": [voltage], 
                                      "Akım (A)": [current], "Güç (W)": [power], "Toplam Tüketim (kWh)": [total_energy]})
            
            # Veriyi mevcut DataFrame ile birleştir
            df = pd.concat([df, new_data], ignore_index=True)
            
            # Verileri Excel dosyasına kaydet
            df.to_excel(excel_filename, index=False)
            print("Veri Excel dosyasına yazıldı.\n")

            # 5 saniye bekle
            sleep(5)

        except Exception as e:
            print("Bir hata oluştu:", e)

if __name__ == "__main__":
    main()

# cd "C:\Users\hp\OneDrive\Masaüstü\AGU_24_25_FALL\SDPII\SDP I\proje\hs1xx"
