
#include <JsonParser.h>

void ParseAnObject()
{
    char json[] = "{\"Headings\": [90,45,135,0,180]}";
    JsonParser<32> parser;

    Serial.print("Parse ");
    Serial.println(json);

    JsonHashTable hashTable = parser.parseHashTable(json);

    if (!hashTable.success())
    {
        Serial.println("JsonParser.parseHashTable() failed");
        return;
    }

    JsonArray headings = hashTable.getArray("Headings");
    Serial.println("headings:");
    for (int i = 0; i < headings.getLength(); i++)
    {
        int value = headings.getLong(i);
        Serial.print(i);
        Serial.print(" ");
        Serial.println(value);
    }
}

void setup()
{
    Serial.begin(9600);
    delay(50);
    ParseAnObject();
}

void loop()
{

}
