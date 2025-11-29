#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> 

// --- Global Durum Değişkenleri 
int health = 100;    // Sağlık (0-100) 
int energy = 100;    // Enerji (0-100) 
int food_count = 5;  // Yemek sayısı 
int has_shelter = 0; // Sığınak bulunup bulunmadığı (0/1)

// --- Yardımcı Fonksiyonlar ---

// Durumun güncel halini ekrana basar
void print_status() {
    printf("\n--- Durum Raporu (E) ---\n");
    printf("Saglik: %d/100\n", health);
    printf("Enerji: %d/100\n", energy);
    printf("Yemek Sayisi: %d\n", food_count);
    printf("Siginak Durumu: %s\n", has_shelter ? "Bulundu" : "Bulunamadi");
    printf("--------------------------\n");
}

// Tüm değerleri 0-100 aralığında tutmak için sınırlar
void clamp_stats() {
    if (health > 100) health = 100;
    if (health < 0) health = 0;

    if (energy > 100) energy = 100;
    if (energy < 0) energy = 0;
}

// --- Ana Oyun Mantığı Fonksiyonları ---

// A: Avlanma 
void action_hunt() {
    // Aritmetik Operatörler: Enerji kaybı 
    int energy_cost = 15;
    energy -= energy_cost;

    printf("\nAvlanmaya ciktiniz. %d enerji harcandi.\n", energy_cost);

    if (energy < 0) {
        printf("Cok yorgunsunuz! Avlanamadan geri dondunuz.\n");
        energy = 0;
        return;
    }

    // Mantıksal Operatörler (&&, ||) ile koşullu sonuç 
    // Başarılı avlanma koşulu: Yeterli enerji VE rastgele şans (70%)
    if (rand() % 10 < 7 && energy > 10) {
        food_count++; // Aritmetik Operatör
        printf("? Basarili av! 1 birim yemek buldunuz. Yemek sayiniz: %d\n", food_count);
    }
    // Yaralanma koşulu: Düşük şans (20%) VEYA sığınak yoksa 
    else if (rand() % 10 < 2 || has_shelter == 0) {
        int damage = (has_shelter == 0) ? 15 : 5;
        health -= damage; // Aritmetik Operatör
        printf("? Bir hayvan tarafindan yaralandiniz! %d saglik kaybettiniz.\n", damage);
    } else {
        printf("?? Bugun sansiniz yoktu. Yemek bulamadiniz.\n");
    }

    clamp_stats();
}

// S: Sığınak Ara 
void action_shelter() {
    printf("\nSiginak aramaya basladiniz. Bu biraz enerji gerektiriyor...\n");
    energy -= 10;
    clamp_stats();

    if (has_shelter) {
        printf("Zaten bir siginaginiz var. Bosa enerji harcamayin.\n");
        return;
    }

    // IF-ELSE Yapıları ile ihtimal değerlendirmesi 
    // Başarılı olma ihtimali: Enerji yüksek VE yemek varsa
    if (energy > 50 && food_count >= 1) { // Mantıksal Operatör (&&)
        has_shelter = 1; // Aritmetik Güncelleme
        food_count--; // Sığınak yapımı için 1 yemek harcandı
        printf("?? Mukemmel bir yer buldunuz ve basit bir siginak kurdunuz! (1 yemek harcandi)\n");
    } 
    // Yetersiz durum: Sağlık çok düşük
    else if (health < 30) {
        printf("?? Cok zayıfsınız. Siginak aramak icin gucunuz yok.\n");
    }
    // Standart başarısızlık
    else {
        printf("?? Cevrede güvenli bir yer bulamadıiniz. Tekrar deneyin.\n");
    }

    clamp_stats();
}

// R: Dinlen 
void action_rest() {
    int health_gain = has_shelter ? 20 : 10;
    int energy_gain = 30;

    // Aritmetik Operatörler: Dinlenme ile artış 
    health += health_gain;
    energy += energy_gain;

    printf("\nDinleniyorsunuz...\n");
    printf("Saglik +%d, Enerji +%d kazandiniz.\n", health_gain, energy_gain);

    // Sağlık Kontrolü 
    if (health > 100) {
        printf("Harika hissediyorsunuz!\n");
    } else if (health < 50) {
        printf("Hala dinlenmeye ihtiyaciniz var.\n");
    }

    clamp_stats();
}

