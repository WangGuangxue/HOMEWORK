function [Delta_y] = Delta_y_func(x,y,z,xk,yk,zk,M)
% function for cacling Delta_y
% z,y,z are the argument
% xk,yk,zk are observation point
% M is a matrix  meant Magnetic intensity
       R = sqrt(power(x - xk,2) + power(y - yk,2) + power(z - zk,2));
          Delta_y = M(1) * log(R + (z - zk))...
       - M(2) * arctg((x - xk) * (z  - zk),(y - yk) * R)...
       + M(3) * log(R + (x - xk));
end