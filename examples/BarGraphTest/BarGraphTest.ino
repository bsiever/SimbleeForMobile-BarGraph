#include <SimbleeForMobile.h>
#include<BarGraph.h>


// An example that creates a small bar graph and updates it with random data
// Search for "BG" comments to see the major components to use this library: 

// BG: Declare the bar graph object
// Arguments are: # of bars, Maximum value of a bar, background color (WHITE by default), bar/text color (BLUE by default)
BarGraph testBarGraph(4,30);

// IDs for UI
uint8_t addDataId;
uint8_t valueAddedId;


void setup() { 
  Serial.begin(9600);
  Serial.println("Starting");
  SimbleeForMobile.deviceName = "BG Tests";
  SimbleeForMobile.advertisementData = "BG";
  SimbleeForMobile.domain = "siever.info";

  // Begin Simble UI
  SimbleeForMobile.begin();
}

void loop() {
  SimbleeForMobile.process();  
}


void SimbleeForMobile_onConnect()
{
  // BG: Optional: do a resetData() on either disconnect or connect if 
  //     data should not be persistent across connections.
  //    (Persistent data doesn't redraw correctly with current version of Simblee)
  testBarGraph.resetData();
}


/*
 * SimbleeForMobile ui callback requesting the user interface
 * 
 * Check which screen is being requested. 
 * If that is the current screen, simply return.
 * If it is a different screen, create the requested screen.
 * A screen request which is out of range, is logged and ignored.
 */
void ui()
{  
  char *p[] = { "Title" };
  SimbleeForMobile.beginScreen(WHITE, PORTRAIT);
  int width = SimbleeForMobile.screenWidth;
  int height = SimbleeForMobile.screenHeight;

  valueAddedId = SimbleeForMobile.drawButton(0, height/3+40, width, "(None)", BLACK, TEXT_TYPE);

  addDataId = SimbleeForMobile.drawButton(0, height/3-40, width, "Add Random Data", BLUE, TEXT_TYPE);
  SimbleeForMobile.setEvents(addDataId, EVENT_PRESS);

  // BG: Add the BarGraph to the UI. 
  // Arguments are: x,y,width,height
  testBarGraph.createUI(0,height-height/3,width, height/3);
  
  SimbleeForMobile.endScreen();
}


void ui_event(event_t &event)
{
  if(event.id == addDataId) {
    // Generate random data to append to the graph
    char buffer[5];
    // The only event possible should be the button
    unsigned newValue = random(0,30);
    sprintf(buffer, "%d", newValue);
    SimbleeForMobile.updateText(valueAddedId, buffer);

    // BG: This is an example of how a new piece of data is added to the BarGraph.
    testBarGraph.appendData(newValue);
  }
}
