#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>

unsigned long long gcd( unsigned long long a, unsigned long long b )
{
  if (a==0) return b;
  return gcd(b%a, a);
}

unsigned long long extended_gcd(unsigned long long a, unsigned long long b)
{
    unsigned long long x = 0;
    unsigned long long lastx = 1;
    unsigned long long y = 1;
    unsigned long long lasty = 0;
    unsigned long long temp, quotient;
    
    
    while(b != 0 || lasty < 0) {
        temp = b;
        quotient = a / b;
        b = a % b;
        a = temp;
        temp = x;
        x = lastx-quotient*x;
        lastx = temp;
        temp = y;
        y = lasty-quotient*y;
        lasty = temp;     
   }       
 
   return lasty;
        
}
int main() {
	unsigned long long primeNos[210] = {3, 5, 17, 27, 59, 69, 129, 143, 153, 185, //20
	9, 19, 21, 55, 61, 69, 105, 111, 121, 129,	//21
	3, 17, 27, 33, 57, 87, 105, 113, 117, 123, 	//22
	15, 21, 27, 37, 61, 69, 135, 147, 157, 159,	//23
	3, 17, 33, 63, 75, 77, 89, 95, 117, 167,	//24
	39, 49, 61, 85, 91, 115, 141, 159, 165, 183,	//25
	5, 27, 45, 87, 101, 107, 111, 117, 125, 135,	//26
	39, 79, 111, 115, 135, 187, 199, 219, 231, 235,	//27
	57, 89, 95, 119, 125, 143, 165, 183, 213, 273,	//28
	3, 33, 43, 63, 73, 75, 93, 99, 121, 133,	//29
	35, 41, 83, 101, 105, 107, 135, 153, 161, 173,	//30
	1, 19, 61, 69, 85, 99, 105, 151, 159, 171,	//31
	5, 17, 65, 99, 107, 135, 153, 185, 209, 267, //32
	9, 25, 49, 79, 105, 285, 301, 303, 321, 355,
	41, 77, 113, 131, 143, 165, 185, 207, 227, 281,
	31, 49, 61, 69, 79, 121, 141, 247, 309, 325, //35
	5, 17, 23, 65, 117, 137, 159, 173, 189, 233,
	25, 31, 45, 69, 123, 141, 199, 201, 351, 375,
	45, 87, 107, 131, 153, 185, 191, 227, 231, 257,
	7, 19, 67, 91, 135, 165, 219, 231, 241, 301,
	87, 167, 195, 203, 213, 285, 293, 299, 389, 437};	//40
	
	unsigned long long i, m, p_len, q_len, n_len, phi_len, prand, qrand, p, d, q, e, plainT, cypherT, phi, temp;
	unsigned char text[1000], cypher_text[1000], plain_text[1000];

	for(i=0; i<210; i++){
		primeNos[i] = (unsigned long long)pow(2,(20+(i/10))) - primeNos[i];
	}
	
	srand((unsigned)time(NULL));  
	prand = rand()%210;
	p = primeNos[prand];
   do {
	   qrand = rand()%210;
	   q = primeNos[qrand];
	} while (p == q || (qrand/10 != prand/10));

	printf("\np = %llu\n", p);
	printf("q = %llu\n", q);
	printf("N = %llu\n", p*q);

	phi = (p-1)*(q-1);
	e = 65537;

	d = extended_gcd(phi, e);
	printf("e = %llu\n", e);
	printf("d = %llu\n", d);
	
	printf("Please enter plain text: ");
	gets(text);
	text[strlen(text)] = '\0';	

	//encrypt
	i = 0;
	while(text[i] != '\0'){
	cypherT = 1;
	plainT = text[i];
	
	while(e > 0){
		if(e % 2 == 1){
			cypherT = (cypherT * plainT) % (p*q);
		}	
		e = e >> 1;
		plainT = (plainT * plainT) % (p*q);
	}
	cypher_text[i] = cypherT;
	
	
	//decrypt
	plainT = 1;
	while(d > 0){
		if(d % 2 == 1){
			plainT = (plainT * cypherT) % (p*q);
		}	
		d = d >> 1;
		cypherT = (cypherT * cypherT) % (p*q);
	}
	
	plain_text[i] = plainT;
	
	i++;
	}
	cypher_text[i] = '\0';plain_text[i] = '\0';
	printf("Encrypted value is: %s\n", cypher_text);
	printf("Decrypted value is: %s\n", plain_text);
	return 0;	
}
