#define bus0  0 
#define bus1  1
#define bus2  2
#define bus3  3
#define bus4  4
#define bus5  5
#define bus6  6
#define bus7  7

#define rdec1 5 
#define rdec2 6
#define rdec3 7

#define clock 8
#define dec1 9
#define dec2 10
#define dec3 11

int outpin;
byte T[] = {B00000000,B00000000,B11100111,B11100111,B11100111,B11100111,B11100111,B11100111};
byte H[] = {B00111100,B00111100,B00111100,B00000000,B00000000,B00111100,B00111100,B00111100};
byte E[] = {B10000001,B11111101,B11111101,B10000001,B10000001,B11111101,B11111101,B10000001};

byte rowCount = B00000000;
byte buffer = B00111100; //do not initialize except for debuggint purposes (REMOVE AFTER DONE DEBUGGING)
int debug = 0;

void setup() {
  // use a for loop to initialize each pin as an output:
  for (outpin = 0; outpin <= 11; outpin++) { //make each column HIGH so no LED will eb turned on 
    pinMode(outpin, OUTPUT);
    //digitalWrite(outpin, LOW); // initialize all BUS ports
  }
  DDRD = B11111111;
  //Serial.begin(9600);
  digitalWrite(clock, HIGH);
}  // setup

void loop() 
{
    int x = 0;
    rowCount = B00000000;
  
    for(x = 0; x <=7; x++)
    {
      
      
      if(H[x] == buffer)
      {
        //ROW set
        PORTB = B0001000;
        PORTD = rowCount;;
        PORTB |= B0000001;
        
        delay (debug);
      }
      
      if(H[x] != buffer)
      {
        //set buffer
        buffer = H[x];
        
        //This is beautiful and is stolen from StackOverflow: http://stackoverflow.com/questions/8639396/verify-if-a-binary-array-is-a-subset-of-another-one-in-c
        
        /* The operation is performed with three bitwise operations, resulting in a
         * sequence of bits that will be equal to zero if set_a is a subset of
         * set_b. As a bonus, the positions where the sets differ will be
         * available in the resulting sequence, and thus the number of differing
         * positions can be obtained by counting the number of bits set (for exemple,
         * with __builtin_popcount in GCC).
         *
         *   Exemple (TRUE):              Exemple (FALSE):
         *   ================             ================
         *   set_a   00010011             set_a   00001011
         *   set_b   00110011             set_b   00110011
         *   ----------------             ----------------
         *   XOR     00100000             XOR     00111000
         *   set_b   00110011             set_b   00110011
         *   ----------------             ----------------
         *   OR      00110011             OR      00111011
         *   set_b   00110011             set_b   00110011
         *   ----------------             ----------------
         *   XOR     00000000             XOR     00001000
         */
         
         if( ( ( (~H[x-1] ^ ~H[x]) | ~H[x]) ^ ~H[x]) != 00000000)
         {
           //blank COL
          PORTB = B0000100;
          PORTD = B11111111;

          PORTB |= B0000001;
        
          delay (debug);
         }  
       
        //ROW set
        PORTB = B0001000;
        PORTD = rowCount;

        PORTB |= B0000001;
        
        delay (debug); 
        
        //COL set
        PORTB = B0000100;
        PORTD = buffer;
        PORTB |= B0000001;
        
        delay (debug);
        
      }
      
//      //COL set
//      PORTB = B0000100;
//      PORTD = H[x];
//
//      PORTB |= B0000001;
//      
//      //ROW set
//      PORTB = B0001000;
//      PORTD = rowCount;
//      
//      PORTB |= B0000001;
//      
      
      delay(0);
      rowCount += 32;
    }
    
//    rowCount = B00000000;
//    
//    PORTB = B0001000;
//    PORTD = rowCount;
//      
//    PORTB |= B0000001;
  
}

