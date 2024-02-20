#include <CircularBuffer.hpp> // Ease of data handling - https://www.arduino.cc/reference/en/libraries/circularbuffer/


// these are the only external variables used by the graph function
// it's a flag to draw the coordinate system only on the first call to the Graph() function
// and will mimize flicker
// also create some variables to store the old x and y, if you draw 2 graphs on the same display
// you will need to store ox and oy per each display
bool display1 = true;
bool update1 = true;         // Flag to redraw coordinate system
double ox = -999, oy = -999; // Force them to be off screen

bool drawingGraph = false;

// Buffer to store x and y axis data coming form sensor
CircularBuffer<double, 200> plotTemp;
CircularBuffer<double, 200> plotTime;

// variable to determine the min and max form buffer, which is then used to dynamicaly update the x and y axis coordinates
double minX = 0;
double maxX = 0;
double minY = 0;
double maxY = 0;

// data to be plotted on the chart
double xplot, yplot;
int graphCounter = 0;


/*

  function to draw a cartesian coordinate system and plot whatever data you want
  just pass x and y and the graph will be drawn

  huge arguement list
  &d name of your display object
  x = x data point
  y = y datapont
  gx = x graph location (lower left)
  gy = y graph location (lower left)
  w = width of graph
  h = height of graph
  xlo = lower bound of x axis
  xhi = upper bound of x asis
  xinc = division of x axis (distance not count)
  ylo = lower bound of y axis
  yhi = upper bound of y asis
  yinc = division of y axis (distance not count)
  title = title of graph
  xlabel = x asis label
  ylabel = y asis label
  &redraw = flag to redraw graph on first call only
  color = plotted trace colour
  axisTextColor = axis coordinates text color in case you want to hide text using a black color on a black background
*/

double xinc = 1;

void Graph(TFT_eSPI &tft, double x, double y, byte dp,
           double gx, double gy, double w, double h,
           double xlo, double xhi, double xinc,
           double ylo, double yhi, double yinc,
           char *title, char *xlabel, char *ylabel,
           bool &redraw, unsigned int color, unsigned int axisTextColor)
{

  double ydiv, xdiv;
  double i;
  double temp;
  int rot, newrot;

  // gcolor = graph grid colors
  // acolor = axes line colors
  // pcolor = color of your plotted data
  // tcolor = text color
  // bcolor = background color
  unsigned int gcolor = DKBLUE;
  unsigned int acolor = RED;
  unsigned int pcolor = color;
  unsigned int tcolor = WHITE;
  unsigned int bcolor = BLACK;

  if (redraw == true)
  {

    redraw = false;
    // initialize old x and old y in order to draw the first point of the graph
    // but save the transformed value
    // note my transform funcition is the same as the map function, except the map uses long and we need doubles
    // ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    // oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

    tft.setTextDatum(MR_DATUM);

    // draw y scale
    for (i = ylo; i <= yhi; i += yinc)
    {
      // compute the transform
      temp = (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == ylo) // 0 will not work if sensor data do not start from 0 so keep ylo the first point
      {
        tft.drawLine(gx, temp, gx + w, temp, acolor);
        tft.setTextColor(acolor, bcolor);
        // tft.drawString(xlabel, (int)(gx + w) , (int)temp, 2); //
        tft.drawString(xlabel, (int)(gx + w + 35 + 20), (320 - 10), 2); // using static value to adjust as per need
      }
      else
      {
        // tft.drawLine(gx, temp, gx + w, temp, gcolor); // Uncomment this to turn on grid
      }
      // draw the axis labels
      tft.setTextColor(tcolor, bcolor); // replace tcolor with axisTextColor to pass black color and hide text
      // precision is default Arduino--this could really use some format control
      // tft.drawFloat(i, dp, gx - 4, temp, 1); // use "dp" to pass decimal value in axis text
      tft.drawFloat(i, 0, gx - 4, temp, 1); // disabled decimal in axis text
    }

    // draw x scale
    for (i = xlo; i <= xhi; i += xinc)
    {

      // compute the transform
      temp = (i - xlo) * (w) / (xhi - xlo) + gx;
      if (i == xlo) // 0 will not work if reading do not start from 0 so keep ylo the first point
      {
        tft.drawLine(temp, gy, temp, gy - h, acolor);
        tft.setTextColor(acolor, bcolor);
        tft.setTextDatum(BC_DATUM);
        // tft.drawString(ylabel, (int)temp, (int)(gy - h - 8) , 2);
        tft.drawString(ylabel, (int)temp + 10, (int)(gy - h - 8), 2); //  using static value to adjust as per need
      }
      else
      {
        // tft.drawLine(temp, gy, temp, gy - h, gcolor); // Uncomment this to turn on grid
      }
      // draw the axis labels
      tft.setTextColor(axisTextColor, bcolor);
      tft.setTextDatum(TC_DATUM);
      // precision is default Arduino--this could really use some format control
      // tft.drawFloat(i, dp, temp, gy + 7, 1); // use "dp" to pass decimal value in axis text
      tft.drawFloat(i, 0, temp, gy + 7, 1); // disabled decimal in axis text
    }

    // now draw the graph labels
    tft.setTextColor(tcolor, bcolor);
    tft.drawString(title, (int)(gx + w / 2), (int)(gy - h - 30), 4); // Not tested the positioning, black fill refresh in chart area may distort or hide this
  }
}


