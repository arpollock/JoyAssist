int CLICK = 9;
int HOR = A1;
int VER = A0;

void setup() {
    Serial.begin(9600);

    pinMode(CLICK, INPUT_PULLUP);
    pinMode(HOR, INPUT);
    pinMode(VER, INPUT);
}

int treatValue(int data) {
    return (data * 9 / 1024) + 48;
}

void loop() {
    int x = analogRead(HOR);
    delay(10);
    int y = analogRead(VER);
    delay(10);
    int c = digitalRead(CLICK);
    delay(10);

    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(c);
}
