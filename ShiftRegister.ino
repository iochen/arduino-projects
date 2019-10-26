int latchPin = 2;
int clockPin = 3;
int dataPin = 4;
int resetPin = 6;

int delayPin = A0;
int delayTime = 100;

int data[8] = {1, 1, 1, 1, 1, 1, 1, 1};

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(delayPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 8; i++)
  {
    putData(data);
    data[i] = 0;
    refreshDelay();
    delay(delayTime);
  }
  for (int i = 0; i < 8; i++)
  {
    putData(data);
    data[i] = 1;
    refreshDelay();
    delay(delayTime);
  }
}

void refreshDelay()
{
  long i = analogRead(delayPin);
  Serial.print(i);
  Serial.print("\n");
  delayTime = map(i, 0, 1023, 1, 250);
}

void putData(int data[8])
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(clockPin, LOW);
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(dataPin, data[7 - i]);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, LOW);
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
  digitalWrite(resetPin, LOW);
}
