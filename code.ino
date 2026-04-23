const int redLED    = 4;
const int yellowLED = 3;
const int greenLED  = 5;
const int button    = 2;

int clickCount = 0;
int lastBtn    = HIGH;

void setup() {
  pinMode(redLED,    OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED,  OUTPUT);
  pinMode(button,    INPUT_PULLUP);
}

void loop() {
  int btn = digitalRead(button);

  if (btn == LOW && lastBtn == HIGH) {
    clickCount++;

    if (clickCount == 1) {
      // 1st click = ALL ON at same time
      digitalWrite(redLED,    HIGH);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(greenLED,  HIGH);
    } 
    else if (clickCount == 2) {
      // 2nd click = ALL OFF at same time
      digitalWrite(redLED,    LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(greenLED,  LOW);
      clickCount = 0; // reset
    }

   // delay(0); // debounce
  }

  lastBtn = btn;
}