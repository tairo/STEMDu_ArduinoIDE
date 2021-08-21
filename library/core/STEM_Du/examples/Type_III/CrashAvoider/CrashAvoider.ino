
/*
 * RDX-X12 衝突回避ロボットサンプル
 *
 * 停止の回数に応じて右か左に曲がります。
 *
 * This example code is in the public domain.
 *
 */

int ir1 = 0;
int ir2 = 0;
int value = 500;  //しきい値
int n = 1;

void setup(){
}

void loop(){
  //機体とポート類の接続は 左：小さい番号←→大きい番号：右
  ir1 = analogRead(1) ;
  ir2 = analogRead(2) ;
  //前進
  digitalWrite( 0 , HIGH );
  digitalWrite( 1 , LOW );
  analogWrite(10 , 200);
  digitalWrite( 11 , HIGH );
  digitalWrite( 12 , LOW );
  analogWrite(13 , 200);

  //赤外線センサが反応したときの動作
  if (ir1 >= value || ir2 >= value){
    switch (n){
      case 1:
        turn_left();
        break;
      case 2:
        turn_right();
        break;
      case 3:
        turn_left();
        break;
      case 4:
        turn_right();
        break;
      case 5:
        turn_left();
        break;
      case 6:
        turn_right();
        break;
      case 7:
        turn_left();
        break;
      case 8:
        turn_right();
        break;
      case 9:
        turn_left();
        break;
      case 10:
        turn_right();
        break;
      default:
        n = 1;
    }
    n++;
  }
}

void turn_right(void)
{
  // 停止
  digitalWrite( 0 , LOW );
  digitalWrite( 1 , LOW );
  digitalWrite( 11 , LOW );
  digitalWrite( 12 , LOW );
  delay(2000);
  // 後退
  digitalWrite( 0 , LOW );
  digitalWrite( 1 , HIGH );
  digitalWrite( 11 , LOW );
  digitalWrite( 12 , HIGH );
  delay(1000);
  // 右旋回
  digitalWrite( 0 , HIGH );
  digitalWrite( 1 , LOW );
  digitalWrite( 11 , LOW );
  digitalWrite( 12 , HIGH );
  delay(1000);
}

void turn_left(void)
{
  // 停止
  digitalWrite( 0 , LOW );
  digitalWrite( 1 , LOW );
  digitalWrite( 11 , LOW );
  digitalWrite( 12 , LOW );
  delay(2000);
  // 後退
  digitalWrite( 0 , LOW );
  digitalWrite( 1 , HIGH );
  digitalWrite( 11 , LOW );
  digitalWrite( 12 , HIGH );
  delay(1000);
  // 左旋回
  digitalWrite( 0 , LOW );
  digitalWrite( 1 , HIGH );
  digitalWrite( 11 , HIGH );
  digitalWrite( 12 , LOW );
  delay(1000);
}

