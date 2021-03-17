//I got some shit with calcing the Reflection_coefficient
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define PI 3.1415927
#define ROW 200 //row of the well_log data
#define COLUM 2 //colum of the well_log data
#define ST 50 //means Sampling Time
// Code for making a Siesmograph
// WangGuangxue 201805050218@stu.cdut.edu.cn
// 2021-03-13 updated
// 2021-03-17 Updated

//Function Statement
void wavelet(FILE *fp,float dt,float t[],float Fm,float n,float m,float xw);
void Calc_Velocity_Dencity_Reflection_coefficient(FILE *fp1,FILE *fp2,float dt);
void conv_data(FILE *fp,FILE *fp2,FILE *fp3);
void conv(float *u,int u_length,float *v,int v_length,float *W);

main()
{
    // Initial dt,Fm,n,m,xw and so on
    float dt;//Sampling interval
    printf("Pls entre the sampling interval(dt):\n");
    scanf("%f", &dt);
    
    float t[ST];// Sampling time

    int Fm;//Centre frequency equals 10 or 25 or 40 or 100
    printf("Pls enter the Center Frequency(Fm):\n");
    scanf("%d",&Fm);

    float n;// The ration between biggest crest and smallest crest of smallest phase
    printf("Pls entre the ration between biggest crest and smallest crest(n):\n");
    scanf("%f", &n);
    
    float m;// The ration between main crest and secondary crest in time domain of bell-shaped phase
    printf("Pls entre the ration between main crest and secondary crest(m):\n");
    scanf("%f", &m);

    float xw;// The initial phase
    printf("Pls entre the initialising phase(xw):\n");
    scanf("%f", &xw);

    // Write the data into File
    FILE *fp;// FILE pointer for wavelet.txt

    fp = fopen("E:/VScode/C/wavelet.txt","w+"); 
    wavelet(fp,dt,t,Fm,n,m,xw);//Call sub-function
    fclose(fp);

    
    FILE *fp1;//File pointer for Well_log_data.txt
    fp1 = fopen("E:/VScode/C/Well_log_data.txt","r");

    FILE *fp2;//File pointer for writing Velocity,Dencity and reflection coefficient
    fp2 = fopen("E:/VScode/C/Velocity_Dencity_Reflection_coefficient.txt","w+");
 
    Calc_Velocity_Dencity_Reflection_coefficient(fp1,fp2,dt);//calling sub-function 

    // fclose(fp1);
    fclose(fp2);
    fclose(fp1);    

    FILE *fp3;//File pointer for writing Seismic data 
    fp3 = fopen("E:/VScode/C/seismic_data.txt","w+");
    conv_data(fp,fp2,fp3);//call subfunction 
    fclose(fp3);

    // system("pause");
    return 0;

}

void wavelet(FILE *fp,float dt,float t[],float Fm,float n,float m,float xw)
//Code for calcing discrete wavelet of zero phase，smallest phase and bell-shaped phase
//And writing data into file
// WangGuangxue 201805050218 wongguangxue@gmail.com
// 2021-03-12 Fist Write
// 2021-03-13 Updated   
{
    //Initial 
    float DT,FM,M,N,XW;
    DT = dt;//Simpling interval
    FM = Fm;//Center frequency
    M = n;
    M = m;
    XW = xw;//Initial phase
    // int i; 

    float Z[ST], S[ST], B[ST];//Here Z[50] means zeros phase, S[50] means smallest phase and B[50] means bell-shaped phase wavelet
    
    // Initialise 
    for(int i = 0;i < ST;i++)
	{
        t[i] = i * DT;
        Z[i] = exp(-pow(PI * FM * t[i],2)) * (1 - 2 * pow((PI * FM * t[i]),2));
        S[i] = exp(-2 * pow(FM * t[i],2) * log(N)) * cos(2 * PI * FM * t[i]);
        B[i] = exp(-pow(FM * t[i], 2) * log(M)) * cos(2 * PI * FM * t[i] + XW);
        fprintf(fp,"%f  %f  %f\n",Z[i],S[i],B[i]);//Writing the data into file
    }
    // printf("%f %f %f",Z[30],S[30],B[30]);//test
    
    return;
}

