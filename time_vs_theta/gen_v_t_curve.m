%filtering tools from 
%   http://www.mathworks.com/help/signal/examples/signal-smoothing.html?prodcode=SG&language=en

%for a first order system see transfer function guidance from
%Nise page 167 

%create an empty array for dt, dx and v
dt = zeros((length(t)-1), 1);
dx = zeros(size(dt));
v_motor = zeros(size(dt));

%generate the data for dt and dx
index = 0;
for index = 1:size(t)-1
    dt(index) = t(index+1) - t(index);
    dx(index) = counts(index+1) - counts(index);
end

%compute the data for v_motor
index = 0;
for index = 1:size(v_motor)
    v_motor(index) = dx(index) / dt(index);
end

%compute the time array to plot against
%..can't use the initial t because the velocity
%data vector is one element shorten than t
t_final = t;
t_final(1) = [];
min_time = min(t_final);
t_final = t_final-min_time;

%plot the raw data
figure(1); 
plot(t_final, v_motor);
ylabel('Angular Velocity (cts/ms)');
xlabel('Time (ms)');
title('Raw Response to Step Input');

%implement a moving average filter
counts_to_smooth = 30;
coeff30MA = ones(1,counts_to_smooth)/counts_to_smooth;
avg_dx = filter(coeff30MA,1,dx);
avg_dt = filter(coeff30MA,1,dt);
%compute the data for avg_v
avg_v = zeros(size(dt));
index = 0;
for index = 1:size(avg_v)
    avg_v(index) = avg_dx(index) / avg_dt(index);
end
%filter one more time
final_v = filter(coeff30MA, 1, avg_v);

%find the velocity that represents 63% rise
tau_val = .63 * max(final_v);
[c, tau_index] = min(abs(final_v - tau_val));
tau_val = final_v(tau_index); % Finds first one only!
tau_val
time_constant = t_final(tau_index)-t_final(1);
time_constant

%find a and K
a = 1/time_constant;
forced_response = max(final_v);
K = a * forced_response;
a
K

%generate the transfer function
num = K;
den = poly([-a]);
G = tf(num, den);
G

%collect data for the step response of G
[G_y, G_t] = step(G);

%plot the smoothed data and the transfer function
figure(2); 
plot(t_final, final_v, G_t, G_y);
ylabel('Angular Velocity (cts/ms)');
xlabel('Time (ms)');
title('\fontsize{14}Moving Average(N=30) Response to Step Input');
legend('Smoothed data', 'Derived transfer function', 'Location', 'SouthEast');

%show the time response to step input
syms s;
C = K/[s*(s+a)];
c_t = ilaplace(C);
pretty(c_t)


%try and scale the response to match a consistent gain
Gain = 11.58 %from relatioship of K/a for all PWM runs
scaled_v = final_v/Gain;
scaled_t = t_final/Gain;

figure(3);
plot(scaled_t, scaled_v, G_t/Gain, G_y/Gain);
ylabel('Angular Velocity (cts/ms)');
xlabel('Time (ms)');
title('\fontsize{14}Scaled Response to Step Input');
legend('Smoothed data', 'Derived transfer function', 'Location', 'SouthEast');

%find the velocity that represents 63% rise
tau_val = .63 * max(scaled_v);
[c, tau_index] = min(abs(scaled_v - tau_val));
tau_val = scaled_v(tau_index); % Finds first one only!
tau_val
time_constant = scaled_t(tau_index);
time_constant

%find a and K
a = 1/time_constant;
forced_response = max(scaled_v);
K = a * forced_response;
a
K

%generate the transfer function
num = K;
den = poly([-a]);
G = tf(num, den);
G



    