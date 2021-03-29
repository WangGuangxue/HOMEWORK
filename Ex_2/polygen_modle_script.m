%%
clear
clc

%Coordinate of the polygen
Xi = [800,1200,1200,800];
Zi = [800,800,1200,1200];
M = [2000,0];

[Delta_G,Delta_X,Delta_Z] = polygon_modle(Xi,Zi,M);
xk = 0:20:2000;

%plot Delta_g
figure(2)
subplot(221)
plot(xk,Delta_G)
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{g}","Fontname","Times new roman")
title("Gravity anomaly with polygen modle","Fontname","Times new roman")
% plot Delta_X
% figure(2)
subplot(222)
plot(xk,Delta_X)
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{X}","Fontname","Times new roman")
title("Magnetic anomaly with polygen modle","Fontname","Times new roman")
%plot Delta_Z
% figure(3)
subplot(223)
plot(xk,Delta_Z)
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{Z}","Fontname","Times new roman")
title("Magnetic anomaly with polygen modle","Fontname","Times new roman")

subplot(224)
plot(Xi,Zi)
fill(Xi,Zi,'y')
xlabel("X","Fontname","Times new roman");
ylabel("{\Delta}_{Z}","Fontname","Times new roman")
title("Shape of the polygen","Fontname","Times new roman")

