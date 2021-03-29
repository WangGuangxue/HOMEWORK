#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415927
#define ROW 200 //row of the well_log data
#define COLUM 2 //colum of the well_log data
#define ST 50 //means Sampling Time points
// Code for making a Siesmograph
// WangGuangxue 201805050218@stu.cdut.edu.cn
// 2021-03-13 updated
// 2021-03-17 Updated
// 2021-03-24 Updated
// 2021-03-26 Updated

//Function Statement
int wavelet(FILE *fp,float dt,float Fm,float n,float m,float xw);
int Calc_Velocity_Dencity_Reflection_coefficient(FILE *fp1,FILE *fp2,FILE *fp4,float dt);
void conv_data(FILE *fp,FILE *fp2,FILE *fp3,FILE *fp4,int length_of_wavelet,int length_of_R);
void conv(float *u,int u_length,float *v,int v_length,float *W);

main()
{
    // Initial dt,Fm,n,m,xw and so on
    float dt;//Sampling interval
    printf("Pls enter the sampling interval(dt):\n");
    scanf("%f", &dt);
    
    float t[ST];// Sampling time

    int Fm;//Centre frequency equals 10 or 25 or 40 or 100
    printf("Pls enter the Center Frequency(Fm):\n");
    scanf("%d",&Fm);

    float n;// The ration between biggest crest and smallest crest of smallest phase
    printf("Pls entre the ration between biggest crest and smallest crest(n):\n");
    scanf("%f", &n);
    
    float m;// The ration between main crest and secondary crest in time domain of bell-shaped phase
    printf("Pls enter the ration between main crest and secondary crest(m):\n");
    scanf("%f", &m);

    float xw;// The initial phase
    printf("Pls enter the initialising phase(xw):\n");
    scanf("%f", &xw);

    int length_of_wavelet = 0;
    int length_of_R = 0;//length_of_Reflection_coefficient
    // Write the data into File
    FILE *fp;// FILE pointer fp->wavelet.txt
    // fp = fopen("E:/VScode/C/wavelet.txt","w+");  
    fp = fopen("wavelet.txt","w+");  
    length_of_wavelet = wavelet(fp,dt,Fm,n,m,xw);//Call sub-function
    fclose(fp);//close the FILE fp->wavelet.txt
   
    FILE *fp1,*fp2,*fp3;
    //File pointer fp1->Well_log_data.txt
    //File pointer fp2->Velocity_Dencity.txt
    //File pointer fp3->Reflection_coefficient.txt  
    // fp1 = fopen("E:/VScode/C/Well_log_data.txt","r");//Open the file
    // fp2 = fopen("E:/VScode/C/Velocity_Density.txt","w+");
    // fp3 = fopen("E:/VScode/C/Reflection_coefficient.txt","w+");
    fp1 = fopen("Well_log_data.txt","r");//Open the file
    fp2 = fopen("Velocity_Density.txt","w+");
    fp3 = fopen("Reflection_coefficient.txt","w+");
    length_of_R = Calc_Velocity_Dencity_Reflection_coefficient(fp1,fp2,fp3,dt);//calling sub-function 
    fclose(fp1); // close file pointer fp1->Well_log_data.txt
    fclose(fp2); // close file pointer fp2->Velocity_Dencity.txt
    fclose(fp3); // close file pointer fp3->Reflection_coefficient.txt     
    
    FILE *fp4,*fp5,*fp6,*fp7;
    //File pointer fp4->Seismic data 
    //File pointer fp5->wavelet.txt Reopen bec writing before
    //File pointer fp6->Velocity_Dencity.txt Reopen bec writing before
    //File pointer fp7->Reflection_coefficient.txt Reopen bec writing before
    // fp4 = fopen("E:/VScode/C/seismic_data.txt","w+");
    // fp5 = fopen("E:/VScode/C/wavelet.txt","r+"); 
    // fp6 = fopen("E:/VScode/C/Velocity_Density.txt","r+");
    // fp7 = fopen("E:/VScode/C/Reflection_coefficient.txt","r+");
    fp4 = fopen("seismic_data.txt","w+");
    fp5 = fopen("wavelet.txt","r+"); 
    fp6 = fopen("Velocity_Density.txt","r+");
    fp7 = fopen("Reflection_coefficient.txt","r+");
    conv_data(fp5,fp6,fp4,fp7,length_of_wavelet,length_of_R);//call subfunction 
    fclose(fp4);// close file pointer fp4->seismic_data.txt
    fclose(fp5);// close file pointer fp5->wavelet.txt
    fclose(fp6);// close file pointer fp5->Velocity_Dencity.txt
    fclose(fp7);// close file pointer fp7->Reflection_coefficient.txt

    system("pause");
    return 0;

}

