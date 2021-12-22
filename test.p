int function(int a, int b, int c, int d, int e, int f, int g, int h, int i){
	 printf("a:%d,d:%d\n", a, i);
     return 123;
};

int main(){
        int begin = clock();
        for(9){
                int a = 5;
                int b = 6;
                int c = 7;
                int d = 8;
                
                int e = 4;
                int f = 2;
                int g = 3;
                int h = 5;

                int i = a % e;
                int j = b % f;
                int k = c % g;
                int l = d % h;

				function(i,j,k,l,1,3,99,999,9999);
        };
        int finish = clock();
        int t = finish - begin;
        printf("time:%d,%d\n", t, t);
		int x;
		return 0;
};
