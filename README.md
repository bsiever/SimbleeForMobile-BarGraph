# SimbleeForMobile-BarGraph
SimbleeForMobile library for a simple scrolling BarGraph.

This library uses an inefficient scroll update method: the bars are at
fixed locations on the screen and every update causes the width and height
of each to update.  A better approach would be to adjust just the x 
coordinate of all the bars that need to "move left" on a scroll and 
update the width, height, and x coordinate of the leftmost bar to become
the new rightmost bar.