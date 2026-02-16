
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc == 2) {
        try {
            BitcoinExchange btc;
            btc.add_database("data.csv");
            btc.process_input(argv[1]);
        }
        catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            return (1);
        }
        return (0);
    }
    else
        std::cerr << "Error: could not open file." << std::endl;
    return (1);
}



/* ex00 Amaç
Belirli bir tarihte belirli miktardaki Bitcoin’in değerini hesaplayan bir program yaz.
Program, iki veri kaynağı kullanacak:
- Verilen CSV dosyası → Bitcoin fiyatlarını tarih bazında içerir (örnek: data.csv).
- Kullanıcı girdisi dosyası → Değerlendirilecek tarih ve miktarları içerir (örnek: input.txt).
Program, her giriş satırındaki Bitcoin miktarını 
o tarihe (veya en yakın önceki tarihe) ait fiyatla çarparak sonucu ekrana yazacak.

Program bir dosya argümanı almalı:
    - ./btc input.txt/csv
Dosya satır formatı tam olarak şöyle olmalı:
    - date | value
- date
    - Tarih biçimi: YYYY-MM-DD
- value: o tarihte kullanıcının kaç adet Bitcoin’e sahip olduğu
    - float veya integer olabilir | 0 ile 1000 arasında olmalı
    - Negatif veya 1000’den büyük değer → hata
- Value bitcoin fiyatı çarpılır ve kullanıcıya kaç para ettiği hesaplanır.

- En az bir STL container kullanılmalı (örnek: std::map, std::vector).
- Hatalar uygun şekilde yönetilmeli ve ekrana anlamlı hata mesajı basılmalı:
    - Dosya açılamazsa → Error: could not open file.
    - Hatalı tarih → Error: bad input => ...
    - Negatif sayı → Error: not a positive number.
    - Çok büyük sayı → Error: too large a number.

Hesaplama Kuralı
Tarih, fiyat veritabanında birebir bulunmuyorsa:
- Bir önceki (en yakın küçük) tarih kullanılmalı.
- Gelecekteki (üst) tarih kullanılmamalı!
    - sonuç format -> YYYY-MM-DD => value = result
*/



/*
Örnek:
- Input -> 2011-01-03 | 3
- Database -> 2011-01-03, 0.3
- çıktı -> 2011-01-03 => 3 = 0.9
- çünkü: 3 (value) × 0.3 (bitcoin fiyatı) = 0.9
*/


/*
Map container
---
std::map, C++’ta anahtar–değer (key–value) ikililerini tutan bir associative container’dır.
Yani, her veriyi bir anahtar (key) ile ilişkilendirir ve bu anahtar sayesinde o veriye erişirsin.
map otomatik olarak anahtar sırasına göre (A → Z) sıralar.
| Özellik                 | Açıklama                                                                  |
| ----------------------- | ------------------------------------------------------------------------- |
| 🔑 **Anahtar (key)**    | Her elemanın benzersiz kimliği                                            |
| 📦 **Değer (value)**    | Anahtara bağlı veri                                                       |
| 🧭 **Sıralı**           | Elemanlar **artan sırada (ascending)** tutulur                            |
| 🚫 **Tekil anahtarlar** | Aynı anahtardan iki tane olamaz                                           |


### Kullanımı   
#include <map>

std::map<string, int> yas;

- Key tipi: string
- Value tipi: int
- Yani her isim (string) bir yaş (int) değeriyle eşleştirilecek.

### map'te kullanılan funcs
| Fonksiyon          | Açıklama                        |
| ------------------ | ------------------------------- |
| `size()`           | Eleman sayısını döner           |
| `empty()`          | Map boş mu kontrol eder         |
| `clear()`          | Tüm elemanları siler            |
| `count(key)`       | Anahtar varsa 1, yoksa 0 döner  |
| `begin()`, `end()` | İlk ve son eleman iterator’ları |

*/



/* Önemli

1. CSV Veritabanını Yükleme
data.csv dosyasını okuyarak tarih ve döviz kuru çiftlerini bir STL container (örneğin, std::map) içine yükleyin. 
std::map kullanımı, tarihleri sıralı bir şekilde saklamanızı sağlar ve en yakın önceki tarihi 
kolayca bulmanıza olanak tanır.

2. Girdi (input) Dosyasını İşleme
Program, bir dosya argümanı alacak (input.txt/csv gibi).
Dosyayı satır satır okuyarak her satırdaki tarihi ve değeri ayrıştırın.
Tarih ve değer formatını kontrol edin. Geçersiz formatlar için uygun hata mesajları yazdırın.

3. Hesaplama
Girdi dosyasındaki her tarih için, data.csv'den en yakın önceki tarihi bulun.
İlgili tarihteki döviz kuru ile değeri çarparak sonucu hesaplayın.

4. Hata Yönetimi
Dosya açılamazsa: Error: could not open file.
Geçersiz tarih formatı: Error: bad input => ...
Negatif değer: Error: not a positive number.
1000'den büyük değer: Error: too large a number.

5. Çıktı Formatı
Sonuçları şu formatta yazdırın: YYYY-MM-DD => value = result.

*/

/*
evo page'de sorulan sorular
1. Neden map container'ını kullandında diğerlerini kullanmadın
2. 
*/
