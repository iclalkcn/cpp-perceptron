Kullanım ve İşleyiş (Usage & Workflow)
Bu uygulama, kullanıcı tarafından arayüz üzerinden sağlanan verileri gerçek zamanlı olarak işlemek üzere tasarlanmıştır:


Veri Girişi: Uygulama arayüzündeki ilgili alanlara sınıflandırılacak örnek veriler (samples) ve hedef etiketler (labels) manuel olarak girilir.

Eğitim (Training): "Train" butonuna basıldığında, girilen veriler bellek üzerinde dinamik dizilere aktarılır.

Normalizasyon: Veriler eğitimden önce Z-Score Normalization yöntemiyle standartlaştırılarak modelin daha hızlı yakınsaması sağlanır.

Sınıflandırma: Perceptron algoritması, belirlenen epok (epoch) ve öğrenme oranı (learning rate) parametrelerine göre ağırlıkları güncelleyerek doğrusal ayrımı gerçekleştirir.
