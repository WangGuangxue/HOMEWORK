%%
%WangGUangxue 201805050218@stu.edu.cdut.cn 
%2021-03-14 1st write
[Delta_G,Delta_X,Delta_Z] = two_dimensional_plate_modle(600,800);
xk = 0:20:2000;
%plot Delta_g
figure(1)
plot(xk,Delta_G)
xlabel("X","Fontname","Times new roman");
ylabel("Delta_{g}","Fontname","Times new roman")
title("Gravity anomaly with two dimensional plate","Fontname","Times new roman")
% plot Delta_X
figure(2)
plot(xk,Delta_X)
xlabel("X","Fontname","Times new roman");
ylabel("Delta_{X}","Fontname","Times new roman")
title("Magnetic anomaly with two dimensional plate","Fontname","Times new roman")
%plot Delta_Z
figure(3)
plot(xk,Delta_Z)
xlabel("X","Fontname","Times new roman");
ylabel("Delta_{Z}","Fontname","Times new roman")
title("Magnetic anomaly with two dimensional plate","Fontname","Times new roman")