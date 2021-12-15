def function(a,b,c,d){
	 printf("a:%d,d:%d\n", a, d);
     return 123;
};

def main(){
        begin = clock();
        for(2){
                a = 5;
                b = 6;
                c = 7;
                d = 8;
                
                e = 1;
                f = 2;
                g = 3;
                h = 4;

                i = a / e;
                j = b / f;
                k = c / g;
                l = d / h;

				function(i,j,k,l);
        };
        finish = clock();
        t = finish - begin;
        printf("time:%d\n", t);
};
