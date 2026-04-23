const int RED_LED   = 2;  
const int GREEN_LED = 3;   
const int BUZZER    = 6; 
const int DOOR_BTN  = 7;  
const int RESET_BTN = 8;   
const int LDR_PIN   = A0;  

bool alarmActive = false;
bool nightMode   = false;

void setup() {
  Serial.begin(9600);

  pinMode(RED_LED,   OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER,    OUTPUT);
  pinMode(DOOR_BTN,  INPUT);
  pinMode(RESET_BTN, INPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BUZZER, LOW);

  Serial.println("MONITORING ACTIVE");
}

void loop() {

  int ldrValue = analogRead(LDR_PIN);

  // 🌙 NIGHT MODE
  if (!alarmActive) {
    if (ldrValue > 600) {

      if (!nightMode) {
        nightMode = true;
        Serial.println("NIGHT MODE ON");
      }

      // slow blinking GREEN LED
      digitalWrite(GREEN_LED, HIGH);
      delay(500);
      digitalWrite(GREEN_LED, LOW);
      delay(500);

    } else {

      if (nightMode) {
        nightMode = false;
        Serial.println("MONITORING ACTIVE");
      }

      digitalWrite(GREEN_LED, HIGH); // solid ON
    }
  }

  // 🚨 DOOR PRESSED → ALARM
  if (digitalRead(DOOR_BTN) == HIGH && !alarmActive) {

    alarmActive = true;
    Serial.println("INTRUDER DETECTED");

    digitalWrite(GREEN_LED, LOW);

    // 🔴 FLASH RED + BUZZER SOUND
    for (int i = 0; i < 10; i++) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BUZZER, HIGH); // SOUND
      delay(150);

      digitalWrite(RED_LED, LOW);
      digitalWrite(BUZZER, LOW);  // OFF
      delay(150);
    }

    // stay ON
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }

  // 🔁 RESET
  if (digitalRead(RESET_BTN) == HIGH && alarmActive) {

    alarmActive = false;
    nightMode   = false;

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);

    Serial.println("SYSTEM RESET");
    Serial.println("MONITORING ACTIVE");

    delay(300);
  }
}
