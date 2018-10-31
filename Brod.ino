#define INPUT_1_PIN   16     // D0
#define INPUT_2_PIN   5      // D1
#define ENABLE_A_PIN  4      // D2

#define INPUT_3_PIN   14     // D5
#define INPUT_4_PIN   12     // D6
#define ENABLE_B_PIN  13     // D7

void setup() {
  Serial.begin(9600);
  
  pinMode(INPUT_1_PIN, OUTPUT);
  pinMode(INPUT_2_PIN, OUTPUT);
  pinMode(ENABLE_A_PIN, OUTPUT);

  pinMode(INPUT_3_PIN, OUTPUT);
  pinMode(INPUT_4_PIN, OUTPUT);
  pinMode(ENABLE_B_PIN, OUTPUT);
  
  digitalWrite(INPUT_1_PIN, HIGH);
  digitalWrite(INPUT_2_PIN, LOW);
  digitalWrite(ENABLE_A_PIN, HIGH);

  digitalWrite(INPUT_3_PIN, HIGH);
  digitalWrite(INPUT_4_PIN, LOW);
  digitalWrite(ENABLE_B_PIN, HIGH);
}

void loop() {
}
