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
-Centre text
-Make pretty border etc.
-Make a start button
*/

#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>

bool waiting = false;
bool gameover = true;
bool gameEnd = true;
int randVal = 0;
float Score = 0;
float oldScore = 0;
int bgR = 250;
int bgG = 16;
int bgB = 200;
float multiplier = 0.9;
char command[10];
char outstr[10];
void correct()
{
  EsploraTFT.text("GOOD!", 10, 30);
  delay(1000);
  EsploraTFT.stroke(bgR, bgG, bgB);
  EsploraTFT.text("GOOD!", 10, 30);
  multiplier += 0.1f;
  Score += 1.0f*multiplier;
  EsploraTFT.fill(255, 255, 255);
  EsploraTFT.rect(45, 77, 80, 20);
  EsploraTFT.stroke(0, 0, 0);
  dtostrf(Score, 7, 3, outstr);
  EsploraTFT.text(outstr, 35 , 80);
  waiting = true;
}

void action(char* instruction)
{
  EsploraTFT.text(instruction, 10 , 20);
  delay(1000);
  EsploraTFT.stroke(bgR, bgG, bgB);
  EsploraTFT.text(instruction, 10 , 20);
  EsploraTFT.stroke(255, 255, 255);
}

void textPressed(char* text, int x, int y)
{
  EsploraTFT.stroke(0, 0, 0);
  EsploraTFT.text(text, x , y);
  delay(50);
  EsploraTFT.stroke(bgR, bgG, bgB);
  EsploraTFT.text(text, x , y);
}
void gameoverRoutine()
{
    EsploraTFT.stroke(255, 255, 255);
    EsploraTFT.text("AGAIN?", 35 , 30);
    if(gameEnd)
    {
      EsploraTFT.fill(255, 255, 255);
      EsploraTFT.rect(50, 77, 80, 20);
      EsploraTFT.stroke(0, 0, 0);
      dtostrf(Score, 7, 3, outstr);
      EsploraTFT.text(outstr, 35 , 80);
      gameEnd = false;
    }
    if(Esplora.readButton(SWITCH_DOWN) == LOW)
    {
      textPressed("AGAIN?", 35, 30);
      EsploraTFT.stroke(bgR, bgG, bgB);
      EsploraTFT.text("GAME OVER!", 25 , 60);
      EsploraTFT.stroke(0, 0, 0);
      dtostrf(Score, 7, 3, outstr);
      EsploraTFT.text(outstr, 35 , 80);
      Score = 0;
      multiplier = 0.9;
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
  EsploraTFT.setTextSize(2); //20 pixels
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
        waiting = true;
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
          EsploraTFT.text("GAME OVER!", 25 , 60);
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
          EsploraTFT.text("GAME OVER!", 25 , 60);
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
          EsploraTFT.text("GAME OVER!", 25 , 60);
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
          EsploraTFT.text("GAME OVER!", 25 , 60);
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
          EsploraTFT.text("GAME OVER!", 25 , 60);
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
          EsploraTFT.text("GAME OVER!", 25 , 60);
          gameover = true;
        }
      }break;
      case 7 :
      {
        action("Stick Right");
        if(Esplora.readJoystickX() < 0)
        {
          correct();
        }
        else
        {
          EsploraTFT.text("GAME OVER!", 25 , 60);
          gameover = true;
        }
      }break;
      case 8 :
      {
        action("Stick Left");
        if(Esplora.readJoystickX() > 0)
        {
          correct();
        }
        else
        {
          EsploraTFT.text("GAME OVER!", 25 , 60);
          gameover = true;
        }
      }break;
      case 9 :
      {
        action("Stick Up");
        if(Esplora.readJoystickY() < 0)
        {
          correct();
        }
        else
        {
          EsploraTFT.text("GAME OVER!", 25 , 60);
          gameover = true;
        }
      }break;
      case 10 :
      {
        action("Stick Down");
        if(Esplora.readJoystickY() > 0)
        {
          correct();
        }
        else
        {
          EsploraTFT.text("GAME OVER!", 25 , 60);
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
      }
    }
    EsploraTFT.stroke(255, 255, 255);
  }
  if(gameover)
  {
    gameoverRoutine();
  }
}

