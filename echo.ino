const byte trigPin=5;    //超声波模块的触发引脚
const int echopin=6;    //超声波模块的接收脚
unsigned long d;      //存储好声波模块的持续时间

//自定义pong()函数将返回unsigned long类型的数值

unsigned long ping(){
  digitalWrite(trigPin,HIGH);    //触发脚设置为高定位
  delayMicroseconds(5);     //延时5毫秒
  digitalWrite(trigPin,LOW);    //触发脚设置为低定位
  
  return pulseIn(echopin,HIGH);   //传回高脉冲的持续时间.

}

void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echopin,INPUT);

  Serial.begin(9600);
  Serial.println("开始");

}

void loop(){
  d=ping() / 58;
  Serial.print(d);    //显示距离
  Serial.print("cm");
  Serial.println();
  delay(1000);
}
