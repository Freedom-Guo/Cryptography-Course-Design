//
//  main.cpp
//  SPN_plus
//
//  Created by 郭倜维 on 2018/10/13.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define Nr 11
unsigned int S_Box[16][16]={
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};
unsigned int S1_Box[16][16]={
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde,0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa,0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b,0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d,0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x5, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x3, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd,0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0xc, 0x7d}};
unsigned int P_Box[16]={1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
unsigned long long Key_0[2] = {0x1234567812345678,0x1234567812345678};//种子密钥

void Ten_Two(unsigned long long temp1, unsigned long long *temp_1);
void SPN_Ecrypt(unsigned long long *Plaintext, unsigned long long *Ciphertext, unsigned long long *K);
void sf_os1(unsigned long long Key1, unsigned long long Key2, unsigned long long *key);
void SPN_Decrypt(unsigned long long *Plaintext, unsigned long long *Ciphertext, unsigned long long *K);
void sf_os(unsigned long long Key1, unsigned long long Key2, unsigned long long *key);
//void copy(unsigned long long In,unsigned long long Out);
void KeyExpansion(unsigned long long Key1, unsigned long long Key2, unsigned long long *K);
void SPN_XOR(unsigned long long *temp, unsigned long long *K, unsigned int i);
void SPN_S(unsigned long long *temp, unsigned long long *temp1);
void SPN_P(unsigned long long *temp1,unsigned long long *temp);
unsigned long long RotWord(unsigned long long Word);
unsigned long long SubWord(unsigned long long Word);
void copy(unsigned long long In,unsigned long long *Out);
void SPN_S1(unsigned long long *temp, unsigned long long *temp1);
//void PExpansion(unsigned long long *P, unsigned long long *P_BOX[8][16]);
void K_P(unsigned long long *K);

int main(int argc, const char * argv[])
{
    unsigned long long Plaintext[2]={0};
    unsigned long long Ciphertext[2]={0};
    unsigned long long K[22]={0};
    //unsigned long long P_BOX[8][16]={0};
    //int KeyOut[16]={0};
    printf("请输入一个32位的十六进制明文:\n");
    scanf("%llx%llx",&Plaintext[0], &Plaintext[1]);//换成数字
    SPN_Ecrypt(Plaintext,Ciphertext,K);
    printf("\n密文为：\n");
    printf("%llx%llx\n",Ciphertext[0],Ciphertext[1]);
    printf("\n");
    SPN_Decrypt(Plaintext, Ciphertext, K);
    printf("\n明文为：\n");
    printf("%.16llx%.16llx\n",Plaintext[0],Plaintext[1]);
    //return 0;
}


void SPN_Ecrypt(unsigned long long *Plaintext, unsigned long long *Ciphertext, unsigned long long *K)
{
    unsigned int i;
    unsigned long long temp[2]={0};
    unsigned long long temp1[2]={0};
    KeyExpansion(Key_0[1],Key_0[0],K);
    copy(Plaintext[0],&temp[0]);
    copy(Plaintext[1], &temp[1]);
    for(i=0; i<Nr-2; i++)
    {
        SPN_XOR(temp,K,i);
        SPN_S(temp,temp1);
        SPN_P(temp1,temp);
    }
    SPN_XOR(temp,K,i);
    i++;
    SPN_S(temp,temp1);
    SPN_XOR(temp1,K,i);
    copy(temp1[0], &Ciphertext[0]);
    copy(temp1[1], &Ciphertext[1]);
}

void SPN_Decrypt(unsigned long long *Plaintext, unsigned long long *Ciphertext, unsigned long long *K)
{
    unsigned int i;
    unsigned long long temp[2]={0};
    unsigned long long temp1[2]={0};
    copy(Ciphertext[0], &temp[0]);
    copy(Ciphertext[1], &temp[1]);
    //printf("%llx %llx\n",temp[0],temp[1]);
    K_P(K);
    for(i=Nr-1; i>1; i--)
    {
        SPN_XOR(temp,K,i);
        SPN_S1(temp,temp1);
        SPN_P(temp1,temp);
    }
    SPN_XOR(temp,K,i);
    i--;
    SPN_S1(temp,temp1);
    SPN_XOR(temp1,K,i);
    //copy(temp1[0],&Plaintext[0]);
    //copy(temp1[1], &Plaintext[1]);
}

void K_P(unsigned long long *K)
{
    int i;
    unsigned long long key[16]={0};
    unsigned long long key1[16]={0};
    /*printf("K:\n");
    for(int k=0; k<11; k++)
    {
        printf("%.16llx ",K[2*k]);
        printf("%.16llx\n",K[2*k+1]);
    }*/
    for(i=1; i<Nr-1; i++)
    {
        sf_os1(K[2*i+1], K[2*i], key);
        /*printf("\nkey:\n");
        for(int k=0; k<16; k++)
        {
            printf("%.2llx",key[k]);
        }*/
        for(int j=0; j<16; j++)
        {
            key1[j] = key[P_Box[j]-1];
        }
        /*printf("\nkey1:\n");
        for(int k=0; k<16; k++)
        {
            printf("%.2llx",key1[k]);
        }
        printf("\n");*/
        K[2*i]=(key1[0]<<56)+(key1[1]<<48)+(key1[2]<<40)+(key1[3]<<32)+(key1[4]<<24)+(key1[5]<<16)+(key1[6]<<8)+key1[7];
        K[2*i+1]=(key1[8]<<56)+(key1[9]<<48)+(key1[10]<<40)+(key1[11]<<32)+(key1[12]<<24)+(key1[13]<<16)+(key1[14]<<8)+key1[15];
        //printf("\n\n");
    }
    /*printf("\n\n");
    for(i=0; i<11; i++)
    {
        printf("%.16llx %.16llx\n",K[2*i], K[2*i+1]);
    }*/
}

void copy(unsigned long long In,unsigned long long *Out)
{
    (*Out) = In;
}

void KeyExpansion(unsigned long long Key1, unsigned long long Key2, unsigned long long *K)
{
    int i;
    long long Rcon[11]={0,0x01000000,0x02000000,0x04000000,0x08000000,0x10000000,0x20000000,0x40000000,0x80000000,0x1B000000,0x36000000};
    unsigned long long w[44]={0};
    unsigned long long key[16]={0};
    unsigned long long t = 0;
    sf_os(Key1, Key2, key);//密钥分成16个分组
    printf("\n\n");
    for(i=0; i<=3; i++)
    {
        w[i]=(key[4*i]<<24)+(key[4*i+1]<<16)+(key[4*i+2]<<8)+(key[4*i+3]);
    }
    for(i=4; i<44; i++)
    {
        t = w[i-1];//主函数中定义
        if((i%4)==0)
        {
            t = SubWord(RotWord(t))^Rcon[i/4];
        }
        w[i]=w[i-4]^t;
    }
    for(i=0; i<11; i++)
    {
        K[2*i]=(w[4*i]<<32)+w[4*i+1];
        K[2*i+1]=(w[4*i+2]<<32)+w[4*i+3];
        //printf("%.16llx %.16llx\n",K[2*i], K[2*i+1]);
    }
}

void sf_os1(unsigned long long Key1, unsigned long long Key2, unsigned long long *key)
{
    int i;
    for(i=15; i>=8; i--)//低位
    {
        key[i]=Key1%256;
        Key1=Key1/256;
        //printf("%llx ",key[i]);
    }
    for(i=7; i>=0; i--)//高位
    {
        key[i]=Key2%256;
        Key2=Key2/256;
        //printf("%llx ",key[i]);
    }
}

void sf_os(unsigned long long Key1, unsigned long long Key2, unsigned long long *key)
{
    int i;
    for(i=15; i>=8; i--)//低位
    {
        key[i]=Key1%256;
        Key1=Key1/256;
        //printf("%llx ",key[i]);
    }
    for(i=7; i>=0; i--)//高位
    {
        key[i]=Key2%256;
        Key1=Key2/256;
        //printf("%llx ",key[i]);
    }
}

unsigned long long SubWord(unsigned long long Word)
{
    unsigned long long temp[4]={0};
    temp[0]=(Word&0xff000000)>>24;
    temp[1]=(Word&0x00ff0000)>>16;
    temp[2]=(Word&0x0000ff00)>>8;
    temp[3]=(Word&0x000000ff);
    temp[0]=S_Box[(temp[0]&0xf0)>>4][temp[0]&0x0f];
    temp[1]=S_Box[(temp[1]&0xf0)>>4][temp[1]&0x0f];
    temp[2]=S_Box[(temp[2]&0xf0)>>4][temp[2]&0x0f];
    temp[3]=S_Box[(temp[3]&0xf0)>>4][temp[3]&0x0f];
    Word=(temp[0]<<24)+(temp[1]<<16)+(temp[2]<<8)+temp[3];
    return Word;
}

unsigned long long RotWord(unsigned long long Word)
{
    unsigned long long temp[4]={0};
    temp[0]=(Word&0x00ff0000)>>16;
    temp[1]=(Word&0x0000ff00)>>8;
    temp[2]=(Word&0x000000ff);
    temp[3]=(Word&0xff000000)>>24;
    Word=(temp[0]<<24)+(temp[1]<<16)+(temp[2]<<8)+temp[3];
    return Word;
}

void SPN_S(unsigned long long *temp, unsigned long long *temp1)
{
    unsigned long long temp_1[16]={0};
    int i;
    sf_os(temp[1], temp[0], temp_1);
    for(i=0; i<16; i++)
    {
        temp_1[i]=S_Box[(temp_1[i]&0xf0)>>4][temp_1[i]&0x0f];
    }
    temp1[0]=(temp_1[0]<<56)+(temp_1[1]<<48)+(temp_1[2]<<40)+(temp_1[3]<<32)+(temp_1[4]<<24)+(temp_1[5]<<16)+(temp_1[6]<<8)+temp_1[7];
    temp1[1]=(temp_1[8]<<56)+(temp_1[9]<<48)+(temp_1[10]<<40)+(temp_1[11]<<32)+(temp_1[12]<<24)+(temp_1[13]<<16)+(temp_1[14]<<8)+temp_1[15];
}

void SPN_S1(unsigned long long *temp, unsigned long long *temp1)
{
    unsigned long long temp_1[16]={0};
    int i;
    sf_os(temp[1], temp[0], temp_1);
    for(i=0; i<16; i++)
    {
        temp_1[i]=S1_Box[(temp_1[i]&0xf0)>>4][temp_1[i]&0x0f];
    }
    temp1[0]=(temp_1[0]<<56)+(temp_1[1]<<48)+(temp_1[2]<<40)+(temp_1[3]<<32)+(temp_1[4]<<24)+(temp_1[5]<<16)+(temp_1[6]<<8)+temp_1[7];
    temp1[1]=(temp_1[8]<<56)+(temp_1[9]<<48)+(temp_1[10]<<40)+(temp_1[11]<<32)+(temp_1[12]<<24)+(temp_1[13]<<16)+(temp_1[14]<<8)+temp_1[15];
}

/*void PExpansion(unsigned long long *P, unsigned long long P_BOX[8][16])
{
    int i, j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<16; j++)
        {
            P_BOX[i][(j+2*i)%16] = P[(j+2*i)%16];
        }
    }
}*/

void SPN_P(unsigned long long *temp1,unsigned long long *temp)
{
    int i;
    //unsigned long long temp0[16]={0};
    unsigned long long temp_0[16]={0};
    unsigned long long temp_1[16]={0};
    sf_os(temp1[1], temp1[0], temp_0);
    for(i=0; i<16; i++)
    {
        temp_1[i] = temp_0[P_Box[i]-1];
    }
    temp[0]=(temp_1[0]<<56)+(temp_1[1]<<48)+(temp_1[2]<<40)+(temp_1[3]<<32)+(temp_1[4]<<24)+(temp_1[5]<<16)+(temp_1[6]<<8)+temp_1[7];
    temp[1]=(temp_1[8]<<56)+(temp_1[9]<<48)+(temp_1[10]<<40)+(temp_1[11]<<32)+(temp_1[12]<<24)+(temp_1[13]<<16)+(temp_1[14]<<8)+temp_1[15];
}

void SPN_XOR(unsigned long long *temp, unsigned long long *K, unsigned int i)
{
    temp[0] = temp[0]^K[2*i];
    temp[1] = temp[1]^K[2*i+1];
}
