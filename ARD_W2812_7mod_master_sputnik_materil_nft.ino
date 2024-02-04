#include <FastLED.h> //https://github.com/FastLED/FastLED
#include <arduinoFFT.h> //https://github.com/kosme/arduinoFFT
#include <IRremote.h> //https://github.com/z3t0/Arduino-IRremote
#include <EEPROM.h>

//#define NUM_LEDS_60 //OR remote control model select

#define RC1

///#define pinIR 3

#ifdef NUM_LEDS_60 //for test
  //#define NUM_LEDS 60
  #define NUM_LEDS 16
#else
  #define NUM_LEDS 100   //number of LEDs   //60 // How many leds in your strip? 
#endif

#define CHANGE_INTERVAL 50 // 50 .. 150 ms interval for increase value  buttons
#define CHANGE_INTERVAL_SELECT_BUTTON 150 // ~150 ms interval for select button

#define SOUND_CHANGE_INTERVAL 256 //350 //150 ms  350 ms

//#define PAUSE_SEC 3    //seconds 
#define SERIAL_ON_INTERVAL1 50 //20 //100    //ms   mode3
#define SERIAL_OFF_INTERVAL1 10
#define PULSE_INTERVAL 10     //seconds swith on and switch off  mode 4
#define SEGMENTS_ON_INTERVAL 10 //seconds mode 5

#define DATA_PIN 2 // For led chips like Neopixels, which have a data line, ground, and power, you just need to define DATA_PIN
#define CHANGE_MODE_PIN 11
#define DECREASE_PIN 12
#define INCREASE_PIN 13

#define NUNMBER_MODES 9 //7 8 9

#define NUNMBER_SECTORS 5 //6 //8

#ifdef NUM_LEDS_60
  #define FIRST_1_SECTOR_N_LED 0  //3
  #define LAST_1_SECTOR_N_LED 2
  
  #define FIRST_2_SECTOR_N_LED 3  //3
  #define LAST_2_SECTOR_N_LED 5
  
  #define FIRST_3_SECTOR_N_LED 6  //3
  #define LAST_3_SECTOR_N_LED 8
  
  #define FIRST_4_SECTOR_N_LED 9  //3
  #define LAST_4_SECTOR_N_LED 11
  
  #define FIRST_5_SECTOR_N_LED 12  //2
  #define LAST_5_SECTOR_N_LED 13
  
  #define FIRST_6_SECTOR_N_LED 14  //2
  #define LAST_6_SECTOR_N_LED 15
  
#else
  #define FIRST_1_SECTOR_N_LED 0
  #define LAST_1_SECTOR_N_LED 53 //54 26 & 27 mid  26-0 together 27-57  27 26 28 25 29 24 30 23 31 22 32 21 33 20 34 19 35 18 36 17 37 16 38 15 39 14 40 13 
                                                                      //41 12 42 11 43 10 44 9 45 8 46 7 47 6 48 5 49 4 50 3 51 2 52 1 53 0
                                                                      //26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
                                                                      //27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53
  
  #define FIRST_2_SECTOR_N_LED 54 //6    54 55 56 57 58 59
  #define LAST_2_SECTOR_N_LED 59        
  
  #define FIRST_3_SECTOR_N_LED 60  //6   60 61 62 63 64 65
  #define LAST_3_SECTOR_N_LED 65
  
  #define FIRST_4_SECTOR_N_LED 66  //12  71 72 70 73 69 74 68 75 67 76 66 77
  #define LAST_4_SECTOR_N_LED 77   
  
  #define FIRST_5_SECTOR_N_LED 78  //22   88 89 87 90 86 91 85 92 84 93 83 94 82 95 81 96 80 97 79 98 78 99
  #define LAST_5_SECTOR_N_LED 99
#endif



#define TEMPERATURE_1 Tungsten40W   //2600 Kelvin
#define TEMPERATURE_2 Tungsten100W //2850 Kelvin
#define TEMPERATURE_3 Halogen   //3200 Kelvin
#define TEMPERATURE_4 CarbonArc   //5200 Kelvin
#define TEMPERATURE_5 HighNoonSun  //5400 Kelvin 
#define TEMPERATURE_6 DirectSunlight //6000 Kelvin
#define TEMPERATURE_7 OvercastSky //7000 Kelvin
#define TEMPERATURE_8 ClearBlueSky  //20000 Kelvin 

#define SELECT_TEMPERATURE TEMPERATURE_4


#define MIN_BRIGHTNESS 0
#define MIN_BRIGHTNESS_1_MODE 3
#define MIN_BRIGHTNESS_2_MODE 3
#define MIN_BRIGHTNESS_3_MODE 5
#define MIN_BRIGHTNESS_4_MODE 3
#define MIN_BRIGHTNESS_5_MODE 3

//mode 6 7
#define MIN_LIGHTMUSIC_BRIGHTNESS 5
#define MAX_LIGHTMUSIC_BRIGHTNESS 255
#define W_SEC_MIN_LIGHTMUSIC_BRIGHTNESS 3    //WHITE SECTOR
#define W_SEC_MAX_LIGHTMUSIC_BRIGHTNESS 250   //WHITE SECTOR

//EQ 6 & 7 mode
#define SEC_1_MIN_LIGHTMUSIC_BRIGHTNESS 2
#define SEC_1_MAX_LIGHTMUSIC_BRIGHTNESS 128

#define SEC_2_MIN_LIGHTMUSIC_BRIGHTNESS 5
#define SEC_2_MAX_LIGHTMUSIC_BRIGHTNESS 248

#define SEC_3_MIN_LIGHTMUSIC_BRIGHTNESS 5
#define SEC_3_MAX_LIGHTMUSIC_BRIGHTNESS 248

#define SEC_4_MIN_LIGHTMUSIC_BRIGHTNESS 7
#define SEC_4_MAX_LIGHTMUSIC_BRIGHTNESS 199

#define SEC_5_MIN_LIGHTMUSIC_BRIGHTNESS 7
#define SEC_5_MAX_LIGHTMUSIC_BRIGHTNESS 254

//#define SEC_6_MIN_LIGHTMUSIC_BRIGHTNESS 25
//#define SEC_6_MAX_LIGHTMUSIC_BRIGHTNESS 255

//#define SEC_7_MIN_LIGHTMUSIC_BRIGHTNESS 25
//#define SEC_7_MAX_LIGHTMUSIC_BRIGHTNESS 255
//
//#define SEC_8_MIN_LIGHTMUSIC_BRIGHTNESS 25
//#define SEC_8_MAX_LIGHTMUSIC_BRIGHTNESS 255


#define MAX_BRIGHTNESS_1_MODE 255
#define MAX_BRIGHTNESS_4_MODE 120
#define MAX_BRIGHTNESS_5_MODE 255
#define MAX_BRIGHTNESS 255 // MAX ! 255 !

#define MAX_COLOR 255 //HUE transform 0..255

//mode 1
#define BR_STEP_1_MODE 3  // 1 3 5 10  brightness increase decrease step

//mode 2
#define BR_STEP_2_MODE 25 //1 3 5 10 brightness increase decrease step

#define COLOR_STEP_2_MODE 5 // 1 2 3 5 10 25  HUSE Color increase decrease step

#define RENEW_INTERVAL 1 //second 

#define WHITE_SECTOR_2 1

 #define MIN_MIC_LEVEL 0  
 #define MAX_MIC_LEVEL 630

//mode 3
#define BR_STEP_3_MODE 5 //1 3 5 10 25 brightness increase decrease step

#define MIN_SERIAL_ON_INTERVAL 1  
#define MAX_SERIAL_ON_INTERVAL 250 //milliseconds 
#define SERIAL_HOLD_ON_TIME 3 //seconds

//4 mode
#define MIN_PULSE_INTERVAL 1  //mode 4
#define MAX_PULSE_INTERVAL 100  //seconds 

//5 mode
#define BR_STEP_5_MODE 5 //1 3 5 10 25 brightness increase decrease step

#define MIN_SWITCH_INTERVAl 1 //sec
#define MAX_SWITCH_INTERVAl 1000

//7 mode
#define WHITE_SECTOR 1  


#define SAMPLES 32 //64            //Must be a power of 2
#define xres 16 //32      // Total number of  columns in the display, must be <= SAMPLES/2  
#define yres 255       // Total number of  rows in the display


