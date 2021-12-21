int function(a,b,c,d,e,f,g,h,i){
	 printf("a:%d,d:%d\n", a, i);
     return 123;
};

int main(){
        begin = clock();
        for(9){
                a = 5;
                b = 6;
                c = 7;
                d = 8;
                
                e = 4;
                f = 2;
                g = 3;
                h = 5;

                i = a % e;
                j = b % f;
                k = c % g;
                l = d % h;

				function(i,j,k,l,1,3,99,999,9999);
        };
        finish = clock();
        t = finish - begin;
        printf("time:%d,%d\n", t, t);
		return 0;
};
