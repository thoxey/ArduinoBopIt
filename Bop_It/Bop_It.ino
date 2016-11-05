//--------------------------------------------------------------------------------------------------------------------------------------------
/// @author Tom Hoxey
/// @version 1.0
/// @date 01/11/16 \n

/*
A fun little project I made to get familiar with the Arduino Esplora,
It is a game inspired by 'Bop it' where the player is given a series 
of commands to execute before the time runs out.

To Do:
-Display Scores, Save High score, for current session.
-Add a random confirmation word generator (good, awesome, great etc.)
-Centre text (Pretty much there)
-Make pretty border etc. (Border Done)
*/

#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include <stdio.h>

#define HEIGHT 128 //Height of the screen
#define WIDTH  160 //Width of the screen

bool waiting = false;
bool gameover = false;
bool gameEnd = true;
bool started = false;
int randVal = 0;
int Score = 0;
int bgR = 250;
int bgG = 16;
int bgB = 200;
int multiplier = 1;
char command[10];
char outstr[10];

void correct()
{
  EsploraTFT.text("GOOD!", 10, 30);
  delay(1000);
  EsploraTFT.stroke(bgR, bgG, bgB);
  EsploraTFT.text("GOOD!", 10, 30);
  Score += 1*multiplier;
  multiplier += 1;
  waiting = true;
  EsploraTFT.stroke(255, 255, 255);
}
int centreX(char* text)
{
  int instLen = strlen(text)*12; //Length of instruction in pixels
  int xPos = (WIDTH/2) - (instLen/2);
  return xPos;
}

void action(char* instruction)
{
  int xPos = centreX(instruction);
  EsploraTFT.text(instruction, xPos , 20);
  delay(1000);
  EsploraTFT.stroke(bgR, bgG, bgB);
  EsploraTFT.text(instruction, xPos , 20);
  EsploraTFT.stroke(255, 255, 255);
}

void textPressed(char* text, int x, int y)
{
  EsploraTFT.stroke(0, 0, 0);
  EsploraTFT.text(text, x , y);
  delay(50);
  EsploraTFT.stroke(bgR, bgG, bgB);
  EsploraTFT.text(text, x , y);
  EsploraTFT.stroke(255, 255, 255);
}

void gameoverRoutine()
{
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.text("GAME OVER!", 25 , 60);
    int Xpos = centreX("AGAIN?");
    EsploraTFT.text("AGAIN?", Xpos , 30);
    if(gameEnd)
    {
      EsploraTFT.fill(255, 255, 255);
      EsploraTFT.stroke(0, 0, 0);
      dtostrf(Score, 7, 3, outstr);
      EsploraTFT.text(Score, 35 , 80);
      gameEnd = false;
    }
    if(Esplora.readButton(SWITCH_DOWN) == LOW)
    {
      textPressed("AGAIN?", Xpos, 30);
      EsploraTFT.stroke(bgR, bgG, bgB);
      EsploraTFT.text("GAME OVER!", 25 , 60);
      EsploraTFT.stroke(bgR, bgG, bgB);
      dtostrf(Score, 7, 3, outstr);
      EsploraTFT.text(Score, 35 , 80);
      Score = 0;
      multiplier = 1;
      EsploraTFT.stroke(255, 255, 255);
      gameover = false;
      waiting = true;
    }
}
void setup() 
{
  EsploraTFT.begin();
  EsploraTFT.background(255, 255, 255);
  EsploraTFT.fill(bgR, bgG, bgB);
  EsploraTFT.rect(5, 5, EsploraTFT.width()-10, EsploraTFT.height()-10);
  EsploraTFT.stroke(255, 255, 255);
  EsploraTFT.setTextSize(2); 
  //Serial.begin(9600); /*Uncomment for Debug*/
}

void loop()
{
  randVal = random(12);
  if(waiting)
  {
    waiting = false;
    switch(randVal)
    {
      case 0 : 
      {
        // action("Shout");
        // if(Esplora.readMicrophone()>100;)
        // {

        // }
        // else
        // {
        //   gameover = true;
        // }
        waiting = true; //Above commented out so I dont lose my voice during testing
      }break;
      case 1 :
      {
        action("Slider Right");
        if(Esplora.readSlider() < 500)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 2 :
      {
        action("Slider Left");
        if(Esplora.readSlider() > 500)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 3 :
      {
        action("Button Down");
        if(Esplora.readButton(SWITCH_DOWN) == LOW)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 4 :
      {
        action("Button Left");
        if(Esplora.readButton(SWITCH_LEFT) == LOW)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 5 :
      {
        action("Button Up");
        if(Esplora.readButton(SWITCH_UP) == LOW)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 6 :
      {
        action("Button Right");
        if(Esplora.readButton(SWITCH_RIGHT) == LOW)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 7 :
      {
        action("Stick Right");
        if(Esplora.readJoystickX() < -100)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 8 :
      {
        action("Stick Left");
        if(Esplora.readJoystickX() > 100)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 9 :
      {
        action("Stick Up");
        if(Esplora.readJoystickY() < -100)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 10 :
      {
        action("Stick Down");
        if(Esplora.readJoystickY() > 100)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
      case 11 :
      {
        action("Shake");
        if(abs(Esplora.readAccelerometer(X_AXIS)) > 200 || abs(Esplora.readAccelerometer(Y_AXIS)) > 200)
        {
          correct();
        }
        else
        {
          gameover = true;
        }
      }break;
    }
    
    EsploraTFT.stroke(255, 255, 255);
  }
  else if(!started)
  {
    int Xpos = centreX("START");
    EsploraTFT.text("START", Xpos , 30);
    if(Esplora.readButton(SWITCH_DOWN) == LOW)
    {
      textPressed("START", Xpos , 30);
      started = true;
      waiting = true;
      return;
    }
  }
  if(gameover)
  {
    gameoverRoutine();
  }
}

