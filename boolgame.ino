include <M5Stack.h>
int color[9]={
  WHITE,
  PINK,
  GREENYELLOW,
  GREEN,
  CYAN,
  BLUE,
  YELLOW,
  ORANGE,
  RED
};
//ランキング用
int rank[5];
void setup(){
    M5.begin();   
    M5.Speaker.begin();
    M5.Speaker.setVolume(4);  
}
void loop() {
  int option=0;
  while(1){
  //ホーム画面
    M5.update();
      M5.Lcd.setCursor(320/5,100);
      M5.Lcd.setTextSize(4);
      M5.Lcd.printf("BALL GAME");
      M5.Lcd.setCursor(10,10);
      M5.Lcd.setTextSize(1);
      M5.Lcd.printf("@2024 TEAM_I MADE IN JAPAN");
      M5.Lcd.setCursor(50,180);
      M5.Lcd.setTextSize(2);
      M5.Lcd.printf("A_butten is ranking.");
      M5.Lcd.setCursor(50,200);
      M5.Lcd.setTextSize(2);
      M5.Lcd.printf("C_butten is start.");
    M5.Lcd.fillRect(0,0,320,5,GREEN);
    M5.Lcd.fillRect(0,0,5,240,GREEN);
    M5.Lcd.fillRect(0,235,320,5,GREEN);
    M5.Lcd.fillRect(315,0,5,240,GREEN);

    if(M5.BtnA.isPressed()==1){
    M5.Speaker.tone(800,1);
    delay(30);
    M5.Speaker.end();
      M5.Lcd.fillScreen(BLACK);
      option=0;
      break;}

    if(M5.BtnC.isPressed()==1){
    M5.Speaker.tone(800,1);
    delay(30);
    M5.Speaker.end();
      M5.Lcd.fillScreen(BLACK);
      option=1;
      break;}
  }
  //ボールの初期位置の設定
  srand(time(NULL));
  int r=(rand()%300)+10;

//使用する変数の定義

//スコア
int S=0;
//ボールのスピード
double speed=3;
//音の高さ
double step=1.059;
//板の位置
int shift=110,save=110;
//板のサイズ
int size=80;
//GAME OVERの判定
int stop=0;
//ボールの位置
int x=r,y=10,m_x=0,m_y=0,chk_x=160,chk_y=120,count=0;
//色の変更
int color_s=0;
//ゲーム用のプログラム
if(option==0){
while(1){
      M5.update();
      M5.Lcd.setTextSize(4);
      M5.Lcd.setCursor(10,0);
      M5.Lcd.printf(" --RANKING--\n");
    for(int i=0;i<5;i++){
      M5.Lcd.setTextSize(4);
      M5.Lcd.setCursor(10,37*(i+1));
      M5.Lcd.printf("    %d:%3d\n",i+1,rank[i]);
    }
    M5.Lcd.setCursor(320/5,220);
      M5.Lcd.setTextSize(2);
      M5.Lcd.printf("B_butten is back.");
      if(M5.BtnB.isPressed()==1){
      M5.Speaker.tone(800,1);
      delay(30);
      M5.Speaker.end();
      M5.Lcd.fillScreen(BLACK);
      break;}
}
}else if(option==1){
while(1){
  M5.update();
//黄色い枠の表示
    M5.Lcd.fillRect(0,180,320,5,ORANGE);
    M5.Lcd.fillRect(0,180,5,240,ORANGE);
    M5.Lcd.fillRect(0,235,320,5,ORANGE);
    M5.Lcd.fillRect(315,180,5,240,ORANGE);
    M5.Lcd.fillRect(230,180,5,240,ORANGE);
M5.update();
//スコアとレベルの表示
  M5.Lcd.setCursor(10,195);
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("SCORE%4d", S);
  M5.Lcd.setCursor(240,200);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Lv.%1d",color_s+1);
//板を左に移動
  if(M5.BtnA.isPressed()==1&&0<=shift){
    shift-=10;
  }
//板を右に移動
  if(M5.BtnC.isPressed()==1&&shift+size<=320){
    shift+=10;
  }
//ボールが左端に当たった時反射
  if(x<=5){
    m_x=0;
    x=5;
    M5.Speaker.tone(392*pow(step,color_s), 1);
    delay(10);
  }
  if(m_x==0){
    x+=speed;
  }
//ボールが右端に当たった時反射
  if(315<=x){
    m_x=1;
    x=315;
    M5.Speaker.tone(392*pow(step,color_s), 1);
    delay(10);
  }
  if(m_x==1){
    x-=speed;
  }
//ボールが画面上に当たったとき反射
  if(y<=5){
    m_y=0;
    y=5;
    M5.Speaker.tone(262*pow(step,color_s), 1);
    delay(10);
  }
  if(m_y==0){
    y+=speed;
  }
//ボールが板に当たった時に反射
  if(170<=y&&shift-5<=x&&x<=shift+size+5){
    m_y=1;
    y=170;
    S+=10;
    //50点ごとにスピードアップ
    if(S%50==0){speed+=0.5;
    //色の変更
    if(color_s<=7)color_s++;
    //板のサイズを短くする
    if(30<size)size-=5;
    }
    M5.Speaker.tone(262*pow(step,color_s), 1);
    delay(10);
  }
  if(m_y==1){
    y-=speed;
  }
 //ボールの描画など 
  M5.Lcd.fillCircle (x, y, 5 ,color[color_s]);
  M5.Lcd.drawLine(shift,175,shift+size,175, WHITE);
  delay(30);
  M5.Lcd.fillCircle (chk_x,chk_y,5,BLACK);
  chk_x=x;
  chk_y=y;
  M5.Lcd.drawLine(save,175,save+size,175, BLACK);
  save=shift;
  M5.Speaker.end();

  //GAME OVERでwhileを脱出
  if(175<=y){
    stop++;
    M5.Lcd.fillScreen(BLACK);
    break;
  }
}
}

//GAME OVERの画面
if(stop!=0){
  //sort(rank.begin(),rank.end());
  for(int i=0;i<5-1;i++){
    for(int j=0;j<5-1;j++){
      if(rank[j]>rank[j+1]){
        int ex=rank[j];
        rank[j]=rank[j+1];
        rank[j+1]=ex;
      }
    }
  }
  rank[0]=S;
  //sort(rank.rbegin(),rank.end());
for(int i=0;i<5-1;i++){
    for(int j=0;j<5-1;j++){
      if(rank[j]<rank[j+1]){
        int ex=rank[j];
        rank[j]=rank[j+1];
        rank[j+1]=ex;
      }
    }
  }
  M5.Lcd.setCursor(320/5,50);
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("GAME OVER\n");
  M5.Lcd.printf("  YOUR SCORE\n   %4d",S);
  delay(3000);
  M5.Lcd.fillScreen(BLACK);}}
