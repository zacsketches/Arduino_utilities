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

%plot the raw data
plot(t_final, v_motor)
ylabel('Angular Velocity (cts/ms)')
xlabel('Time (ms)')
title('Raw Response to Step Input')

'raw data figure drawn...press any key to continue'
pause

%implement a moving average filter
counts_to_smooth = 30;
coeff30MA = ones(1,counts_to_smooth)/counts_to_smooth;
avg30_v_motor = filter(coeff30MA, 1, v_motor);

%plot the smoothed data
plot(t_final, avg30_v_motor)
ylabel('Angular Velocity (cts/ms)')
xlabel('Time (ms)')
title('Moving Average 30 Sample Response to Step Input')

%find the velocity that represents 63% rise
tau_val = .63 * max(avg30_v_motor);
[c, tau_index] = min(abs(avg30_v_motor - tau_val));
tau_val = avg30_v_motor(tau_index); % Finds first one only!
tau_val
time_constant = t_final(tau_index)-t_final(1);
time_constant

%find a and K
a = 1/time_constant;
forced_response = max(avg30_v_motor);
K = a * forced_response;
a
K

%generate the transfer function
num = K;
den = poly([-a]);
G = tf(num, den);
G

%plot the time response
syms s;
C = K/[s*(s+a)];
c = ilaplace(C);
c






    