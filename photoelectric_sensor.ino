// 定义光电开关的引脚
const int sensorPin = 2;  // 光电开关信号连接到Arduino的D2引脚
int sensorState = 0;      // 存储光电开关的状态

void setup() {
  Serial.begin(9600);         // 初始化串口通信
  pinMode(sensorPin, INPUT);  // 设置光电开关引脚为输入
}

void loop() {
  // 读取光电开关的状态
  sensorState = digitalRead(sensorPin);
  Serial.print (sensorState);

  // 如果检测到物体
  if (sensorState == HIGH) {
    Serial.println("Object detected!");
  } else {
    Serial.println("No object detected.");
  }

  delay(500);  // 每500毫秒检测一次
}
