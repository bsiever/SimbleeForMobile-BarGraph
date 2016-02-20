/*
 * Developed by Bill Siever (http://siever.info)
 * 
 * Objects of this class can draw a simple bar graph using SimbleeForMobile.
 * It has NOT been optimized for RAM usage (each graph will consume more 
 * memory than strictly necessary)
 *
 * This module is specifically for a scrolling bar graph.
 */

class BarGraph {
  static const int MAX_BARS = 30;
  static const int LABEL_WIDTH = 20;

public:
  // Construct a BarGraph object
  BarGraph(int bars, unsigned maxValue);

  // Set Background & Foreground.  Must be set before creatUI
  void setBarColor(color_t newColor);
  void setBackgroundColor(color_t newColor);

  // Reset the data  
  void resetData();
 
  void appendData(unsigned newItem);

  void createUI(unsigned x, unsigned y, unsigned width, unsigned height);

  void updateUI();

private:
  void createBars();


  int x;
  int y;
  int width;
  int height;
  int bars;
  int currentBars;
  int firstBar;
  int lastBar;
  color_t backgroundColor;
  color_t barColor;
  
  unsigned maxValue;
  unsigned data[MAX_BARS];
  uint8_t barIds[MAX_BARS]; 
};

