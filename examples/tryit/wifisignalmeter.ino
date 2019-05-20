#include <ESP8266WiFi.h>
#include "AESLib.h"

AESLib aesLib;

char cipherText[512], clearText[265];
int rssi;
String str;

// Informasi WiFi
char ssid[] = "OpenWrt";
char pass[] = "ngelungelu";

// Key 16 Byte atau 128 bit
byte aes_key[] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68 };

String encrypt(char * msg, byte iv[]) {  
  int msgLen = strlen(msg);
  char encrypted[2 * msgLen];
  aesLib.encrypt64(msg, encrypted, aes_key, iv);  
  return String(encrypted);
}

String decrypt(char * msg, byte iv[]) {
  unsigned long ms = micros();
  int msgLen = strlen(msg);
  char decrypted[msgLen];
  aesLib.decrypt64(msg, decrypted, aes_key, iv);  
  return String(decrypted);
}

void setup() {
  Serial.begin(9600);
  Serial.print("\n\n\nStarting...");
  Serial.println("\nBerhasil terhubung ke WiFi!");
}

void loop() {
  // Deteksi Power Signal WiFi
  rssi = WiFi.RSSI();
  sprintf(clearText, "%d", rssi);
  
  // Encrypt
  byte enc_iv[N_BLOCK] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };
  String encrypted = encrypt(clearText, enc_iv);
  sprintf(cipherText, "%s", encrypted.c_str());
  Serial.print("Chiper: ");
  Serial.println(encrypted);

  // Decrypt
  byte dec_iv[N_BLOCK] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38 };
  String decrypted = decrypt(cipherText, dec_iv);  
  Serial.print("Signal WiFi Plaintext: ");
  Serial.println(decrypted);

  delay(5000);
}
