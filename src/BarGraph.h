/*
 * Developed by Bill Siever (http://siever.info)
 * 
 * Objects of this class can draw a simple bar graph using SimbleeForMobile.
 * It has NOT been optimized for RAM usage (each graph will consume more 
 * memory than strictly necessary)
 *
 * This module is specifically for a scrolling bar graph.
 */

#ifndef SimbleeForMobile_BarGraph_h
#define SimbleeForMobile_BarGraph_h

#include "Arduino.h"

#if !defined(_VARIANT_SIMBLEE_)
#error "BarGraph.h is only for use with Simblee-based boards"
#endif

#include<SimbleeForMobile.h>

class BarGraph {
  static const int LABEL_WIDTH = 20;

public:
  // Construct a BarGraph object
  BarGraph(int bars, unsigned maxValue, color_t backgroundColor=WHITE, color_t barColor=BLUE);


  // Reset the data  
  void resetData();
 
  void appendData(unsigned newItem);

  void createUI(unsigned x, unsigned y, unsigned width, unsigned height);

  void updateUI();  // Update changes
 
// BSIEVER: Tested refreshUI() to redraw persistent data.  
//  void refreshUI(); // Refresh all bars
  
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
  unsigned *data;
  uint8_t *barIds; 
};

#endif