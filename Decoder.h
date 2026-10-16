const uint8_t DIGITS[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

// Allows connectivity from the board to the 7-Seg
void displayDigit(int digit, const uint8_t pins[]) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(pins[i], DIGITS[digit][i]);
    }
}

// Determines the display of SEG1's Ones and SEG2's Tens
// via sensor count
void displayCounter(int counter) {
    int tens = counter / 10;
    int ones = counter % 10;

    displayDigit(tens, LED_2);
    displayDigit(ones, LED_1);
}

void decoder(int previousState) {
    int currentState = digitalRead(IR_PIN);
    // Kung may new detection since kay 1 naman ang sa main

    if (previousState == 1 && currentState == 0) {
        ir_counter = (ir_counter + 1) % 100;

        displayCounter(ir_counter);
    }

    previousState = currentState;

    delay(20);
}