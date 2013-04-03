#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<string.h>
#include<time.h>

unsigned int gcd( unsigned int a, unsigned int b )
{
  if (a==0) return b;
  return gcd(b%a, a);
}

unsigned int main() {
	unsigned int primeNos[40] = {5, 15, 17, 23, 27, 29, 33, 45, 57, 59,
	3, 9, 13, 21, 25, 33, 45, 49, 51, 55,
	3, 5, 11, 15, 27, 33, 41, 47, 53, 57,
	9, 19, 21, 31, 37, 45, 49, 51, 55, 61};

	unsigned int p, q, i, prand, qrand, phi, e, d=0;
	unsigned int plainT, cypherT = 1;
	
	for(i=0; i<40; i++){
		primeNos[i] = (unsigned int)pow(2,(8+(i/10))) - primeNos[i];
	}
	
	srand((unsigned)time(NULL));  
   
	
	i=0; e = 2;
	do{
		prand = rand()%40;
  		p = primeNos[prand];
  		 do {
		   qrand = rand()%40;
		   q = primeNos[qrand];
		} while (p == q || (qrand/10 != prand/10));
	
	phi = (p-1)*(q-1);
	e++; d= 1;

	//generate e
	while(gcd(phi, e) != 1){	
		e++;
	}
	
	//generate d
   do{
		prand = (d*e)%phi;
		d++;
		}while(prand != 1);
	d--;

	} while( d > 100000 || p*q > 100000);
	
	
	printf("p = %d\n", p);
	printf("q = %d\n", q);
	printf("N = %d\n", p*q);

	printf("phi = %d\n", phi);
	printf("e = %d\n", e);
	printf("d = %d\n", d);
	
	printf("Please enter a number: ");
	scanf("%llu", &plainT);
	
	
	//encrypt
	cypherT = 1;
	prand = plainT;
	
	while(e > 0){
		if(e % 2 == 1){
			cypherT = (cypherT * plainT) % (p*q);
		}	
		e = e >> 1;
		plainT = (plainT * plainT) % (p*q);
	}
	printf("Encrypted value is: %llu\n", cypherT);
	
	//decrypt
	plainT = 1;
	while(d > 0){
		if(d % 2 == 1){
			plainT = (plainT * cypherT) % (p*q);
		}	
		d = d >> 1;
		cypherT = (cypherT * cypherT) % (p*q);
	}
	printf("Decrypted value is: %llu\n", plainT);
	
		
	return 0;	
}

