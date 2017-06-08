#include <stdio.h>
#define IN 		1
#define OUT		0

main(){
	int c, nl, nw, nc, state;
	state = OUT;
	nl = nw = nc = 0;
	while((c=getchar()) != EOF){
		nc++;		
		if(c == '\n')
			nl++;

		if(c == ' ' || c == '\t' || c == '\n')
			state = OUT;
		else if(state == OUT){
			nw++;
			state = IN;
		}
	}
	int max_high = 0;
	if(nl>nw && nl>nc)
		max_high =  nl;
	else if(nw > nl && nw>nc)
		max_high = nw;
	else
		max_high = nc;
	
	int i;
	for(i=max_high;i > 0;i--){
		if(nl >= i)
			printf("%5d ** ",i);
		else
			printf("%5d    ",i);
		
		if(nw >= i)
			printf(" ** ");
		else
			printf("    ");
		
		if(nc >= i)
			printf(" ** \n");
		else
			printf("    \n");
	}
	printf("     ------------\n");
	printf("      nl  nw  nc \n");	
}