int wavelet(FILE *fp,float dt,float Fm,float n,float m,float xw)
// Subfunction for calcing discrete wavelet of zero phase，smallest phase and bell-shaped phase
// file pointer fp->wavelet.txt
// WangGuangxue 201805050218 wongguangxue@gmail.com
// 2021-03-12 Fist Write
// 2021-03-13 Updated   
{
    //Initial 
    float DT,FM,M,N,XW,t[ST * 2];
    DT = dt;//Simpling interval
    FM = Fm;//Center frequency
    N = n;
    M = m;
    XW = xw;//Initial phase
    // int i; 
    // int length_of_wavelet = 0;

   float Z[ST * 2], S[ST * 2], B[ST * 2];//Here Z[50] means zeros phase, S[50] means smallest phase and B[50] means bell-shaped phase wavelet
    
    // Initialise 
    for(int i = 0;i < ST * 2;i++)//For the negative points in array
	{
        int temp = i - ST;// For negative index
        t[i] = temp * DT;
         
        Z[i] = exp(-1 * pow(PI * FM * t[i],2)) * (1 - 2 * pow((PI * FM * t[i]),2));
        S[i] = exp(-2 * pow(FM,2) * pow(t[i],2) * log(N)) * sin(2 * PI * FM * t[i]);
        B[i] = exp(-1 * pow(FM, 2) * pow(t[i],2) * log(M)) * cos(2 * PI * FM * t[i] + XW);
        fprintf(fp,"%f  %f  %f\n",Z[i],S[i],B[i]);//Writing the data into file fp->wavelet.txt
    }
    // printf("%f %f %f",Z[30],S[30],B[30]);//test the array
    
    return (ST * 2);
}

int Calc_Velocity_Dencity_Reflection_coefficient(FILE *fp1,FILE *fp2,FILE *fp3,float dt)
// subfunction for Calcing Velocity,Dencity and Reflection_coefficient
// File pointer fp1->Well_log_data,fp2->Velocity_and_Dencity,fp3->Reflection_coefficiant
// WangGaungxue 2021-03-14 UPdated
{
    
    float Well_log[ROW][COLUM];//Data from Well_log
    double  V[ROW];//Velocity
    float D1[ROW],D2[ROW];//Dencity
    // float R[ROW][2];//Reflection_coefficient of 2 relations
    float t_vertical[ROW];//vertical time 
    int n[ROW];//number of layers
    float DT = dt;//Sampling interval
    // int length_of_R = 0;



    
    for(int i = 0;i < ROW;i++)
    //loop for puttting data from fp1 into  array:Well_log[][]
    {    
            fscanf(fp1,"%f%f",&Well_log[i][0],&Well_log[i][1]);//puttting data from fp1->Well_log_data into  array
            // printf("%f   %f\n",Well_log[i][0],Well_log[i][1]);//test if it's right or not   
    }
    

    for(int i = 0;i < ROW ;i++)
    //loop for calcing Velocity and Density
    {        
        V[i] = pow(10,6) / (Well_log[i][0]);//Velocity
        D1[i] = V[i] * 0.00021 + 1.62;//Density using linear relation
        D2[i] = 0.31 * pow(V[i],0.25);//Density using nonlinear relation
        // printf("%f  %f  %f\n",V[i],D1[i],D2[i]);             
    }

    for(int i = 0;i < ROW;i++)
    //loop for calcing R1 and R2
    {
        if(i == 0)
        {
            t_vertical[i] = 2 * Well_log[i][1] / V[i];
            // n = t_vertical[i] / DT;//discrete time and find n 
            // printf("%d\n",n);//test n
        }
        else
        {
            t_vertical[i] = t_vertical[i - 1] + 2 * (Well_log[i][1] - Well_log[i - 1][1]) / V[i];
            // n = t_vertical[i] / DT;////discrete time and find n
            // printf("%d\n",n);//test n
        }
    }

    for(int i = 0;i < sizeof(t_vertical)/sizeof(t_vertical[0]);i++)
    {
        n[i] = (int)(t_vertical[i] / DT);
        // printf("%d\n",n[i]);
    }
    // printf("length is %d\n",n[sizeof(t_vertical)/sizeof(t_vertical[0]) - 1]);

    float R[n[sizeof(t_vertical)/sizeof(t_vertical[0]) - 1] + 10][2];
    for(int i = 0;i < n[sizeof(t_vertical)/sizeof(t_vertical[0]) - 1] + 10;i++)
    {
        R[i][1] = 0;
        R[i][2] = 0;
    }
    

    for(int i = 0;i < ROW;i++)
    {
        if(n[i] == 0)
        {
            continue;
        }
        else 
        {        
            R[n[i]][0] = (D1[i + 1] * V[i + 1] - D1[i] * V[i]) / (D1[i + 1] * V[i + 1] + D1[i] * V[i]);//Reflection_coefficient
            R[n[i]][1] = (D2[i + 1] * V[i + 1] - D2[i] * V[i]) / (D2[i + 1] * V[i + 1] + D2[i] * V[i]);//Reflection_coefficient
            // printf("%f %f\n",R[n[i]][0],R[n[i]][1]);
            
        }
    }

    for(int i = 0;i < ROW;i++)
    //loop for writting Velocity, Density, and R into file fp2->Velocity_and_Dencity
    {
        fprintf(fp2,"%f  %f  %f\n",V[i],D1[i],D2[i]);//fp2->Velocity_and_Dencity
    }
    for(int i = 0;i < n[sizeof(t_vertical)/sizeof(t_vertical[0]) - 1];i++)
    {
        fprintf(fp3,"%f  %f\n",R[i][0],R[i][1]);//fp3->Reflection_coefficiant
    }

    return (n[sizeof(t_vertical)/sizeof(t_vertical[0]) - 1]);
}

