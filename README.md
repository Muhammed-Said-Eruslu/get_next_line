*This project has been created as part of the 42 curriculum by mueruslu.*

# get_next_line

## Description
get_next_line, bir dosya tanıtıcısından (file descriptor) her çağrıda **bir satır** döndürmeyi amaçlayan 42 projesidir. Amaç; statik bellek yönetimi, buffer kullanımı ve satır sonu (`\n`) ayrıştırma mantığını doğru şekilde uygulayarak, büyük dosyalarda dahi satır satır okuma yapabilmektir.

## Instructions

### Derleme
Varsayılan örnek derleme (BUFFER_SIZE değiştirilebilir):

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Çalıştırma
```
./gnl
```

> `main.c` örnek amaçlıdır. Kendi testleriniz için düzenleyebilirsiniz.

## Algorithm Explanation (Detaylı Açıklama ve Gerekçe)
Bu proje için seçilen yaklaşım, **statik bir “stash” (biriktirme) tamponu** kullanarak, `read()` ile gelen parçaları birleştirmek ve her çağrıda tek satır döndürmektir.

### Adımlar
1. **Stash oluşturma**: `static` bir değişken, önceki çağrılardan kalan veriyi saklar.
2. **Okuma döngüsü**: Stash içinde `\n` bulunana kadar `read()` ile `BUFFER_SIZE` kadar veri okunur ve stash’e eklenir.
3. **Satırı çıkarma**: Stash’teki ilk `\n` dahil edilerek satır çıkarılır ve kullanıcıya döndürülür.
4. **Stash’i güncelleme**: Döndürülen satırın geri kalanı stash’te tutulur; yoksa stash temizlenir.
5. **EOF yönetimi**: `read()` 0 döndürdüğünde, stash’te kalan veri satır olarak döndürülür, sonra `NULL` ile bitirilir.

### Gerekçe
- **Statik stash** kullanımı, fonksiyonun her çağrıda bir önceki okumadan kalan veriyi korumasını sağlar.
- **`BUFFER_SIZE` ile parça parça okuma**, büyük dosyalarda bellek verimliliği sağlar.
- **Satır sonu bazlı ayrıştırma**, istenen fonksiyonel davranışı garanti eder.

### Karmaşıklık
- Zaman: Ortalama olarak her satır için $O(n)$, burada $n$ satır uzunluğu.
- Bellek: Stash boyutu satır uzunluğu ile sınırlı olup ek buffer ile birlikte $O(n)$.

## Resources
- `man 2 read`
- `man 3 malloc` / `free`
- 42 get_next_line subject PDF
- https://man7.org/linux/man-pages/man2/read.2.html

### AI Kullanımı
Projenin algoritma tasarımı aşamasında, buffer ve stash yönetiminin teorik mantığını kavramak ve bellek yönetimini (malloc/free) optimize etmek amacıyla AI araçları yardımcı bir kaynak olarak kullanılmıştır.

## Dosya Yapısı
- `get_next_line.c` : Ana okuma ve satır döndürme mantığı
- `get_next_line_utils.c` : Yardımcı string fonksiyonları
- `get_next_line.h` : Prototipler ve tanımlar
- `main.c` : Örnek test dosyası
- `test.txt` : Örnek giriş
