#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>
#define chanPhat A0
#define chanThu A1
#define tocDoMax 140
#define tocDoMin 50
#define khoangCachMax 300
#define khoangCachGioiHan 50
#define khoangCachDung 30
#define led 13
NewPing camBien(chanPhat, chanThu, khoangCachMax);

AF_DCMotor motor1(1, MOTOR12_1KHZ); // tao dong co trai 1
AF_DCMotor motor2(2, MOTOR12_1KHZ); // tao dong co trai 2
AF_DCMotor motor3(3, MOTOR34_1KHZ); // tao dong co phai 1
AF_DCMotor motor4(4, MOTOR34_1KHZ); // tao dong co phai 2
Servo myservo;
int khoangCachTrai, khoangCachPhai, khoangCachTruoc;
int khoangCach = 0;

void setup() {
  Serial.begin(115200); // mở cổng Serial monitor 115200 bps
  myservo.attach(10); // Khai báo chân servo
  myservo.write(90);
  delay(1000);
  pinMode(led, OUTPUT);
}

void loop() {
  quayServo();
}

void quayServo(){
  myservo.write(45);
  delay(50);
  khoangCachPhai = docKhoangCach();
  myservo.write(90);
  delay(100);
  myservo.write(135);
  delay(50);
  khoangCachTrai = docKhoangCach();
  delay(50);
  myservo.write(90);
  delay(50);
  khoangCachTruoc = docKhoangCach();
  soSanhTraiTruocPhai();
  }
void soSanhTraiTruocPhai() {
  if (khoangCachTruoc < khoangCachDung) {
    luiSau();
    delay(5);
    dungLai();
    myservo.write(90);
    delay(5);
    quayServo();
    if (khoangCachTrai > khoangCachPhai) {
      quayTrai();
    } else if (khoangCachPhai > khoangCachTrai) {
      quayPhai();
    }
    delay(5);
  } else if (khoangCachTrai < khoangCachGioiHan) {
    quayNuaPhai();
  } else if (khoangCachPhai < khoangCachGioiHan) {
    quayNuaTrai();
  } else
    tienTruoc();
  delay(5);
}

int docKhoangCach() {
  delay(70);
  unsigned int doKhoangCach = camBien.ping();
  int quangDuong = doKhoangCach / US_ROUNDTRIP_CM;
  Serial.println(quangDuong);
  return quangDuong;
}

void dungLai() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  digitalWrite(led, HIGH);
}

void tienTruoc() {
  motor1.run(FORWARD);
  motor1.setSpeed(tocDoMax);
  motor2.run(FORWARD);
  motor2.setSpeed(tocDoMax);
  motor3.run(FORWARD);
  motor3.setSpeed(tocDoMax);
  motor4.run(FORWARD);
  motor4.setSpeed(tocDoMax);
  digitalWrite(led, LOW);
  delay(5);
}

void luiSau() {
  motor1.run(BACKWARD);
  motor1.setSpeed(tocDoMax);
  motor2.run(BACKWARD);
  motor2.setSpeed(tocDoMax);
  motor3.run(BACKWARD);
  motor3.setSpeed(tocDoMax);
  motor4.run(BACKWARD);
  motor4.setSpeed(tocDoMax);
  digitalWrite(led, HIGH);
  delay(500);
}
void quayPhai() {
  motor1.run(FORWARD);
  motor1.setSpeed(tocDoMax);
  motor2.run(FORWARD);
  motor2.setSpeed(tocDoMax);
  motor3.run(BACKWARD);
  motor3.setSpeed(tocDoMax);
  motor4.run(BACKWARD);
  motor4.setSpeed(tocDoMax);
  digitalWrite(led, HIGH);
  delay(400);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void quayTrai() {
  motor1.run(BACKWARD);
  motor1.setSpeed(tocDoMax);
  motor2.run(BACKWARD);
  motor2.setSpeed(tocDoMax);
  motor3.run(FORWARD);
  motor3.setSpeed(tocDoMax);
  motor4.run(FORWARD);
  motor4.setSpeed(tocDoMax);
  digitalWrite(led, HIGH);
  delay(400);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void quayNuaPhai() {
  motor1.run(FORWARD);
  motor1.setSpeed(tocDoMax);
  motor2.run(FORWARD);
  motor2.setSpeed(tocDoMax);
  motor3.run(BACKWARD);
  motor3.setSpeed(tocDoMax);
  motor4.run(BACKWARD);
  motor4.setSpeed(tocDoMax);
  digitalWrite(led, HIGH);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void quayNuaTrai() {
  motor1.run(BACKWARD);
  motor1.setSpeed(tocDoMax);
  motor2.run(BACKWARD);
  motor2.setSpeed(tocDoMax);
  motor3.run(FORWARD);
  motor3.setSpeed(tocDoMax);
  motor4.run(FORWARD);
  motor4.setSpeed(tocDoMax);
  digitalWrite(led, HIGH);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
