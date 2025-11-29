# 🏕️ C Dili Hayatta Kalma Simülatörü

Bu proje, C programlama dilinin temel yapılarını uygulamalı olarak göstermek amacıyla geliştirilmiş, konsol tabanlı **basit bir hayatta kalma simülatörüdür**. Oyun, **Sağlık**, **Enerji** ve **Yemek** gibi global değişkenleri yönetir ve kullanıcının girdiği komutlarla ilerler. Kodun merkezinde, sürekli oyun akışını sağlayan **`do-while`** döngüsü ve komutları yönlendiren **`switch-case`** yapısı bulunur. Aksiyonlar (**Avlanma**, **Sığınak Yapma** vb.), başarıyı kontrol etmek için **mantıksal operatörleri** (`&&`, `||`) ve anlık koşullu karar verme için **koşullu operatörü** (`?:`) yoğun olarak kullanır. Özellikle, Tehlike Serisi (**`for` döngüsü**) ve Şifreli İlerleme (**iç döngü olarak `do-while`**) fonksiyonları, C dilindeki temel döngü yapılarını pratik senaryolarda sergiler. Proje, C öğrenenler için fonksiyonel, okunabilir ve temel dilbilgisi kurallarını pekiştiren iyi bir başlangıç örneğidir.

## 🚀 Kurulum ve Çalıştırma

Bu proje C dilinde yazılmıştır. Çalıştırmak için bir C derleyicisine (örneğin **GCC**) ihtiyacınız vardır.

1.  **Kodu Kaydedin:** Kodu `survival_game.c` gibi bir dosyaya kaydedin.

2.  **Derleme (Compile):** Terminalinizde aşağıdaki komutu kullanın:
    ```bash
    gcc survival_game.c -o survival
    ```

3.  **Çalıştırma:** Derlenen programı çalıştırın:
    ```bash
    ./survival
    ```

## 🎮 Temel Komutlar

| Komut | Açıklama | Vurgulanan Yapı |
| :--- | :--- | :--- |
| **A** | Avlan | Mantıksal Operatörler (`&&`, `||`) |
| **S** | Sığınak Ara | `if-else if-else` |
| **R** | Dinlen | Koşullu Operatör (`?:`) |
| **F** | Tehlike Serisi | `for` Döngüsü |
| **P** | İlerle | `do-while` Döngüsü |
| **X** | Çıkış | `do-while` Ana Döngü Kontrolü |
