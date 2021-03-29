function [Delta_x] = Delta_x_func(x,y,z,xk,yk,zk,M)
% function for cacling Delta_x
% z,y,z are the argument
% xk,yk,zk are observation point
% M is a matrix  meant Magnetic intensity
       R = sqrt(power(x - xk,2) + power(y - yk,2) + power(z - zk,2));
       Delta_x = - M(1) * arctg((y - yk) * (z - zk),(x - xk) * R)...
            + M(2) * log(R + (z - zk))...
            + M(3) * log(R + (y - yk));
end