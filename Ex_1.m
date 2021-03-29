%% Conver Exel into .txt
% it's a script to convert data from excel to .txt
% import the data
path = 'E:\MATLAB\Mycode\Seismolgy_Explore\Ex_1\Well_log_data.xls';
data = importdata(path);
data = data.data.Sheet1(:,2:3);
data(:,1) = data(:,1);% Microseconds->Seconds

%Converting the data into .txt
filename = 'E:\MATLAB\Mycode\Seismolgy_Explore\Ex_1\Well_log_data.txt';
file_id = fopen(filename,'a+');
dlmwrite(filename,data,'\t');
fclose(file_id);
%%
% Code for drawing wavelet
% WangGuangxue 201805050218@stu.cdut.edu.cn
% 1st Write 2021-03-13

%IMPORT data
path_wavelet = "E:\vscode\C\wavelet.txt";% path_wavelet data 
data = importdata(path_wavelet);

%INITILISING DATA
% Zero_phase = data(1:end,1);% The first collum
% Smallest_phase = data(1:end,2);%The second collum
% Bell_shaped_phase = data(1:end,3);% The last collum

x = -50:49;
% PLOTTING
figure(1)
% plot(x,Zero_phase);
hold on
for k = 1:3
   plot(data(:,k)) 
end
% plot(x,Smallest_phase);
% plot(x,Bell_shaped_phase);
%%
path_of_Velocity_and_Dencity = 'E:\vscode\C\Velocity_Dencity.txt';
path_of_Reflection_coeff = 'E:\vscode\C\Reflection_coefficient.txt';
data_Velocity_and_Dencity = importdata(path_of_Velocity_and_Dencity);
data_Reflection_coeff = importdata(path_of_Reflection_coeff);
figure(2)
for i = 1:3
    hold on
   plot(data_Velocity_and_Dencity(:,i)) 
end
figure(3)
for j = 1:2
   hold on
   plot(data_Reflection_coeff(:,j))
end
% plot those mother fucker plots by urself
%%
path_seismic = 'E:\vscode\C\seismic_data.txt';
data_seismic = importdata(path_seismic);
hold on 
figure(4)
for i = 1:6
   plot(data_seismic(:,i)); 
end
% making the stupid plot nicer by ueself UMF!
