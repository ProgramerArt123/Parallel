int func1(){
	return 99;
};

int func2(){
	return 1234;
};

void func3(){
	printf("I am func3!\n");
};

int main(){
		int x = 1 % 2 + 5 * 6 + 9 / 3;
		int y = 1 % 2 + 5 * (6 + 9) / 3;
		int z = x + y;
        printf("x=%d, y=%d, z=%d\n", x, y, z);
		z = 999;
		printf("z=%d\n", z);
		int w = func1();
		printf("w=%d\n", w);
		printf("w2=%d,w=%d\n", func1() + func2() * 3, w);
		w += 99;
		printf("w3=%d\n", w);
		func3();
		return 0;
};
