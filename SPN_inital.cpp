//
//  main.cpp
//  SPN_inital
//
//  Created by 郭倜维 on 2018/10/12.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "math.h"

const int K[32]={0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1};
static int S_Box[16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
static int S1_Box[16]={14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
static int P_Box[16]={1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
static int P1_Box[16]={1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
static int Key[5][16]={0};

void BittoSix(int *Out,int *In,int num);//二进制转十六进制
void SixtoBit(int *Out,int *In,int num);//十六进制转二进制
void Six_Bit(int *Out,int In,int num);
void Bit_Six(int Output, int *Input, int num);
void SPN_P(int *Out,int *In,int num, int *change);//置换
void SPN_XOR(int *DatA,int *DatB,int num );//异或
void SPN_Ecrypt(int *Plaintext,int *Ciphertext);//加密
void SPN_Decrypt(int *Plaintext, int *Ciphertext);//解密
void SPN_K(void);//初始化密钥
void Copy(int *Out,int *In,int len);//复制内容
void Text(int *Out,int *In);//随机明密文生成
void SPN_Wire(int len);//线性攻击
void SPN_Cha(int len);//差分攻击

int main(int argc, const char * argv[])
{
    int i,j;
    int Plaintext[16]={0};
    int Ciphertext[16]={0};
    //int KeyOut[16]={0};
    printf("请选择下列功能：\n");
    printf("1.spn加密明文  2.spn解密明文  3.线性攻击   4.差分分析\n");
    
    while(~scanf("%d",&j))
    {
        switch(j){
            case 1:
            {
                printf("请输入一个16位的1/0明文:\n");
                for(i=0;i<16;i++)
                    scanf("%d",&Plaintext[i]);
                SPN_Ecrypt(Plaintext,Ciphertext);
                printf("\n密文为：\n");
                for(i=0;i<16;i++)
                    printf("%d ",Ciphertext[i]);
            }break;
            case 2:
            {
                SPN_Decrypt(Plaintext, Ciphertext);
                printf("\n明文为：\n");
                for(i=0;i<16;i++)
                    printf("%d ",Plaintext[i]);
            }break;
            case 3:
            {
                printf("");
                SPN_Wire(8000);
                
            }break;
            case 4:
            {
                printf("");
                SPN_Cha(8000);
            }
            default:break;
        }
        system("pause");
    }
}

void BittoSix(int *Out,int *In,int num)
{
    int i;
    for (i=0; i<num/4; i++) {
        Out[i]=8*In[4*i]+4*In[4*i+1]+2*In[4*i+2]+In[4*i+3];//高字节为数组的低位
    }
}

void SixtoBit(int *Out,int *In,int num)
{
    int i;
    for (i=num-1;i>=0;i--) {
        Out[i]=In[i/4]%2;
        In[i/4]/=2;
    }
}

void SPN_P(int *Out,int *In,int num, int *change)
{
    int i;
    static int temp[32]={0};
    for(i=0;i<num;i++)
        temp[i]=In[change[i]-1];//置换中数字从1开始计数
    Copy(Out,temp,num);//将置换结果拷贝到相同处
}

void SPN_XOR(int *DatA,int *DatB, int num )
{
    int i=0;
    for(i=0;i<num;i++)
    {
        DatA[i]=DatA[i]^DatB[i];
    }
}

void SPN_Ecrypt(int *Plaintext,int *Ciphertext)
{
    int i,j;
    static int Temp[16]={0};
    static int Temp1[16]={0};
    Copy(Temp,Plaintext,16);
    SPN_K();
    for (i=0; i<4; i++) {
        SPN_XOR(Temp, Key[i], 16);
        BittoSix(Temp1, Temp, 16);
        for (j=0; j<4; j++) {
            Temp[j]=S_Box[Temp1[j]];
        }
        SixtoBit(Temp1, Temp, 16);
        if(i<3)
        {
            SPN_P(Temp, Temp1, 16, P_Box);
        }
        else continue;
    }
    SPN_XOR(Temp1, Key[i], 16);
    Copy(Ciphertext, Temp1, 16);
}

void SPN_Decrypt(int *Plaintext, int *Ciphertext)
{
    int i,j;
    int Key_P[5][16]={0};
    for (i=0; i<16; i++)
    {
        Key_P[0][i] = Key[0][i];
        Key_P[4][i] = Key[4][i];
    }
    for (i=0; i<16; i++)
    {
        SPN_P(Key_P[1], Key[1], 16, P1_Box);
        SPN_P(Key_P[2], Key[2], 16, P1_Box);
        SPN_P(Key_P[3], Key[3], 16, P1_Box);
    }
    static int Temp[16]={0};
    static int Temp1[16]={0};
    Copy(Temp,Ciphertext,16);
    for (i=4; i>0; i--)
    {
        SPN_XOR(Temp, Key_P[i], 16);
        BittoSix(Temp1, Temp, 16);
        for (j=0; j<4; j++) {
            Temp[j]=S1_Box[Temp1[j]];
        }
        SixtoBit(Temp1, Temp, 16);
        if(i>1)
        {
            SPN_P(Temp, Temp1, 16, P1_Box);
        }
        else continue;
    }
    SPN_XOR(Temp1, Key[i], 16);
    Copy(Plaintext, Temp1, 16);
}

void SPN_K(void)
{
    int i,j;
    int z=0;
    for(i=0;i<5;i++)
    {
        //printf("密钥K%d为",i);
        for(j=0;j<16;j++,z++)
        {
            Key[i][j] = K[z];
            //printf("%d",Key[i][j]);
        }
        z-=12;
        //printf("\n");
    }
}

void Copy(int *Out,int *In,int len)
{
    int i;
    for (i=0; i<len; i++) {
        Out[i] = In[i];
    }
}

void Text(int *Out,int *In)
{
    int i,j;
    //srand((unsigned)time(NULL));
    i=rand()%65536;
    for (j=15; j>=0; j--)
    {
        In[j]=i%2;
        i/=2;
    }
    SPN_Ecrypt(In, Out);
}

void Six_Bit(int *Out,int In,int num)
{
    int i;
    for(i=num-1; i>=0; i--)
    {
        Out[i]=In%2;
        In/=2;
    }
}

void SPN_Wire(int len)
{
    int L1,L2,v2,v4,z;
    int i;
    int j=0;
    int u2,u4,m;
    int max=-1;
    int key1 = 0,key2 = 0;
    int count[16][16];
    int Input[16]={0};
    int Output[16]={0};
    int KeyOut[8]={0};
    int KeyOut_1[8]={0};
    int U2[4]={0},U4[4]={0};
    for(L1=0;L1<16;L1++)
    {
        for(L2=0;L2<16;L2++)
        {
            count[L1][L2]=0;
        }
    }
    for(m=0; m<len; m++)
    {
        Text(Output, Input);
        for (L1=0; L1<16; L1++)
        {
            for(L2=0; L2<16; L2++)
            {
                v2 = L1^(Output[4]*8+Output[5]*4+Output[6]*2+Output[7]); //L1^y2
                v4 = L2^(Output[12]*8+Output[13]*4+Output[14]*2+Output[15]); //L2^y4
                u2=S1_Box[v2];
                SixtoBit(U2,&u2,4);
                u4=S1_Box[v4];
                SixtoBit(U4,&u4,4);
                z=Input[4]^Input[6]^Input[7]^U2[1]^U2[3]^U4[1]^U4[3];
                if(z==0)
                {
                    ++count[L1][L2];
                }
            }
        }
    }
    for(L1=0;L1<16;L1++)
    {
        for(L2=0;L2<16;L2++)
        {
            count[L1][L2]=abs(count[L1][L2]-len/2);
            if(count[L1][L2]>max)
            {
                max=count[L1][L2];
                key1=L1;
                key2=L2;
            }
        }
    }
    Six_Bit(KeyOut,key1,4);
    Six_Bit(KeyOut_1,key2,4);
    for(i=4;i<8;i++,j++)
    {
        KeyOut[i]=KeyOut_1[j];
    }
    for(u2=0;u2<8;u2++)
        printf("%d",KeyOut[u2]);
    printf("\n");
}

void Bit_Six(int Output, int *Input, int num)
{
    int i;
    for (i=0; i<num/4; i++)
    {
        Output=8*Input[4*i]+4*Input[4*i+1]+2*Input[4*i+2]+Input[4*i+3];
    }
}

void SPN_Cha(int len)
{
    int L1,L2,v2,v4;
    int k,l;
    int u2,u4,i,j,p,q,m;
    int max =-1;
    int key1 = 0,key2 = 0;
    int x[16]={0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0};
    int KeyOut[8]={0};
    int KeyOut_1[8]={0};
    int count[16][16];
    
    int Input[16]={0};
    int Input1[16]={0};
    int Output[16]={0};
    int Output1[16]={0};
    
    int Output_0[16]={0};
    //int Input_1[16]={0};
    int Output_1[16]={0};
    
    int U2,U4,U2_1,U4_1;
    for(L1=0;L1<16;L1++)
    {
        for(L2=0;L2<16;L2++)
        {
            count[L1][L2]=0;
        }
    }
    for(m=0;m<len;m++)
    {
        Text(Output,Input);//随机生成明密文对
        //Text(Output_1,Input_1);
        /*for(i=0;i<16;i++)
         {
         printf("%d",Output[i]);
         }
         printf("\n");*/
        
        /*随机生成另一对明密文对*/
        for(u2=0;u2<16;u2++)
        {
            Input1[u2]=Input[u2]^x[u2];
        }
        SPN_Ecrypt(Input1, Output1);
        
        /*二进制转化为十进制*/
        BittoSix(&i,Output,4);
        for(k=8,l=0;k<12;k++,l++)
        {
            Output_0[l]=Output[k];
        }
        BittoSix(&j,Output_0,4);//y3
        //printf("%d  %d\n",i,j);
        // printf("*");
        /*for(p=0;p<16;p++)
         {
         printf("%d",Output_1[p]);
         }*/
        //printf("\n");
        BittoSix(&p,Output1,4);
        for(k=8,l=0;k<12;k++,l++)
        {
            Output_1[l]=Output1[k];
        }
        BittoSix(&q,Output_1,4);//y3_1
        //printf("%d  %d\n",p,q);
        
        /*差分分析*/
        if(i==p && j==q)
        {
            //printf("111111\n");
            for(L1=0; L1<16; L1++)
            {
                for(L2=0;L2<16;L2++)
                {
                    v2=L1^(Output[4]*8+Output[5]*4+Output[6]*2+Output[7]);
                    v4=L2^(Output[12]*8+Output[13]*4+Output[14]*2+Output[15]);
                    U2=S1_Box[v2];
                    U4=S1_Box[v4];
                    v2=L1^(Output1[4]*8+Output1[5]*4+Output1[6]*2+Output1[7]);
                    v4=L2^(Output1[12]*8+Output1[13]*4+Output1[14]*2+Output1[15]);
                    U2_1=S1_Box[v2];
                    U4_1=S1_Box[v4];
                    u2=U2^U2_1;
                    u4=U4^U4_1;
                    if(u2==6 && u4==6)
                    {
                        count[L1][L2]++;
                    }
                }
            }
            /*for(L1=0;L1<16;L1++)
             {
             for(L2=0;L2<16;L2++)
             {
             printf("%d",count[i][j]);
             }
             }*/
        }
    }
    for(L1=0;L1<16;L1++)
    {
        for(L2=0;L2<16;L2++)
        {
            if(count[L1][L2]>max)
            {
                max=count[L1][L2];
                key1=L1;
                key2=L2;
            }
        }
    }
    //printf("%d %d",key1,key2);
    Six_Bit(KeyOut,key1,4);
    Six_Bit(KeyOut_1,key2,4);
    j=0;
    for(i=4;i<8;i++,j++)
    {
        KeyOut[i]=KeyOut_1[j];
    }
    for(i=0;i<8;i++)
        printf("%d",KeyOut[i]);
    printf("\n");
}

