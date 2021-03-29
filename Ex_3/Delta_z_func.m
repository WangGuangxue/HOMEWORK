function [Delta_z] = Delta_z_func(x,y,z,xk,yk,zk,M)
% function for cacling Delta_z
% z,y,z are the argument
% xk,yk,zk are observation point
% M is a matrix  meant Magnetic intensity
       R = sqrt(power(x - xk,2) + power(y - yk,2) + power(z - zk,2));
       Delta_z = M(1) * log(R + (y - yk))...
            - M(2) * log(R + (x - xk))...
            - M(3) * arctg((x - xk) * (y - yk),(z - zk) * R);
end