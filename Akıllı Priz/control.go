package main

import (
	"fmt"
	"time"

	"github.com/sausheong/hs1xxplug"
)

func main() {
	plug := hs1xxplug.Hs1xxPlug{IPAddress: "192.168.1.29"} // HS110 akıllı fişinizin IP adresini buraya girin

	// 10 saniye sonra fişi aç
	time.AfterFunc(10*time.Second, func() {
		err := plug.TurnOn()
		if err != nil {
			fmt.Println("Fişi açarken hata oluştu:", err)
		} else {
			fmt.Println("Fiş açıldı")
		}
	})

	// 20 saniye sonra fişi kapat
	time.AfterFunc(20*time.Second, func() {
		err := plug.TurnOff()
		if err != nil {
			fmt.Println("Fişi kapatırken hata oluştu:", err)
		} else {
			fmt.Println("Fiş kapatıldı")
		}
	})

	// 30 saniye sonra programı sonlandır
	time.AfterFunc(30*time.Second, func() {
		fmt.Println("Program sonlandırıldı")
	})

	// Programın sonlandırılmasını beklemek için 31 saniye uyuyoruz
	time.Sleep(31 * time.Second)
}
