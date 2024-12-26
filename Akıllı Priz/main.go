package main

import (
	"fmt"
	"github.com/sausheong/hs1xxplug"
	"time"
)

func main() {
	plug := hs1xxplug.Hs1xxPlug{IPAddress: "192.168.1.29"} // HS110 akıllı fişinizin IP adresini buraya girin

	// Her 5 saniyede bir veri güncelleme döngüsü
	for {
		// HS110 akıllı fişinden anlık veri al
		results, err := plug.MeterInfo()
		if err != nil {
			fmt.Println("Veri alınırken hata oluştu:", err)
		} else {
			fmt.Println("Anlık veriler:", results)
		}7

		// 5 saniye bekleyin
		time.Sleep(5 * time.Second)
	}
}
