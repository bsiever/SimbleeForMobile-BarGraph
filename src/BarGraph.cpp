#include <Arduino.h>
#include "BarGraph.h"

// A SimbleeForMobile scrolling bar graph. 
// The location and size are configured when it appears. 
// The number of bars, maxValue, and colors are specified when declared.
 
/*
 Scrolling behavior requires updating several X coordinates
 (More bars will lower performance)
 */
 
BarGraph::BarGraph(int bars, unsigned maxValue, color_t backgroundColor, color_t barColor): 
   x(0), y(0), width(0), height(0), bars(bars), 
   currentBars(0), maxValue(maxValue), barColor(barColor), backgroundColor(backgroundColor) { 
   barIds = (uint8_t* )malloc(bars*sizeof(uint8_t));
   data = (unsigned *)malloc(bars*sizeof(unsigned));
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
  // Max Value Label
  id = SimbleeForMobile.drawText(x, y, maxValue);
  SimbleeForMobile.updateColor(id, barColor);
  // Label for min value (0)
  id = SimbleeForMobile.drawText(x, y+height-20, (int16_t)0);
  SimbleeForMobile.updateColor(id, barColor);
  // Create Bars
  createBars();
}


void BarGraph::createBars() {
  // Divide space not used by labels and pixels between bars among bars
  uint16_t barWidth = (width - LABEL_WIDTH - bars)/bars;
  uint16_t start;
  uint16_t h;
  unsigned barIndex;   
  for(int i=0;i<bars;i++) {
    start = x+LABEL_WIDTH+i*(barWidth+1);
    barIndex = (firstBar+i)%bars;
    if(i < currentBars) {      
      h = max(1,(data[barIndex]*height)/maxValue);
    } else {
      h = 1;
    }
    uint16_t yCoord = y+(height-h);
    barIds[i] = SimbleeForMobile.drawRect(start, yCoord, barWidth, h, barColor); 
//printf("Connect: (%d,%d) x %d\n", start, yCoord, h);
  }
}


/*
// BSIEVER: Test code for redrawing persistent data.
void BarGraph::refreshUI() {
  if(SimbleeForMobile.updatable == false)
    return;

  uint16_t barWidth = (width - LABEL_WIDTH - bars)/bars;

  for(int i=0;i<bars;i++) {
      unsigned index = (i+firstBar)%bars;

      uint16_t newX = x+LABEL_WIDTH+i*(barWidth+1);
      uint16_t newH;
      if(i<currentBars) 
        newH = max(1,(data[index]*height)/maxValue);
      else 
        newH = 1;
      uint16_t newY = y+(height-newH);

//printf("Refresh: (%d,%d) x %d\n", newX, newY, newH);
      SimbleeForMobile.updateRect(barIds[index], newX, newY, barWidth, newH);
  }
}
*/

void BarGraph::updateUI() {
  if(SimbleeForMobile.updatable == false)
    return;

  int index;  // Start at the last added bar 
  uint16_t newX;
  uint16_t barWidth = (width - LABEL_WIDTH - bars)/bars;

  // if it's time to scroll
  if(currentBars == bars) {
    index = (lastBar+1) % bars; // Start at the first bar
    for(int i=0;i<bars-1;i++) {
      unsigned start = x+LABEL_WIDTH+i*(barWidth+1);
      SimbleeForMobile.updateX(barIds[index],start);
      index = (index+1)%bars;
    }    
    newX = x+LABEL_WIDTH+(bars-1)*(barWidth+1);    
  } else {
    index = currentBars-1;
    newX = x+LABEL_WIDTH+index*(barWidth+1);
  }
  // Update the last bar added
  uint16_t newH = max(1,(data[index]*height)/maxValue);
  uint16_t newY = y+(height-newH);
  SimbleeForMobile.updateOrigin(barIds[index], newX, newY);
  SimbleeForMobile.updateH(barIds[index], newH);
//printf("Latest: (%d,%d) x %d\n", newX, newY, newH);
}

