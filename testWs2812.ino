/*http://www.fablabredon.org/wordpress/2017/12/17/lumiere-sur-larduino-avec-de-la-couleur-et-des-led/*/
/*https://learn.adafruit.com/florabrella/test-the-neopixel-strip*/

#include <Adafruit_NeoPixel.h> // Charge la librairie Neo Pixel d'Adafruit utilisé pour piloter le ruban de LED

#define PIXEL_PIN 6 // On définit le pin où est connecté la patte DATA du bandeau
#define PIXEL_COUNT 64 // On définit le nombre de LED compris sur le Ruban de LED soit 150 pour le ruban de 5m50

/* Définition des couleurs */
int RED[3] = {255, 0, 0}; // Couleur Rouge
int GREEN[3] = {0, 255, 0}; // Couleur Verte
int CYAN[3] = {0, 255, 255}; // Couleur Cyan
int YELLOW[3] = {255, 125, 0}; // Couleur Jaune
int ORANGE[3] = {255, 40, 0}; // Couleur Orange
int PURPLE[3] = {255, 0 , 255}; // Couleur Violette
int PINK[3] = {255, 0, 100}; // Couleur Rose
int BLUE[3] = {0, 0, 255}; // Couleur Bleu
int WHITE[3] = {255, 255, 255}; // Couleur Blanche

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800); // Paramètre l'objet strip qui correspond à toute les LED du ruban
 
 void setup() {
  strip.begin(); // Lance la connection
   strip.show(); // Initialise toute les led à 'off'
}

void loop() {
  all(0, 255, 255, 255);
  delay(1000); 
  all(0, 0, 0, 0);
  delay(1000); 
  
  chenillardUp(10, 255, 255, 255);
  delay(1000); 

  progressiveUp(0, 125, 125, 125);
  delay(1000); 
  
  anim_nineColor(0);
  delay(1000); 

  anim_rainbowCycle(0);
  delay(1000); 

  anim_theaterChaseRainbow(0);
  delay(1000); 

  anim_fire();
  delay(1000); 

  anim_allBiColor(0,PURPLE, CYAN);
  delay(1000); 

  anim_changeColor(20,GREEN, ORANGE);
  delay(1000); 
  
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void chenillardUp(int temps, int r, int v, int b)
{
  for(int i = 0 ; i < PIXEL_COUNT ; i++)
  {
     strip.setPixelColor(i, r, v, b);
        strip.show();
            strip.setPixelColor(i, 0, 0, 0);
        strip.show();
          delay(temps);  
  }
}

void all(int temps, int r, int v, int b)
{
   for(int i = 0 ; i < PIXEL_COUNT ; i++)
  {
     strip.setPixelColor(i, r, v, b);
  }
  strip.show();
   delay(temps); 
}

void progressiveUp(int temps, int r, int v, int b)
{
  for(int lumi = 0 ; lumi < 100 ; lumi++)
  {
     for(int i = 0 ; i < PIXEL_COUNT ; i++)
    {
       strip.setPixelColor(i, r, v, b);
    }
    strip.setBrightness(lumi); 
    strip.show();
     delay(temps);
  }
}

void anim_nineColor(int temps)
{
  for(int i = 0 ; i < PIXEL_COUNT ; i = i + 9)
  {
   strip.setPixelColor(i, RED[0], RED[1], RED[2]);
   strip.setPixelColor(i+1, GREEN[0], GREEN[1], GREEN[2]);
   strip.setPixelColor(i+2, CYAN[0], CYAN[1], CYAN[2]);
   strip.setPixelColor(i+3, YELLOW[0], YELLOW[1], YELLOW[2]);
     strip.setPixelColor(i+4, ORANGE[0], ORANGE[1], ORANGE[2]);
     strip.setPixelColor(i+5, PURPLE[0], PURPLE[1], PURPLE[2]);
     strip.setPixelColor(i+6, PINK[0], PINK[1], PINK[2]);
     strip.setPixelColor(i+7, BLUE[0], BLUE[1], BLUE[2]);
     strip.setPixelColor(i+8, WHITE[0], WHITE[1], WHITE[2]);
  }  
   strip.show();
   delay(temps);
}

/*
  Animation : Effet de vague avec toute les couleur
    > uint8_t wait => temps d'attente en ms
 */
  
void anim_rainbowCycle(uint8_t wait) {
  uint16_t i, j, numbers;
  numbers = 256 * 5;
  
  for(j=0; j < numbers; j++) { // 5 cycles of all colors on wheel
    for(i=0; i < PIXEL_COUNT; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / PIXEL_COUNT) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

/*
  Animation : Effet lumière manège
    > uint8_t wait => temps d'attente en ms
 */
 
void anim_theaterChaseRainbow(uint8_t wait) {
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < PIXEL_COUNT; i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();
  
      delay(wait*2.5);

      for (int i=0; i < PIXEL_COUNT; i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

/*
  Animation : Effet flame
 */
 
void anim_fire()
{
  int r = ORANGE[0];
  int g = ORANGE[1]+5;
  int b = ORANGE[2];
  
  int variation = 45;
  
  for(int x = 0; x <PIXEL_COUNT; x++)
  {
    int flicker = random(0,variation);
    int r1 = r-flicker;
    int g1 = g-flicker;
    int b1 = b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip.setPixelColor(x,r1,g1, b1);
  }
  strip.show();
  delay(random(50,115));
}

/*
  Animation : Effet deux couleur
  > int temps => temps en ms
  > int colorLeft => Couleur de Gauche
  > int colorRight => Couleur de Droite
*/

void anim_allBiColor( int temps, int colorLeft[3], int colorRight[3])
{

        for(int i = 0 ; i < PIXEL_COUNT/2 ; i++)
            {
               strip.setPixelColor(i, colorRight[0], colorRight[1], colorRight[2]);
            }
            for(int i = PIXEL_COUNT/2 ; i < PIXEL_COUNT ; i++)
            {
               strip.setPixelColor(i, colorLeft[0], colorLeft[1], colorLeft[2]);
            }
          strip.show();
           delay(temps);
  
}

/*
  Animation : Changement d'une couleur à une autre de manière progressive
    > int temps => temps d'attente en ms
    > int colorDebut => Couleur 1
     > int colorFin => Couleur 2
 */
 
void anim_changeColor(int temps, int colorDebut[3], int colorFin[3])
{
  
  int color[3] = {0};
  
  color[0] = colorDebut[0];
  color[1] = colorDebut[1];
  color[2] = colorDebut[2];
  
 while(color[0] != colorFin[0] || color[1] != colorFin[1] || color[2] != colorFin[2])
  {
    
    if(color[0] > colorFin[0])
    {
      color[0]--;
    }
    else if(color[0] < colorFin[0])
    {
      color[0]++;
    }
    
     if(color[1] > colorFin[1])
    {
      color[1]--;
    }
    else if(color[1] < colorFin[1])
    {
      color[1]++;
    }
    
     if(color[2] > colorFin[2])
    {
      color[2]--;
    }
    else if(color[2] < colorFin[2])
    {
      color[2]++;
    }
    
    all(temps, color[0], color[1], color[2]);
  }
}
