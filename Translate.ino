
#include "SoftwareSerial.h"

//SoftwareSerial bt(6,7);
/*Orange and black thread for thumb */

char temp = '0';

int FLEX_PIN1 = A0;
int flexADC1 = 0;
int sensorMin1;
int sensorMax1;

/*Yellow and black thread for index */
int FLEX_PIN2 = A1;
int flexADC2 = 0;
int sensorMin2;
int sensorMax2;

/*Blue and black thread for middle */
int FLEX_PIN3 = A2;
int flexADC3 = 0;
int sensorMin3;
int sensorMax3;

/*Red and black thread for ring finger */
int FLEX_PIN4 = A3;
int flexADC4 = 0;
int sensorMin4;
int sensorMax4;

/*White and black thread for pinky */
int FLEX_PIN5 = A4;
int flexADC5 = 0;
int sensorMin5;
int sensorMax5;

int xpin = A5;
int xadc = 0;
int ypin = A6;
int yadc = 0;
int xVertical, yVertical;
int xHorizontal, yHorizontal;
int xEquilibrium, yEquilibrium;
char letter = ' ';
void setup() {
    Serial.begin(9600);
    //Serial.println("Start");
    //bt.begin(1200);
      Serial.println("Calibrating for open hand. Please keep your hand open.");
      delay(5000); 

      sensorMin1 = analogRead(FLEX_PIN1);
      sensorMin2 = analogRead(FLEX_PIN2);
      sensorMin3 = analogRead(FLEX_PIN3);
      sensorMin4 = analogRead(FLEX_PIN4);
      sensorMin5 = analogRead(FLEX_PIN5);
      
      Serial.println("Calibrating for closed hand. Please close your hand.");
      delay(5000);
      
      sensorMax1 = analogRead(FLEX_PIN1);
      sensorMax2 = analogRead(FLEX_PIN2);
      sensorMax3 = analogRead(FLEX_PIN3);
      sensorMax4 = analogRead(FLEX_PIN4);
      sensorMax5 = analogRead(FLEX_PIN5);

      Serial.println("Calibrating for vertical orientation. Please hold your hand vertically.");
      delay(5000);
      xVertical = analogRead(xpin);
      yVertical = analogRead(ypin);
      
      Serial.println("Calibrating for horizontal orientation. Please hold your hand horizontally.");
      delay(5000);
      xHorizontal = analogRead(xpin);
      yHorizontal = analogRead(ypin);
      
      Serial.println("Calibrating for equilibrium orientation. Please hold your hand in a neutral position.");
      delay(5000);
      xEquilibrium = analogRead(xpin);
      yEquilibrium = analogRead(ypin);
    
    Serial.println("CALIBRATION_COMPLETE"); // Send completion signal

    
  //delay(10000);
}
      