void TraceDam(TFT_eSPI &tft, double x, double y, byte dp,
           double gx, double gy,
           double w, double h,
           double xlo, double xhi, double xinc,
           double ylo, double yhi, double yinc,
           char *title, char *xlabel, char *ylabel,
           bool &update1, unsigned int color, unsigned int axisTextColor)
{
  double ydiv, xdiv;
  double i;
  double temp;
  int rot, newrot;

  unsigned int gcolor = DKBLUE;   // gcolor = graph grid color
  unsigned int acolor = RED;        // acolor = main axes and label color
  unsigned int pcolor = color;      // pcolor = color of your plotted data
  unsigned int tcolor = WHITE;      // tcolor = text color
  unsigned int bcolor = BLACK;      // bcolor = background color

  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  if (update1)
  {
    update1 = false;

    ox = (x - xlo) * (w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

    if ((ox < gx) || (ox > gx + w))
    {
      update1 = true;
      return;
    }
    if ((oy < gy - h) || (oy > gy))
    {
      update1 = true;
      return;
    }

    tft.setTextDatum(MR_DATUM);

    // draw y scale
    for (i = ylo; i <= yhi; i += yinc)
    {
      // compute the transform
      temp = (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == ylo) // 0 will not work if reading do not start from 0 so keep ylo the first point
      {
        tft.setTextColor(acolor, bcolor);
        // tft.drawString(xlabel, (int)(gx + w) , (int)temp, 2);
        tft.drawString(xlabel, (int)(gx + w + 35 + 20), (320 - 10), 2); // Due to x axis padding moving away from axis
      }
      // draw the axis labels
      tft.setTextColor(tcolor, bcolor);
      // precision is default Arduino--this could really use some format control
      // tft.drawFloat(i, dp, gx - 4, temp, 1);
      tft.drawFloat(i, 0, gx - 4, temp, 1); // Changed to remove decimal places
    }

    // draw x scale
    for (i = xlo; i <= xhi; i += xinc)
    {

      // compute the transform
      temp = (i - xlo) * (w) / (xhi - xlo) + gx;
      if (i == xlo)
      { // 0 will not work if reading do not start from 0 so keep ylo the first point
        tft.setTextColor(acolor, bcolor);
        tft.setTextDatum(BC_DATUM);
        // tft.drawString(ylabel, (int)temp, (int)(gy - h - 8) , 2);
        tft.drawString(ylabel, (int)temp + 10, (int)(gy - h - 8), 2); // Custom value for best fit
      }

      // draw the axis labels
      tft.setTextColor(axisTextColor, bcolor);
      tft.setTextDatum(TC_DATUM);
      // precision is default Arduino--this could really use some format control
      // tft.drawFloat(i, dp, temp, gy + 7, 1);
      tft.drawFloat(i, 0, temp, gy + 7, 1); // remove decimal by using 0
    }

    // now draw the graph labels
    tft.setTextColor(tcolor, bcolor);
    tft.drawString(title, (int)(gx + w / 2), (int)(gy - h - 30), 4);
  }

  // the coordinates are now drawn, plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized above
  x = (x - xlo) * (w) / (xhi - xlo) + gx;
  y = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

  if ((x < gx) || (x > gx + w))
  {
    update1 = true;
    return;
  }
  if ((y < gy - h) || (y > gy))
  {
    update1 = true;
    return;
  }

  tft.drawLine(ox, oy, x, y, pcolor);
  // it's up to you but drawing 2 more lines to give the graph some thickness
  tft.drawLine(ox, oy + 1, x, y + 1, pcolor); // thickness added
  tft.drawLine(ox, oy - 1, x, y - 1, pcolor); // thickness added
  ox = x;
  oy = y;
}




void plotGraphP()
{
  // Iteratig through the buffer to find the min and max values to be used in creating the axis limits dumanically
  for (int z = 0; z < plotTemp.size(); z++)
  {
    minX = min(minX, plotTime[z]);
    maxX = max(maxX, plotTime[z]);
    minY = min(minY, plotTemp[z]); // my y axis is static so dont need to find the min max to generate the axis limit
    maxY = max(maxY, plotTemp[z]); // my y axis is static so dont need to find the min max to generate the axis limit
  }

  update1 = true;
  tft.fillRect(21, 100, 310, 199, BLACK); // need to wipe graph before each update else old traces will show, calculate or trial and error your coordinates
  tft.fillRect(25, 301, 300, 20, BLACK);  // x axis wiping is required as my x axis is dynamic
  tft.fillRect(0, 100, 17, 195, BLUE ); // y axis is stable for me so no wiping: Hint - use visible color to wipe to see the area that is wiped (for testing)

  for (int u = 0; u < plotTemp.size(); u++)
  {
    yplot = plotTemp[u];
    xplot = plotTime[u];
    TraceDam(tft, xplot, yplot, 1, 20, 300, 300, 192, minX, (maxX + 1), xinc, minY, maxY, 5, "", "", "", update1, PINK, WHITE);
    // Textcolor BLACK can be passed to hide it from viewing
    // Do not update axis lables if not necessary
  }
}