import pandas as pd
from pyHS100 import SmartPlug
from datetime import datetime
from time import sleep

def main():
    # Excel dosyasının adı ve konumu
    excel_filename = "veriler2.xlsx"

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

            # Verileri al
            voltage = data["voltage_mv"] / 1000  # Gerilim (V)
            current = data["current_ma"] / 1000   # Akım (A)
            power = data["power_mw"] / 1000       # Güç (W)
            total_energy = data["total_wh"] / 1000  # Toplam tüketim (kWh)

            # Şuanki tarih ve saat
            now = datetime.now()
            date = now.strftime("%d/%m/%Y")  # Gün/Ay/Yıl
            time = now.strftime("%H:%M:%S")  # Saat:Dakika:Saniye

            # Veriyi bir DataFrame'e dönüştür
            new_data = pd.DataFrame({"Tarih": [date], "Saat": [time], "Gerilim (V)": [voltage], 
                                      "Akım (A)": [current], "Güç (W)": [power], "Toplam Tüketim (kWh)": [total_energy]})
            
            # Boş veya tümü-NA girişleri kontrol et
            if not new_data.isna().all().all():
                # Veriyi mevcut DataFrame ile birleştir
                df = pd.concat([df, new_data], ignore_index=True)
                
                # Verileri Excel dosyasına kaydet
                df.to_excel(excel_filename, index=False)
                print("Veri Excel dosyasına yazıldı:", data)

            # 5 saniye bekle
            #sleep(5)

        except Exception as e:
            print("Bir hata oluştu:", e)

if __name__ == "__main__":
    main()
