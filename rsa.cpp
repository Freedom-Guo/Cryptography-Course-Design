//
//  main.cpp
//  rsa_final
//
//  Created by 郭倜维 on 2018/10/10.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE
#pragma warning( disable : 4996)

#include <openssl/bn.h>
#include <stdio.h>
#include <time.h>
#include <openssl/rsa.h>
#include <stdlib.h>

#define T 1024
#define BN_RAND_TOP_ANY -1
#define BN_RAND_BOTTOM_ODD 1

BIGNUM* ExpBySquare(BIGNUM * m, BIGNUM * e, BIGNUM * n); //模重复平方算法
BIGNUM* ChineseReminder(BIGNUM* m, BIGNUM* e, BIGNUM* n, BIGNUM* p, BIGNUM* q); //中国剩余定理
BIGNUM* mgml(BIGNUM* y, BIGNUM* dd, BIGNUM* n);
BIGNUM* mgml1(BIGNUM* y, BIGNUM* dd, BIGNUM* n);
bool mod_reverse(BIGNUM*ret, const BIGNUM*a, const BIGNUM*n, BN_CTX *CTX); //求逆
bool Miller_Rabin(BIGNUM * bn);
BIGNUM* Mont_mul(BIGNUM* a, BIGNUM* b, BIGNUM* N); //蒙哥马利乘法

int main(void)
{
    unsigned long  t1, t2;
    int time1, time2, time3;
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *r = BN_new();
    BIGNUM *p_1 = BN_new();
    BIGNUM *q_1 = BN_new();
    BIGNUM *n = BN_new();
    BIGNUM *n_1 = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *dd = BN_new();
    BN_CTX *ctx = BN_CTX_new();//申请一个上下文结构
    
    do{
        BN_rand(p, 1024, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ODD);
    } while (!Miller_Rabin(p));
    do{
        BN_rand(q, 1024, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ODD);
    } while (!Miller_Rabin(q));
    
    BN_copy(p_1, p);
    BN_copy(q_1, q);
    BN_sub_word(p_1, 1);//p_1=p-1
    BN_sub_word(q_1, 1);//q_1=q-1
    BN_mul(n, p, q, ctx);//n=p*q
    BN_mul(n_1, p_1, q_1, ctx);//nn=p_1*q_1=(p-1)(q-1)
    int t = 0;
    while (!t)
    {
        BN_rand_range(e, n_1);//产生公钥e满足0<e<nn=(p-1)(q-1)
        BN_gcd(r, e, n_1, ctx);//r=gcd(e,nn)
        if (BN_is_one(r))  t = 1;
    }
    mod_reverse(d, e, n_1, ctx);//d是e的逆
    BN_copy(dd, d);
    char* cp = BN_bn2dec(p);//p转化为10进制字符串
    char* cq = BN_bn2dec(q);//q转化为10进制字符串
    char* cn = BN_bn2dec(n);
    char* ce = BN_bn2dec(e);
    char* cd = BN_bn2dec(d);
    printf("The public key is：\n");
    printf("n=\n%s\n\n", cn);
    printf("e=\n%s\n\n", ce);
    printf("The private key is：\n");
    printf("p=\n%s\n\n\n", cp);
    printf("q=\n%s\n\n\n", cq);
    printf("d=\n%s\n\n\n", cd);
    
    BIGNUM *x = BN_new();
    BIGNUM *y = BN_new();
    BIGNUM *dky1 = BN_new();
    BIGNUM *z = BN_new();
    BIGNUM *dky3 = BN_new();
    BIGNUM *dky4 = BN_new();
    BN_rand(x, 936, 0, 0);//产生一个伪随机数x,大小为936bits
    BN_mod_exp(y, x, e, n, ctx);//y=x^e mod n
    BN_mod_exp(dky1, y, d, n, ctx); //dky1=y^d mod n
    
    t1 = clock();
    z = ExpBySquare(y, d, n);
    t2 = clock();
    time1 = (double)(t2 - t1);
    
    t1 = clock();
    dky3 = ChineseReminder(y, dd, n, p, q);
    t2 = clock();
    time2 = (double)(t2 - t1);
    
    t1 = clock();
    dky4 = mgml(y, dd, n);
    //BN_add(dky4, dky4, x);
    t2 = clock();
    time3 = (double)(t2 - t1);
    
    char* cx = BN_bn2dec(x);//将x转为十进制
    char* cy = BN_bn2dec(y);
    char* cdky1 = BN_bn2dec(dky1);
    char* cdky2 = BN_bn2dec(z);
    char* cdky3 = BN_bn2dec(dky3);
    char* cdky4 = BN_bn2dec(dky4);
    printf("plaintext m=\n%s\n\n", cx);
    printf("RSA加密得到密文 y=\n%s\n\n", cy);
    printf("直接解密 dky=\n%s\n\n", cdky1);
    printf("利用模重复平方解密 dky=\n%s\n\n", cdky2);
    printf("时间为%dms\n\n", time1);
    printf("利用中国剩余定理解密 dky=\n%s\n\n", cdky3);
    printf("时间为%dms\n\n", time2);
    printf("利用蒙哥马利法解密 dky=\n%s\n\n", cdky4);
    printf("时间为%dms\n\n", time3);
    getchar();
}

