//
//  main.c
//  Spn_1.0
//
//  Created by 郭倜维 on 2018/8/17.
//  Copyright © 2018年 郭倜维. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "math.h"

const int K[32]={0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1};
static int S_Box[16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
static int S1_Box[16]={14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
static unsigned int P_Box[16]={1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
static int Key[5][16]={0};

void BittoSix(unsigned int *Out,unsigned int *In,unsigned int num);//二进制转十六进制
void SixtoBit(unsigned int *Out,unsigned int *In,unsigned int num);//十六进制转二进制
void Six_Bit(unsigned int *Out,unsigned int In,unsigned int num);
void Bit_Six(unsigned int Output, unsigned int *Input, unsigned int num);
void SPN_P(unsigned int *Out,unsigned int *In,unsigned int num, unsigned int *change);//置换
void SPN_XOR(unsigned int *DatA,unsigned int *DatB,unsigned int num );//异或
void SPN_Ecrypt(unsigned int *Plaintext,unsigned int *Ciphertext);//加密
void SPN_K(void);//初始化密钥
void Copy(unsigned int *Out,unsigned int *In,unsigned int len);//复制内容
void Text(unsigned int *Out,unsigned int *In);//随机明密文生成
void SPN_Wire(int len);//线性攻击
void SPN_Cha(unsigned int len);//差分攻击
void SPN_Ecrypt_1(unsigned int *Plaintext,unsigned int *Ciphertext,unsigned int *K1);
void SPN_K1(unsigned int *K1);

int main(int argc, const char * argv[])
{
    unsigned int i,j;
    unsigned int Plaintext[16]={0};
    unsigned int Ciphertext[16]={0};
    //int KeyOut[16]={0};
    printf("请选择下列功能：\n");
    printf("1.spn加密明文  2.线性攻击   3.差分分析\n");
    scanf("%d",&j);
    
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
            printf("\n");
        }break;
        case 2:
        {
            printf("");
            SPN_Wire(8000);
            
        }break;
        case 3:
        {
            printf("");
            SPN_Cha(8000);
        }
        default:break;
    }
    system("pause");
}

void BittoSix(unsigned int *Out,unsigned int *In,unsigned int num)
{
    unsigned int i;
    for (i=0; i<num/4; i++) {
        Out[i]=8*In[4*i]+4*In[4*i+1]+2*In[4*i+2]+In[4*i+3];//高字节为数组的低位
    }
}

void SixtoBit(unsigned int *Out,unsigned int *In,unsigned int num)
{
    int i;
    for (i=num-1;i>=0;i--) {
        Out[i]=In[i/4]%2;
        In[i/4]/=2;
    }
}

void SPN_P(unsigned int *Out,unsigned int *In,unsigned int num, unsigned int *change)
{
    int i;
    static unsigned int temp[32]={0};
    for(i=0;i<num;i++)
        temp[i]=In[change[i]-1];//置换中数字从1开始计数
    Copy(Out,temp,num);//将置换结果拷贝到相同处
}

void SPN_XOR(unsigned int *DatA,unsigned int *DatB,unsigned int num )
{
    int i=0;
    for(i=0;i<num;i++)
    {
        DatA[i]=DatA[i]^DatB[i];
    }
}

void SPN_Ecrypt(unsigned int *Plaintext,unsigned int *Ciphertext)
{
    int i,j;
    unsigned int Temp[16]={0};
    unsigned int Temp1[16]={0};
    unsigned int Key2[16]={0};
    Copy(Temp,Plaintext,16);
    SPN_K();
    for (i=0; i<4; i++) {
        for(j=0; j<16; j++)
        {
            Key2[j]=Key[i][j];
        }
        SPN_XOR(Temp, Key2, 16);
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
    for(j=0; j<16; j++)
    {
        Key2[j]=Key[i][j];
    }
    SPN_XOR(Temp1, Key2, 16);
    Copy(Ciphertext, Temp1, 16);
}

void SPN_Ecrypt_1(unsigned int *Plaintext,unsigned int *Ciphertext,unsigned int *K1)
{
    unsigned int i,j;
    unsigned int Temp[16]={0};
    unsigned int Temp1[16]={0};
    unsigned int Key2[16]={0};
    Copy(Temp,Plaintext,16);
    SPN_K1(K1);
    for (i=0; i<4; i++) {
        for(j=0; j<16; j++)
        {
            Key2[j]=Key[i][j];
        }
        SPN_XOR(Temp, Key2, 16);
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
    for(j=0; j<16; j++)
    {
        Key2[j]=Key[i][j];
    }
    SPN_XOR(Temp1, Key2, 16);
    Copy(Ciphertext, Temp1, 16);
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

void SPN_K1(unsigned int *K1)
{
    int i,j;
    int z=0;
    for(i=0;i<5;i++)
    {
        //printf("密钥K%d为",i);
        for(j=0;j<16;j++,z++)
        {
            Key[i][j] = K1[z];
            //printf("%d",Key[i][j]);
        }
        z-=12;
        //printf("\n");
    }
}

void Copy(unsigned int *Out,unsigned int *In,unsigned int len)
{
    int i;
    for (i=0; i<len; i++) {
        Out[i] = In[i];
    }
}

void Text(unsigned int *Out,unsigned int *In)
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

void Six_Bit(unsigned int *Out,unsigned int In,unsigned int num)
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
    unsigned int L1,L2,v2,v4,z;
    int i;
    int j=0;
    unsigned int u2,u4,m;
    int max=-1;
    unsigned int key1 = 0,key2 = 0;
    int count[16][16];
    unsigned int Input[16]={0};
    unsigned int Output[16]={0};
    unsigned int KeyOut[8]={0};
    unsigned int KeyOut_1[8]={0};
    unsigned int U2[4]={0},U4[4]={0};
    double cost;
    clock_t start, end;
    start = clock();
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
    for(i=0;i<8;i++)
        printf("%d",KeyOut[i]);
    printf("\n");
    end = clock();
    cost = (double)(end-start)/CLOCKS_PER_SEC;
    printf("时间：%lf\n",cost);
    
    //32位分析
    unsigned int keyhigh,k1,k2;
    unsigned int In[16]={0};
    unsigned int Out[16]={0};
    
    unsigned int Out1[16]={0};
    unsigned int K1[32]={0};
    unsigned int key=0;
    //unsigned int K1[32]={0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1};
    //SPN_Ecrypt(In,Out);
    //SPN_Ecrypt_1(In,Out1,K1);
    start = clock();
    for(keyhigh=0; keyhigh<=0xffff; keyhigh++)
    {
        for(k1=0; k1<=0xf; k1++)
        {
            for(k2=0; k2<0xf; k2++)
            {
                key = (keyhigh<<16)+(k1<<12)+(key1<<8)+(k2<<4)+key2;
                //key = 982832703;
                Six_Bit(K1,key,32);
                int l=0;
                int L=0;
                for(i=0; i<5; i++)
                {
                    int r,j;
                    r=rand()%65536;
                    for (j=15; j>=0; j--)
                    {
                        In[j]=r%2;
                        r/=2;
                    }
                    SPN_Ecrypt(In,Out);
                    SPN_Ecrypt_1(In,Out1,K1);
                    j=0;
                    for(l=0; l<=15; l++)
                    {
                        if(Out[l]==Out1[l])
                        {
                            j++;
                        }
                    }
                    if(j==16)
                    {
                        L++;
                    }
                }
                if(L==5)
                {
                    printf("%d\n",key);//并结束循环
                    keyhigh=0xffff;
                    k1=0xf;
                    k2=0xf;
                }
                
            }
        }
    }
    end = clock();
    cost = (double)(end-start)/CLOCKS_PER_SEC;
    printf("时间：%lf\n",cost);
    //printf("00111010100101001101011000111111\n");
}

void Bit_Six(unsigned int Output, unsigned int *Input, unsigned int num)
{
    int i;
    for (i=0; i<num/4; i++)
    {
        Output=8*Input[4*i]+4*Input[4*i+1]+2*Input[4*i+2]+Input[4*i+3];
    }
}

void SPN_Cha(unsigned int len)
{
    unsigned int L1,L2,v2,v4;
    unsigned int k,l;
    unsigned int u2,u4,i,j,p,q,m;
    int max =-1;
    unsigned int key1 = 0,key2 = 0;
    unsigned int x[16]={0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0};
    unsigned int KeyOut[8]={0};
    unsigned int KeyOut_1[8]={0};
    int count[16][16];
    
    unsigned int Input[16]={0};
    unsigned int Input1[16]={0};
    unsigned int Output[16]={0};
    unsigned int Output1[16]={0};
    
    unsigned int Output_0[16]={0};
    //int Input_1[16]={0};
    unsigned int Output_1[16]={0};
    double cost;
    clock_t start, end;
    start = clock();
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
        }
    }
    for(L1=0;L1<16;L1++)
    {
        for(L2=0;L2<16;L2++)
        {
            if(count[L1][L2]>max)
            {
                max=count[L1][L2];
                //printf("%d",max);
                key1=L1;
                key2=L2;
            }
        }
    }
    //printf("%d %d\n",key1,key2);
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
    end = clock();
    cost = (double)(end-start)/CLOCKS_PER_SEC;
    printf("时间：%lf\n",cost);
    
    //32位分析
    unsigned int keyhigh,k1,k2;
    unsigned int In[16]={0};
    unsigned int Out[16]={0};
    unsigned int Out1[16]={0};
    unsigned int K1[32]={0};
    unsigned int key=0;
    start = clock();
    for(keyhigh=0; keyhigh<=0xffff; keyhigh++)
    {
        for(k1=0; k1<=0xf; k1++)
        {
            for(k2=0; k2<0xf; k2++)
            {
                key = (keyhigh<<16)+(k1<<12)+(key1<<8)+(k2<<4)+key2;
                //2key = 982832703;
                Six_Bit(K1,key,32);
                int l=0;
                int L=0;
                for(i=0; i<5; i++)
                {
                    int r,j;
                    r=rand()%65536;
                    for (j=15; j>=0; j--)
                    {
                        In[j]=r%2;
                        r/=2;
                    }
                    SPN_Ecrypt(In,Out);
                    SPN_Ecrypt_1(In,Out1,K1);
                    j=0;
                    for(l=0; l<=15; l++)
                    {
                        if(Out[l]==Out1[l])
                        {
                            j++;
                        }
                    }
                    if(j==16)
                    {
                        L++;
                    }
                }
                if(L==5)
                {
                    printf("%d\n",key);//并结束循环
                    keyhigh=0xffff;
                    k1=0xf;
                    k2=0xf;
                }
                
            }
        }
    }
    end = clock();
    cost = (double)(end-start)/CLOCKS_PER_SEC;
    printf("时间：%lf\n",cost);
}



