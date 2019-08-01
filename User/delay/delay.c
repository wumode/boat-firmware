void delay_us(unsigned long n){
	unsigned long j;
	while(n--){
		j = 8;
		while(j--);
	}
}

void delay_ms(unsigned long n){
	while(n--)
		delay_us(1100);
}