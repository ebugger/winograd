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
        x = 1;
        y = 0;
        return a;
    }

    int gcd = exgcd(b, a%b, x, y);
    
    int t = x;
    x = y;
    y = t - (a/b)*x; 
    printf("exit  iter#%d  a:%2d b:%2d x:%2d y:%2d\n", --iter, a, b, x, y);

    return gcd;
}

int reverse_unit(int a, int b) {
	int x, y;
	int gcd = exgcd(a, b, x, y);
	if (gcd != 1) {
 		printf("reverse unit does not exist.\n");
		return -1;
	}
    printf("reverse_unit of %d, %d : %d \n", a,b, (x % b + b) % b);
	return (x % b + b) % b;  //最小正整数解
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

    int x , y;

    int navie_gcd = GCDRecursive(a, b);
    printf("GCD value of %d and %d:%d\n", a, b, navie_gcd);

    //int gcd = exgcd(a, b, x, y);

    //printf("%d * %d + %d * %d = %d\n", a, x, b, y, gcd);

    int Reseve_uint = reverse_unit(a, b);

    printf("%d * %d = 1 (mod %d) \n", a, Reseve_uint, b);


    return 0;
}
