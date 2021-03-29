% WangGuangxue 2021-03-21 Updated
% Script of cubid modle
clear
clc

% Initialising
% Centre coordinates of the Cubid modle
x0 = 1000;
y0 = 1000;
z0 = 1000;

% Length of each sides
a = 500;
b = 400;
c = 300;
M = [0,0,1];

[Delta_G,Delta_X,Delta_Y,Delta_Z] = cubid_modle(x0,y0,z0,a,b,c,M);

xk = 0:20:2000;
yk = 0:20:2000;

[X,Y] = meshgrid(xk,yk);

% plot Delta_G
figure(3)
subplot(221)
surfc(X,Y,Delta_G)
colorbar;
colormap jet;
xlabel("X","Fontname","Times new roman");
ylabel("Y","Fontname","Times new roman");
zlabel("{\Delta}_g")
title("Gravity anomaly with cubid modle","Fontname","Times new roman")

% plot Delta_X
% figure(2)
subplot(222)
surfc(X,Y,Delta_X)
colorbar;
colormap jet;
xlabel("X","Fontname","Times new roman");
ylabel("Y","Fontname","Times new roman");
zlabel("{\Delta}_X")
title("Magnetic anomaly with cubid modle","Fontname","Times new roman")

% plot Delta_Y
% figure(3)
subplot(223)
surfc(X,Y,Delta_Y)
colorbar;
colormap jet;
xlabel("X","Fontname","Times new roman");
ylabel("Y","Fontname","Times new roman");
zlabel("{\Delta}_Y")
title("Magnetic anomaly with cubid modle","Fontname","Times new roman")

%plot Delta_Z
% figure(4)
subplot(224)
surfc(X,Y,Delta_Z)
colorbar;
colormap jet;
xlabel("X","Fontname","Times new roman");
ylabel("Y","Fontname","Times new roman");
zlabel("{\Delta}_Z")
title("Magnetic anomaly with cobid modle","Fontname","Times new roman")