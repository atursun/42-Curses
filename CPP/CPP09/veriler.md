## 1️⃣ `vector`
### 🔹 Nedir?

Dinamik boyutlu dizi (dynamic array).
- Dinamik boyutlu array, program çalışırken boyutu değişebilen dizidir

### 🔹 Özellikleri

* Bellekte **bitişik (contiguous)** tutulur.
* `push_back()` çok hızlıdır.
* Rastgele erişim çok hızlıdır: `v[i]` → **O(1)**
* Ortaya eleman eklemek yavaştır.

### 🔹 Ne zaman kullanılır?

En çok kullanılan container’dır.
Liste gibi ama index ile hızlı erişmek istiyorsan → `vector`

```cpp
#include <vector>
vector<int> v;
v.push_back(10);
```

---

## 2️⃣ `deque`
### 🔹 Nedir?

Double Ended Queue (iki uçlu kuyruk)

### 🔹 Özellikleri

* Baştan ve sondan hızlı ekleme/silme
* `push_front()` ve `push_back()` hızlıdır
* `vector` gibi index ile erişilebilir

### 🔹 Ne zaman kullanılır?

Hem baştan hem sondan işlem yapacaksan.

```cpp
#include <deque>
deque<int> d;
d.push_front(5);
d.push_back(10);
```

---

## 3️⃣ `stack`
### 🔹 Nedir?

LIFO (Last In First Out) → **Son giren ilk çıkar**

### 🔹 Özellikleri

* Sadece üst elemana erişebilirsin
* `push()` → ekle
* `pop()` → çıkar
* `top()` → üst eleman

### 🔹 Ne zaman kullanılır?

* Parantez kontrolü
* Geri alma (undo)
* Recursive mantık

```cpp
#include <stack>
stack<int> s;
s.push(10);
s.pop();
```

---

## 4️⃣ `map`
### 🔹 Nedir?

Anahtar-değer (key-value) yapısı.

### 🔹 Özellikleri

* Otomatik sıralıdır (C++ `map` → Red-Black Tree)
* Arama süresi: **O(log n)**
* Key benzersizdir

### 🔹 Ne zaman kullanılır?

Bir anahtara karşılık veri tutmak istiyorsan.

```cpp
#include <map>
map<string, int> m;
m["Ali"] = 25;
```

---

# 🚀 Kısa Karşılaştırma

| Yapı   | Hızlı Erişim | Baştan Ekleme | Sondan Ekleme | Sıralı |
| ------ | ------------ | ------------- | ------------- | ------ |
| vector | ✅ O(1)       | ❌             | ✅             | ❌      |
| deque  | ✅ O(1)       | ✅             | ✅             | ❌      |
| stack  | ❌            | ❌             | ✅ (üst)       | ❌      |
| map    | ❌ (O(log n)) | ❌             | ❌             | ✅      |
