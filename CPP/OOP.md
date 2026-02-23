# C++ Nesne Yönelimli Programlama (OOP) Kavramları

## Giriş

Nesne Yönelimli Programlama (Object Oriented Programming - OOP), yazılımı daha düzenli, modüler ve sürdürülebilir hale getirmek için kullanılan bir programlama yaklaşımıdır.

C++’ta OOP’nin temel ilkeleri:

* Sınıflar ve Nesneler
* Kapsülleme (Encapsulation)
* Kalıtım (Inheritance)
* Çok Biçimlilik (Polymorphism)
* Soyutlama (Abstraction)

---

# Sınıflar ve Nesneler

## Teori

**Sınıf (class)**, ortak özellikleri (değişkenler) ve davranışları (fonksiyonlar) bir arada tutan bir şablondur.

**Nesne (object)** ise bu sınıfın bellekte oluşturulmuş somut bir örneğidir.

---

## Örnek

```cpp
#include <iostream>
using namespace std;

class Ogrenci {
public:
    string isim;
    int yas;

    void bilgileriGoster() {
        cout << "Isim: " << isim << ", Yas: " << yas << endl;
    }
};

int main() {
    Ogrenci ali;   // Nesne oluşturma
    ali.isim = "Ali";
    ali.yas = 20;
    ali.bilgileriGoster();
    return 0;
}
```

### Açıklama

* `class Ogrenci` → Bir sınıf tanımıdır.
* `Ogrenci ali;` → Bu sınıftan bir nesne oluşturur.
* Nesne üzerinden sınıfın üyelerine erişilir.

---

# Kapsülleme (Encapsulation)

## Teori

Kapsülleme, veriyi gizlemek ve kontrollü erişim sağlamaktır.

C++’ta genellikle:

* `private` → dışarıdan erişilemez
* `public` → dışarıdan erişilebilir

---

## Örnek

```cpp
#include <iostream>
using namespace std;

class Ogrenci {
private:
    int yas;

public:
    void setYas(int y) {
        if (y >= 0)
            yas = y;
    }

    int getYas() {
        return yas;
    }
};

int main() {
    Ogrenci ali;
    ali.setYas(20);
    cout << ali.getYas() << endl;
    return 0;
}
```

### Açıklama

* `yas` değişkeni dışarıdan erişilemez.
* Değişiklik sadece `setYas()` ile yapılabilir.
* Böylece veri kontrol altına alınır.

---

# Kalıtım (Inheritance)

## Teori

Bir sınıfın başka bir sınıfın özelliklerini devralmasıdır.

Amaç:

* Kod tekrarını azaltmak
* Ortak davranışı üst sınıfta toplamak

---

## Örnek

```cpp
#include <iostream>
using namespace std;

class Hayvan {
public:
    void sesCikar() {
        cout << "Hayvan ses cikardi." << endl;
    }
};

class Kedi : public Hayvan {
public:
    void miyavla() {
        cout << "Miyav!" << endl;
    }
};

int main() {
    Kedi k;
    k.sesCikar();  // Mirastan geldi
    k.miyavla();   // Kendine ait
    return 0;
}
```

### Açıklama

* `Kedi`, `Hayvan` sınıfından miras alır.
* `Kedi` hem kendi fonksiyonlarına hem de `Hayvan`’ın fonksiyonlarına sahiptir.

---

# Çok Biçimlilik (Polymorphism)

## Teori

Aynı isimli fonksiyonların farklı davranış göstermesidir.

İki tür vardır:

* **Compile-time Polymorphism** → Overloading
* **Run-time Polymorphism** → Virtual + Override

---

## Örnek (Run-time Polymorphism)

```cpp
#include <iostream>
using namespace std;

class Sekil {
public:
    virtual void ciz() {
        cout << "Sekil ciziliyor." << endl;
    }
};

class Daire : public Sekil {
public:
    void ciz() override {
        cout << "Daire ciziliyor." << endl;
    }
};

int main() {
    Sekil* s = new Daire();
    s->ciz();
    delete s;
    return 0;
}
```

### Açıklama

* `virtual` → Dinamik bağlama sağlar.
* `override` → Üst sınıftaki fonksiyonu ezer.
* Çalışma anında doğru fonksiyon çağrılır.

---

# Soyutlama (Abstraction)

## Teori

Gereksiz detayları gizleyip sadece gerekli arayüzü sunmaktır.

C++’ta soyutlama genellikle **pure virtual function** ile yapılır.

---

## Örnek

```cpp
#include <iostream>
using namespace std;

class Calisan {
public:
    virtual double maasHesapla() = 0;
};

class Mudur : public Calisan {
public:
    double maasHesapla() override {
        return 5000.0;
    }
};

int main() {
    Calisan* c = new Mudur();
    cout << c->maasHesapla() << endl;
    delete c;
    return 0;
}
```

### Açıklama

* `= 0` → Saf sanal fonksiyon.
* `Calisan` soyut sınıftır.
* Doğrudan nesne oluşturulamaz.
* Alt sınıf implement etmek zorundadır.

---

# OOP Kavramlarının Birbirleriyle İlişkisi

| Kavram         | Amaç                        |
| -------------- | --------------------------- |
| Sınıf          | Veri + Davranış bir arada   |
| Kapsülleme     | Veriyi korumak              |
| Kalıtım        | Kod tekrarını azaltmak      |
| Çok Biçimlilik | Esnek davranış              |
| Soyutlama      | Gereksiz detayları gizlemek |

---