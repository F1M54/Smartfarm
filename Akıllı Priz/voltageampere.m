[data, headers] = xlsread('veriler.xlsx');
plot(data(:,1), data(:,2), '-o'); % x eksenindeki değerler data(:,1), y eksenindeki değerler data(:,2)
xlabel('Gerilim (Volt)');
ylabel('Akım (Ampere)');
title('Gerilim ve Akım Grafiği');
saveas(gcf, 'grafik.png'); % O anki grafik penceresini grafik.png olarak kaydeder