void loop() {
    // put your main code here, to run repeatedly:
    Serial.print("angle1:");
    float flexADC1 = analogRead(FLEX_PIN1);
    flexADC1 = constrain(flexADC1, sensorMin1, sensorMax1);
    float angle1 = map(flexADC1, sensorMin1, sensorMax1, 0, 90);
    Serial.print(angle1);
    Serial.print("\t");
    Serial.print("angle2:");
    float flexADC2 = analogRead(FLEX_PIN2);
    flexADC2 = constrain(flexADC2, sensorMin2, sensorMax2);
    float angle2 = map(flexADC2, sensorMin2, sensorMax2, 0, 90);
    Serial.print(angle2);
    Serial.print("\t");
    Serial.print("angle3:");
    float flexADC3 = analogRead(FLEX_PIN3);
    flexADC3 = constrain(flexADC3, sensorMin3, sensorMax3);
    float angle3 = map(flexADC3, sensorMin3, sensorMax3, 0, 90);
    Serial.print(angle3);
    Serial.print("\t");
    Serial.print("angle4:");
    float flexADC4 = analogRead(FLEX_PIN4);
    flexADC4 = constrain(flexADC4, sensorMin4, sensorMax4);
    float angle4 = map(flexADC4, sensorMin4, sensorMax4, 0, 90);
    Serial.print(angle4);
    Serial.print("\t");
    Serial.print("angle5:");
    float flexADC5 = analogRead(FLEX_PIN5);
    flexADC5 = constrain(flexADC5, sensorMin5, sensorMax5);
    float angle5 = map(flexADC5, sensorMin5, sensorMax5, 0, 90);
    Serial.print(angle5);
    Serial.print("\t");

    Serial.print("x:");
    xadc = analogRead(xpin);
    Serial.print(xadc);
    Serial.print("\t");

    Serial.print("y:");
    yadc = analogRead(ypin);
    Serial.println(yadc);
    
    int tolerance = 20;
    bool horizontal = (abs(xadc - xHorizontal) <= tolerance) && (abs(yadc - yHorizontal) <= tolerance);
    bool vertical = (abs(xadc - xVertical) <= tolerance) && (abs(yadc - yVertical) <= tolerance);
    bool equilibrium = (abs(xadc - xEquilibrium) <= tolerance) && (abs(yadc - yEquilibrium) <= tolerance);

    Serial.print("Horizontal: ");
    Serial.print(horizontal ? "Yes" : "No");
    Serial.print("\t");
    Serial.print("Vertical: ");
    Serial.print(vertical ? "Yes" : "No");
    Serial.print("\t");
    Serial.print("Equilibrium: ");
    Serial.println(equilibrium ? "Yes" : "No");


    if ((angle1 <= 40) && (angle2 >= 60) && (angle3 >= 72) && (angle4 >= 68) && (angle5 >= 72)) {
        Serial.println(letter);
        letter = 'A';
    }
    if ((angle1 >= 35) && (angle2 <= 15) && (angle3 <= 15) && (angle4 <= 15) && (angle5 <= 15)) {
        Serial.println('B');
        letter = 'B';
    }
    if ((angle1 < 30) && ((angle2 >= 40) && (angle2 < 80)) && ((angle3 >= 30) && (angle3 < 85)) && ((angle4 >= 30) && (angle4 < 85)) && ((angle5 >= 30) && (angle5 < 85))) {
        Serial.println('C');
        letter = 'C';
    }
    if (((angle1 >= 30) && (angle1 <= 70)) && (angle2 <= 15) && (angle3 >= 60) && (angle4 >= 40) && (angle5 >= 40) && vertical) {
        Serial.println('D');
        letter = 'D';
    }
    if ((angle1 >= 85) && (angle2 >= 85) && (angle3 >= 85) && (angle4 >= 85) && (angle5 >= 85)) {
        Serial.println('E');
        letter = 'E';
    }
    if ((angle1 >= 30) && (angle2 >= 40) && (angle3 <= 15) && (angle4 <= 15) && (angle5 <= 15)) {
        Serial.println('F');
        letter = 'F';
    }
    if ((angle1 <= 30) && (angle2 <= 15) && (angle3 >= 55) && (angle4 >= 55) && (angle5 >= 60) && horizontal) {
        Serial.println('G');
        letter = 'G';
    }
    if ((angle1 >= 40) && (angle2 <= 15) && (angle3 <= 15) && (angle4 >= 55) && (angle5 >= 50) && horizontal) {
        Serial.println('H');
        letter = 'H';
    }
    if ((angle1 >= 30) && (angle2 >= 70) && (angle3 >= 55) && (angle4 >= 55) && (angle5 <= 30) && vertical) {
        Serial.println('I');
        letter = 'I';
    }
    if ((angle1 >= 30) && (angle2 >= 70) && (angle3 >= 55) && (angle4 >= 55) && (angle5 <= 30) && !vertical) {
        Serial.println('J');
        letter = 'J';
    }
    if ((angle1 <= 30) && (angle2 <= 15) && (angle3 <= 15) && (angle4 >= 55) && (angle5 >= 55) && vertical) {
        Serial.println('K');
        letter = 'K';
    }
    if ((angle1 <= 10) && (angle2 <= 18) && (angle3 >= 40) && (angle4 >= 40) && (angle5 >= 40) && vertical) {
        Serial.println('L');
        letter = 'L';
    }
    if (((angle1 >= 30) && (angle1 <= 75)) && ((angle2 >= 40) && (angle2 < 80)) && ((angle3 >= 40) &&(angle3 < 80)) && ((angle4 >= 50) && (angle4 <= 85)) && (angle5 >= 85)) {
        Serial.println('M');
        letter = 'M';
    }
    if (((angle1 >= 20) && (angle1 <= 70)) && ((angle2 >= 40) && (angle2 < 80)) && ((angle3 >= 40) &&(angle3 < 80)) && (angle4 > 85) && (angle5 >= 85)) {
        Serial.println('N');
        letter = 'N';
    }
    if ((angle1 >= 30) && ((angle2 >= 30) && (angle2 < 80)) && ((angle3 >= 30) && (angle3 < 85)) && ((angle4 >= 30) && (angle4 < 85)) && ((angle5 >= 30) && (angle5 < 85)) && vertical) {
        Serial.println('O');
        letter = 'O';
    }
    if ((angle1 <= 40) && (angle2 <= 15) && (angle3 <= 30) && (angle4 >= 55) && (angle5 >= 55) && equilibrium) {
        Serial.println('P');
        letter = 'P';
    }
    if ((angle1 <= 15) && (angle2 <= 15) && (angle3 >= 50) && (angle4 >= 50) && (angle5 >= 60) && equilibrium) {
        Serial.println('Q');
        letter = 'Q';
    }
    if ((angle1 >= 30) && (angle2 <= 10) && ((angle3 >= 10) && (angle3 <= 20)) && (angle4 >= 55) && (angle5 >= 55) && vertical) {
        Serial.println('R');
        letter = 'R';
    }
    if (((angle1 >= 60) && (angle1 < 85)) && (angle2 >= 70) && (angle3 >= 70) && (angle4 >= 70) && (angle5 >= 70)) {
        Serial.println('S');
        letter = 'S';
    }
    if (((angle1 >= 10) && (angle1 <= 40)) && ((angle2 >= 20) && (angle2 <= 50)) && (angle3 >= 80) &&(angle4 >= 80) && (angle5 >= 80)) {
        Serial.println('T');
        letter = 'T';
    }
    if ((angle1 >= 30) && (angle2 <= 10) && (angle3 < 10) && (angle4 >= 55) && (angle5 >= 55) && vertical) {
        Serial.println('U');
        letter = 'U';
    }
    if ((angle1 >= 30) && (angle2 <= 10) && (angle3 < 10) && (angle4 >= 55) && (angle5 >= 55) && vertical) {
        Serial.println('V');
        letter = 'V';
    }
    if ((angle1 >= 40) && (angle2 <= 10) && (angle3 <= 15) && (angle4 <= 15) && (angle5 >= 55)) {
        Serial.println('W');
        letter = 'W';
    }
    if ((angle1 >= 30) && ((angle2 >= 15) && (angle2 <= 40)) && (angle3 >= 30) && (angle4 >= 30) && (angle5 >= 30) && vertical) {
        Serial.println('X');
        letter = 'X';
    }
    if ((angle1 <= 10) && (angle2 >= 44) && (angle3 >= 40) && (angle4 >= 40) && (angle5 <= 15)) {
        Serial.println('Y');
        letter = 'Y';
    }
    if (((angle1 >= 30) && (angle1 <= 70)) && (angle2 <= 15) && (angle3 >= 60) && (angle4 >= 40) && (angle5 >= 40) && !vertical && !horizontal) {
        Serial.println('Z');
        letter = 'Z';
    }
    Serial.print(letter);
    //bt.write(letter);
    delay(500);
}