byte sectors_eq_arr[(NUNMBER_SECTORS + 1)][2] = { {0,0},
                                                  {SEC_1_MIN_LIGHTMUSIC_BRIGHTNESS, SEC_1_MAX_LIGHTMUSIC_BRIGHTNESS},
                                                  {SEC_2_MIN_LIGHTMUSIC_BRIGHTNESS, SEC_2_MAX_LIGHTMUSIC_BRIGHTNESS},
                                                  {SEC_3_MIN_LIGHTMUSIC_BRIGHTNESS, SEC_3_MAX_LIGHTMUSIC_BRIGHTNESS},
                                                  {SEC_4_MIN_LIGHTMUSIC_BRIGHTNESS, SEC_4_MAX_LIGHTMUSIC_BRIGHTNESS},
                                                  {SEC_5_MIN_LIGHTMUSIC_BRIGHTNESS, SEC_5_MAX_LIGHTMUSIC_BRIGHTNESS} };


byte serial_LED_n[NUM_LEDS] = {27, 26, 28, 25, 29, 24, 30, 23, 31, 22, 32, 21, 33, 20, 34, 19, 35, 18, 36, 17, 37, 16, 38, 15, 39, 14, 40, 13, 41, 12, 42, 11, 43, 10,
                   44, 9, 45, 8, 46, 7, 47, 6, 48, 5, 49, 4, 50, 3, 51, 2, 52, 1, 53, 0, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 71, 72, 70, 73,
                   69, 74, 68, 75, 67, 76, 66, 77, 88, 89, 87, 90, 86, 91, 85, 92, 84, 93, 83, 94, 82, 95, 81, 96, 80, 97, 79, 98, 78, 99};

byte mem_mode = 0;

//mode 1
int n = 0;
int br = 0;
int br_button = 127; //0 .. 255 defalut value
byte current_mode = 1;

CRGB leds[NUM_LEDS]; // Define the array of leds

//mode 2
byte white_sector_2 = WHITE_SECTOR_2 - 1;

 int br_mic_level = 127; //0 .. 255
 int Mic_level = 0;

int br_button_2 = 127;
int n_cur = 0;

//mode 3 speed up
int serial_on_interval = SERIAL_ON_INTERVAL1; //100;
int serial_off_interval = SERIAL_OFF_INTERVAL1;
bool turn_on_way = true;

bool bright_button_plus = false;
bool bright_button_minus = false;

byte k_mode3 = 1;

int br_button_3 = 127;

int pause_m3_ms = 0;

int br3_var = MAX_BRIGHTNESS;

int turn_off = false;

//mode 4
int pulse_interval_sec = PULSE_INTERVAL;
int br_pulse = 127; //0
int pulse_interval_ms = (int) 1000.0*pulse_interval_sec/510.0;

int br_button_4 = MAX_BRIGHTNESS_4_MODE;

int pause_ms = 0;

//mode 5
int n_sect = 0;
int n_led_segments[NUNMBER_SECTORS][2] = { {FIRST_1_SECTOR_N_LED, LAST_1_SECTOR_N_LED}, {FIRST_2_SECTOR_N_LED, LAST_2_SECTOR_N_LED}, {FIRST_3_SECTOR_N_LED, LAST_3_SECTOR_N_LED},
                                           {FIRST_4_SECTOR_N_LED, LAST_4_SECTOR_N_LED}, {FIRST_5_SECTOR_N_LED, LAST_5_SECTOR_N_LED} };

int m5_switch_interval = 3; //MIN_SWITCH_INTERVAl  MAX_SWITCH_INTERVAl

int br_button_5 = 127;
int br_var = MIN_BRIGHTNESS_5_MODE;
bool start_br_up = false;

//mode 7
byte white_sector = WHITE_SECTOR - 1;


//2 mode
byte selected_segment_2 = 1;
byte segments_colors_2[(NUNMBER_SECTORS + 1)] = {0, 127, 42, 84, 126, 168}; //225  EEPROM 6 7 8 9 10 11

//7 mode
byte selected_segment = 1;
byte segments_colors[(NUNMBER_SECTORS + 1)] = {0, 0, 80, 80, 126, 168}; // {0, 1 seg, 2 seg, 3 seg, 4 seg, 5 seg colors}


double vReal[SAMPLES];
double vImag[SAMPLES];
char data_avgs[xres];
byte br_freq[xres];

int yvalue;
int displaycolumn, displayvalue;
int peaks[xres];

arduinoFFT FFT = arduinoFFT();

long timer_cm = 0;
long timer_1 = 0;
long timer_2 = 0;
long timer_2_1 = 0;
long timer_2_2 = 0;
long timer_3 = 0;
long timer_3_1 = 0;
long timer_3_2 = 0;
long timer_3_3 = 0;
long timer_4 = 0;
long timer_4_1 = 0;
long timer_5 = 0;
long timer_5_1 = 0;
long timer_6 = 0;
long timer_7 = 0;
long timer_7_1 = 0;
long timer_7_2 = 0;

const int RECV_PIN = 7;

long code_command = 0;

bool br_button_plus = false;
bool br_button_minus = false;

int step = 0;
int c = 0;

bool turn = true;

byte seg = 1;

String str_1 = "";
String str_2 = "";

IRrecv irrecv(RECV_PIN);
decode_results results;

///int cur_code_command = 0;
///CNec IRLremote;

void Read_EEPROM_values();

void setup() { 
  
  Serial.begin(115200);

  //EEPROM.begin(1024);
  
  pinMode(DATA_PIN, OUTPUT);

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

  pinMode(INCREASE_PIN, INPUT);
  pinMode(DECREASE_PIN, INPUT);
  pinMode(CHANGE_MODE_PIN, INPUT);

  FastLED.setTemperature( SELECT_TEMPERATURE );

  FastLED.setBrightness(0);
  FastLED.show();
  for (n = 0; n < NUM_LEDS; n++)
  {
    leds[n] = CRGB::White;
  }
  n = 0;

  irrecv.enableIRIn();
  ///  if (!IRLremote.begin(pinIR))
  ///  Serial.println(F("Please choose a valid pin for IR RC"));

  Read_EEPROM_values();

  prepare_vals_for_new_mode();
  
}

void Read_EEPROM_values()
{

  //1 mode
  EEPROM.get( (6*sizeof(float)), br_button);
  if ( (br_button < MIN_BRIGHTNESS_1_MODE) || (br_button > MAX_BRIGHTNESS_1_MODE) ) { br_button = 127; }
  Serial.print(br_button);
  Serial.print(F(" br_1   "));
  
  //2 mode
  EEPROM.get( (3*sizeof(float)), br_button_2);
  if ( (br_button_2 < MIN_BRIGHTNESS_2_MODE) || (br_button_2 > MAX_BRIGHTNESS) ) { br_button_2 = 127; }
  Serial.print(br_button_2);
  Serial.print(F(" br_2  "));

  Serial.print(F(" 2 mode colors: "));

  //6 7 8 9 10 11
  for(n_sect = 0; n_sect < NUNMBER_SECTORS; n_sect++)
  {
    EEPROM.get( ((6 + n_sect)*sizeof(float)), segments_colors_2[n_sect + 1]);
    Serial.print(segments_colors_2[n_sect + 1]);
    Serial.print(" ");
  }

  //3 mode
  EEPROM.get( (0*sizeof(float)), serial_on_interval); //eeAddress, customVar
  if (serial_on_interval < MIN_SERIAL_ON_INTERVAL) { serial_on_interval = MIN_SERIAL_ON_INTERVAL; }
  if (serial_on_interval > MAX_SERIAL_ON_INTERVAL) { serial_on_interval = MAX_SERIAL_ON_INTERVAL; }

  EEPROM.get( (1*sizeof(float)), br_button_3);
  if ( (br_button_3 < MIN_BRIGHTNESS_3_MODE) || (br_button_3 > MAX_BRIGHTNESS) ) { br_button_3 = 127; }

  Serial.print(F("3: "));
  Serial.print(serial_on_interval);
  Serial.print(F(" "));
  Serial.print(br_button_3);
  Serial.print(F("   "));
  
  //4 mode
  EEPROM.get( (2*sizeof(float)), pulse_interval_sec);
  if (pulse_interval_sec < MIN_PULSE_INTERVAL) { pulse_interval_sec = MIN_PULSE_INTERVAL; }
  if (pulse_interval_sec > MAX_PULSE_INTERVAL) { pulse_interval_sec = MAX_PULSE_INTERVAL; }
  
  pulse_interval_ms = (int) 1000.0 * pulse_interval_sec / 510.0;

  Serial.print(F("4: "));
  Serial.print(pulse_interval_sec);
  Serial.print(F(" "));
  Serial.print(pulse_interval_ms);
  Serial.print(F(" "));
  
  //5 mode
  EEPROM.get( (4*sizeof(float)), m5_switch_interval);
  if (m5_switch_interval < MIN_SWITCH_INTERVAl) { m5_switch_interval = MIN_SWITCH_INTERVAl; } 
  if (m5_switch_interval > MAX_SWITCH_INTERVAl) { m5_switch_interval = MAX_SWITCH_INTERVAl; } 
  
  //m5_switch_interval = ; // 3
  EEPROM.get( (5*sizeof(float)), br_button_5);
  if ( (br_button_5 < MIN_BRIGHTNESS_5_MODE) || (br_button_5 > MAX_BRIGHTNESS_5_MODE) ) { br_button_5 = 127; }
  //br_button = ;

  Serial.print(F("5: "));
  Serial.print(m5_switch_interval);
  Serial.print(F(" "));
  Serial.println(br_button_5);

}

