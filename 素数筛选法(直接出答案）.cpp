#include<iostream>
using namespace std;
#define MAX_NUM 100
char isPrime[MAX_NUM + 10];//最终如果isPrime[i]为1，则i表示素数
int main() {
	//开始假设所有的数都是素数
	for (int i = 2; i <= MAX_NUM; ++i)
		isPrime[i] = 1;
	//每一次都将一个素数的倍数标记为非素数
	for (int i = 2; i <= MAX_NUM; ++ i) {
		if(isPrime[i])//标记所有素数
			//将素数i的倍数标记为非素数
			for(int j=2*i;j<=MAX_NUM;j+=i)
				isPrime[j]=0;
		}
	for (int i = 2; i <= MAX_NUM; ++i)
		if (isPrime[i])
			cout << i << endl;

	return 0;
}