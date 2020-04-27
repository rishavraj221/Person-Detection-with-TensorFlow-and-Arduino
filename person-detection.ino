// at the top of the script, initialize a variable for the relay signal
int relayOut = 10;

// in the setup() loop, initialize the relayOut pin as output
void setup(){
   /*  ....   */
   pinMode(relayOut, OUTPUT);
}

// in the void() loop:
void loop() {
// Get image from provider.
if (kTfLiteOk != GetImage(error_reporter, kNumCols, kNumRows, kNumChannels,
input->data.uint8)) {
error_reporter->Report("Image capture failed.");
}
// Run the model on this input and make sure it succeeds.
if (kTfLiteOk != interpreter->Invoke()) {
error_reporter->Report("Invoke failed.");
}
TfLiteTensor* output = interpreter->output(0);
// Process the inference results.
uint8_t person_score = output->data.uint8[kPersonIndex];
uint8_t no_person_score = output->data.uint8[kNotAPersonIndex];
RespondToDetection(error_reporter, person_score, no_person_score);

// Add the following lines:
if (person_score >= no_person_score){
  digitalWrite(relayOut, HIGH);
}
else {
  digitalWrite(relayOut, LOW);
}

}
