
extern void delay_ms(uint t){
  uint i,j;
  for( i = 0 ; i < t ; i++)
    for( j = 0 ; j < 1000 ; j++) ; 
}
