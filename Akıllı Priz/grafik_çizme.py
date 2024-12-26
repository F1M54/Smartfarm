import pandas as pd
import matplotlib.pyplot as plt

def plot_graphs(excel_filename):
    # Excel dosyasını oku
    df = pd.read_excel(excel_filename)

    # Zaman bilgisi için "Tarih" ve "Saat" sütunlarını birleştir
    df["Zaman"] = pd.to_datetime(df["Tarih"] + " " + df["Saat"])

    # Grafik 1: Güç (W) - Zaman
    plt.figure(figsize=(10, 5))
    plt.plot(df["Zaman"], df["Güç (W)"], marker="o", label="Güç (W)")
    plt.title("Güç (W) Zaman Grafiği")
    plt.xlabel("Zaman")
    plt.ylabel("Güç (W)")
    plt.grid(True)
    plt.legend()
    plt.show()

    # Grafik 2: Toplam Tüketim (kWh) - Zaman
    plt.figure(figsize=(10, 5))
    plt.plot(df["Zaman"], df["Toplam Tüketim (kWh)"], marker="s", color="orange", label="Toplam Tüketim (kWh)")
    plt.title("Toplam Tüketim (kWh) Zaman Grafiği")
    plt.xlabel("Zaman")
    plt.ylabel("Toplam Tüketim (kWh)")
    plt.grid(True)
    plt.legend()
    plt.show()

if __name__ == "__main__":
    # Excel dosyasının yolunu belirtin
    excel_filename = "veriler3.xlsx"
    plot_graphs(excel_filename)
