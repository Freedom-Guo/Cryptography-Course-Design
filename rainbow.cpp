//
//  main.cpp
//  rainbow
//
//  Created by 郭倜维 on 2018/10/15.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <openssl/md5.h>
#include <time.h>
#include <stdint.h>

#define MAX 36
#define Len 5000 //记录 LEN 条链
#define L_Len 1000000 //链长

typedef struct RainBow{
    char first[7];
    char last[7];
    struct RainBow* next;
}rainbow;

unsigned char Space[] = "0123456789abcdefghijklmnopqrstuvwxyz"; //字符串空间大小
int success = 0;
int fail = 0;


//采用MD5进行哈希运算
void MD5(unsigned char * output, unsigned char * input)
{
    MD5_CTX ctx;
    unsigned char out[16];
    //int i = 0;
    memset(out, 0, sizeof(out));
    MD5_Init(&ctx);
    MD5_Update(&ctx, input, 6);
    MD5_Final(out, &ctx);
    for (int i = 0; i < 16; i++)
    {
        output[i] = out[i];
    }
    output[16] = '\0';
}

//衰减函数R7
void ReductionFunction(unsigned char * pwd, unsigned char *hash, int n_redux)
{
    
    /* Convert the hash to four unsigned 32-bit integers. */
    
    uint32_t idx[4];//每个是32bit
    
    idx[0] = (*(uint32_t*)hash) ^ n_redux;
    idx[1] = (*(uint32_t*)(hash + 4));
    idx[2] = (*(uint32_t*)(hash + 8));
    idx[3] = (*(uint32_t*)(hash + 12));
    
    /* Compute the password */
    
    idx[0] %= MAX*MAX;
    idx[1] %= MAX*MAX;
    idx[2] %= MAX*MAX;
    idx[3] %= MAX*MAX;
    
    pwd[0] = Space[idx[0] / MAX];
    pwd[1] = Space[idx[0] % MAX];
    pwd[2] = Space[idx[1] / MAX];
    pwd[3] = Space[idx[2] % MAX];
    pwd[4] = Space[idx[3] / MAX];
    pwd[5] = Space[idx[3] % MAX];
    
    /* Finish the password. */
    
    pwd[6] = '\0';
    
}

//彩虹表生成函数
void GenerateRainbow()
{
    FILE *fp;
    int i, j;
    unsigned char temp1[7], temp2[17];
    srand((unsigned)time(NULL));
    printf("The rainbow table is generating...\n");
    if ((fp = fopen("rainbow.txt", "w")) == NULL)
    {
        printf("Open fail! \n");
        exit(1);
    }
    fclose(fp);
    if ((fp = fopen("rainbow.txt", "a")) == NULL)
    {
        printf("Open fail! \n");
        exit(1);
    }
    for (i = 0; i < L_Len; i++)
    {
        for (j = 0; j < 6; j++)
            temp1[j] = Space[rand() % MAX];
        temp1[6] = '\0';
        fprintf(fp, "%s\t", temp1); //sprintf
        for (j = 0; j < Len; j++)
        {
            MD5(temp2, temp1);
            ReductionFunction(temp1, temp2, j);
        }
        fprintf(fp, "%s\n", temp1);
    }
    fclose(fp);
    fp = NULL;
    printf("Successful！\n\n");
}

void find_plain(unsigned char* after_hash)
{
    FILE *fp;
    rainbow* Chb = (rainbow*)malloc(sizeof(rainbow));
    rainbow* temp = Chb;
    unsigned char Start[7], End[7];
    char temp1[7], temp2[17];
    if ((fp = fopen("//Users//hustguo//Desktop//U201614848_郭倜维_密码学课设//rainbow.txt", "r")) == NULL)
    {
        printf("Open fail! \n");
        exit(1);
    }
    while (fscanf(fp, "%s", Start)==1)
    {
        getc(fp);
        fscanf(fp, "%s", End);
        getc(fp);
        temp->next = (rainbow*)malloc(sizeof(rainbow));
        strcpy(temp->next->first, (char*)Start);
        strcpy(temp->next->last, (char*)End);
        temp = temp->next;
    }
    temp->next = NULL;
    fclose(fp);
    fp = NULL;
    for (int j = Len-1; j >=0 ; j--)
    {
        strcpy(temp2, (char*)after_hash);
        for (int k = 1; k < Len - j; k++)
        {
            ReductionFunction((unsigned char*)temp1, (unsigned char*)temp2, j-1+k);
            MD5((unsigned char*)temp2, (unsigned char*)temp1);
        }
        ReductionFunction((unsigned char*)temp1, (unsigned char*)temp2, Len-1);
        temp = Chb->next;
        int k = 1;
        while (temp)
        {
            if (strcmp(temp1, temp->last) == 0)
            {
                char plaintext[7], ciphertext[17];
                strcpy(plaintext, temp->first);
                for (int i = 0; i < j; i++)
                {
                    //printf("第%d个结点：", i+1);
                    MD5((unsigned char*)ciphertext, (unsigned char*)plaintext);
                    //printf("hash后=%s\n", cypher);
                    ReductionFunction((unsigned char*)plaintext, (unsigned char*)ciphertext, i);
                    //printf("reduce后=%s\n\n", plain);
                }
                MD5((unsigned char*)ciphertext, (unsigned char*)plaintext);
                if (strcmp(ciphertext, (char*)after_hash) == 0)
                {
                    printf("Find the plaintext：%s\n\n", plaintext);
                    free(Chb);
                    Chb = NULL;
                    success++;
                    return;
                }
            }
            temp = temp->next;
            k++;
        }
        
    }
    fail++;
    printf("Don't find！\n\n");
    free(Chb);
    Chb = NULL;
}

int main(void)
{
     //生成彩虹表并输入字符串测试
     GenerateRainbow();
     printf("The rainbow table is generating...\n");
     printf("The rainbow table is generated successfully!\n\n");
     unsigned char plaintext[7], digest[17];
     printf("Please input six-bit string：\n");
     scanf("%s", plaintext);
     MD5(digest, plaintext);
     printf("The hash is：%s\n", digest);
     find_plain(digest);
    
    //测试程序
    for (int i = 0; i < 25; i++)
    {
        unsigned char plaintext[7], digest[17];
        for (int j = 0; j < 6; j++)
            plaintext[j] = Space[rand() % MAX];
        plaintext[6] = '\0';
        MD5(digest, plaintext);
        printf("Plaintext：%s, HASH：%s\n", plaintext, digest);
        find_plain(digest);
    }
    printf("The success rate：%lf\n", success / 25.0);
    
    system("pause");
    return 0;
}