void prepare_vals_for_new_mode()
{
  switch ( current_mode )
  {
    case 1: // bright all
      FastLED.setTemperature( SELECT_TEMPERATURE );
      //memset8( leds, 255, NUM_LEDS * sizeof(CRGB) );
      for (n = 0; n < NUM_LEDS; n++)
      {
        leds[n] = CRGB::White;
      }
      //br_button = 127;
      FastLED.setBrightness(br_button); // 0 .. 255
      FastLED.show();
      n = 0;
      delay(1000);
      break;
    case 2: //mic sound level
      FastLED.setTemperature( SELECT_TEMPERATURE );

      for(n_sect = 0; n_sect < NUNMBER_SECTORS; n_sect++)
      {
        for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++) // + 1
        {
          if ( n_sect == white_sector_2 )
          {
            leds[n] = CRGB(segments_colors_2[n_sect + 1], segments_colors_2[n_sect + 1], segments_colors_2[n_sect + 1]);
          } else {
            leds[n] = CHSV(segments_colors_2[n_sect + 1], 255, br_button_2); //or random saturation
          }
        }
      }
      FastLED.setBrightness(br_button_2);
      //delay(1);
      n = 0;
      FastLED.show();
      delay(1000);
      break;
    case 3: //serial all
      FastLED.setTemperature( SELECT_TEMPERATURE );
      //memset8( leds, 255, NUM_LEDS * sizeof(CRGB) );
      for (n = 0; n < NUM_LEDS; n++)
      {
        leds[n] = CRGB::Black;
      }
      FastLED.setBrightness(br_button_3); //127
      FastLED.show();
      delay(1000);
      timer_3_2 = millis();
      n = 0;
      turn_on_way = true;
      break;
    case 4: //pulse
      FastLED.setTemperature( SELECT_TEMPERATURE );
      //memset8( leds, 255, NUM_LEDS * sizeof(CRGB) );
      FastLED.setBrightness(MAX_BRIGHTNESS_4_MODE);
      FastLED.show();
      delay(100);
      for (n = 0; n < NUM_LEDS; n++)
      {
        //leds[n] = CRGB::White;
        leds[n] = CRGB(MAX_BRIGHTNESS_4_MODE, MAX_BRIGHTNESS_4_MODE, MAX_BRIGHTNESS_4_MODE);
      }
      //FastLED.setBrightness(0);
      br_pulse = MAX_BRIGHTNESS_4_MODE; //0 127
      //FastLED.setBrightness(br_pulse);
      FastLED.show();
      delay(1000);
      n = 0;
      turn_on_way = true;
      break;
    case 5: //segments on off
      FastLED.setTemperature( SELECT_TEMPERATURE );
      memset8( leds, 0, NUM_LEDS * sizeof(CRGB) );
      for (n = 0; n < NUM_LEDS; n++)
      {
        leds[n] = CRGB::Black;
        //leds[n] = CRGB(MIN_BRIGHTNESS_5_MODE, MIN_BRIGHTNESS_5_MODE, MIN_BRIGHTNESS_5_MODE);
      }
      //FastLED.setBrightness(255);
      FastLED.setBrightness(br_button_5);
      FastLED.show();
      delay(1000);
      n_sect = 0;
      turn_on_way = true;
      break;
    case 6: //light music white
      FastLED.setTemperature( SELECT_TEMPERATURE );
      //memset8( leds, 0, NUM_LEDS * sizeof(CRGB) );
      for (n = 0; n < NUM_LEDS; n++)
      {
        leds[n] = CRGB::Black;
      }
      FastLED.setBrightness(127);
      FastLED.show();
      delay(1000);
      n = 0;
      FastLED.setBrightness(MAX_BRIGHTNESS);
      break;
    case 7: //light music color
      FastLED.setTemperature( SELECT_TEMPERATURE );
      memset8( leds, 0, NUM_LEDS * sizeof(CRGB) );
      for (n = 0; n < NUM_LEDS; n++)
      {
        leds[n] = CRGB::Black;
      }
      FastLED.setBrightness(127);
      FastLED.show();
      delay(1000);
      n = 0;
      FastLED.setBrightness(MAX_BRIGHTNESS);
      break;
  }
}

