clearvars

csv = csvread ('debug_nuovo3.csv');
time = csv(:,1) * 1e-9;
time_stamp = csv(:,3) * 1e-9;

time2 = csv(:,5) + csv(:,6) * 1e-9;

rate = diff(time);

t_ref = min(time):0.01:max(time);

ticks = zeros(length(t_ref),1);

for i=1:length(time)
    ticks(find(abs (t_ref - time(i)) < 1e-5)) = 1;
end

plot(t_ref, ticks)

axis ([t_ref(1) t_ref(end) 0 2])
grid on
grid minor
