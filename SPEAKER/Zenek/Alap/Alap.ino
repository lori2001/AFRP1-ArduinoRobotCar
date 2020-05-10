int SPEAKER = 53;
int sec=1310;
int c = 261;
int d = 294;
int e = 329;
int f = 349;
int g = 391;
int gS = 415;
int a = 440;
int aS = 455;
int b = 466;
int cH = 523;
int cSH = 554;
int dH = 587;
int dSH = 622;
int eH = 659;
int fH = 698;
int fSH = 740;
int gH = 784;
int gSH = 830;
int aH = 880;
int DO = 261;
int RE = 294;
int MI = 329;
int FA = 349; 
int SO = 391;
int La = 440;
int SI = 466;
void setup()
{
pinMode(SPEAKER,OUTPUT);

beep(900,900);
delay(sec/4);
beep(1200,700);
delay(sec/8);
beep(900,600);
delay(sec/4);
beep(1200,400);
}
void loop()
{
 beep(1200,400); 
}
void beep(int note, int duration)
{
//Play tone on buzzerPin
tone(SPEAKER, note, duration);
}

