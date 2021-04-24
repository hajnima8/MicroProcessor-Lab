const int clk_ML = 2;
const int clk_MR = 3;
const int clk_SL = 4;
const int clk_SR = 5;
const int rst_ML = 6;
const int rst_MR = 7;
const int rst_SL = 8;
const int rst_SR = 9;
const int DE_ML = 10;
const int DE_MR = 11;
const int DE_SL = 12;
const int DE_SR = 13;
const int inc = A0;
const int ok = A1;
const int buzzer = A2;
int i = 0;
int j = 0;
int var = 0;
int var1 = 0;
int var2 = 0;
int var3 = 0;
int var4 = 0;
int secR = 0;
int secL = 0;
int MinL = 0;
int MinR = 0;
int X = 0;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
boolean Setup = true;
boolean Stop = false;
void setup()
{
  pinMode(clk_ML, OUTPUT);
  pinMode(clk_MR, OUTPUT);
  pinMode(clk_SL, OUTPUT);
  pinMode(clk_SR, OUTPUT);
  pinMode(rst_ML, OUTPUT);
  pinMode(rst_MR, OUTPUT);
  pinMode(rst_SL, OUTPUT);
  pinMode(rst_SR, OUTPUT);
  pinMode(DE_ML, OUTPUT);
  pinMode(DE_MR, OUTPUT);
  pinMode(DE_SL, OUTPUT);
  pinMode(DE_SR, OUTPUT);
  pinMode(inc, INPUT_PULLUP);
  pinMode(ok, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  all_rst();
  digitalWrite(DE_ML, HIGH);
  digitalWrite(DE_MR, HIGH);
  digitalWrite(DE_SL, HIGH);
  digitalWrite(DE_SR, HIGH);
  delay(500);
  Display_Test();
}
void loop()
{
  if (Setup)
  {
    digitalWrite(DE_ML, LOW);
    digitalWrite(DE_MR, LOW);
    digitalWrite(DE_SL, LOW);
    digitalWrite(DE_SR, HIGH);
    while (digitalRead(ok) != LOW)
    {
      if (digitalRead(inc) == LOW)
      {
        X = clk_SR;
        secR = secR + 1;
        c_inc();
        delay(250);
        if (secR > 9)
        {
          secR = 0;
        }
      }
    }
    delay(250);
    digitalWrite(DE_ML, LOW);
    digitalWrite(DE_MR, LOW);
    digitalWrite(DE_SL, HIGH);
    digitalWrite(DE_SR, LOW);
    while (digitalRead(ok) != LOW)
    {
      if (digitalRead(inc) == LOW)
      {
        X = clk_SL;
        secL = secL + 1;
        c_inc();
        if (secL > 5)
        {
          secL = 0;
          digitalWrite(rst_SL, HIGH);
          digitalWrite(rst_SL, LOW);
        }
        delay(250);
      }
    }
    delay(250);
    digitalWrite(DE_ML, LOW);
    digitalWrite(DE_MR, HIGH);
    digitalWrite(DE_SL, LOW);
    digitalWrite(DE_SR, LOW);
    while (digitalRead(ok) != LOW)
    {
      if (digitalRead(inc) == LOW)
      {
        X = clk_MR;
        MinR = MinR + 1;
        c_inc();
        delay(250);
        if (MinR > 9)
        {
          MinR = 0;
        }
      }
    }
    delay(250);
    digitalWrite(DE_ML, HIGH);
    digitalWrite(DE_MR, LOW);
    digitalWrite(DE_SL, LOW);
    digitalWrite(DE_SR, LOW);
    while (digitalRead(ok) != LOW)
    {
      if (digitalRead(inc) == LOW)
      {
        X = clk_ML;
        MinL = MinL + 1;
        c_inc();
        delay(250);
        if (MinL > 9)
        {
          MinL = 0;
        }
      }
    }
    digitalWrite(DE_MR, HIGH);
    digitalWrite(DE_SL, HIGH);
    digitalWrite(DE_SR, HIGH);
    var1 = secR;
    var2 = secL;
    var3 = MinR;
    var4 = MinL;
    Setup = false;
  }
  var1 = var1 - 1;
  if (var1 == -1 && var2 == 0 && Stop == false)
  {
    var1 = 9;
    var2 = 5;
    var3 = var3 - 1;
  }
  if (var1 == -1 && Stop == false)
  {
    var2 = var2 - 1;
    var1 = 9;
  }
  if (var3 == -1)
  {
    var3 = 9;
    var4 = var4 - 1;
  }
  if (var1 == 9   && var2 == 5 && var3 == 9 && var4 == -1)
  {
    Stop = true;
    buzz();
  }
  while (Stop)
  {
    digitalWrite(DE_ML, LOW);
    digitalWrite(DE_MR, LOW);
    digitalWrite(DE_SL, LOW);
    digitalWrite(DE_SR, LOW);
    delay(300);
    digitalWrite(DE_ML, HIGH);
    digitalWrite(DE_MR, HIGH);
    digitalWrite(DE_SL, HIGH);
    digitalWrite(DE_SR, HIGH);
    delay(300);
  }
  delay(1000);
  digitalWrite(rst_SR, HIGH);
  digitalWrite(rst_SR, LOW);
  for (a = 0; a < var1; a++)
  {
    digitalWrite(clk_SR, HIGH);
    digitalWrite(clk_SR, LOW);
  }
  digitalWrite(rst_SL, HIGH);
  digitalWrite(rst_SL, LOW);
  for (b = 0; b < var2; b++)
  {
    digitalWrite(clk_SL, HIGH);
    digitalWrite(clk_SL, LOW);
  }
  digitalWrite(rst_MR, HIGH);
  digitalWrite(rst_MR, LOW);
  for (c = 0; c < var3; c++)
  {
    digitalWrite(clk_MR, HIGH);
    digitalWrite(clk_MR, LOW);
  }
  digitalWrite(rst_ML, HIGH);
  digitalWrite(rst_ML, LOW);
  for (d = 0; d < var4; d++)
  {
    digitalWrite(clk_ML, HIGH);
    digitalWrite(clk_ML, LOW);
  }
}
void Display_Test()
{
  all_rst();
  var = 10;
  for (j = 0; j < 10; j++)
  {
    var = var - 1;
    for (i = 0; i < var; i++)
    {
      digitalWrite(clk_ML, HIGH);
      digitalWrite(clk_MR, HIGH);
      digitalWrite(clk_SL, HIGH);
      digitalWrite(clk_SR, HIGH);
      digitalWrite(clk_ML, LOW);
      digitalWrite(clk_MR, LOW);
      digitalWrite(clk_SL, LOW);
      digitalWrite(clk_SR, LOW);
    }
    delay(250);
    all_rst();
  }
}
void all_rst()
{
  digitalWrite(rst_ML, HIGH);
  digitalWrite(rst_MR, HIGH);
  digitalWrite(rst_SL, HIGH);
  digitalWrite(rst_SR, HIGH);
  digitalWrite(rst_ML, LOW);
  digitalWrite(rst_MR, LOW);
  digitalWrite(rst_SL, LOW);
  digitalWrite(rst_SR, LOW);
}
void c_inc()
{
  digitalWrite(X, HIGH);
  digitalWrite(X, LOW);
}
void buzz()
{
  for (e = 0; e < 10; e++)
  {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
  }
}