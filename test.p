int main(){
		int x = 1 % 2 + 5 * 6 + 9 / 3;
		int y = 1 % 2 + 5 * (6 + 9) / 3;
		int z = x + y;
        printf("x=%d, y=%d, z=%d\n", x, y, z);
		z = 999;
		printf("z=%d\n", z);
		return 0;
};
