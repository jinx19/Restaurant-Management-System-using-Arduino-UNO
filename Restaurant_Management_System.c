#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h> 
#include<Wire.h>
 
#define FIREBASE_HOST "--------------------------------" // Firebase host
#define FIREBASE_AUTH "--------------------------------" //Firebase Auth code

#define WIFI_SSID "-_-_-_-_" //Enter your wifi Name
#define WIFI_PASSWORD "_-_-_-_" // Enter your password
int fireStatus = 0;

const byte ROWS = 4; 
const byte COLS = 4;

LiquidCrystal_I2C lcd(0X27,16,2);

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {D7, D6, D5, D4}; 
byte colPins[COLS] = {D3, D8, D3, D0};

char order[3];

void fillOrder(int position,char x){
  order[position]=x;
}

int bill=0;

int billCalculator() {
  bill=(int)order[1]*(int)order[2];
  return bill;
}
void funA();
void funNumA();
void funB();
void funNumB();
void funC();
void funNumC();
void funD();
void funNumD();
void funHash();
void funNumHash();
void serverCall(String);


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin();
  pinMode(3, FUNCTION_3);
  pinMode(3, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected.");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//  Firebase.reconnectWiFi(true);
  

  lcd.setCursor(2, 0);
  lcd.print("WELCOME!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TO ORDER PRESS *");
  lcd.setCursor(0, 1);
  lcd.print("TO EXIT PRESS 9");
  delay(2000);
}



void loop(){
  char key = keypad.getKey();
  Serial.print(key);
  if (key=='*'){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("PRESS APPROP");
    lcd.setCursor(5,1);
    lcd.print("BUTTON");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A : BREAKFAST");
    lcd.setCursor(0,1);
    lcd.print("B : STARTERS");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("C : VEG MENU");
    lcd.setCursor(0,1);
    lcd.print("D:NON-VEG MENU");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("# : DESSERTS");
    delay(1000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("PRESS APPROP");
    lcd.setCursor(5,1);
    lcd.print("BUTTON");
    delay(1000);
    lcd.clear();
  }

    switch(key){
      case 'A':{
         funA();
         break;
      }
      case 'B':{
        funB();
        break;
      }
      case 'C':{
         funC();
         break;
      }
      case 'D':{
         funD();
         break;
      }
      case '#':{
         funHash();
         break;
      }
      default:{
        break;
      }
    }
    
}


void funA(){
  lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1 : IDLI");
      lcd.setCursor(0,1);
      lcd.print("7 : DOSA");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3 : VADA");
      lcd.setCursor(0,1);
      lcd.print("4 : PURI");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("0 : EXIT");
      delay(1000);
      lcd.clear();
      char key1=keypad.getKey();
      while(key1 == NO_KEY){
        key1=keypad.getKey();
        Serial.print(key1);

      }
      fillOrder(0,'A');
      fillOrder(1,key1);
      funNumA();
}



void funNumA(){
      lcd.setCursor(0,0);
      lcd.print("No.of plates to");
      lcd.setCursor(0,1);
      lcd.print("be ordered: ");
      delay(1000);
      char n;
      n=keypad.getKey();
      while(n == NO_KEY){
        n=keypad.getKey();
        Serial.print(n);
      }
      fillOrder(2,n);
      int bill=billCalculator();
      serverCall(order,bill);
}


void funB(){
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1:DRY CHICKEN");
      lcd.setCursor(0,1);
      lcd.print("7:BUTTER-NAAN");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3:TANDOORI");
      lcd.setCursor(0,1);
      lcd.print("4:CHICKEN-65");
      delay(1000);
      lcd.clear();
      char key1=keypad.getKey();
      while(key1 == NO_KEY){
        key1=keypad.getKey();
        Serial.print(key1);

      }
      fillOrder(0,'B');
      fillOrder(1,key1);
      funNumB();
}


void funNumB(){
      lcd.setCursor(0,0);
      lcd.print("No.of plates to");
      lcd.setCursor(0,1);
      lcd.print("be ordered: ");
      delay(1000);
      char n;
      n=keypad.getKey();
      while(n == NO_KEY){
        n=keypad.getKey();
        Serial.print(n);
      }
      fillOrder(2,n);
      int bill=billCalculator();
      serverCall(order,bill);
}


void funC(){
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1:CHICKEN BIR.");
      lcd.setCursor(0,1);
      lcd.print("7:MUTTON BIR.");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3:SP.FRIEDRICE");
      lcd.setCursor(0,1);
      lcd.print("4:FULL MEALS");
      delay(1000);
      lcd.clear();
      char key1=keypad.getKey();
      while(key1 == NO_KEY){
        key1=keypad.getKey();
        Serial.print(key1);
      }
      fillOrder(0,'C');
      fillOrder(1,key1);
      funNumC();
}
void funNumC(){
      lcd.setCursor(0,0);
      lcd.print("No.of plates to");
      lcd.setCursor(0,1);
      lcd.print("be ordered: ");
      delay(1000);
      char n;
      n=keypad.getKey();
      while(n == NO_KEY){
        n=keypad.getKey();
        Serial.print(n);
      }
      fillOrder(2,n);
      int bill=billCalculator();
      serverCall(order,bill);
}

void funD(){
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1:PULAV");
      lcd.setCursor(0,1);
      lcd.print("7:FULL MEALS");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3:FRIED RICE");
      lcd.setCursor(0,1);
      lcd.print("4:PANEER RICE");
      delay(1000);
      lcd.clear();
      char key1=keypad.getKey();
      while(key1 == NO_KEY){
        key1=keypad.getKey();
        Serial.print(key1);

      }
      fillOrder(0,'D');
      fillOrder(1,key1);
      funNumD();
}

      
void funNumD(){
      lcd.setCursor(0,0);
      lcd.print("No.of plates to");
      lcd.setCursor(0,1);
      lcd.print("be ordered: ");
      delay(1000);
      char n;
      n=keypad.getKey();
      while(n == NO_KEY){
        n=keypad.getKey();
        Serial.print(n);
      }
      fillOrder(2,n);
      Serial.print(n);
      int bill=billCalculator();
      serverCall(order,bill);
}

void funHash(){
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1:ICE CREAM");
      lcd.setCursor(0,1);
      lcd.print("7:SODA");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3:HALWA");
      lcd.setCursor(0,1);
      lcd.print("4:COFFEE");
      delay(1000);
      lcd.clear();
      char key1=keypad.getKey();
      while(key1 == NO_KEY){
        key1=keypad.getKey();
        Serial.print(key1);

      }
      fillOrder(0,'#');
      fillOrder(1,key1);
      funNumHash();
}
void funNumHash(){
      lcd.setCursor(0,0);
      lcd.print("No.of plates to");
      lcd.setCursor(0,1);
      lcd.print("be ordered: ");
      delay(1000);
      char n;
      n=keypad.getKey();
      while(n == NO_KEY){
        n=keypad.getKey();
        Serial.print(n);
      }
      fillOrder(2,n);
      int bill=billCalculator();
      serverCall(order,bill);
}


void serverCall(String order, int bill) {
  Serial.println("\n");
  Serial.println(order);
  Firebase.setString("order",order);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /order failed:");
      Serial.println(Firebase.error());  
      return;
  }

  Serial.println("\n");
  Serial.println(order);
  Firebase.setInt("bill",bill);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /order failed:");
      Serial.println(Firebase.error());  
      return;
  delay(1000);

  }
  }
