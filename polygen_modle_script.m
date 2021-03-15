%%
% The depth of the polygen
% z1 = 600;
% z2 = 800;
%Coordinate of the polygen
xi = [200,250,300,350,400];
zi = [200,250,300,350,400];
M = [1,2];

[Delta_G,Delta_X,Delta_Z] = polygon_modle(xi,zi,M);
xk = 0:20:2000;

%plot Delta_g
figure(1)
plot(xk,Delta_G)
xlabel("X","Fontname","Times new roman");
ylabel("Delta_{g}","Fontname","Times new roman")
title("Gravity anomaly with polygen modle","Fontname","Times new roman")
% plot Delta_X
figure(2)
plot(xk,Delta_X)
xlabel("X","Fontname","Times new roman");
ylabel("Delta_{X}","Fontname","Times new roman")
title("Magnetic anomaly with polygen modle","Fontname","Times new roman")
%plot Delta_Z
figure(3)
plot(xk,Delta_Z)
xlabel("X","Fontname","Times new roman");
ylabel("Delta_{Z}","Fontname","Times new roman")
title("Magnetic anomaly with polygen modle","Fontname","Times new roman")