void conv_data(FILE *fp5,FILE *fp6,FILE *fp4,FILE *fp7,int length_of_wavelet,int length_of_R)
//subfunction for conv the wavelet data and the reflection_coefficiant data
//file pointer fp5 ->wavelet.txt,fp7->Reflection_coefficient.txt,fp4->seismic_data.txt
//2021-03-26 UPdated
{
    int L1,L2;//length 
    L1 = length_of_wavelet;//length of Z,S,B
    L2 = length_of_R;//length of R
    int k = L1 + L2 -1;//length of W
    float conv_Z_R1[k],conv_Z_R2[k],conv_S_R1[k],conv_S_R2[k],conv_B_R1[k],conv_B_R2[k];
    //for array after conving the wavelet data and the reflection_coefficiant data

    float Z[L1],S[L1],B[L1],R1[L2],R2[L2];
    //R1 for first linear relation R2 for the 2nd nonlinear relation 
    //Conv_data arrays
    for(int i = 0;i <length_of_wavelet;i++)
    {
        fscanf(fp5,"%f%f%f",&Z[i],&S[i],&B[i]); // file pointer fp5 ->wavelet.txt
        // printf("%f %f %f\n",Z[i],B[i],S[i]);
    }

    for(int i = 0;i < length_of_R;i++)
    {
        fscanf(fp7,"%f%f",&R1[i],&R2[i]);//file pointer fp7->Reflection_coefficient.txt
        // printf("%f %f\n",R1[i],R2[i]);
    }   
    
    //Conving the data
    conv(Z,L1,R1,L2,conv_Z_R1);//call subfunction conv
    conv(Z,L1,R2,L2,conv_Z_R2);
    conv(S,L1,R1,L2,conv_S_R1);
    conv(S,L1,R2,L2,conv_S_R2);
    conv(B,L1,R1,L2,conv_B_R1);
    conv(B,L1,R2,L2,conv_B_R2);

    for(int i = 0;i < k;i++)
    {
        // printf("%f %f %f %f %f\n",conv_Z_R1[i],conv_Z_R2[i],conv_S_R1[i],conv_S_R2[i],conv_B_R1[i],conv_B_R2[i]);
        fprintf(fp4,"%f  %f  %f  %f  %f  %f\n",conv_Z_R1[i],conv_Z_R2[i],conv_S_R1[i],conv_S_R2[i],conv_B_R1[i],conv_B_R2[i]);
        // fp4->seismic_data.txt
    }

    return;
}

void conv(float *u,int u_length,float *v,int v_length,float *W)
// subfunc conv for conv
// We need to know the length of the array
// u,v are the array to be conv,and W is the answer
// Copying from the Internet
{
    int i = 0;
    int j = 0;
    int k = u_length + v_length - 1;//length of W
 
    for(i = 0; i < k; i++)
    {
        *(W + i) = 0;
        for(j = (0 > i + 1 - v_length ? 0 : i + 1 - v_length);j <= (i < u_length - 1 ? i : u_length - 1); j++)
        {
            W[i] += u[j] * v[i - j];//conv
        }
    }
}
