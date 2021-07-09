void setup()
{
    Serial.begin(9600);
}

void loop()
{
    unsigned long currentMills = millis();
    Serial.println(currentMills);
}