/*辗转相除法求逆*/
bool mod_reverse(BIGNUM*ret, const BIGNUM*a, const BIGNUM*n, BN_CTX *CTX)
{
    BIGNUM *a0 = BN_new();
    BIGNUM *b0 = BN_new();
    BIGNUM *t0 = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *r = BN_new();
    BIGNUM *s0 = BN_new();
    BIGNUM *s = BN_new();
    BIGNUM *mid_1 = BN_new();
    BIGNUM *mid_2 = BN_new();
    BIGNUM*temp = BN_new();
    BIGNUM*zero = BN_new();
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *t = BN_new();
    
    BN_copy(a0, a);
    BN_copy(b0, n);
    BN_zero(t0);
    BN_zero(zero);
    BN_one(t);
    BN_one(s0);
    BN_zero(s);
    BN_div(q, r, a0, b0, ctx);//q=a0/b0,r=a0%b0
    while (!BN_is_zero(r))
    {
        BN_mul(mid_1, q, t, ctx);//mid_1=q*t
        BN_sub(temp, t0, mid_1);//temp=t0-mid_1
        BN_copy(t0, t);//t0=t
        BN_copy(t, temp);//t=temp
        BN_mul(mid_2, q, s, ctx); //mid_2=q*s
        BN_sub(temp, s0, mid_2);//temp=s0-mid_2
        BN_copy(s0, s);//s0=s
        BN_copy(s, temp);//s=temp
        BN_copy(a0, b0);//a0=b0
        BN_copy(b0, r);//b0=r
        BN_div(q, r, a0, b0, ctx);//q=a0/b0,r=a0%b0
    }
    BN_copy(r, b0);//r=b0
    while (BN_cmp(s, zero) == -1)//保证求得逆是正数
        BN_add(s, s, n);//s=s+n
    BN_mod(ret, s, n, ctx);//ret=s%n
    if (!BN_is_one(b0))
    {
        printf("b has no inverse modulo a");
        return false;
    }
    return true;
}

