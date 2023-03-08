void setColor(int r, int g, int b) { // orldper function to set indicator LED color
  float brightness = 0.1;
  pixels.setPixelColor(0, pixels.Color(r * brightness, g * brightness, b * brightness));
  pixels.show();
}