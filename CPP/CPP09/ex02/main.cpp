
#include "PmergeMe.hpp"

int ctrl_aruments(int argc, char **args) {
    for (int i=1; i < argc; i++) {
        std::string str = args[i];
        for (size_t j=0; j < str.size(); j++) {
            if (!std::isdigit(str[j]))
                return (1);
        }
        if (atoi(str.c_str()) <= 0)
            return (1);
    }
    return (0);
}

int main(int argc, char **argv) {

    if (ctrl_aruments(argc, argv) || argc < 2)
        return (std::cerr << "Error" << std::endl, 1);

    PmergeMe me;
    me.add_to_containers(argc, argv);
    me.calculate_duration();
    return (0);
}


// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
/*
senden merge-insert algoritmasını kullanarak sıralamanı istediği için biraz zor olabilir mantığını anlamak için
bu yüzden ilk olarak normal basit std::sort ile sırala daha sonra egzersizin mantığını anladıktan sonra 
merge insert algoritmasını eklersin senin için daha kolay olur
*/

/*
ex02 (PmergeMe)
Amaç
- Komut satırından verilen pozitif tam sayıları alıp Ford–Johnson (Merge-Insert) algoritmasını kullanarak sıralamaktır
- Aynı algoritmayı en az iki farklı STL container ile uygulamak
- Her iki container için çalışma süresini ölçüp karşılaştırmak

örnek argüman girdisi -> ./PmergeMe 3 5 9 7 4

Girdi Kuralları
- Sadece pozitif tam sayıları kabul etmeli
- En az 3000 sayı ile çalışabilmeli
- Şu durumlarda Error yazmalı:
    - Negatif sayı (-1)
    - Sayı olmayan argüman (abc)
    - Boş argüman
- Duplicate (aynı sayıdan iki tane) kontrolü zorunlu değil, sana bırakılmış.


Kullanılması zorunlu STL container’lar
En az 2 farklı container
Örneğin: std::vector<int> | std::deque<int>
⚠️ Önceki modüllerde kullandığın container’lar yasak (genelde list, map vb.)

Zaman ölçümü (Performance kısmı)    
Her container için:
Tüm işlem süresi ölçülmeli
- veri alma, kopyalama, sıralama
Mikro saniye (us) hassasiyetinde olmalı


Ekran çıktısı (Output formatı)
1. Sıralanmamış hali
    Before: 3 5 9 7 4
2. Sıralanmış hali
    After: 3 4 5 7 9
3. İlk container süresi
    Time to process a range of 5 elements with std::vector : 0.00031 us
4. İkinci container süresi
    Time to process a range of 5 elements with std::deque : 0.00014 us


ÖZETLE
Komut satırından gelen pozitif sayıları, Ford-Johnson algoritmasıyla, 
en az iki farklı STL container kullanarak sıralayan ve performanslarını 
karşılaştıran bir C++ programı yazman isteniyor.
*/