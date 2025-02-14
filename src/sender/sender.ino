const uint DOT_PIN = D11;   // Digital pin 11
const uint DASH_PIN = D12;  // Digital pin 12

const unsigned long BASE_DELAY = 300;  // 300ms
const unsigned long DOT_DELAY = BASE_DELAY;
const unsigned long DASH_DELAY = BASE_DELAY * 3;
const unsigned long CHAR_DELAY = DASH_DELAY;

const bool DEBUG = true;  // Verbose mode

void setup() {
  pinMode(DOT_PIN, OUTPUT);   // Set DOT_PIN as an output
  pinMode(DASH_PIN, OUTPUT);  // Set DASH_PIN as an output
  Serial.begin(9600);         // Initializes serial communication.
}

void loop() {
  if (Serial.available() == 0) return;

  String input = Serial.readStringUntil('\n');
  input.toUpperCase();
  if (DEBUG) {
    Serial.println("Received input: " + input);
  } else {
    Serial.println(input);
  }

  for (uint i = 0; i < input.length(); i++) {
    char c = input.charAt(i);
    if (DEBUG) {
      Serial.print("\n\tEncoding character: ");
      Serial.println(c);
    }

    encode(c);
    delay(CHAR_DELAY);
  }

  if (DEBUG) {
    Serial.println("\nFinished sending: " + input);
  }
}

void encode(char c) {
  const char* code = getMorseCode(c);
  if (code == nullptr) {
    if (DEBUG) {
      Serial.print("\tCharacter not supported: ");
      Serial.println(c);
    }
    return;
  }

  if (DEBUG) {
    Serial.print("\tMorse code for ");
    Serial.print(c);
    Serial.print(": ");
    Serial.println(code);
  }

  for (uint i = 0; code[i] != '\0'; i++) {
    if (code[i] == '.') {
      if (DEBUG) {
        Serial.println("\t\tSending DOT");
      }
      sendDot();
    } else if (code[i] == '-') {
      if (DEBUG) {
        Serial.println("\t\tSending DASH");
      }
      sendDash();
    }
  }
}

const char* getMorseCode(char c) {
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
    case ' ': return ".......";
    default: return nullptr;
  }
}

/*
 * Sends a dot signal by setting the DOT_PIN high for a specified duration.
 * Then, it resets the pin and waits for the base delay before the next signal.
 */
void sendDot() {
  digitalWrite(DOT_PIN, HIGH);
  delay(DOT_DELAY);
  digitalWrite(DOT_PIN, LOW);
  delay(BASE_DELAY);
}

/*
 * Sends a dash signal by setting the DASH_PIN high for a specified duration.
 * Then, it resets the pin and waits for the base delay before the next signal.
 */
void sendDash() {
  digitalWrite(DASH_PIN, HIGH);
  delay(DASH_DELAY);
  digitalWrite(DASH_PIN, LOW);
  delay(BASE_DELAY);
}
