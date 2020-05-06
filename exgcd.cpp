#include <iostream>


static int iter = 0;

int GCDRecursive(int a, int b) {
	if (b == 0)  //递归函数的边界条件
    {
        return a;
    }

	return GCDRecursive(b, a % b);
}

int exgcd(int a, int b, int &x, int &y)
{
    printf("start iter#%d  a:%2d b:%2d x:%2d y:%2d\n", iter++, a, b, x, y);

    if(b == 0)  //递归函数的边界条件
    {
        x = 1;  //其中一组解
        y = 0;
        return a;
    }

    int gcd = exgcd(b, a%b, x, y);  //先找到边界条件然后再反推回去求解
    
    int t = x;
    x = y;
    y = t - (a/b)*x; 
    printf("exit  iter#%d  a:%2d b:%2d x:%2d y:%2d\n", --iter, a, b, x, y);

    return gcd;
}

int reverse_unit(int a, int b) {
	int x, y;
	int gcd = exgcd(a, b, x, y);
	if (gcd != 1) {   //模逆元存在的充要条件，ab互素（gcd为1）
 		printf("reverse unit does not exist.\n");
		return -1;
	}
    printf("reverse_unit of %d, %d : %d \n", a,b, (x % b + b) % b);
	return (x % b + b) % b;  //最小正整数解
}

int get_crt(int *a, int *m, int len)//m-模数, a-余数
{
    int r, y;

    int N = 1; //初始化所有除数的最小公倍数
    for(int i = 0; i < len; i++)
    {
        N *= m[i];
    }

    int X = 0;
    for(int i = 0; i < len; i++)
    {
        
        int Mi = N / m[i];  //求解第i组同余等式时。同时把余数当系数抽取出来，转换为求模逆元的a值, m[i]即为b值，
        int gcd = exgcd(Mi, m[i], r, y);
        
        X += a[i] * Mi * r;  //r即为ax+by=1（ax≡1(mod b)）的一个解

        printf("a[i] = %2d, Mi = %2d, r = %2d, iter###%d, X = %d\n",  a[i], Mi, r, i, X);
    }

    return X % N; //同余情况下， 解唯一。  X,Y都是解的话，X-Y也是解

}

int main(int argc, char *argv[])
{
    if(argc != 3) return 0;
    
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    if(a<b)
    {
        int t = a;
        a = b;
        b = t;
    }

    // int x , y;

    // int navie_gcd = GCDRecursive(a, b);
    // printf("GCD value of %d and %d:%d\n", a, b, navie_gcd);

    // //int gcd = exgcd(a, b, x, y);

    // //printf("%d * %d + %d * %d = %d\n", a, x, b, y, gcd);

    // int Reseve_uint = reverse_unit(a, b);

    // printf("%d * %d = 1 (mod %d) \n", a, Reseve_uint, b);

    int mi[3] = {3, 5, 7};
    int ai[3] = {2, 3, 2};

    int X = get_crt(ai, mi, 3);

    printf("crt = %d \n", X);

    return 0;
}
