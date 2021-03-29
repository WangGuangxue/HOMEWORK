function [theta] = arctg(M,D)
% M for molecular and D for denominator
% The code is for function arctg which when denominator = 0
% WangGuangxue 201805050218 201805050218@stu.cdut.edu.cn
% 2021-03-04 1st write

if abs(D) >= 10e-16
    if M/D > 0         
        if M > 0 && D > 0
            theta = atan(M/D);
        else
            theta = atan(M/D) - pi;
        end        
    else
        theta = pi + atan(M/D);
    end      
else    
    if M < 0 
        theta = - pi / 2;
    else
        theta = pi / 2;
    end    
end
end