/*利用模重复平方法*/
BIGNUM* ExpBySquare(BIGNUM * m, BIGNUM * e, BIGNUM * n)
{
    BIGNUM* b = BN_new();
    BIGNUM* out = BN_new();
    BN_one(out);
    BN_copy(b, m);
    int k;
    k = BN_num_bits(e);
    BN_CTX * ctx = BN_CTX_new();
    for (int i = 0; i < k; i++)
    {
        if (BN_is_bit_set(e, i))
        {
            BN_mod_mul(out, out, b, n, ctx); // a = a*b; m = m^2
            BN_mod_mul(b, b, b, n, ctx);
        }
        else
        {
            BN_mod_mul(b, b, b, n, ctx);
        }
    }
    BN_free(b);
    BN_CTX_free(ctx);
    return out;
}
/*利用中国剩余定理*/
BIGNUM* ChineseReminder(BIGNUM* m, BIGNUM* e, BIGNUM* n, BIGNUM* p, BIGNUM* q)
{
     BN_CTX* ctx = BN_CTX_new();
     BIGNUM* result1 = BN_new();
     BIGNUM* result2 = BN_new();
     BIGNUM* x1 = BN_new();
     BIGNUM* x2 = BN_new();
     BIGNUM* p_n = BN_new();
     BIGNUM* q_n = BN_new();
     BIGNUM* out = BN_new();
     result1 = ExpBySquare(m, e, p);
     result2 = ExpBySquare(m, e, q);
     BN_mod_mul(x1, result1, q, n, ctx);
     BN_mod_mul(x2, result2, p, n, ctx);
     BN_mod_inverse(q_n, q, p, ctx);
     BN_mod_inverse(p_n, p, q, ctx);
     BN_mod_mul(x1, x1, q_n, n, ctx);
     BN_mod_mul(x2, x2, p_n, n, ctx);
     BN_mod_add(out, x1, x2, n, ctx);
     BN_free(x1);
     BN_free(x2);
     BN_free(p_n);
     BN_free(q_n);
     BN_free(result1);
     BN_free(result2);
     return out;
}

/*利用蒙哥马利法*/
BIGNUM* mgml1(BIGNUM* y, BIGNUM* dd, BIGNUM* n)
{
    BIGNUM *dky4 = BN_new();
    BN_one(dky4);
    BN_CTX *ctx = BN_CTX_new();//申请一个上下文结构
    //BN_CTX_init(ctx);//将所有项赋值为0
    //Mont_mul(y, dd, n);
    do
    {
        if (BN_is_odd(dd) == 1)//如果dd是1
        {
            BN_sub_word(dd, 1);//dd=dd-1
            Mont_mul(y, dd, n);
            BN_mod_mul(dky4, dky4, y, n, ctx);//dky4=(dky4*y)%n
        }
        else
        {
            BN_div_word(dd, 2); //dd=dd/2
            Mont_mul(y, dd, n);
            BN_mod_sqr(y, y, n, ctx);//y=(y*y)%n
        }
    } while (!BN_is_zero(dd));//dd=0时跳出循环
    return dky4;
}

/*蒙哥马利*/
BIGNUM* Mont_mul(BIGNUM* a, BIGNUM* b, BIGNUM* N)
{
    //BIGNUM *k = BN_new();
    BIGNUM *r = BN_new();
    BIGNUM *c = BN_new();
    BN_CTX *ctx = BN_CTX_new();//申请一个上下文结构
    //BN_CTX_init(ctx);//将所有项赋值为0
    int k;
    BN_mul(c, a, b, ctx);//c=a*b
    k = BN_num_bits(N);
    k += 1;
    BN_set_bit(r, k);//r=1<<k
    
    for (int i = 0; i < k-1; i++)
    {
        if (!(BN_is_odd(c)))
            BN_rshift(c, c, 1);//c右移一位
        else{
            BN_add(c, c, N);//c=c+N
            BN_rshift(c, c, 1);//c右移一位
        }
        if (BN_cmp(c, N) >= 0)
        {
            BN_sub(c, c, N);
        }
    }
    return c;
}

BIGNUM* mgml(BIGNUM* y, BIGNUM* dd, BIGNUM* n)
{
    BIGNUM *dky4 = BN_new();
    BN_one(dky4);
    BN_CTX *ctx = BN_CTX_new();//申请一个上下文结构
    //BN_CTX_init(ctx);//将所有项赋值为0
    do
    {
        if (BN_is_odd(dd) == 1)//如果dd是1
        {
            BN_sub_word(dd, 1);//dd=dd-1
            //Mont_mul(y, dd, n);
            BN_mod_mul(dky4, dky4, y, n, ctx);//dky4=(dky4*y)%n
        }
        else
        {
            BN_div_word(dd, 2); //dd=dd/2
            //Mont_mul(y, dd, n);
            BN_mod_sqr(y, y, n, ctx);//y=(y*y)%n
        }
    } while (!BN_is_zero(dd));//dd=0时跳出循环
    return dky4;
}

