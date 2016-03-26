#!/bin/sh
rm -f ./SimbleeForMobile-BarGraph.zip 
cd ..
zip -r SimbleeForMobile-BarGraph.zip SimbleeForMobile-BarGraph -x ./SimbleeForMobile-BarGraph/.git**\* -x ./SimbleeForMobile-BarGraph.zip/Makelib.sh
mv SimbleeForMobile-BarGraph.zip ./SimbleeForMobile-BarGraph
