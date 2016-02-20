#include<Arduino.h>
#include <SimbleeForMobile.h>
#include "BarGraph.h"

// A SimbleeForMobile scrolling bar graph. The location and size are configured when it appears. The number of bars and maxValue is specified when declared.

BarGraph::BarGraph(int bars, unsigned maxValue): x(0), y(0), width(0), height(0), bars(bars), currentBars(0), barColor(BLUE), backgroundColor(RED), maxValue(maxValue) { }

void BarGraph::setBarColor(color_t newColor) {
  barColor = newColor;
}

void BarGraph::setBackgroundColor(color_t newColor) {
  backgroundColor = newColor;
}

void BarGraph::resetData() {
  firstBar = lastBar = currentBars = 0;
}
 
void BarGraph::appendData(unsigned newItem) {
  if(currentBars == 0) {
    firstBar = 0;
    lastBar = 0;
  }
  data[lastBar] = newItem;
  lastBar = (lastBar+1)%bars;
  if(currentBars == bars) {
    firstBar = (firstBar+1)%bars;
  }
  currentBars = min(bars, currentBars+1);
  updateUI();
}

void BarGraph::createUI(unsigned x, unsigned y, unsigned width, unsigned height) {
  uint8_t id;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  // Draw background
  SimbleeForMobile.drawRect(x,y,width,height,backgroundColor);
  // Place Labels
  id = SimbleeForMobile.drawText(x, y, maxValue);
  SimbleeForMobile.updateColor(id, barColor);
  // Label for min value (0)
  id = SimbleeForMobile.drawText(x, y+height-20, (int16_t)0);
  SimbleeForMobile.updateColor(id, barColor);
  // Create Bars
  createBars();
  updateUI();
}


void BarGraph::createBars() {
  // Divide space not used by labels and pixels between bars among bars
  unsigned barWidth = (width - LABEL_WIDTH - bars)/bars;
  for(int i=0;i<bars;i++) {
        unsigned start = x+LABEL_WIDTH+i*(barWidth+1);
        unsigned value = 0; // Updates to y & height
        barIds[i] = SimbleeForMobile.drawRect(start, y+height-value, barWidth, value, barColor); 
  }
}


void BarGraph::updateUI() {
  if(SimbleeForMobile.updatable == false)
    return;

  // For Each available bar.  
  int index = firstBar;  
  for(int i=0;i<currentBars;i++) {
    unsigned newH = (data[index]*height)/maxValue;
    unsigned newY = y+(height-newH);
    SimbleeForMobile.updateY(barIds[i], newY);
    SimbleeForMobile.updateH(barIds[i], newH);
    index = (index+1)%bars;
  }
}