/*素性检测*/
bool Miller_Rabin(BIGNUM * bn)
{  //素性检测
    BIGNUM*n_plus_one = BN_new();
    BIGNUM* n = BN_new();
    BIGNUM* k = BN_new();
    BIGNUM* m = BN_new();
    BIGNUM* a = BN_new();
    BIGNUM* b = BN_new();
    BIGNUM* gcd = BN_new();
    BIGNUM* temp = BN_new();
    BIGNUM* two = BN_new();
    BN_CTX* ctx = BN_CTX_new();
    
    BN_copy(n, bn);
    BN_one(k);
    BN_set_word(temp, 2);
    BN_set_word(two, 2);
    BN_sub(n_plus_one, n, BN_value_one());
    BN_gcd(gcd, n_plus_one, temp, ctx);
    while (BN_cmp(gcd, temp) == 0)
    {
        BN_mul_word(temp, 2);
        BN_gcd(gcd, n_plus_one, temp, ctx);
        BN_add_word(k, 1);
    }
    BN_sub_word(k, 1);//得到k-1
    //printf("k-1:%s\n\n", BN_bn2dec(k));
    //出来以后gcd中是2^k
    BN_div(m, NULL, n_plus_one, gcd, ctx);
    BN_rand_range(a, n);//产生随机数a
    BN_mod_exp(b, a, m, n, ctx);
    if (BN_cmp(b, BN_value_one()) == 0)
    {
        return true;
    }
    do
    {
        if (BN_cmp(b, n_plus_one) == 0)
        {
            return true;
        }
        else
        {
            BN_mod_exp(temp, b, two, n, ctx);
            BN_copy(b, temp);
            BN_sub_word(k, 1);
        }
    }
     while (BN_is_zero(k) != 1);
     return false;
     /*BIGNUM *bn_m = BN_new();
     BIGNUM* b = BN_new();
     BIGNUM* b_2 = BN_new();
     BIGNUM* a = BN_new();
     BN_CTX* ctx = BN_CTX_new();
     BIGNUM* _n = BN_new();
     BIGNUM* m = BN_new();
     BN_zero(bn_m);
     BN_add_word(bn_m, 2);
     if (!BN_cmp(bn, bn_m)) //bn是否为2，2是素数，是则返回0；
     {
     BN_free(bn_m);
     return true;
     }
     if (!BN_cmp(bn, BN_value_one()) || !BN_is_odd(bn)) //bn是否为1或者偶数，是则不是素数
     {
     BN_free(bn_m);
     return false;
     }
     BN_free(bn_m);
     BN_copy(m, bn);
     BN_sub_word(m, 1); //u=n-1;
     int k;
     for (k = 0; !BN_is_bit_set(m, 0); k++) //
     {
     BN_rshift1(m, m); //求n-1=(2^k)*m的k值和m值
     }
     BN_copy(_n, bn);
     BN_sub_word(_n, 1); //_n=bn-1
    
     BN_rand_range(a,bn); //随机选取整数a，a<bn
     for (int j = 0; j < k; j++) //j=0~k-1
     {
     BN_mod_mul(b_2, b, b, bn, ctx); //b_2=b^2 % bn
     if (!BN_cmp(b_2, BN_value_one()) && BN_cmp(b, BN_value_one()) && BN_cmp(b, _n))
     {//b^2 == 1, b != 1, b != n-1;
     BN_free(a); //释放
     BN_free(m);
     BN_free(b);
     BN_free(b_2);
     BN_free(_n);
     BN_CTX_free(ctx);
     return false;
     }
     BN_copy(b, b_2);
     }
     if (BN_cmp(b_2, BN_value_one())) //a^(2^k * m) != 1;
     {
     BN_free(a);
     BN_free(m);
     BN_free(b);
     BN_free(b_2);
     BN_free(_n);
     BN_CTX_free(ctx);
     return false;
     }
     BN_free(a);
     BN_free(m);
     BN_free(b);
     BN_free(b_2);
     BN_free(_n);
     BN_CTX_free(ctx);
     return true;*/
}
