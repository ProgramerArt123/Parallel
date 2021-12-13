def function(a,b,c,d){
	 printf("a:%d,d:%d\n", a, d);
     return 123;
};

def main(){
        begin = clock();
        for(2){
                a = 1;
                b = 2;
                c = 3;
                d = 4;
                
                e = 5;
                f = 6;
                g = 7;
                h = 8;

                i = a * e;
                j = b * f;
                k = c * g;
                l = d * h;

				function(i,j,k,l);
        };
        finish = clock();
        t = finish - begin;
        printf("time:%d\n", t);
};