void loop() { 

  //buttons remote control
  if (irrecv.decode(&results)) {
    
    code_command = results.value;
    irrecv.resume();

    #ifdef RC1 //arrows top RC
    
      switch (code_command)
      {
        case 0xFFA25D:
          current_mode = 1;
          Serial.println("Mode 1");
          prepare_vals_for_new_mode();
          break;
        case 0xFF629D:
          current_mode = 2;
          Serial.println("Mode 2");
          prepare_vals_for_new_mode();
          break;
        case 0xFFE21D:
          //current_mode = 3; //
          //Serial.println("Mode 3"); //
          break;
        case 0xFF22DD:
          //current_mode = 4; //
          //Serial.println("Mode 4"); //
          break;
        case 0xFF02FD:
          current_mode = 5;
          Serial.println("Mode 5");
          prepare_vals_for_new_mode();
          break;
        case 0xFFC23D:
          current_mode = 6;
          Serial.println("Mode 6");
          prepare_vals_for_new_mode();
          break;
        case 0xFFE01F:
          current_mode = 7;
          Serial.println("Mode 7");
          prepare_vals_for_new_mode();
          break;
        case 0xFFA857:
          //Serial.println("8");
          break;
        case 0xFF906F:
          //Serial.println("9");
          break;
        case 0xFF6897:
          //Serial.println("*");
          bright_button_minus = true;
          break;
        case 0xFF9867:
          //Serial.println("0");
          break;
        case 0xFFB04F:
          //Serial.println("#");
          bright_button_plus = true;
          break;
        case 0xFF18E7: //
          br_button_plus = true;
          //Serial.println("Up");
          break;
        case 0xFF10EF:
          current_mode--;
          if (current_mode == 4) {current_mode = 3;} //
          if (current_mode < 1) { current_mode = NUNMBER_MODES; }
          if (current_mode > NUNMBER_MODES) { current_mode = 1; }
          Serial.print(current_mode);
          Serial.println(" mode select");
          //Serial.println("Left");
          prepare_vals_for_new_mode();
          break;
        case 0xFF38C7:
          Serial.println("Oк");
          
          if (turn == true) //OFF
          {
            turn = false;
            mem_mode = current_mode;
            current_mode = 0; //109
            FastLED.setBrightness(0);
            FastLED.show();
            delay(1000);
          } else { //ON
            turn = true;
            //current_mode = 1;
            //Serial.println("Mode 1");
            current_mode = mem_mode;
            Serial.print("Mode ");
            Serial.println(current_mode);
            prepare_vals_for_new_mode();
          }
          
          break;
        case 0xFF5AA5:
          current_mode++;
          if (current_mode == 4) {current_mode = 5;} //
          if (current_mode > NUNMBER_MODES) { current_mode = 1; }
          if (current_mode < 1) { current_mode = NUNMBER_MODES; }
          Serial.print(current_mode);
          Serial.println(" mode select");
          //Serial.println("Right");
          prepare_vals_for_new_mode();
          break;
        case 0xFF4AB5:
          br_button_minus = true;
          //Serial.println("Down");
          break;
      }
    
    #else //arrows bottom RC

      switch (code_command)
      {
        case 0xFF629D:
          br_button_plus = true;
          Serial.println("Up");
          break;
        case 0xFF22DD:
          current_mode--;
          if (current_mode == 4) {current_mode = 3;} //
          if (current_mode < 1) { current_mode = NUNMBER_MODES; }
          if (current_mode > NUNMBER_MODES) { current_mode = 1; }
          Serial.print(current_mode);
          Serial.println(" mode select");
          //Serial.println("Left");
          prepare_vals_for_new_mode();
          break;
        case 0xFF02FD:
          Serial.println("Ok");
          
          if (turn == true) //OFF
          {
            turn = false;
            mem_mode = current_mode;
            current_mode = 0; //109
            FastLED.setBrightness(0);
            FastLED.show();
            delay(1000);
          } else { //ON
            turn = true;
            //current_mode = 1;
            //Serial.println("Mode 1");
            current_mode = mem_mode;
            Serial.print("Mode ");
            Serial.println(current_mode);
            prepare_vals_for_new_mode();
          }
          
          break;
        case 0xFFC23D:
          current_mode++;
          if (current_mode == 4) {current_mode = 5;} //
          if (current_mode > NUNMBER_MODES) { current_mode = 1; }
          if (current_mode < 1) { current_mode = NUNMBER_MODES; }
          Serial.print(current_mode);
          Serial.println(" mode select");
          //Serial.println("Right");
          prepare_vals_for_new_mode();
          break;
        case 0xFFA857:
          br_button_minus = true;
          Serial.println("Down");
          break;
        case 0xFF6897:
          current_mode = 1;
          Serial.println("Mode 1");
          prepare_vals_for_new_mode();
          break;
        case 0xFF9867:
          current_mode = 2;
          Serial.println("2");
          prepare_vals_for_new_mode();
          break;
        case 0xFFB04F:
          //current_mode = 3;
          //Serial.println("3");
          break;
        case 0xFF30CF:
          //current_mode = 4;
          //Serial.println("4");
          break;
        case 0xFF18E7:
          current_mode = 5;
          Serial.println("5");
          prepare_vals_for_new_mode();
          break;
        case 0xFF7A85:
          current_mode = 6;
          Serial.println("6");
          prepare_vals_for_new_mode();
          break;
        case 0xFF10EF:
          current_mode = 7;
          Serial.println("7");
          prepare_vals_for_new_mode();
          break;
        case 0xFF38C7:
          //Serial.println("8");
          break;
        case 0xFF5AA5:
          //Serial.println("9");
          break;
        case 0xFF42BD:
          //Serial.println("*");
          bright_button_minus = true;
          break;
        case 0xFF4AB5:
          //Serial.println("0");
          break;
        case 0xFF52AD:
          //Serial.println("#");
          bright_button_plus = true;
          break;
      }
      
    #endif
  }

  if ( millis() > (timer_cm + CHANGE_INTERVAL_SELECT_BUTTON) )
  {
    timer_cm = millis();
    if (digitalRead(CHANGE_MODE_PIN)) {
      current_mode++;
      if (current_mode > NUNMBER_MODES) { current_mode = 1; }
      if (current_mode < 1) { current_mode = NUNMBER_MODES; }
      Serial.print(current_mode);
      Serial.println(F(" mode select"));

      prepare_vals_for_new_mode();
    } 
  }
  
  switch ( current_mode ) //переключение в любой момент
  {
    case 1: //button increase and decrease brightness
      //Serial.println("1 mode select");

      if ( millis() > (timer_1 + CHANGE_INTERVAL) )
      {
        timer_1 = millis();
        if (digitalRead(INCREASE_PIN) || (br_button_plus == true) || (bright_button_plus == true) ) {
          
          if (br_button < MAX_BRIGHTNESS_1_MODE) {
            //br_button++;
            br_button += BR_STEP_1_MODE;
            
            EEPROM.put( (6*sizeof(float)), br_button);
            Serial.print(F("EEPROM update 1 bright: "));
            Serial.println(br_button);
            
            if (br_button > MAX_BRIGHTNESS_1_MODE) { br_button = MAX_BRIGHTNESS_1_MODE; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button);
            FastLED.setBrightness(br_button);
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();
            //delay(CHANGE_INTERVAL);
          }
          br_button_plus = false;
          bright_button_plus = false;
          
        } else if (digitalRead(DECREASE_PIN) || (br_button_minus == true) || (bright_button_minus == true)) {
          
          if (br_button > MIN_BRIGHTNESS_1_MODE) {
            //br_button--;
            br_button -= BR_STEP_1_MODE;
            
            EEPROM.put( (6*sizeof(float)), br_button);
            Serial.print(F("EEPROM update 1 bright: "));
            Serial.println(br_button);
            
            if (br_button < MIN_BRIGHTNESS_1_MODE) { br_button = MIN_BRIGHTNESS_1_MODE; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button);
            FastLED.setBrightness(br_button); //or apply after button turn off pause
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();
            //delay(CHANGE_INTERVAL);
          }
          br_button_minus = false;
          bright_button_minus = false;
          
        } else { //all buttons off
          
        }
      }
      break;
    case 2:
      
      if ( millis() > (timer_2_1 + CHANGE_INTERVAL) )
      {
        timer_2_1 = millis();
        //pulse interval change
        if ( digitalRead(INCREASE_PIN) || (br_button_plus == true) )  //select color  x10
        {
          if ( (segments_colors[selected_segment_2] + COLOR_STEP_2_MODE) <= MAX_COLOR) { //10
            segments_colors_2[selected_segment_2] += COLOR_STEP_2_MODE; //1 2 3 5 10 25
          } else {
            segments_colors_2[selected_segment_2] = 0;
          }

          Serial.print(F("Segment: "));
          Serial.print(String(selected_segment_2));
          Serial.print(F("  Color: "));
          Serial.println(String(segments_colors_2[selected_segment_2]));

          EEPROM.put( ( ( 5 + selected_segment_2 )*sizeof(float)), segments_colors_2[selected_segment_2]);
          Serial.print(F("EEPROM update segment "));
          Serial.print(selected_segment_2);
          Serial.print(F(" color: "));
          Serial.println(segments_colors_2[selected_segment_2]);
        
          for (n = n_led_segments[selected_segment_2 - 1][0]; n <= n_led_segments[selected_segment_2 - 1][1]; n++)
          {
            if ( (n >= n_led_segments[white_sector_2][0]) && (n <= n_led_segments[white_sector_2][1]) )
            {
              leds[n] = CRGB(segments_colors_2[selected_segment_2], segments_colors_2[selected_segment_2], segments_colors_2[selected_segment_2]);
            } else {
              leds[n] = CHSV(segments_colors_2[selected_segment_2], 255, br_button_2); //or random saturation
            }
            //Serial.println(String(n_sect) + " " + String(n) + " " + String(br_freq[xres - 1 - i]));
          }

          FastLED.setBrightness(br_button_2);
          FastLED.setTemperature( SELECT_TEMPERATURE );
          FastLED.show();
          delay(100);

          br_button_plus = false;
        } else if (bright_button_plus == true) {
          if (br_button_2 < MAX_BRIGHTNESS) {
            //br_button_2++;
            br_button_2 += BR_STEP_2_MODE;  //25 10 5 1 
            if (br_button_2 > MAX_BRIGHTNESS) { br_button_2 = MAX_BRIGHTNESS; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button_2);

            EEPROM.put( (3*sizeof(float)), br_button_2);
            Serial.print(F("EEPROM update 2 bright: "));
            Serial.println(br_button_2);

            for(n_sect = 0; n_sect < NUNMBER_SECTORS; n_sect++)
            {
              for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++) // + 1
              {
                if ( (n >= n_led_segments[white_sector_2][0]) && (n <= n_led_segments[white_sector_2][1]) )
                {
                  segments_colors_2[n_sect + 1] = br_button_2;
                  leds[n] = CRGB(segments_colors_2[n_sect + 1], segments_colors_2[n_sect + 1], segments_colors_2[n_sect + 1]);
                } else {
                  leds[n] = CHSV(segments_colors_2[n_sect + 1], 255, br_button_2); //or random saturation
                }
              }
            }
            
            //FastLED.setBrightness(br_button_2);
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();
            delay(100);
            
            //EEPROM.put( (1*sizeof(float)), br_button_2);
            //Serial.print(F("EEPROM update 2 bright: "));
            //Serial.println(br_button_2);
            
            //delay(CHANGE_INTERVAL);
          }
          bright_button_plus = false;
        } else if (bright_button_minus == true) {
          if (br_button_2 > MIN_BRIGHTNESS_2_MODE) {
            //br_button_2--;
            br_button_2 -= BR_STEP_2_MODE; //1 5 10 25
            if (br_button_2 < MIN_BRIGHTNESS_2_MODE) { br_button_2 = MIN_BRIGHTNESS_2_MODE; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button_2);

            /*EEPROM.put( (3*sizeof(float)), br_button_2);
            Serial.print(F("EEPROM update 2 bright: "));
            Serial.println(br_button_2);*/

            for(n_sect = 0; n_sect < NUNMBER_SECTORS; n_sect++)
            {
              for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++) // + 1
              {
                if ( (n >= n_led_segments[white_sector_2][0]) && (n <= n_led_segments[white_sector_2][1]) )
                {
                  segments_colors_2[n_sect + 1] = br_button_2;
                  leds[n] = CRGB(segments_colors_2[n_sect + 1], segments_colors_2[n_sect + 1], segments_colors_2[n_sect + 1]);
                } else {
                  leds[n] = CHSV(segments_colors_2[n_sect + 1], 255, br_button_2); //or random saturation  255
                }
              }
            }
            
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();

            EEPROM.put( (3*sizeof(float)), br_button_2);
            Serial.print(F("EEPROM update 2 bright: "));
            Serial.println(br_button_2);
            
            delay(100);
            
            //delay(CHANGE_INTERVAL);
          }
          bright_button_minus = false;
        }
      }

      if ( millis() > (timer_2_2 + CHANGE_INTERVAL_SELECT_BUTTON) )
      {
        timer_2_2 = millis();
        if ( digitalRead(DECREASE_PIN) || (br_button_minus == true)  ) { //select segment

          selected_segment_2 += 1;
          if (selected_segment_2 > NUNMBER_SECTORS) {
            selected_segment_2 = 1;
          }
          Serial.println();
          Serial.print(F("Segment: "));
          Serial.println(String(selected_segment_2));
          
          for (seg = 1; seg <= NUNMBER_SECTORS; seg++)
          {
            Serial.print(F("Segment: "));
            Serial.print(String(seg));  
            Serial.print(F("  color: "));
            Serial.println(String(segments_colors[seg]));
          }
          br_button_minus = false;
        }
      }
    
      break;
    case 3: //serial switch on all LEDs

      if ( millis() > (timer_3 + CHANGE_INTERVAL) )
      {
        timer_3 = millis();
        //serial interval turn on
        if (digitalRead(INCREASE_PIN) || (br_button_plus == true) ) {
          if (serial_on_interval < MAX_SERIAL_ON_INTERVAL) {
            serial_on_interval++; 
            if (serial_on_interval > MAX_SERIAL_ON_INTERVAL) { serial_on_interval = MAX_SERIAL_ON_INTERVAL; }
            Serial.print(F("Serial On interval: "));
            Serial.println(String(serial_on_interval) + " ms");
            
            EEPROM.put( (0*sizeof(float)), serial_on_interval); //eeAddress, f  put
            Serial.print("EEPROM update 3 time: ");
            Serial.println(serial_on_interval);
            //delay(CHANGE_INTERVAL);
          }
          br_button_plus = false;
        } else if (digitalRead(DECREASE_PIN) || (br_button_minus == true) ) {
          if (serial_on_interval > MIN_SERIAL_ON_INTERVAL) {
            serial_on_interval--;
            if (serial_on_interval < MIN_SERIAL_ON_INTERVAL) { serial_on_interval = MIN_SERIAL_ON_INTERVAL; }
            Serial.print(F("Serial On interval: "));
            Serial.println(String(serial_on_interval) + " ms");

            EEPROM.put( (0*sizeof(float)), serial_on_interval); //eeAddress, f
            Serial.print(F("EEPROM update 3 time: "));
            Serial.println(serial_on_interval);
            //delay(CHANGE_INTERVAL);
          }
          br_button_minus = false;
        } else if (bright_button_plus == true) {
          if (br_button_3 < MAX_BRIGHTNESS) {
            //br_button_3++;
            br_button_3 += BR_STEP_3_MODE;
            if (br_button_3 > MAX_BRIGHTNESS) { br_button_3 = MAX_BRIGHTNESS; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button_3);
            FastLED.setBrightness(br_button_3);
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();

            EEPROM.put( (1*sizeof(float)), br_button_3);
            Serial.print(F("EEPROM update 3 bright: "));
            Serial.println(br_button_3);
            //delay(CHANGE_INTERVAL);
          }
          bright_button_plus = false;
        } else if (bright_button_minus == true) {
          if (br_button_3 > MIN_BRIGHTNESS_1_MODE) {
            //br_button_3--;
            br_button_3 -= BR_STEP_3_MODE;
            if (br_button_3 < MIN_BRIGHTNESS_3_MODE) { br_button_3 = MIN_BRIGHTNESS_3_MODE; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button_3);
            FastLED.setBrightness(br_button_3); //or apply after button turn off pause
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();

            EEPROM.put( (1*sizeof(float)), br_button_3);
            Serial.print(F("EEPROM update 3 bright: "));
            Serial.println(br_button_3);
            //delay(CHANGE_INTERVAL);
          }
          bright_button_minus = false;
        }
      }


      if ( millis() > (timer_3_1 + (serial_on_interval * k_mode3) + pause_m3_ms ) )
      {
        timer_3_1 = millis();
        //Serial.println("3 mode select");
        
        if (n > FIRST_3_SECTOR_N_LED)
        {
          k_mode3 = 3;
        } else {
          k_mode3 = 1;
        }

        //set white color
        // Serial turn LEDs on
        if (turn_on_way == true)
        {
          pause_m3_ms = 0;
          if ( n < (NUM_LEDS + 5) )
          {

            n_cur = n;
            while ( (n_cur >= 0) && (n_cur >= (n - 5)) )
            {
              if (n_cur < NUM_LEDS)
              {
                leds[n_cur] = CRGB (MIN_BRIGHTNESS_3_MODE + ( (int) ( ( (n - n_cur)*(br_button_3 - MIN_BRIGHTNESS_3_MODE) )/5) ) , 
                          MIN_BRIGHTNESS_3_MODE + ( (int) ( ( (n - n_cur)*(br_button_3 - MIN_BRIGHTNESS_3_MODE) )/5 ) ),
                          MIN_BRIGHTNESS_3_MODE + ( (int) ( ( (n - n_cur)*(br_button_3 - MIN_BRIGHTNESS_3_MODE) )/5 ) ) );
                Serial.println( String(n_cur) + " " + String(MIN_BRIGHTNESS_3_MODE + ( (int) ( ( (n - n_cur)*(br_button_3 - MIN_BRIGHTNESS_3_MODE) )/5 ) ) ) );
              }
              n_cur--;
            }
            
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();
            //delay(100);
            Serial.println(String(millis()) + " " + String(n) + " LED+");
            n++;
            //delay(serial_on_interval); //regulation
          } else if (n == (NUM_LEDS + 5) ) {
            n = 0;
            Serial.println("turn off start");
            turn_on_way = false;
            timer_3_2 = millis();
            //10 sec off then start 
          }
          //delay(PAUSE_SEC*1000);
        }
      }
      
      //or fast serial off
      if (turn_on_way == false)
      {
        if ( millis() > (timer_3_2 + (SERIAL_HOLD_ON_TIME*1000) ) )
        {
          Serial.println("off_1");
          turn_off = true;
          br3_var = br_button_3;
        }
      }

      if ( turn_off == true )
      {
        timer_3_2 = millis();
        
        if (br3_var >= MIN_BRIGHTNESS_3_MODE)
        {
          for (n = 0; n < NUM_LEDS; n++) // n--
          {
            //leds[n] = CRGB::White;
            ///leds[n] = CRGB(br3_var, br3_var, br3_var);
            leds[serial_LED_n[n]] = CRGB(br3_var, br3_var, br3_var);
          }
          Serial.println(String(br3_var) + " off");
          FastLED.setTemperature( SELECT_TEMPERATURE );
          FastLED.show();
          delay(10);
          
          if (br3_var > MIN_BRIGHTNESS_3_MODE) {
            //br3_var--;
            if ( (br3_var - 10) > MIN_BRIGHTNESS_3_MODE ) { br3_var -= 10; } else { br3_var = MIN_BRIGHTNESS_3_MODE; }  //5 
            
          } else if (br3_var = MIN_BRIGHTNESS_3_MODE) {
            br3_var = MAX_BRIGHTNESS;
            turn_off = false;
            
            pause_m3_ms = 1000;
            n = 0;
            Serial.println("turn on start");
            turn_on_way = true;
          }
        }
      }
      
      break;
    case 4: //pulse all LEDs
      //Serial.println("4 mode select");
      
      if ( millis() > (timer_4 + CHANGE_INTERVAL) )
      {
        timer_4 = millis();
        //pulse interval change
        if (digitalRead(INCREASE_PIN) || (br_button_plus == true) ) {
          if (pulse_interval_sec < MAX_PULSE_INTERVAL) {
            pulse_interval_sec++; 
            if (pulse_interval_sec > MAX_PULSE_INTERVAL) { pulse_interval_sec = MAX_PULSE_INTERVAL; }
            Serial.print(F("Pulse interval: "));
            Serial.println(String(pulse_interval_sec) + " s");
            pulse_interval_ms = (int) (1000.0*pulse_interval_sec/510.0);

            EEPROM.put( (2*sizeof(float)), pulse_interval_sec); //update
            Serial.print(F("EEPROM update 4 time: "));
            Serial.print(pulse_interval_sec);
            Serial.print(" ");
            Serial.println(pulse_interval_ms);
            //delay(CHANGE_INTERVAL);
          }
          br_button_plus = false;
        } else if (digitalRead(DECREASE_PIN) || (br_button_minus == true) ) {
          if (pulse_interval_sec > MIN_PULSE_INTERVAL) {
            pulse_interval_sec--;
            if (pulse_interval_sec < MIN_PULSE_INTERVAL) { pulse_interval_sec = MIN_PULSE_INTERVAL; }
            Serial.print(F("Pulse interval: "));
            Serial.println(String(pulse_interval_sec) + " s");
            pulse_interval_ms =  (int) (1000.0*pulse_interval_sec/510.0);

            EEPROM.put( (2*sizeof(float)), pulse_interval_sec);
            Serial.print(F("EEPROM update 4 time: "));
            Serial.print(pulse_interval_sec);
            Serial.print(F(" "));
            Serial.println(pulse_interval_ms);
            //delay(CHANGE_INTERVAL);
          }
          br_button_minus = false;
        } 
      }
      
      if ( millis() > (timer_4_1 + pulse_interval_ms + pause_ms ) )
      {
        timer_4_1 = millis();
        //add ease in //add sinus
        if (turn_on_way == true)
        {
          if (br_pulse < MAX_BRIGHTNESS_4_MODE)
          {
            br_pulse++;
            FastLED.setBrightness(br_pulse);
            FastLED.show();
            Serial.println(br_pulse);
            pause_ms = 0;
            //delay((int) (1000*pulse_interval_sec/510.0)); 
          } else if (br_pulse == MAX_BRIGHTNESS_4_MODE) {
            Serial.println("pause_2");
            turn_on_way = false;
            //pause_ms = pulse_interval_ms*10;
          }
        }
        //add ease out
        if (turn_on_way == false)
        {
          if (br_pulse > MIN_BRIGHTNESS_4_MODE)
          {
            br_pulse--;
            FastLED.setBrightness(br_pulse);
            FastLED.show();
            Serial.println(br_pulse);
            pause_ms = 0;
            //delay((int) (1000*pulse_interval_sec/510.0));
          } else if (br_pulse == MIN_BRIGHTNESS_4_MODE) {
            Serial.println("pause_1");
            turn_on_way = true;
            pause_ms = pulse_interval_ms*10;
          }
        }
      }
      break;
    case 5: //5 segments turn on all together LEDs in segment
      //Serial.println("6 mode select");

      if ( millis() > (timer_5_1 + CHANGE_INTERVAL) )
      {
        timer_5_1 = millis();
        if (digitalRead(INCREASE_PIN) || (br_button_plus == true) ) {
          
          if (m5_switch_interval < MAX_SWITCH_INTERVAl) {
            m5_switch_interval++; 
            if (m5_switch_interval > MAX_SWITCH_INTERVAl) { m5_switch_interval = MAX_SWITCH_INTERVAl; }
            Serial.print(F("Switch interval: "));
            Serial.println(String(m5_switch_interval) + " s");
            bright_button_plus = false;

            EEPROM.put( (4*sizeof(float)), m5_switch_interval);
            Serial.print(F("EEPROM update 5 time: "));
            Serial.println(m5_switch_interval);
          }
          br_button_plus = false;
          
        } else if (digitalRead(DECREASE_PIN) || (br_button_minus == true) ) {

          if (m5_switch_interval < MIN_SWITCH_INTERVAl) {
            m5_switch_interval--; 
            if (m5_switch_interval < MIN_SWITCH_INTERVAl) { m5_switch_interval = MIN_SWITCH_INTERVAl; }
            Serial.print(F("Switch interval: "));
            Serial.println(String(m5_switch_interval) + " s");
            bright_button_minus = false;

            EEPROM.put( (4*sizeof(float)), m5_switch_interval);
            Serial.print(F("EEPROM update 5 time: "));
            Serial.println(m5_switch_interval);
          }
          br_button_minus = false;
          
        } else if (bright_button_plus == true) {

          if (br_button_5 < MAX_BRIGHTNESS) {
            //br_button_5++;
            br_button_5 += BR_STEP_5_MODE; 
            if (br_button_5 > MAX_BRIGHTNESS) { br_button_5 = MAX_BRIGHTNESS; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button_5);
            FastLED.setBrightness(br_button_5);
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();

            EEPROM.put( (5*sizeof(float)), br_button_5);
            Serial.print(F("EEPROM update 5 bright: "));
            Serial.println(br_button_5);
            //delay(CHANGE_INTERVAL);
          }

        } else if (bright_button_minus == true) {
          
          if (br_button_5 > MIN_BRIGHTNESS_5_MODE) {
            //br_button_5--;
            br_button_5 -= BR_STEP_5_MODE;
            if (br_button_5 < MIN_BRIGHTNESS_5_MODE) { br_button_5 = MIN_BRIGHTNESS_5_MODE; }
            Serial.print(F("Brightness: "));
            Serial.println(br_button_5);
            FastLED.setBrightness(br_button_5); //or apply after button turn off pause
            FastLED.setTemperature( SELECT_TEMPERATURE );
            FastLED.show();

            EEPROM.put( (5*sizeof(float)), br_button_5);
            Serial.print(F("EEPROM update 5 bright: "));
            Serial.println(br_button_5);
            //delay(CHANGE_INTERVAL);
          }
        }
      }

      if ( (turn_on_way == true) && (start_br_up == true) )
      {
          if (br_var <= MAX_BRIGHTNESS_5_MODE)
          //for (int br_var = MIN_BRIGHTNESS_5_MODE; br_var < br_button_5; br_var+=5)
          {
            for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++)
            {
              //leds[n] = CRGB::White;
              leds[n] = CRGB(br_var, br_var, br_var);
            }
            Serial.println(String(n_sect) + " " + String(br_var) + " on");
            FastLED.show();
            delay(10);
            if (br_var < MAX_BRIGHTNESS_5_MODE) {
              //br_var++;
              
              if ( (br_var + 10) < MAX_BRIGHTNESS_5_MODE ) { br_var += 10; } else { br_var = MAX_BRIGHTNESS_5_MODE; }  //5 
              
            } else if (br_var = MAX_BRIGHTNESS_5_MODE) {
              br_var = MIN_BRIGHTNESS_5_MODE;
              n_sect++;
              start_br_up = false;
            }
          }
      }

      if ( (turn_on_way == false) && (start_br_up == false) )
      {

          if (br_var >= MIN_BRIGHTNESS_5_MODE)
          //for (int br_var = MIN_BRIGHTNESS_5_MODE; br_var < br_button_5; br_var+=5)
          {
            for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++)
            {
              //leds[n] = CRGB::White;
              leds[n] = CRGB(br_var, br_var, br_var);
            }
            Serial.println(String(n_sect) + " " + String(br_var) + " off");
            FastLED.show();
            delay(10);
            if (br_var > MIN_BRIGHTNESS_5_MODE) {
              //br_var--;
              
              if ( (br_var - 10) > MIN_BRIGHTNESS_5_MODE ) { br_var -= 10; } else { br_var = MIN_BRIGHTNESS_5_MODE; }  //5 
              
            } else if (br_var = MIN_BRIGHTNESS_5_MODE) {
              br_var = MAX_BRIGHTNESS_5_MODE;
              n_sect++;
              start_br_up = true;
            }
          }
      }


      if ( ( millis() > timer_5 + (SEGMENTS_ON_INTERVAL*1000/NUNMBER_SECTORS) ) )
      {
        timer_5 = millis();
        if ( (turn_on_way == true) && (start_br_up == false) )
        {
          if (n_sect < NUNMBER_SECTORS)
          {
            br_var = MIN_BRIGHTNESS_5_MODE;

            start_br_up = true;
            
            //delay(SEGMENTS_ON_INTERVAL*1000/NUNMBER_SECTORS);
          } else if (n_sect == NUNMBER_SECTORS) {
            turn_on_way = false;
            n_sect = 0;
            br_var = MAX_BRIGHTNESS_5_MODE;
            //delay(SEGMENTS_ON_INTERVAL*1000/NUNMBER_SECTORS);
          }
        }

        if ( (turn_on_way == false) && (start_br_up == true) )
        {
          if (n_sect < NUNMBER_SECTORS)
          {

            start_br_up = false;
            br_var = MAX_BRIGHTNESS_5_MODE;
            
            //delay(SEGMENTS_ON_INTERVAL*1000/NUNMBER_SECTORS);
          } else if (n_sect == NUNMBER_SECTORS) {
            turn_on_way = true;
            n_sect = 0;
            br_var = MIN_BRIGHTNESS_5_MODE;
          }
          
        }
      }
      
      break;
    case 6: //lightmusic white 3 brightness of 5 sectors
      //Serial.println("7 mode select");

      // Sampling
      for(int i = 0; i < SAMPLES; i++)
      {
        //while(!(ADCSRA & 0x10));        // wait for ADC to complete current conversion ie ADIF bit set
        //ADCSRA = 0b11110101 ;               // clear ADIF bit so that ADC can do next operation (0xf5)
        int ADC_11 = analogRead(A0);
        //int value = ADC_11 - 512 ;                 // Read from ADC and subtract DC offset caused value
        int value = ADC_11 ;                 // Read from ADC and subtract DC offset caused value
        //int value = ADC - 512 ;
        //Serial.print(String(value) + " ");
        vReal[i] = value / 8;                      // Copy to bins after compressing
        vImag[i] = 0;
      }
      //Serial.println();
   
      // FFT
      FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
      FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
      
      // ++ re-arrange FFT result to match with number of columns ( xres )
      step = ( SAMPLES / 2 )/xres;
      c = 0;
      for(int i = 0; i < ( SAMPLES / 2 ); i += step)
      {
        data_avgs[c] = 0;
        for (int k = 0; k < step; k++) {
            data_avgs[c] = data_avgs[c] + vReal[i + k];
        }
        data_avgs[c] = data_avgs[c] / step;
        c++;

        str_1 = str_1 + " " + String((byte) data_avgs[c]);
      }
      Serial.println(str_1);
      str_1 = "";
  
      if ( millis() < (timer_6 + SOUND_CHANGE_INTERVAL) )
      { //find max
        //data_avgs[i] = constrain(data_avgs[i], 0, 255);
        for(int i = 0; i < xres; i++)
        {
          if (data_avgs[xres - 1 - i] > br_freq[xres - 1 - i])
          {
            br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          }
        }
        
      } else {
        
        timer_6 = millis();
        for(int i = 0; i < xres; i++)
        {
          //Serial.print("max val before constrain ");
          //Serial.println(br_freq[xres - 1 - i]);
          
          //br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], MIN_LIGHTMUSIC_BRIGHTNESS, MAX_LIGHTMUSIC_BRIGHTNESS);
          br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], sectors_eq_arr[(xres - i)][0], sectors_eq_arr[(xres - i)][1]);
          
          //str_1 = str_1 + " " + String(br_freq[xres - 1 - i]);
          
          //data_avgs[i] = constrain(data_avgs[i], 0, 255);            // set max & min values for buckets 0 80
          //br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          
          if (br_freq[xres - 1 - i] > 255) {br_freq[xres - 1 - i] = 255;}
          //Serial.println(String(xres - 1 - i) + " " + String(br_freq[xres - 1 - i]) + "  ");
            
            if (i >= (xres - NUNMBER_SECTORS) )
            {
              n_sect = xres - 1 - i; //  - (xres - NUNMBER_SECTORS)   0 1 low freq  2 3 mid freq  4 5 - high freq
              for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++)
              {
                leds[n] = CRGB(br_freq[xres - 1 - i], br_freq[xres - 1 - i], br_freq[xres - 1 - i]);
                //Serial.println(String(n_sect) + " " + String(n) + " " + String(br_freq[xres - 1 - i]));
              }
              FastLED.show();
            }
         }

         //Serial.println(str_1);
         //str_1 = "";
          
         memset(br_freq, 0, sizeof(br_freq)); //clear array
         //Serial.println();
      }
      break;
    case 7: //lightmusic RGB 3 brightness of 5 sectors
      //Serial.println("7 mode select");

      if ( millis() > (timer_7_1 + CHANGE_INTERVAL) )
      {
        timer_7_1 = millis();
        //pulse interval change
        if ( digitalRead(INCREASE_PIN) || (br_button_plus == true) ) { //select color  x10
          
          if ( (segments_colors[selected_segment] + 1) <= MAX_BRIGHTNESS) { //10
            segments_colors[selected_segment] += 1; //10
          } else {
            segments_colors[selected_segment] = 0;
          }

          Serial.print("Color: ");
          Serial.println(String(segments_colors[selected_segment]));
          
          br_button_plus = false;
        } 
      }

      if ( millis() > (timer_7_2 + CHANGE_INTERVAL_SELECT_BUTTON) )
      {
        timer_7_2 = millis();
        if ( digitalRead(DECREASE_PIN) || (br_button_minus == true)  ) { //select segment

          selected_segment += 1;
          if (selected_segment > NUNMBER_SECTORS) {
            selected_segment = 1;
          }
          Serial.print(F("Segment: "));
          Serial.println(String(selected_segment));
          Serial.println();
          
          for (seg = 1; seg <= NUNMBER_SECTORS; seg++)
          {
            Serial.print(F("Segment: "));
            Serial.print(String(seg));  
            Serial.print(F("  color: "));
            Serial.println(String(segments_colors[seg]));
          }
          br_button_minus = false;
        }
      }

      // Sampling
      for(int i=0; i<SAMPLES; i++)
      {
        //while(!(ADCSRA & 0x10));        // wait for ADC to complete current conversion ie ADIF bit set
        //ADCSRA = 0b11110101 ;               // clear ADIF bit so that ADC can do next operation (0xf5)
        int ADC_11 = analogRead(A0);
        //int value = ADC_11 - 512 ;                 // Read from ADC and subtract DC offset caused value
        int value = ADC_11 ;                 // Read from ADC and subtract DC offset caused value
        //int value = ADC - 512 ;
        //Serial.print(String(value) + " ");
        vReal[i]= value / 8;                      // Copy to bins after compressing
        vImag[i] = 0;                         
      }
      //Serial.println();
   
      // FFT
      FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
      FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
      
      // ++ re-arrange FFT result to match with number of columns ( xres )
      step = (SAMPLES/2)/xres;
      c = 0;
      for(int i = 0; i < (SAMPLES/2); i += step)
      {
        data_avgs[c] = 0;
        for (int k = 0; k < step; k++) {
            data_avgs[c] = data_avgs[c] + vReal[i + k];
        }
        data_avgs[c] = data_avgs[c] / step;
        c++;

        str_2 = str_2 + " " + String((byte) data_avgs[c]);
      }
      Serial.println(str_2);
      str_2 = "";
  
      if ( millis() < (timer_7 + SOUND_CHANGE_INTERVAL) )
      { //find max
        //data_avgs[i] = constrain(data_avgs[i], 0, 255);
        for(int i = 0; i < xres; i++)
        {
          if (data_avgs[xres - 1 - i] > br_freq[xres - 1 - i])
          {
            br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          }
        }
      } else {
        
        timer_7 = millis();
        for(int i = 0; i < xres; i++)
        {
          if ((xres - 1 - i) == white_sector)
          {
            br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], W_SEC_MIN_LIGHTMUSIC_BRIGHTNESS, W_SEC_MAX_LIGHTMUSIC_BRIGHTNESS); //MIN_LIGHTMUSIC_BRIGHTNESS
          } else {
            //br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], MIN_LIGHTMUSIC_BRIGHTNESS, MAX_LIGHTMUSIC_BRIGHTNESS); //MIN_LIGHTMUSIC_BRIGHTNESS
            //br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], sectors_eq_arr[(xres - 1 - i)][0], sectors_eq_arr[(xres - 1 - i)][1]);
            br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], sectors_eq_arr[(xres - i)][0], sectors_eq_arr[(xres - i)][1]); //xres = 8
          }
          
          //sectors_eq_arr[(xres - 1 - i)][0]; //MIN
          //sectors_eq_arr[(xres - 1 - i)][1]; //MAX
          
          //data_avgs[i] = constrain(data_avgs[i], 0, 255);            // set max & min values for buckets 0 80
          //br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          
          if (br_freq[xres - 1 - i] > 255) {br_freq[xres - 1 - i] = 255;}
          
            if (i >= (xres - NUNMBER_SECTORS) )
            {
              n_sect = xres - 1 - i; //  - (xres - NUNMBER_SECTORS)   0 1 low freq  2 3 mid freq  4 5 - high freq
              for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++)
              {
                if ( (n >= n_led_segments[white_sector][0]) && (n <= n_led_segments[white_sector][1]) )
                {
                  leds[n] = CRGB(br_freq[xres - 1 - i], br_freq[xres - 1 - i], br_freq[xres - 1 - i]);
                } else {
                  leds[n] = CHSV(segments_colors[n_sect + 1], 255, br_freq[xres - 1 - i]); //or random saturation
                }
              }
              FastLED.show();
            }
         }
         memset(br_freq, 0, sizeof(br_freq)); //clear array
      }
      break;
    case 8: //lightmusic white 3 position of 5 sectors
      //Serial.println("7 mode select");

      // Sampling
      for(int i = 0; i < SAMPLES; i++)
      {
        //while(!(ADCSRA & 0x10));        // wait for ADC to complete current conversion ie ADIF bit set
        //ADCSRA = 0b11110101 ;               // clear ADIF bit so that ADC can do next operation (0xf5)
        int ADC_11 = analogRead(A0);
        //int value = ADC_11 - 512 ;                 // Read from ADC and subtract DC offset caused value
        int value = ADC_11 ;                 // Read from ADC and subtract DC offset caused value
        //int value = ADC - 512 ;
        //Serial.print(String(value) + " ");
        vReal[i] = value / 8;                      // Copy to bins after compressing
        vImag[i] = 0;
      }
      //Serial.println();
   
      // FFT
      FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
      FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
      
      // ++ re-arrange FFT result to match with number of columns ( xres )
      step = ( SAMPLES / 2 )/xres;
      c = 0;
      for(int i = 0; i < ( SAMPLES / 2 ); i += step)
      {
        data_avgs[c] = 0;
        for (int k = 0; k < step; k++) {
            data_avgs[c] = data_avgs[c] + vReal[i + k];
        }
        data_avgs[c] = data_avgs[c] / step;
        c++;

        str_1 = str_1 + " " + String((byte) data_avgs[c]);
      }
      Serial.println(str_1);
      str_1 = "";
  
      if ( millis() < (timer_6 + SOUND_CHANGE_INTERVAL) )
      { //find max
        //data_avgs[i] = constrain(data_avgs[i], 0, 255);
        for(int i = 0; i < xres; i++)
        {
          if (data_avgs[xres - 1 - i] > br_freq[xres - 1 - i])
          {
            br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          }
        }
        
      } else {
        
        timer_6 = millis();
        for(int i = 0; i < xres; i++)
        {
          //Serial.print("max val before constrain ");
          //Serial.println(br_freq[xres - 1 - i]);
          
          //br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], MIN_LIGHTMUSIC_BRIGHTNESS, MAX_LIGHTMUSIC_BRIGHTNESS);
          br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], sectors_eq_arr[(xres - i)][0], sectors_eq_arr[(xres - i)][1]);
          
          //str_1 = str_1 + " " + String(br_freq[xres - 1 - i]);
          
          //data_avgs[i] = constrain(data_avgs[i], 0, 255);            // set max & min values for buckets 0 80
          //br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          
          if (br_freq[xres - 1 - i] > 255) {br_freq[xres - 1 - i] = 255;}
          //Serial.println(String(xres - 1 - i) + " " + String(br_freq[xres - 1 - i]) + "  ");
            
            if (i >= (xres - NUNMBER_SECTORS) )
            {
              n_sect = xres - 1 - i; //  - (xres - NUNMBER_SECTORS)   0 1 low freq  2 3 mid freq  4 5 - high freq
              for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++)
              {
                //leds[n] = CRGB(br_freq[xres - 1 - i], br_freq[xres - 1 - i], br_freq[xres - 1 - i]);
                leds[serial_LED_n[n]] = CRGB(br_freq[xres - 1 - i], br_freq[xres - 1 - i], br_freq[xres - 1 - i]);
                //Serial.println(String(n_sect) + " " + String(n) + " " + String(br_freq[xres - 1 - i]));
              }
              FastLED.show();
            }
         }

         //Serial.println(str_1);
         //str_1 = "";
          
         memset(br_freq, 0, sizeof(br_freq)); //clear array
         //Serial.println();
      }
      break;
    case 9: //lightmusic RGB 3 brightness of 6 sectors
      //Serial.println("7 mode select");

      if ( millis() > (timer_7_1 + CHANGE_INTERVAL) )
      {
        timer_7_1 = millis();
        //pulse interval change
        if ( digitalRead(INCREASE_PIN) || (br_button_plus == true) ) { //select color  x10
          
          if ( (segments_colors[selected_segment] + 1) <= MAX_BRIGHTNESS) { //10
            segments_colors[selected_segment] += 1; //10
          } else {
            segments_colors[selected_segment] = 0;
          }

          Serial.print("Color: ");
          Serial.println(String(segments_colors[selected_segment]));
          
          br_button_plus = false;
        } 
      }

      if ( millis() > (timer_7_2 + CHANGE_INTERVAL_SELECT_BUTTON) )
      {
        timer_7_2 = millis();
        if ( digitalRead(DECREASE_PIN) || (br_button_minus == true)  ) { //select segment

          selected_segment += 1;
          if (selected_segment > NUNMBER_SECTORS) {
            selected_segment = 1;
          }
          Serial.print(F("Segment: "));
          Serial.println(String(selected_segment));
          Serial.println();
          
          for (seg = 1; seg <= NUNMBER_SECTORS; seg++)
          {
            Serial.print(F("Segment: "));
            Serial.print(String(seg));  
            Serial.print(F("  color: "));
            Serial.println(String(segments_colors[seg]));
          }
          br_button_minus = false;
        }
      }

      // Sampling
      for(int i=0; i<SAMPLES; i++)
      {
        //while(!(ADCSRA & 0x10));        // wait for ADC to complete current conversion ie ADIF bit set
        //ADCSRA = 0b11110101 ;               // clear ADIF bit so that ADC can do next operation (0xf5)
        int ADC_11 = analogRead(A0);
        //int value = ADC_11 - 512 ;                 // Read from ADC and subtract DC offset caused value
        int value = ADC_11 ;                 // Read from ADC and subtract DC offset caused value
        //int value = ADC - 512 ;
        //Serial.print(String(value) + " ");
        vReal[i]= value / 8;                      // Copy to bins after compressing
        vImag[i] = 0;                         
      }
      //Serial.println();
   
      // FFT
      FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
      FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
      FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
      
      // ++ re-arrange FFT result to match with number of columns ( xres )
      step = (SAMPLES/2)/xres;
      c = 0;
      for(int i = 0; i < (SAMPLES/2); i += step)
      {
        data_avgs[c] = 0;
        for (int k = 0; k < step; k++) {
            data_avgs[c] = data_avgs[c] + vReal[i + k];
        }
        data_avgs[c] = data_avgs[c] / step;
        c++;

        str_2 = str_2 + " " + String((byte) data_avgs[c]);
      }
      Serial.println(str_2);
      str_2 = "";
  
      if ( millis() < (timer_7 + SOUND_CHANGE_INTERVAL) )
      { //find max
        //data_avgs[i] = constrain(data_avgs[i], 0, 255);
        for(int i = 0; i < xres; i++)
        {
          if (data_avgs[xres - 1 - i] > br_freq[xres - 1 - i])
          {
            br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          }
        }
      } else {
        
        timer_7 = millis();
        for(int i = 0; i < xres; i++)
        {
          if ((xres - 1 - i) == white_sector)
          {
            br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], W_SEC_MIN_LIGHTMUSIC_BRIGHTNESS, W_SEC_MAX_LIGHTMUSIC_BRIGHTNESS); //MIN_LIGHTMUSIC_BRIGHTNESS
          } else {
            //br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], MIN_LIGHTMUSIC_BRIGHTNESS, MAX_LIGHTMUSIC_BRIGHTNESS); //MIN_LIGHTMUSIC_BRIGHTNESS
            //br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], sectors_eq_arr[(xres - 1 - i)][0], sectors_eq_arr[(xres - 1 - i)][1]);
            br_freq[xres - 1 - i] = constrain(br_freq[xres - 1 - i], sectors_eq_arr[(xres - i)][0], sectors_eq_arr[(xres - i)][1]); //xres = 8
          }
          
          //sectors_eq_arr[(xres - 1 - i)][0]; //MIN
          //sectors_eq_arr[(xres - 1 - i)][1]; //MAX
          
          //data_avgs[i] = constrain(data_avgs[i], 0, 255);            // set max & min values for buckets 0 80
          //br_freq[xres - 1 - i] = data_avgs[xres - 1 - i];
          
          if (br_freq[xres - 1 - i] > 255) {br_freq[xres - 1 - i] = 255;}
          
            if (i >= (xres - NUNMBER_SECTORS) )
            {
              n_sect = xres - 1 - i; //  - (xres - NUNMBER_SECTORS)   0 1 low freq  2 3 mid freq  4 5 - high freq
              for (n = n_led_segments[n_sect][0]; n <= n_led_segments[n_sect][1]; n++)
              {
                if ( (n >= n_led_segments[white_sector][0]) && (n <= n_led_segments[white_sector][1]) )
                {
                  //leds[n] = CRGB(br_freq[xres - 1 - i], br_freq[xres - 1 - i], br_freq[xres - 1 - i]);
                  leds[serial_LED_n[n]] = CRGB(br_freq[xres - 1 - i], br_freq[xres - 1 - i], br_freq[xres - 1 - i]);
                } else {
                  //leds[n] = CHSV(segments_colors[n_sect + 1], 255, br_freq[xres - 1 - i]); //or random saturation
                  leds[serial_LED_n[n]] = CHSV(segments_colors[n_sect + 1], 255, br_freq[xres - 1 - i]);
                }
              }
              FastLED.show();
            }
         }
         memset(br_freq, 0, sizeof(br_freq)); //clear array
      }
      break;
  }
}
