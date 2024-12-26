veriler = readtable('veriler.xlsx');
Power =  (veriler(:,3));
Power= table2array(Power);
time = linspace(0,40,618);
time = transpose(time);

plot(time,Power)