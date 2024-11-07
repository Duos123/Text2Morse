const int outputPin = 13; // Ausgangspin für Morse-Code
const int dotDuration = 200; // Dauer eines "Punkts" in Millisekunden
const int dashDuration = dotDuration * 3; // Dauer eines "Strichs"
const int spaceDuration = dotDuration * 7; // Dauer einer Pause zwischen Wörtern

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Bitte geben Sie den Text ein, der in Morsezeichen kodiert werden soll:");
}

void loop() {
  if (Serial.available() > 0) {
    String text = Serial.readStringUntil('\n');
    text.toUpperCase();
    for (int i = 0; i < text.length(); i++) {
      char c = text.charAt(i);
      if (c == ' ') {
        delay(spaceDuration); // Pause zwischen Wörtern
      } else {
        encodeMorse(c);
        delay(dotDuration * 3); // Pause zwischen Buchstaben
      }
    }
    Serial.println("Kodierung abgeschlossen.");
  }
}

void encodeMorse(char c) {
  String morseCode = getMorseCode(c);
  for (int i = 0; i < morseCode.length(); i++) {
    if (morseCode[i] == '.') {
      sendDot();
    } else if (morseCode[i] == '-') {
      sendDash();
    }
  }
}

void sendDot() {
  send_1();
  delay(dotDuration);
  send_0();
  delay(dotDuration); // Pause zwischen Symbolen
}

void sendDash() {
  send_1();
  delay(dashDuration);
  send_0();
  delay(dotDuration); // Pause zwischen Symbolen
}

String getMorseCode(char c) {
  switch (c) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '0': return "-----";
    default: return ""; // Für unbekannte Zeichen
  }
}

void send_1() {
  digitalWrite(outputPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void send_0() {
  digitalWrite(outputPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}


// TODO: Text to Morse: 
// Arduino Output: Eingabe über serial monitor (text) -> Uebersetzung in HIGH und LOW 
// => Weitergabe an 2 parallel geschaltete Neuronen (encoding das Signal, getrennt)
// => Ergebniss der beiden (getrennten) Neuronen wird zusammen dekodiert
// => Weitergabe des Ergebnisses der Dekodierung an den Arduino zurück  
// Arduino Input: 
