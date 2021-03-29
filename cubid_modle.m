function [Delta_G,Delta_X,Delta_Y,Delta_Z] = cubid_modle(x0,y0,z0,a,b,c,M)
% WangGuangxue 2021-03-21 Updated
% 201805050219@stu.cdut.edu.cn
% Code for cacing anamolies of cubid_modle
% x0,y0,z0 are the Centre Coordinates of the cubid
% a,b,c are the length of each side
% M is a matrix  meant Magnetic intensity

Sigma = 2.67;% electrical conductivity
G = 6.67*10e-11;
% xk = 0:20:2000;
% yk = 0:20:2000;
zk =0;

% down limit and up limit
X = [x0 - a/2,x0 + a/2];
Y = [y0 - b/2;y0 + b/2];
Z = [z0 - c/2;z0 + c/2];

% % Delta_g = 0;
% Delta_G = [];
% % Delta_x = 0;
% Delta_X =[];
% Delta_y = 0;
% Delta_Y = [];
% Delta_z = 0;
% Delta_Z = [];

for xk = 0:20:2000 
    for yk = 0:20:2000
        
    Delta_g = 0;    
    Delta_x = 0;
    Delta_y = 0;    
    Delta_z = 0;   
        
       for i = 1:2
           for j = 1:2
               for k = 1:2
                   % Cacling the int(f)
                   if mod((i + j + k),2) == 0 
                       sign = 1;
                   else
                       sign = -1;
                   end 
                   
                   Delta_g = Delta_g + sign * Delta_g_func(X(i),Y(j),Z(k),xk,yk,zk,M);
                   Delta_x = Delta_x + sign * Delta_x_func(X(i),Y(j),Z(k),xk,yk,zk,M);
                   Delta_y = Delta_y + sign * Delta_y_func(X(i),Y(j),Z(k),xk,yk,zk,M);
                   Delta_z = Delta_z + sign * Delta_z_func(X(i),Y(j),Z(k),xk,yk,zk,M);
               end
               
           end
           
       end       
   Delta_G(xk/20 + 1,yk/20 + 1) = -G * Sigma * Delta_g;
   
   Delta_X(xk/20 + 1,yk/20 + 1) = 1 / (4 * pi) * Delta_x;
   
   Delta_Y(xk/20 + 1,yk/20 + 1) = 1 / (4 * pi) * Delta_y;
   
   Delta_Z(xk/20 + 1,yk/20 + 1) = 1 / (4 * pi) * Delta_z;
      
    end
end

end