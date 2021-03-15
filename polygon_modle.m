function [Delta_G,Delta_X,Delta_Z] = polygon_modle(xi,zi,M)
%WangGuangxue 2021-03-14 1st Write
%201805050219@stu.cdut.edu.cn
% polygen for Calcing Delta_g Delta_X,Delta_Y
% z1,z2 for coordinate of the plate 
% xi, zi are matrixs
% M is a matrix  meant Magnetic intensity

b = 200;% half length of the plate
L = 400;% half width of thr plate;
Sigma = 2.67;% electrical conductivity
G = 6.67*10e-11;

% xk = 0:20:2000;
zk = 0;% the coordinate of the observation point
% alpha = 90 * pi / 180;% or 45 * pi / 180;
% i = 90 * pi /180;% or 45 * pi / 180;

%inItial the P and Q
q = 0;
sum_q = 0;
Q = [];
p = 0;
sum_p = 0;
P = [];

Delta_g = 0;
sum_Delta_g = 0;
Delta_G = [];

Delta_x = 0;
Delta_X =[];
Delta_z = 0;
Delta_Z = [];

%Initial DONE
for xk = 0:20:2000
       xi = xi - xk;
       zi = zi - zk;   
    for j = 1:length(xi)|length(zi)
    
%     % The loop for coordinates exchange
%     for xk =  0:20:2000
%         xi = xi - xk;
%         zi = zi - zk;       
%     end
    
    q = ((zi(j + 1) - zi(j)) * (xi(j + 1) - xi(j)))...
        /(power(zi(j + 1) - zi(j),2) + power(xi(j + 1) - xi(j),2))...
        * (arctg(zi(j),xi(j)) - arctg(zi(j + 1), xi(j + 1)))...
        -1/2 * (power(zi(j + 1) -zi(j),2) / (power(zi(j + 1) -zi(j),2) + power(xi(j + 1) -xi(j),2)))...
        * log((power(xi(j + 1),2) + power(zi(j + 1),2)) / (power(xi(j),2) + power(zi(j),2)));
    sum_q = sum_q + q;%Sum up
    
    
    p = (power(zi(j + 1),2) / (power(zi(j + 1) -zi(j),2) + power(xi(j + 1) -xi(j),2)))...
        * (arctg(zi(j),xi(j)) - arctg(zi(j + 1), xi(j + 1)))...
        + 1/2 * ((zi(j + 1) -zi(j) * (xi(j) - xi(j + 1))) / (power(zi(j + 1) -zi(j),2) + power(xi(j + 1) -xi(j),2)))...
        * log((power(xi(j + 1),2) + power(zi(j + 1),2)) / (power(xi(j ),2) + power(zi(j),2)));
    sum_p = sum_p + q;%Sum up
    
    Delta_g = 1/2 * (zi(j + 1) - zi(j) * (xi(j) * zi(j + 1) - xi(j + 1) * zi(j))...
        / (power(zi(j + 1) -zi(j),2) + power(xi(j + 1) -xi(j),2))...
        * log((power(xi(j + 1),2) + power(zi(j + 1),2)) / (power(xi(j),2) + power(zi(j),2)))...
        + ((xi(j + 1) - xi(j)) * (xi(j) * zi(j + 1))...
        / (power((zi(j + 1) - zi(j)),2) + power((xi(j + 1) - xi(j)),2)))...
        * (arctg(zi(j),xi(j)) - arctg(zi(j + 1), xi(j + 1))));
    
    sum_Delta_g = sum_Delta_g + Delta_g;
    end
    
    Delta_G = [Delta_G;2 * G * Sigma * sum_Delta_g];
%     Q = [Q:sum_q];
    Delta_x = 1 / (2 * pi) * (M(1) * sum_p + M(2) * sum_q);
    Delta_X = [Delta_X;Delta_x];
    Delta_z = 1 / (2 * pi) * (M(1) * sum_p - M(2) * sum_q);
    Delta_Z = [Delta_Z;Delta_z];
%     P = [P;sum_p];
end



end