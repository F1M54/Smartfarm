% Veriyi Excel dosyasından oku
data = xlsread('motor verileri.xlsx');

% Veri setinden güç ve gerilim sütunlarını ayır
gerilim = data(:, 1); % İlgili sütun numarasına ayarlayın
guc = data(:, 2); % İlgili sütun numarasına ayarlayın

% Güç ve gerilim grafiğini çiz
figure;
subplot(2, 1, 1); % İki alt grafikten birincisi
plot(gerilim, 'b'); % Gerilim verisini mavi renkte çiz
xlabel('Zaman'); % X ekseni etiketi
ylabel('Gerilim'); % Y ekseni etiketi
title('Gerilim Grafiği'); % Grafik başlığı

subplot(2, 1, 2); % İki alt grafikten ikincisi
plot(guc, 'r'); % Güç verisini kırmızı renkte çiz
xlabel('Zaman'); % X ekseni etiketi
ylabel('Güç'); % Y ekseni etiketi
title('Güç Grafiği'); % Grafik başlığı
