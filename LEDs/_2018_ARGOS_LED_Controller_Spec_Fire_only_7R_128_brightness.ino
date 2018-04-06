// 2018 Argos LED Controller i2c


// Receives Game Status from Robo RIO over i2c and controls LEDs

//Libraries

#include <FastLED.h>
//#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <avr/pgmspace.h>
#include <ffft.h>
#include <math.h>
#include <Wire.h>

//FASTLED_USING_NAMESPACE

//LED Strip Size
#define NUM_LEDS_SIDES 144// Number of LEDs in strip
#define NUM_LEDS_FNB 9// Number of LEDs in strip

// control the LEDs pins:
#define DATAPIN1    51
#define CLOCKPIN1   53
#define DATAPIN2    5
#define CLOCKPIN2   6
//#define DATAPIN3    7
//#define CLOCKPIN3   8
//#define DATAPIN4    9
//#define CLOCKPIN4   10

//FastLED setup
#define COLOR_ORDER BGR
#define CHIPSET APA102
#define BRIGHTNESS  128
#define FRAMES_PER_SECOND 60


CRGB leds_sides[NUM_LEDS_SIDES]; //setup array for side leds
CRGB leds_fnb[NUM_LEDS_FNB]; //setup array for turret leds
//CRGB leds_strip3[NUM_LEDS_3];
//CRGB leds_strip4[NUM_LEDS_4]; //setup array for side leds

//Spectrum Analyzer Setup
#define ADC_CHANNEL 0
int16_t       capture[FFT_N];    // Audio capture buffer
complex_t     bfly_buff[FFT_N];  // FFT "butterfly" buffer
uint16_t      spectrum[FFT_N/2]; // Spectrum output buffer
volatile byte samplePos = 0;     // Buffer position counter

byte
  peak[8],      // Peak level of each column; used for falling dots
  dotCount = 0, // Frame counter for delaying dot-falling speed
  colCount = 0; // Frame counter for storing past column data
int
  col[8][10],   // Column levels for the prior 10 frames
  minLvlAvg[8], // For dynamic adjustment of low & high ends of graph,
  maxLvlAvg[8], // pseudo rolling averages for the prior few frames.
  colDiv[8];    // Used when filtering FFT output to 8 columns

