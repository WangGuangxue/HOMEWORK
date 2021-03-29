%WangGuangxue 201805050218@stu.edu.cdut.cn 
%2021-03-14 Updated
clear
clc

alpha = 90 * pi / 180;% or 45 * pi / 180;
i = 90 * pi /180;% or 45 * pi / 180;
Z1 = 800;
Z2 = 1200;
[Delta_G,Delta_X,Delta_Z] = two_dimensional_plate_modle(Z1,Z2,alpha,i);
xk = 0:20:2000;

%plot Delta_g
figure(1)
subplot(221)
plot(xk,Delta_G)
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{g}","Fontname","Times new roman")
title("Gravity anomaly with two dimensional plate","Fontname","Times new roman")

% plot Delta_X
% figure(2)
subplot(222)
plot(xk,Delta_X)
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{X}","Fontname","Times new roman")
title("Magnetic anomaly with two dimensional plate","Fontname","Times new roman")

%plot Delta_Z
% figure(3)
subplot(223)
plot(xk,Delta_Z)
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{Z}","Fontname","Times new roman")
title("Magnetic anomaly with two dimensional plate","Fontname","Times new roman")