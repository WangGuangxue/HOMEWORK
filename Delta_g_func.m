function [Delta_g] = Delta_g_func(x,y,z,xk,yk,zk,M)
% function for cacling Delta_g
% z,y,z are the argument
% xk,yk,zk are observation point
% M is a matrix  meant Magnetic intensity
       R = sqrt(power(x - xk,2) + power(y - yk,2) + power(z - zk,2));
       Delta_g = (x - xk) * log((y - yk) + R)...
       + (y - yk) * log((x - xk) + R)...
       + (z - zk) * arctg((z - zk) * R,(x - xk) * (y - yk));
end