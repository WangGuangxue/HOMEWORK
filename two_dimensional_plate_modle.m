% function [Delta_g,Delta_X,Delta_Y] = two_dimensional_plate_modle(z1,z2,x0,y0,z0,b,L,Sigma,xk,yk,zk,alpha,i,G)
function [Delta_G,Delta_X,Delta_Z] = two_dimensional_plate_modle(z1,z2)
% two-dimensional plate for Calcing Delta_g Delta_X,Delta_Y
% z1,z2 for coordinate of the plate 
% WangGuangxue 201805050218 201805050218@stu.cdut.edu.cn
% 2021-03-04 1st WRITE
% INNITIALISING 2021-03-10 UPDATED

x0 = 1000;
% y0 = 0;
z0 = 1000;% the center coordinate of the plate

b = 200;% half length of the plate
L = 400;% half width of thr plate
M = 2000;% Magnetic intensity
Sigma = 2.67;% electrical conductivity
G = 6.67*10e-11;

% xk = 0:20:2000;
zk = 0;% the coordinate of the observation point
alpha = 90 * pi / 180;% or 45 * pi / 180;
i = 90 * pi /180;% or 45 * pi / 180;

r1 = 0;
R1 = [];
r2 = 0;
R2 = [];
r3 = 0;
R3 = [];
r4 = 0;
R4 = [];

phi1 = 0;
PHI1 = [];
phi2 = 0;
PHI2 = [];
phi3 = 0;
PHI3 = [];
phi4 = 0;
PHI4 = [];

Delta_g = 0;
Delta_x = 0;
Delta_z = 0;
Delta_G = [];
Delta_X = [];
Delta_Z = [];
% INNITIALISING DONE

for xk = 0:20:2000
% r means distance from four angles(A,B,C and D) to observation point
r1 = sqrt((xk - x0 + b + L * cos(alpha))^2 + (z0 - zk - L * sin(alpha))^2);
R1 = [R1;r1];
r2 = sqrt((xk - x0 + b - L * cos(alpha))^2 + (z0 - zk + L * sin(alpha))^2);
R2 = [R2;r2];
r3 = sqrt((xk - x0 - b + L * cos(alpha))^2 + (z0 - zk - L * sin(alpha))^2);
R3 = [R3;r3];
r4 = sqrt((xk - x0 - b - L * cos(alpha))^2 + (z0 - zk + L * sin(alpha))^2);
R4 = [R4;r4];
% phi means angle which is r with coordinate_X
phi1 = pi - arctg(z0 - zk - L * sin(alpha),xk - x0 + b + L * cos(alpha));
PHI1 = [PHI1:phi1];
phi2 = pi - arctg(z0 - zk + L * sin(alpha),xk - x0 + b - L * cos(alpha));
PHI2 = [PHI2:phi2];
phi3 = pi - arctg(z0 - zk - L * sin(alpha),xk - x0 - b + L * cos(alpha));
PHI3 = [PHI3:phi3];
phi4 = pi - arctg(z0 - zk + L * sin(alpha),xk - x0 - b - L * cos(alpha));
PHI4 = [PHI4:phi4];
% Cacling the anomalies
Delta_g = 2 * G * Sigma * (...
    (z2 * (phi2 - phi4) - z1 * (phi1 - phi3))...
    + xk * (sin(alpha)^2 * log((r2 * r3)/(r1 * r4)) + cos(alpha) * sin(alpha) * (phi1 - phi2 - phi3 + phi4))...
    + 2 * b * (sin(alpha)^2 * log(r4/r3) + cos(alpha) * sin(alpha) * (phi3 - phi4)));
Delta_G = [Delta_G;Delta_g];

Delta_x = M / (2 * pi) * sin(alpha) * (log((r2 * r3)/ (r1 * r4)) * cos(alpha - i)...
    - sin(alpha - i) * (phi1 - phi2 - phi3 + phi4));
Delta_X = [Delta_X;Delta_x];

Delta_z = M / (2 * pi) * sin(alpha) * (log((r2 * r3)/ (r1 * r4)) * sin(alpha - i)...
    - cos(alpha - i) * (phi1 - phi2 - phi3 + phi4));
Delta_Z = [Delta_Z;Delta_z];


end

end