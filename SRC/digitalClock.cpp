#include <graphics.h>
#include <ctime>
using namespace std;

class DigitalClock{

     private : int fillStyle,segColor,bGColor,segSize,
     locationX, locationY, segColor2 = segColor;

     private : float gap = 0.2;
     bool format12;

public : DigitalClock(int x, int y, int segColor, int segSize, bool format12){
          this->locationX = x;
          this->locationY = y;

          if (segSize < 5 && format12)
          { segSize = 5; }

          if (segSize % 2 == 0){   this->segSize = segSize;  }
          else{  this->segSize = segSize + 1;  }
          
          this->segColor = segColor;
          this->bGColor = 0;
          this->fillStyle = SOLID_FILL;
          this->format12 = format12;
     }

private : void drawSegment(int locationX, int locationY, int segColor, int segSize, char segNum){
          
          setcolor(segColor);

          int X = locationX + segSize + (segSize * gap);
          int Y = locationY;

          for (int i = 0; i < 3; i++){ //------------------- horizontal Lights ----------------------
               setcolor(segColor);
               if (i == 0 && segNum != '1' && segNum != '4'){
                    segColor2 = segColor; // set segment color to user defined
                    setcolor(segColor2);
               }else if (i == 1 && segNum != '0' && segNum != '1' && segNum != '7'){
                    segColor2 = segColor;
                    setcolor(segColor2);
               }else if (i == 2 && segNum != '1' && segNum != '4' && segNum != '7'){
                    segColor2 = segColor;
                    setcolor(segColor2);
               }else{
                    segColor2 = bGColor;
                    setcolor(segColor2);
               }

               line(X - (segSize / 2), Y + (segSize / 2), X, Y);
               line(X - (segSize / 2), Y + (segSize / 2), X, Y + segSize);
               line(X, Y, X + (segSize * 2) - (segSize * gap), Y); //constant line

               Y += segSize;

               line(X, Y, X + (segSize * 2) - (segSize * gap), Y); //constant line
               line(X + (segSize * 2) + (segSize / 2) - (segSize * gap), Y - (segSize / 2),
                    X + (segSize * 2) - (segSize * gap), Y - segSize);

               line(X + (segSize * 2) + (segSize / 2) - (segSize * gap), Y - (segSize / 2),
                    X + (segSize * 2) - (segSize * gap), Y);

               setfillstyle(fillStyle, segColor2);
               floodfill(X + 1, Y - 1, segColor2);

               Y += 2.4 * segSize;
          }

          setcolor(segColor);

          X = locationX; 
          Y = locationY + segSize;
          setcolor(segColor);

          for (int i = 0; i < 2; i++){ //-------------------vertical Lights----------------------
               for (int j = 0; j < 2; j++){
                    if (i == 0 && j == 0 && segNum != '1' && segNum != '2' && segNum != '3' && segNum != '7'){
                         segColor2 = segColor;
                         setcolor(segColor2);
                    }else if (i == 0 && j == 1 && segNum != '5' && segNum != '6'){
                         segColor2 = segColor;
                         setcolor(segColor2);
                    }else if (i == 1 && j == 0 && (segNum == '0' || segNum == '2' || segNum == '6' || segNum == '8')){
                         segColor2 = segColor;
                         setcolor(segColor2);
                    }else if (i == 1 && j == 1 && segNum != '2'){
                         segColor2 = segColor;
                         setcolor(segColor2);
                    }else{
                         segColor2 = bGColor;
                         setcolor(segColor2);
                    }

                    line(X + (segSize / 2), (Y + segSize * gap) - (segSize / 2),
                         X, (Y + segSize * gap)); // sharp edge
                    line(X + (segSize / 2), (Y + segSize * gap) - (segSize / 2),
                         X + segSize, (Y + segSize * gap)); // sharp edge 

                    line(X, (Y + segSize * gap), X, (Y + segSize * 2) + segSize * gap);
                    line(X + segSize, (Y + segSize * gap), X + segSize, (Y + segSize * 2) + segSize * gap);

                    line(X + (segSize / 2), ((Y + segSize * 2) + segSize * gap) + (segSize / 2),
                         X, ((Y + segSize * 2) + segSize * gap)); // sharp edge 
                    line(X + (segSize / 2), ((Y + segSize * 2) + segSize * gap) + (segSize / 2),
                         X + segSize, ((Y + segSize * 2) + segSize * gap)); // sharp edge 

                    setfillstyle(fillStyle, segColor2);
                    floodfill(X + 1, (Y + segSize * gap) + 1, segColor2);

                    X += ((segSize * 3) + (segSize * gap));
               }
               Y += segSize + (2.4 * segSize);
               X = locationX;
          }
          setcolor(segColor);
     }

private : int hourFormatHandler(int hour,bool is12format){

     if (is12format && hour > 12){
          hour -= 12;
     }else if(hour == 0 && is12format){
          hour = 12;
     }

     return hour;
}     

public: void start(){
          // int gd = DETECT,gm;
          // initgraph(&gd,&gm,(char*)"");

            initwindow(1360, 640);
            int hours, minutes, seconds;
            int formattedHour;
                    
        while (true){ // main loop
            
            time_t currentTime = time(NULL);
            struct tm *localTime = localtime(&currentTime);

            hours = localTime->tm_hour;
            minutes = localTime->tm_min;
            seconds = localTime->tm_sec;

        for (int hr = hours; hr < 24; hr++){   // hour loop

               formattedHour = hourFormatHandler(hr,format12);

               drawSegment(locationX, locationY, segColor, segSize, to_string(formattedHour / 10).at(0));
               drawSegment(locationX + (segSize * 5), locationY, segColor, segSize, to_string(formattedHour - (formattedHour/10)*10).at(0));
               
               rectangle(locationX + (segSize * 10), locationY + (segSize * 2), locationX + (segSize * 10) + segSize, locationY + (segSize * 2) + segSize);
               rectangle(locationX + (segSize * 10), locationY + (segSize * 5), locationX + (segSize * 10) + segSize, locationY + (segSize * 5) + segSize);
               
               setfillstyle(fillStyle, segColor);
               floodfill(locationX + (segSize * 10) + 1, locationY + (segSize * 2) + 1, segColor);
               floodfill(locationX + (segSize * 10) + 1, locationY + (segSize * 5) + 1, segColor);

          for (int min = minutes; min < 60; min++){  // minute loop

               drawSegment(locationX + (segSize * 12), locationY, segColor, segSize, to_string(min / 10).at(0));
               drawSegment(locationX + (segSize * 17), locationY, segColor, segSize, to_string(min - (min/10)*10).at(0));

               rectangle(locationX + (segSize * 22), locationY + (segSize * 2), locationX + (segSize * 22) + segSize, locationY + (segSize * 2) + segSize);
               rectangle(locationX + (segSize * 22), locationY + (segSize * 5), locationX + (segSize * 22) + segSize, locationY + (segSize * 5) + segSize);

               setfillstyle(fillStyle, segColor);
               floodfill(locationX + (segSize * 22) + 1, locationY + (segSize * 2) + 1, segColor);
               floodfill(locationX + (segSize * 22) + 1, locationY + (segSize * 5) + 1, segColor);


            for (int sec = seconds; sec < 60; sec++){  // second loop

               drawSegment(locationX + (segSize * 24), locationY, segColor, segSize, to_string(sec / 10).at(0));
               drawSegment(locationX + (segSize * 29), locationY, segColor, segSize, to_string(sec - (sec/10)*10).at(0));
               
               if (format12 && hr >= 12){

                    settextstyle(3,1,segSize/4);
                    outtextxy(locationX + (segSize * 38),locationY + (segSize * 8),"PM");

               }else if(format12 && hr < 12){

                settextstyle(3,1,segSize/4);
                outtextxy(locationX + (segSize * 38),locationY + (segSize * 8),"AM");
                
               }
             delay(1000);                
          }   
          seconds = 0;
         }   
         minutes = 0;
        }
        hours = 0;
    }
    closegraph();
  }
};

int main(){
     DigitalClock digitalClock(20, 200, YELLOW, 10, true);
     digitalClock.start();
}