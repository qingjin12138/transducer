#define BLINKER_MIOT_LIGHT
#define BLINKER_WIFI

#include <Blinker.h>
#define GPIO_LED4 4  //指定IO口
char auth[] = "c84ff5221eba";   //换成APP获取到的密匙
char ssid[] = "TP-LINK_AI";          //WiFi账号
char pswd[] = "66507357";   //WIFI密码

int GPIO4=0;//定义GPIO口用于控制继电器

#define BUTTON_1 "ButtonKey"


BlinkerButton Button1("123");//这里需要根据自己在BLINKER里面设置的名字进行更改

void button1_callback(const String & state)
{
    //BLINKER_LOG("get button state: ", state);
    Blinker.vibrate(); 
    if (state=="on") {
        //digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(GPIO_LED4, LOW);
        // 反馈开关状态
        Button1.print("on");
    } else if(state=="off"){
        //digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(GPIO_LED4, HIGH);
        // 反馈开关状态
        Button1.print("off");
    }
}



void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ",state);

    if (state == BLINKER_CMD_OFF) {//如果语音接收到是关闭灯就设置GPIO口为高电平
        digitalWrite(GPIO_LED4, HIGH);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_ON) {
        digitalWrite(GPIO_LED4, LOW);
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
}


void setup() {
    Serial.begin(115200);
    //pinMode(LED_BUILTIN, OUTPUT);
    pinMode(GPIO_LED4,OUTPUT);
    digitalWrite(GPIO_LED4,HIGH);//初始化，由于继电器是低电平触发。所以刚开始设为高电平
    //digitalWrite(LED_BUILTIN, HIGH);
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    BlinkerMIOT.attachPowerState(miotPowerState);//这段代码一定要加，不加小爱同学控制不了,务必在回调函数中反馈该控制状态


}

void loop()
{
    Blinker.run();
}
