t = temp_out.time; 
temp = temp_out.data;

plot(t, temp); 
fy = interp1(t,temp,0:0.01:30)
y = fy;
tm = 0:30/(length(fy)-1):30;
plot(tm, fy);
d1y = gradient(y,tm);                                            % Numerical Derivative
d2y = gradient(d1y,tm);                                          % Numerical Second Derivative
t_infl = interp1(d1y, tm, max(d1y));                             % Find ‘t’ At Maximum Of First Derivative
y_infl = interp1(tm, y, t_infl);                                 % Find ‘y’ At Maximum Of First Derivative
slope  = interp1(tm, d1y, t_infl);                               % Slope Defined Here As Maximum Of First Derivative
intcpt = y_infl - slope*t_infl;                                 % Calculate Intercept
tngt = slope*tm + intcpt;                                        % Calculate Tangent Line


figure(1)
plot(tm, y)
hold on
plot(tm, fy)
% plot(t, d1y, '-.m',    t, d2y, '--c')                           % Plot Derivatives (Optional)
plot(tm, tngt, '-r', 'LineWidth',1)                              % Plot Tangent Line
% xlim([0 4])
% ylim([0 1])
% plot(t_infl, y_infl, 'bp')                                      % Plot Maximum Slope
hold off
grid
% legend('y(t)', 'y(t) Fit', 'dy/dt', 'd^2y/dt^2', 'Tangent', 'Location','E')
% axis([xlim    min(min(y),intcpt)  ceil(max(y))])