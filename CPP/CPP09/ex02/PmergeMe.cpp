
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) {*this = other;}
PmergeMe &PmergeMe::operator=(const PmergeMe& other) {
    (void)other;
    return (*this);
}
PmergeMe::~PmergeMe() {}


void PmergeMe::add_to_containers(int argc, char **args) {
    for (int i=1; i < argc; i++) {
        int number = atoi(args[i]);
        t_vector.push_back(number); // vektöre ekleme
        t_deque.push_back(number);  // deque ekleme
    }
}

/*
Bu fonksiyon, aynı veri kümesi üzerinde std::vector ve std::deque kullanarak sıralama işlemi yapar 
ve gettimeofday ile mikro saniye seviyesinde performans ölçümü gerçekleştirir
- Önce verileri yazdırır (Before)
- vector’ü sıralar ve süresini ölçer
- deque’yi sıralar ve süresini ölçer
- Sonuçları ve geçen süreleri ekrana yazdırır

Zaman Ölçmek İçin Kullanılan Yapı: timeval
timeval yapısı şunları içerir:
struct timeval {
    long tv_sec;   // saniye
    long tv_usec;  // mikrosaniye (1 saniye = 1.000.000 mikrosaniye)
};


us: mikrosaniye
s: saniye

*/

void PmergeMe::calculate_duration() {
    struct timeval v_st, v_en;
    struct timeval d_st, d_en;

    std::cout << "Before v: ";
    for (std::vector<int>::iterator it = t_vector.begin(); it != t_vector.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    // Yani zaman ölçümü şu aralığı kapsıyor: [ sort_elements_in_vector çalıştığı süre ]
    gettimeofday(&v_st, NULL);              // 1. Başlangıç zamanını al
    sort_elements_in_vector(t_vector);      // 2. Sıralama yap
    gettimeofday(&v_en, NULL);              // 3. Bitiş zamanını al

    /* Süreyi Hesaplama Mantığı
    Amaç: Toplam süreyi mikrosaniye cinsine çevirmek.
    toplam süre (v_duration) = (saniye farkı × 1.000.000) + mikrosaniye farkı
    */
    long v_seconds = v_en.tv_sec - v_st.tv_sec;         // saniye cinsinden zaman hesaplaması
    long v_microseconds = v_en.tv_usec - v_st.tv_usec;  // mikrosaniye cinsinden zaman hesaplaması
    double v_duration = v_seconds * 1000000 + v_microseconds; // toplam süreyi mikrosaniye cinsinden hesaplama
    /* Bilimsel Gösterimi (8e-06) Kapatmak için fixed() kullanmalısın
    
    std::fixed << std::setprecision(6) -> Bu satır cout’un yazdırma formatını değiştirir.
    Yani, fixed Bilimsel gösterimi kapatır Ondalıklı normal sayı formatına geçirir
    normalde double x = 0.000028; std::cout << x;
    yaptığında çıktı 2.8e-05
    ama fixed kullandığında bu bilimsel gösterimi kapatır ve normal bir şekilde yazdırır

    eğer fixed yoksa Toplam 5 anlamlı basamak gösterir.
    std::setprecision(5)
    yok eğer fixed varsa, Virgülden sonra 5 basamak gösterir.

    std::fixed << std::setprecision(5) bu satırın anlamı:
    kısacası, Bundan sonra yazdıracağım tüm double değerleri Bilimsel gösterim olmadan Virgülden sonra 6 basamaklı yaz.
    */

    // ------------
    gettimeofday(&d_st, NULL);
    sort_elements_in_deque(t_deque);    // sorting algorithm
    gettimeofday(&d_en, NULL);

    long d_seconds = d_en.tv_sec - d_st.tv_sec;
    long d_microseconds = d_en.tv_usec - d_st.tv_usec;
    double d_duration = d_seconds * 1000000 + d_microseconds;

    std::cout << "After v: ";
    for (std::vector<int>::iterator it = t_vector.begin(); it != t_vector.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << t_vector.size()
        << " elements with std::vector : " << v_duration << " us" << std::endl;

    std::cout << std::fixed << std::setprecision(5) << "Time to process a range of " << t_deque.size() 
        << " elements with std::deque  : " << d_duration << " us" << std::endl;
}

void PmergeMe::sort_elements_in_vector(std::vector<int>& array) {
    std::vector<int> sml;
    std::vector<int> lrg;
    int straggler = 0;          // Eğer vektörün boyutu tekse, son elemanı geçici olarak tutmak için kullanılan değişken.

    if (array.size() <= 2) {    // hem 2 hem de 1 için
        if (array.size() == 2 && array[0] > array[1])
            std::swap(array[0], array[1]);
        return ;
    }
    // vektördeki elemanlar karşılaştırılır ve çiftlenir (yani küçükçse sml yoksa lrg gider)
    for (size_t i=0; i + 1 < array.size(); i += 2) {
        if (array[i] < array[i + 1]) {
            sml.push_back(array[i]);
            lrg.push_back(array[i + 1]);
        }
        else {
            sml.push_back(array[i + 1]);
            lrg.push_back(array[i]);
        }
    }
    // Eğer vektörün boyutu tekse, son eleman (straggler) tek başına kalır ve straggler değişkenine atanır.
    if (array.size() % 2 == 1)
        straggler = array.back();

    sort_elements_in_vector(lrg);   // lrg vektörü yeniden sıralanır. Bu işlem, büyük elemanların sıralı bir şekilde yer almasını sağlar.

    /* Küçük Elemanları Yerleştirme
    sml vektöründeki her bir eleman için, lrg vektöründe uygun pozisyonu bulmak amacıyla std::lower_bound fonksiyonu kullanılır.
    Bu fonksiyon, lrg vektöründe, elemanın eklenebileceği doğru yeri bulur.
    Ardından, eleman bu pozisyona eklenir.
    */ 
    for (std::vector<int>::const_iterator it = sml.begin(); it != sml.end(); it++) {
        std::vector<int>::iterator pos = std::lower_bound(lrg.begin(), lrg.end(), *it);
        lrg.insert(pos, *it);
    }

    // Eğer bir "straggler" varsa (tek sayıda eleman durumu), bu eleman da lrg vektörüne uygun bir pozisyonda eklenir.
    if (straggler) {
        std::vector<int>::iterator pos = std::lower_bound(lrg.begin(), lrg.end(), straggler);
        lrg.insert(pos, straggler);
    }

    // Sonuç Olarak array Vektörünü Güncelleme
    // Sıralı lrg vektörü, array'e atanarak sıralama işlemi tamamlanır.
    array = lrg;
}

void PmergeMe::sort_elements_in_deque(std::deque<int>& array) {
    std::deque<int> sml;
    std::deque<int> lrg;
    int straggler = 0;

    if (array.size() <= 2) {   
        if (array.size() == 2 && array[0] > array[1])
            std::swap(array[0], array[1]);
        return ;
    }

    for (size_t i=0; i + 1 < array.size(); i += 2) {
        if (array[i] < array[i + 1]) {
            sml.push_back(array[i]);
            lrg.push_back(array[i + 1]);
        }
        else {
            sml.push_back(array[i + 1]);
            lrg.push_back(array[i]);
        }
    }

    if (array.size() % 2 == 1)
        straggler = array.back();

    sort_elements_in_deque(lrg);  

    /* Küçük Elemanları Yerleştirme
    sml vektöründeki her bir eleman için, lrg vektöründe uygun pozisyonu bulmak amacıyla std::lower_bound fonksiyonu kullanılır.
    Bu fonksiyon, lrg vektöründe, elemanın eklenebileceği doğru yeri bulur.
    Ardından, eleman bu pozisyona eklenir.
    */ 
    for (std::deque<int>::const_iterator it = sml.begin(); it != sml.end(); it++) {
        std::deque<int>::iterator pos = std::lower_bound(lrg.begin(), lrg.end(), *it);
        lrg.insert(pos, *it);
    }


    if (straggler) {
        std::deque<int>::iterator pos = std::lower_bound(lrg.begin(), lrg.end(), straggler);
        lrg.insert(pos, straggler);
    }

    array = lrg;
}