/*
These tables were arrived at through testing, modeling and trial and error,
exposing the unit to assorted music and sounds.  But there's no One Perfect
EQ Setting to Rule Them All, and the graph may respond better to some
inputs than others.  The software works at making the graph interesting,
but some columns will always be less lively than others, especially
comparing live speech against ambient music of varying genres.
*/
static const uint8_t PROGMEM
  // This is low-level noise that's subtracted from each FFT output column:
  noise[64]={ 8,6,6,5,3,4,4,4,3,4,4,3,2,3,3,4,
              2,1,2,1,3,2,3,2,1,2,3,1,2,3,4,4,
              3,2,2,2,2,2,2,1,3,2,2,2,2,2,2,2,
              2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,4 },
  // These are scaling quotients for each FFT output column, sort of a
  // graphic EQ in reverse.  Most music is pretty heavy at the bass end.
  eq[64]={
    255, 175,218,225,220,198,147, 99, 68, 47, 33, 22, 14,  8,  4,  2,
      0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
  // When filtering down to 8 columns, these tables contain indexes
  // and weightings of the FFT spectrum output values to use.  Not all
  // buckets are used -- the bottom-most and several at the top are
  // either noisy or out of range or generally not good for a graph.
  col0data[] = {  2,  1,  // # of spectrum bins to merge, index of first
    111,   8 },           // Weights for each bin
  col1data[] = {  4,  1,  // 4 bins, starting at index 1
     19, 186,  38,   2 }, // Weights for 4 bins.  Got it now?
  col2data[] = {  5,  2,
     11, 156, 118,  16,   1 },
  col3data[] = {  8,  3,
      5,  55, 165, 164,  71,  18,   4,   1 },
  col4data[] = { 11,  5,
      3,  24,  89, 169, 178, 118,  54,  20,   6,   2,   1 },
  col5data[] = { 17,  7,
      2,   9,  29,  70, 125, 172, 185, 162, 118, 74,
     41,  21,  10,   5,   2,   1,   1 },
  col6data[] = { 25, 11,
      1,   4,  11,  25,  49,  83, 121, 156, 180, 185,
    174, 149, 118,  87,  60,  40,  25,  16,  10,   6,
      4,   2,   1,   1,   1 },
  col7data[] = { 37, 16,
      1,   2,   5,  10,  18,  30,  46,  67,  92, 118,
    143, 164, 179, 185, 184, 174, 158, 139, 118,  97,
     77,  60,  45,  34,  25,  18,  13,   9,   7,   5,
      3,   2,   2,   1,   1,   1,   1 },
  // And then this points to the start of the data for each of the columns:
  * const colData[]  = {
    col0data, col1data, col2data, col3data,
    col4data, col5data, col6data, col7data };



//Variables Communicated over I2C
char gameMode = 'D';
char autonMode = 'L';
char win = 'C';
char alliance = 'R';
byte armPos = 0;
char intake = 'P';
char climb = 'J';
int armPosLED = 0;

//Color Definitions
uint32_t auto_1 = CRGB::White; //white
uint32_t auto_2 = CRGB::Yellow; //Yellow
uint32_t auto_3 = CRGB::Green; //Green
uint32_t auto_4 = CRGB::Purple; //Purple
uint32_t auto_5 = CRGB::Pink; //Pink
uint32_t auto_6 = CRGB::Teal; //Teal


uint32_t teleColor = CRGB::Red;      // 'On' color (starts red)
uint32_t testColor = CRGB::Red;       // 'On' color (starts red)
uint32_t alliancecolor = CRGB::Red;      // 'On' color (starts red)
uint32_t disablecolor = CRGB::Red;      // 'On' color (starts red)
uint32_t catyellowcolor = 0xFFC500;      //
uint32_t autonModecolor = auto_1;      // 'On' color (starts red)
uint32_t intakeColor = catyellowcolor;      // 'On' color (starts red)

//Fire Setup
CRGBPalette16 gPal;
bool gReverseDirection = true;
int pk_low = 0;
int pk_high = 0;

//
int autoFlashdelay = 0;
int autoFlashcounter = 0;


//Variables for teleop
int upLEDpos = 0;
int lwLEDpos = 0;

void setup()
{
  Wire.begin(84);                // join i2c bus with address #84
  TWBR = 12;
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for output
  analogReference(EXTERNAL);
  FastLED.addLeds<CHIPSET, DATAPIN1,CLOCKPIN1, COLOR_ORDER>(leds_sides, NUM_LEDS_SIDES);
  FastLED.addLeds<CHIPSET, DATAPIN2,CLOCKPIN2, GBR>(leds_fnb, NUM_LEDS_FNB);
  //FastLED.addLeds<CHIPSET, DATAPIN3,CLOCKPIN3, COLOR_ORDER>(leds_front, NUM_LEDS_FRONT);
  //FastLED.addLeds<CHIPSET, DATAPIN4,CLOCKPIN4, COLOR_ORDER>(leds_tur_right, NUM_LEDS_FRONT);
  FastLED.setBrightness( BRIGHTNESS );
  gPal = CRGBPalette16( CRGB::Black, alliancecolor,  CRGB::White);
  uint8_t i, j, nBins, binNum, *data;
  gPal = CRGBPalette16( CRGB::Black, alliancecolor,  CRGB::White);
  memset(peak, 0, sizeof(peak));
  memset(col , 0, sizeof(col));

  for(i=0; i<8; i++) {
    minLvlAvg[i] = 0;
    maxLvlAvg[i] = 512;
    data         = (uint8_t *)pgm_read_word(&colData[i]);
    nBins        = pgm_read_byte(&data[0]) + 2;
    binNum       = pgm_read_byte(&data[1]);
    for(colDiv[i]=0, j=2; j<nBins; j++)
      colDiv[i] += pgm_read_byte(&data[j]);
  }
  Serial.print("ARGOS 1756!");


  // Init ADC free-run mode; f = ( 16MHz/prescaler ) / 13 cycles/conversion 
  ADMUX  = ADC_CHANNEL; // Channel sel, right-adj, use AREF pin
  ADCSRA = _BV(ADEN)  | // ADC enable
           _BV(ADSC)  | // ADC start
           _BV(ADATE) | // Auto trigger
           _BV(ADIE)  | // Interrupt enable
           _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // 128:1 / 13 = 9615 Hz
  ADCSRB = 0;                // Free run mode, no high MUX bit
  DIDR0  = 1 << ADC_CHANNEL; // Turn off digital input for ADC pin
  TIMSK0 = 0;                // Timer0 off

  sei(); // Enable interrupts
  }


void loop()
{

//Variable Status for Troubleshooting
/*Serial.print(gameMode);
  Serial.print(gameTime);
  Serial.print(battLevel);
  Serial.print(yoyoPos);
  Serial.print(win);
  Serial.println(alliance);
  Serial.println("main");
*/

  if (win == 'W') {
    celebrationMode();
  }
  else
  {
    switch (gameMode)
    {
      case 'A':
        auton();  //Auto Blue
        break;
      case 'T':
        teleopMode(); //Tele Green
        break;
      case 'X':
        testMode(); //Test Multi color
        break;
      default:
        disabledMode(); // Disabled Red
    }

  }

  //  strip.show();
}

void celebrationMode()
{
  for(int i = (NUM_LEDS_SIDES)-1; i >= 0; i--) {
  leds_sides[i] = CHSV(random8() ,random8(), random8());
  }
  for(int i = (NUM_LEDS_FNB)-1; i >= 0; i--) {
  leds_fnb[i] = CHSV(random8() ,random8(), random8());
  } 
  FastLED.show();
}

void auton()
{
  while (gameMode == 'A')
  {
    fnbLEDS();

    
    //  static uint8_t hue = 0;
    //fill_solid(leds_fnb, NUM_LEDS_FNB, autonModecolor );
    // First slide the led in one direction
   for(int i = 0; i < NUM_LEDS_SIDES; i++) {
    // Set the i'th led to red 
    leds_sides[i] = alliancecolor;
    // Show the leds
    fnbLEDS();
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    for(int i = 0; i < NUM_LEDS_SIDES; i++) { leds_sides[i].nscale8(250);}
    //fadeall();
    // Wait a little bit before we loop around and do it again
    delay(1);
  }
  //Serial.print("x");

  // Now go in the other direction.  
  for(int i = (NUM_LEDS_SIDES)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds_sides[i] = alliancecolor;
    // Show the leds
    fnbLEDS();
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
   // leds_sides[i] = CRGB::Black;
    for(int i = 0; i < NUM_LEDS_SIDES; i++) { leds_sides[i].nscale8(250);}
    // Wait a little bit before we loop around and do it again
    delay(1);
  }
  }
}

void teleopMode()
{
    fadeToBlackBy( leds_sides, NUM_LEDS_SIDES, 15);
    
      if (climb=='Z')
    {
      leds_sides[upLEDpos] = CRGB::Green;
      leds_sides[lwLEDpos] = CRGB::Green;
    }
    else
    {
      leds_sides[upLEDpos] = alliancecolor;
      leds_sides[lwLEDpos] = alliancecolor; 
    }
    
    leds_sides[armPosLED] = CRGB::White;
    if (armPosLED < NUM_LEDS_SIDES-1)
      leds_sides[armPosLED+1] = CRGB::Black;
    if (armPosLED > 0)
      leds_sides[armPosLED-1] = CRGB::Black;
    
    fill_solid(leds_fnb, NUM_LEDS_FNB, intakeColor );
    FastLED.show();     
      
    ++upLEDpos;
    --lwLEDpos;
    if (upLEDpos > (NUM_LEDS_SIDES-1))
      upLEDpos = armPosLED;
    if (lwLEDpos < 0)
      lwLEDpos = armPosLED;
    delay(20);  
  

    
}
void testMode()
{
   
  fill_rainbow( leds_sides, NUM_LEDS_SIDES, 222);
  fill_rainbow(leds_fnb, NUM_LEDS_FNB, 222); 
  FastLED.show();
  
}

void disabledMode() {
  uint8_t  i, x, L, *data, nBins, binNum, weighting, c;
  uint16_t minLvl, maxLvl;
  int      level, y, sum;

  while(ADCSRA & _BV(ADIE)); // Wait for audio sampling to finish

  fft_input(capture, bfly_buff);   // Samples -> complex #s
  samplePos = 0;                   // Reset sample counter
  ADCSRA |= _BV(ADIE);             // Resume sampling interrupt
  fft_execute(bfly_buff);          // Process complex data
  fft_output(bfly_buff, spectrum); // Complex -> spectrum

  // Remove noise and apply EQ levels
  for(x=0; x<FFT_N/2; x++) {
    L = pgm_read_byte(&noise[x]);
    spectrum[x] = (spectrum[x] <= L) ? 0 :
      (((spectrum[x] - L) * (256L - pgm_read_byte(&eq[x]))) >> 8);
  }

  // Downsample spectrum output to 8 columns:
  for(x=0; x<8; x++) {
    data   = (uint8_t *)pgm_read_word(&colData[x]);
    nBins  = pgm_read_byte(&data[0]) + 2;
    binNum = pgm_read_byte(&data[1]);
    for(sum=0, i=2; i<nBins; i++)
      sum += spectrum[binNum++] * pgm_read_byte(&data[i]); // Weighted
    col[x][colCount] = sum / colDiv[x];                    // Average
    minLvl = maxLvl = col[x][0];
    for(i=1; i<10; i++) { // Get range of prior 10 frames
      if(col[x][i] < minLvl)      minLvl = col[x][i];
      else if(col[x][i] > maxLvl) maxLvl = col[x][i];
    }
    // minLvl and maxLvl indicate the extents of the FFT output, used
    // for vertically scaling the output graph (so it looks interesting
    // regardless of volume level).  If they're too close together though
    // (e.g. at very low volume levels) the graph becomes super coarse
    // and 'jumpy'...so keep some minimum distance between them (this
    // also lets the graph go to zero when no sound is playing):
    if((maxLvl - minLvl) < 8) maxLvl = minLvl + 8;
    minLvlAvg[x] = (minLvlAvg[x] * 7 + minLvl) >> 3; // Dampen min/max levels
    maxLvlAvg[x] = (maxLvlAvg[x] * 7 + maxLvl) >> 3; // (fake rolling average)

    // Second fixed-point scale based on dynamic min/max levels:
    level = 10L * (col[x][colCount] - minLvlAvg[x]) /
      (long)(maxLvlAvg[x] - minLvlAvg[x]);

    // Clip output and convert to byte:
    if(level < 0L)      c = 0;
    else if(level > 10) c = 10; // Allow dot to go a couple pixels off top
    else                c = (uint8_t)level;
    
    
    peak[x] = c; // Keep dot on top
    
  }
  
  // Add entropy to random number generator; we use a lot of it.
  // random16_add_entropy( random());

  Fire2012(); // run simulation frame
  fnbLEDS();
  FastLED.show(); // display this frame
  //FastLED.delay(1000 / FRAMES_PER_SECOND);
  if(++colCount >= 10) colCount = 0;
}

#define COOLING  150

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat_low[NUM_LEDS_SIDES/2];
  static byte heat_high[NUM_LEDS_SIDES/2];

  pk_low = (peak[0]+peak[1]+peak[2]+peak[3])/4;

  
  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS_SIDES/2; i++) {
      heat_low[i] = qsub8( heat_low[i],  random8(0, ((COOLING * 20) / NUM_LEDS_SIDES/2) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS_SIDES/2 - 1; k >= 2; k--) {
      heat_low[k] = (heat_low[k - 1] + heat_low[k - 2] + heat_low[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( pk_low<4 && pk_low>0 ) {
      int y = random8(7);
      heat_low[y] = qadd8( heat_low[y], 160 );
    } else if( pk_low<7 && pk_low>=4 ) {
      int y = random8(7);
      heat_low[y] = qadd8( heat_low[y], 210 );
    } else if(pk_low>=7 ) {
      int y = random8(7);
      heat_low[y] = qadd8( heat_low[y], 255 );
    }
    else
     {}
    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS_SIDES/2; j++) {
      byte colorindex = scale8( heat_low[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS_SIDES/2-1) - j;
      } else {
        pixelnumber = j;
      }
      leds_sides[pixelnumber] = color;
    }
      pk_high = (peak[4]+peak[5]+peak[6]+peak[7])/4;
  
  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS_SIDES/2; i++) {
      heat_high[i] = qsub8( heat_high[i],  random8(0, ((COOLING * 20) / NUM_LEDS_SIDES/2) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS_SIDES/2 - 1; k >= 2; k--) {
      heat_high[k] = (heat_high[k - 1] + heat_high[k - 2] + heat_high[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( pk_high<3 && pk_high>0 ) {
      int y = random8(7);
      heat_high[y] = qadd8( heat_high[y], 160 );
    } else if( pk_high<6 && pk_high>=3 ) {
      int y = random8(7);
      heat_high[y] = qadd8( heat_high[y], 210 );
    } else if(pk_high>=6 ) {
      int y = random8(7);
      heat_high[y] = qadd8( heat_high[y], 255 );
    }
    else
     {}
    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS_SIDES/2; j++) {
      byte colorindex = scale8( heat_high[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      pixelnumber = j+NUM_LEDS_SIDES/2;
      leds_sides[pixelnumber] = color;
    }


}
void fnbLEDS()
{

  //Serial.println(autoFlashcounter);
 // Serial.println(autoFlashdelay);
  if (autoFlashdelay == 1)
  {
    ++autoFlashcounter;
    
    if (autoFlashcounter < 50) {
      fill_solid(leds_fnb, NUM_LEDS_FNB, autonModecolor );
    //  Serial.println(autoFlashcounter);
    }
    else if (autoFlashcounter < 100) {
       fill_solid(leds_fnb, NUM_LEDS_FNB, CRGB::Black);
     //  Serial.println(autoFlashcounter);
    }
    else {
       autoFlashcounter = 0;
    //   Serial.println(autoFlashcounter);

    }

  }
  else
    fill_solid(leds_fnb, NUM_LEDS_FNB, autonModecolor );
}


void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds_fnb[ random16(NUM_LEDS_FNB) ] += CRGB::White;
    leds_sides[ random16(NUM_LEDS_SIDES)] += CRGB::White;
  }
}


  ISR(ADC_vect) { // Audio-sampling interrupt
  static const int16_t noiseThreshold = 4;
  int16_t              sample         = ADC; // 0-1023

  capture[samplePos] =
    ((sample > (512-noiseThreshold)) &&
     (sample < (512+noiseThreshold))) ? 0 :
    sample - 512; // Sign-convert for FFT; -512 to +511

  if(++samplePos >= FFT_N) ADCSRA &= ~_BV(ADIE); // Buffer full, interrupt off
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()



void receiveEvent(int numBytes)
{
  String temp = "";
  int byteNum = 10;
  char text[byteNum + 1];
  char blank[byteNum + 1];
  int i = 0;
  while (Wire.available()) {
    text[i] = Wire.read();
    text[i + 1] = '\0';
    i++;
  }  
  if (text[0] = 'M') // verify sync letter 'M' before processing message
  {
    gameMode = text[1]; // receive byte as a character
    autonMode = text[2];
    win = text[3];
    alliance= text[4];
    climb = text[5];
    armPos = text[6];
    intake = text[7];
  
    //debugging message
    /*
    Serial.print(text[0]);
    Serial.print(gameMode);   
    Serial.print(autonMode);
    Serial.print(win);
    Serial.print(alliance);
    Serial.print(climb);
    Serial.print(armPos);
    Serial.println(intake);
    */
  }

  //Convert armpos to scale on robot
  float x = ((float)armPos/100)*(NUM_LEDS_SIDES-60-1)+30; //offset of 30 leds to make lights more interesting
  //Serial.println(x);
  armPosLED = (int)x;
  //Serial.println(armPosLED);

  //set alliance color based on message
  if (alliance == 'R')
  {
    alliancecolor = CRGB::Red;
  }
  else
  {
    alliancecolor = CRGB::Blue;
  }
  switch (autonMode)
    {
        case 'S':
          autonModecolor = CRGB::White;
          autoFlashdelay = 0;
          break;
        case 'L':
          autonModecolor = CRGB::Red;
          autoFlashdelay = 0;
          break;
        case 'G':
          autonModecolor = CRGB::Red;
          autoFlashdelay = 1;
          break;
        case 'F':
          autonModecolor = CRGB::Green;
          autoFlashdelay = 0;
          break;
        case 'K':
          autonModecolor = CRGB::Green;
          autoFlashdelay = 1;
          break;
        case 'V':
          autonModecolor = CRGB::Blue;
          autoFlashdelay = 0;
          break;                   
        default:
          autonModecolor = CRGB::Blue;
          autoFlashdelay = 1;
   }
  
  gPal = CRGBPalette16( CRGB::Black, alliancecolor,  CRGB::White);
  switch (intake)
    {
      case 'I':
        intakeColor = CRGB::Blue;
        break;
      case 'C':
        intakeColor = CRGB::Yellow;
        break;
      case 'H':
        intakeColor = CRGB::Green;
        break;                 
      default:
        intakeColor = CRGB::White;
    }

}