void Calc_Velocity_Dencity_Reflection_coefficient(FILE *fp1,FILE *fp2,float dt)
// Code for Calcing Velocity,Dencity and Reflection_coefficient
// After calcing those data,writing them into file
// WangGaungxue 2021-03-14 UPdated
{
    
    float Well_log[ROW][COLUM];//Data from Well_log
    float V[ROW];//Velocity
    float D1[ROW],D2[ROW];//Dencity
    float R[ROW][2];//Reflection_coefficient of 2 relations
    float t_vertical[ROW];//vertical time 
    int n;//number of layers
    float DT = dt;//Sampling interval



    
    for(int i = 0;i < ROW;i++)
    //loop for puttting data from fp1 into  array:Well_log[][]
    {    
            fscanf(fp1,"%f%f",&Well_log[i][0],&Well_log[i][1]);//puttting data from fp1 into  array
            // printf("%f   %f\n",Well_log[i][0],Well_log[i][1]);//test if it's right or not   
    }
    

    for(int i = 0;i < ROW ;i++)
    //loop for calcing Velocity and Density
    {
        V[i] = pow(10,6) / (Well_log[i + 1][0] - Well_log[i][0]);//Velocity
        D1[i] = V[i] * 0.00021 + 1.62;//Density using linear relation
        D2[i] = 0.31 * pow(V[i],0.25);//Density using nonlinear relation
            // printf("%f  %f  %f\n",V[i],D1[i],D2[i]);         
    }

    


    for(int i = 0;i < ROW;i++)
    //loop for calcing R1 and R2
    {
        if(i == 0)
        {
            t_vertical[i] = 2 * Well_log[i][1] / V[0];
            n = t_vertical[i] / DT;//discrete time and find n 
            // printf("%d\n",n);//test n
            // R[n][0] = (D2[i + 1] * V[i + 1] - D2[i] * V[i]) / (D1[i + 1] * V[i + 1] + D1[i] * V[i]);//Reflection_coefficient
            // R[n][1] = (D2[i + 1] * V[i + 1] - D2[i] * V[i]) / (D2[i + 1] * V[i + 1] + D2[i] * V[i]);//Reflection_coefficient
        }
        else
        {
            t_vertical[i] = t_vertical[i - 1] + 2 * (Well_log[i][1] - Well_log[i - 1][1]) / V[i];
            n = t_vertical[i] / dt;////discrete time and find n
            // printf("%d\n",n);//test n
            // R[n][0] = (D1[i + 1] * V[i + 1] - D1[i] * V[i]) / (D1[i + 1] * V[i + 1] + D1[i] * V[i]);//Reflection_coefficient
            // R[n][1] = (D2[i + 1] * V[i + 1] - D2[i] * V[i]) / (D2[i + 1] * V[i + 1] + D2[i] * V[i]);//Reflection_coefficient
        }
    }

    for(int i = 0;i < ROW;i++)
    //loop for writting Velocity, Density, and R into file->fp2
    {
        fprintf(fp2,"%f  %f  %f %f  %f\n",V[i],D1[i],D2[i],R[i][0],R[i][1]);
    }

    return;
}

void conv_data(FILE *fp,FILE *fp2,FILE *fp3)
//Code for conving 
{
    float Z[ST],S[ST],B[ST],R1[COLUM],R2[COLUM],V[COLUM],D1[COLUM],D2[COLUM];
    //R1 for first linear relation R2 for the 2nd nonlinear relation
    int L1,L2;//length 
    L1 = ST;//length of Z,S,B
    L2 = COLUM;//length of R
    int k = L1 + L2 -1;//length of W

    float conv_Z_R1[k],conv_Z_R2[k],conv_S_R1[k],conv_S_R2[k],conv_B_R1[k],conv_B_R2[k];
    //Conv_data arrays

    for(int i = 0;i < ST;i++)
    {
        fscanf(fp,"%f%f%f",Z[i],S[i],B[i]);   
    }


    for(int i = 0;i < COLUM;i++)
    {
        fscanf(fp2,"%f%f%f%f%f",V[i],D1[i],D2[i],R1[i],R2[i]);
    }

    //Conving the data
    conv(Z,L1,R1,L2,conv_Z_R1);
    conv(Z,L1,R2,L2,conv_Z_R2);
    conv(S,L1,R1,L2,conv_S_R1);
    conv(S,L1,R2,L2,conv_S_R2);
    conv(B,L1,R1,L2,conv_B_R1);
    conv(B,L1,R2,L2,conv_B_R2);

    for(int i = 0;i < k;i++)
    {
        fprintf(fp3,"%f  %f  %f  %f  %f  %f\n",conv_Z_R1[i],conv_Z_R2[i],conv_S_R1[i],conv_S_R2[i],conv_B_R1[i],conv_B_R2[i]);
    }

    return;
}

void conv(float *u,int u_length,float *v,int v_length,float *W)
// subfunc conv
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