// F: Tehlike Serisi Simülasyonu
void action_danger_wave() {
    printf("\n\n?? Bolgedeki 3 turluk tehlike dalgasi basliyor! (F)\n"); 

 
    int i; 
    int damage = 0; // i, damage ve energy_drain'i buraya taşıdık.
    int energy_drain = 0;

    // FOR Döngüsü: 3 tur simülasyon 
    for (i = 1; i <= 3; i++) {
        damage = rand() % 10 + 5; 
        energy_drain = 10;        
        
        printf("\n-- Tur %d --\n", i);
        
        // Oyuncu durumuna bağlı can kaybı
        if (has_shelter) {
            damage /= 2;
            printf("Siginak sayesinde hasar hafifledi.\n");
        }
        
        // Aritmetik Operatörler
        health -= damage;
        energy -= energy_drain;
    }
    
    // Döngü bitti. Artık damage ve energy_drain erişilebilir.
    printf("Tehlike atlattiniz: Saglik -%d, Enerji -%d.\n", damage, energy_drain);

    
    
    printf("Tehlike dalgasi sona erdi!\n");
    clamp_stats();
}

// P: Şifreli İlerleme (Engel Aşma) 
void action_progression() {
    char key_input;
    const char correct_key = 'G'; // Gizli anahtar 'G'

    printf("\n?? Onumuzde bir engel var. Gecmek için sifreyi girin.\n");

    // DO-WHILE Döngüsü: Doğru karakter girilene kadar tekrar etme 
    do {
        printf("Anahtar karakteri girin (İpucu: G ile baslar): ");
        // Dikkat: scanf'ten önce boşluk koymak, önceki new-line karakterini yoksayar.
        if (scanf(" %c", &key_input) != 1) {
            // Hata durumunda buffer'ı temizle
            while(getchar() != '\n'); 
            key_input = ' '; 
        }
        
        // Komutları büyük harf kabul et
        key_input = toupper(key_input);

        if (key_input != correct_key) {
            printf("Yanlis anahtar! Tekrar denemelisiniz.\n");
        }

    } while (key_input != correct_key); // Doğru koşul sağlanana kadar devam 

    // Aritmetik Operatörler: Ödül
    energy += 25;
    food_count++;
    printf("?? Basarili! Engeli astiniz. Enerji +25, Yemek +1 kazandiniz.\n");

    clamp_stats();
}


int main() {
    char command;
    srand(time(NULL)); // Rastgelelik için zaman tabanlı tohumlama

    printf("==========================================\n");
    printf("   Karakter Tabanli Hayatta Kalma Simulatoru\n");
    printf("==========================================\n");
    printf("Komutlar: A(vlan), S(iginak), R(dinlen), E(nvanter), F(Tehlike), P(İlerle), X(Cikis)\n");

    // Ana komut dinleme döngüsü (DO-WHILE zorunluluğu) 
    do {
        print_status();
        
        if (health <= 0) {
            printf("\n--- OYUN BİTTİ ---\n");
            printf("Sagliginiz bitti. Hayatta kalamadiniz.\n");
            break;
        }

        printf("\nKomutunuz (X ile cikis): ");
        if (scanf(" %c", &command) != 1) {
             // Geçersiz giriş durumunda tamponu temizle
             while(getchar() != '\n'); 
             command = ' '; 
        }

        command = toupper(command); // Komutları büyük harfe çevir 

        // SWITCH-CASE Komut Yönetimi 
        switch (command) {
            case 'A': // Avlan 
                action_hunt();
                break;
            case 'S': // Sığınak Ara 
                action_shelter();
                break;
            case 'R': // Dinlen 
                action_rest();
                break;
            case 'E': // Envanteri Görüntüle 
                // Zaten do-while döngüsünün başında yapılıyor, tekrar çağırmaya gerek yok.
                printf("Durum görüntülendi.\n");
                break;
            case 'F': // Tehlike Serisi (FOR döngüsü) 
                action_danger_wave();
                break;
            case 'P': // Şifreli İlerleme (DO-WHILE döngüsü) 
                action_progression();
                break;
            case 'X': // Çıkış 
                printf("Simulatorden cikiliyor...\n");
                break;
            default:
                printf("Gecersiz komut. Lutfen gecerli bir komut girin (A, S, R, E, F, P, X).\n");
                // Hata durumunda enerji kaybı
                energy -= 5; 
                clamp_stats();
                break;
        }
        
    } while (command != 'X'); // Çıkış komutu verilene kadar devam et 

    printf("\nSimulasyon basariliyla sonuclandirildi.\n");
    return 0;
}
