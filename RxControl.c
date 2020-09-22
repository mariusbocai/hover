int AccIn= 2;
int SteerIn = 3;

#define DEBUG_VERSION
#define AccIdleUpperThr 400
#define AccIdleLowerThr 300

#define SteerIdleUpperThr 600
#define SteerIdleLowerThr 400

void setup ()

{
  pinMode (AccIn, INPUT);
  pinMode (SteerIn, INPUT);
  Serial.begin (19200);
}

void loop ()

{
  int xVal, yVal;
  int16_t yMap, xMap;

  xVal = pulseIn(SteerIn, HIGH, 25000);
  yVal = pulseIn(AccIn, HIGH, 25000);

  /*Y handling*/
  if((yVal>1000)&&(yVal<2000))
  {
    yVal-=1000;
    if(yVal>AccIdleUpperThr)
    {
               yMap = map(yVal,(AccIdleLowerThr+1),1023,0,1023);
    }
    else if(yVal<AccIdleLowerThr)
    {
               yMap = map(yVal,0,AccIdleLowerThr-1,-AccIdleLowerThr,0);
    }
    else
    {
               yMap = 0;
    }
  }

  /*X handling*/
  if((xVal>1000)&&(xVal<2000))
  {
    xVal-=1000;
    if(xVal>SteerIdleUpperThr)
    {
               xMap = map(xVal,(SteerIdleUpperThr+1),1023,0,1023);
    }
    else if(xVal<SteerIdleLowerThr)
    {
               xMap = map(xVal,0,(SteerIdleLowerThr-1),-1023,0);
    }
    else
    {
               xMap = 0;
    }
  }
  xMap = xMap * (-1); //added this to invert left and right steer

#ifndef DEBUG_VERSION
  Serial.write((uint8_t *) &xMap, sizeof(xMap));
  Serial.write((uint8_t *) &yMap, sizeof(yMap));
#endif

#ifdef DEBUG_VERSION
//if(xMap>0) Serial.write("X_pozitiv\n");
//  else if(xMap<0) Serial.write("X_negativ\n");
//  else Serial.write("X_zero\n");

//if(yMap>0) Serial.write("Y_pozitiv\n");
//  else if(yMap<0) Serial.write("Y_negativ\n");
//  else Serial.write("Y_zero\n");


  Serial.print("X = ");
  Serial.println (xMap, DEC);

  Serial.print ("Y = ");
  Serial.println (yMap, DEC);
#endif

}