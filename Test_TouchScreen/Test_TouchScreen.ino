#include <SPI.h>
#include <TFT_eSPI.h>
#include <TouchScreen.h>

#define MINPRESSURE 10
#define MAXPRESSURE 40000
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

//        D6_LCD   LCD_RS   LCD_WR   D7_LCD
const int XP = 18, XM = 14, YP = 12, YM = 17; //ID=0x9341

const int TS_LEFT = 380, TS_RT = -2700, TS_TOP = -2500, TS_BOT = 520;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
    
    TSPoint p = ts.getPoint();
   
    
 
     p.z=abs(p.z);
    
     if(!(p.z)==0)
     {
      Serial.println(p.z);
     
    
        Serial.print("pixel_x:");
        Serial.print(p.x);
        Serial.print(", pixel_y:");
        Serial.println(p.y);
}
 
    bool pressed = (p.z>0 && p.y < 700);
   
    if (pressed) 
    {
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
         
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
     
        Serial.print("pixel_x:");
        Serial.print(pixel_x);
        Serial.print(", pixel_y:");
        Serial.println(pixel_y);
       
        p.z=0;
       
    }
    return pressed;
    
}

void setup()
{
  Serial.begin(9600);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLUE);
  tft.setTextSize(3);
  tft.setCursor(60,20);
  tft.setTextColor(TFT_WHITE);
  tft.print("ESP   Scale");
  Serial.println("ESP Scale");
  tft.setTextSize(2); 
}

void loop()
{
    
    
        tft.setTextColor(TFT_GREEN);
        tft.fillRect(40,120,300,30,TFT_BLUE);
        tft.setTextColor(TFT_WHITE);
        tft.setCursor(40,120);
        tft. print ("X = ");
        tft.print(pixel_x);
        tft.setCursor(160,120);
        tft. print ("Y = ");
        tft.print(pixel_y);
        delay(10);
        bool down = Touch_getXY();
        
}
