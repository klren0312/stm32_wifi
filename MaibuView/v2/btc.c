
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "maibu_sdk.h"
#include "maibu_res.h"


/*Web通讯ID*/
static uint32_t g_comm_id_web = 0;

/*Web request地址*/
#define DATA_WEB     "http://www.zzes1314.cn:3000/newwatch"

/* 时间项 */
#define DATE_TEXT_POS_X                      2
#define DATE_TEXT_POS_Y                      6
#define DATE_TEXT_SIZE_W                     70
#define DATE_TEXT_SIZE_H                     14

#define TIME_TEXT_POS_X                      90
#define TIME_TEXT_POS_Y                      6
#define TIME_TEXT_SIZE_W                     36
#define TIME_TEXT_SIZE_H                     14


/*图片坐标：第一项为背景图片，后面依次为时间的1~4位*/
static uint8_t ORIGIN_X = 0;
static uint8_t ORIGIN_Y = 0;
static uint8_t ORIGIN_H = 128;
static uint8_t ORIGIN_W = 128;


static const char weekday[7][11] =
{
    {"周日"},
    {"周一"},
    {"周二"},
    {"周三"},
    {"周四"},
    {"周五"},
    {"周六"}
};


/*窗口ID*/
static int32_t g_window_id = -1;

 
//治电科技
static int32_t g_layer_id_zzes = -1;
 

//温度数据内容
static int32_t g_layer_id_temdata = -1;
//湿度数据内容
static int32_t g_layer_id_humdata = -1;
//屋内判断数据内容
static int32_t g_layer_id_indoordata = -1;

//时间的句柄
static int32_t g_layer_id_time   = -1;
//日期的句柄
static int32_t g_layer_id_date   = -1;

//整个窗体句柄
static P_Window h_window;

void data_request_web()
{
    /*拼接url请求地址, 注意url的缓存大小*/
    char url[200] = ""; 
    sprintf(url, "%s", DATA_WEB);       

    /*
        拼接过滤参数，即只接受和过滤参数匹配的返回值
        个人感觉这里的过滤可能是让手机做的，就是这里通知手机：json中的数据除了我制定的其他都过滤掉
    */
   char param[50] = "";
   sprintf(param,"%s,%s,%s","tem","hum","indoor");


    /*发送一次*/
    g_comm_id_web = maibu_comm_request_web(url, param, 0);//过滤
}

void add_text_layer(P_Window p_window, int32_t *p_layer_id, char *p_str, GRect *p_frame, enum GAlign align, int8_t font, enum GColor color)
{
    LayerText text_cfg = {p_str, *p_frame, align, font, 0};
    P_Layer layer = app_layer_create_text(&text_cfg);
    app_layer_set_bg_color(layer, color);

    P_Layer old_layer = app_window_get_layer_by_id(p_window, *p_layer_id);
    if(old_layer)
    {
        *p_layer_id = app_window_replace_layer(p_window, old_layer, layer);
    }
    else
    {
        *p_layer_id = app_window_add_layer(p_window, layer);
    }
}

/*
 *--------------------------------------------------------------------------------------
 *     function:  get_layer
 *    parameter: 
 *       return:
 *  description:  生成表盘窗口的各图层
 *        other:
 *--------------------------------------------------------------------------------------
 */
static P_Layer get_layer()
{
    GRect frame = {{ORIGIN_X, ORIGIN_Y}, {ORIGIN_H, ORIGIN_W}};
    GBitmap bitmap;
        
    /*获取用户图片*/
 
    res_get_user_bitmap(PIC_BG, &bitmap);
    
    LayerBitmap layerbmp = { bitmap, frame, GAlignLeft};    

    /*生成图层*/
    P_Layer  layer_back = NULL;
    layer_back = app_layer_create_bitmap(&layerbmp);

    return (layer_back);
}

/* 添加时间图层 */
static void add_time_bar(P_Window p_window)
{
    uint8_t text_buf[40];
    struct date_time t;
    app_service_get_datetime(&t);

    memset(text_buf, 0, sizeof(text_buf));
    sprintf((char *)text_buf, "%s", (char *)&weekday[t.wday][0]);
    sprintf(&text_buf[6], "%02d-%02d", t.mon, t.mday);

    GRect frame;
    frame.origin.x = DATE_TEXT_POS_X;
    frame.origin.y = DATE_TEXT_POS_Y;
    frame.size.h   = DATE_TEXT_SIZE_H;
    frame.size.w   = DATE_TEXT_SIZE_W;

    add_text_layer(p_window, &g_layer_id_date, (char*)text_buf, &frame, GAlignLeft, U_ASCII_ARIAL_14, GColorWhite);

    frame.origin.x = TIME_TEXT_POS_X;
    frame.origin.y = TIME_TEXT_POS_Y;
    frame.size.h   = TIME_TEXT_SIZE_H;
    frame.size.w   = TIME_TEXT_SIZE_W;

    memset(text_buf, 0, sizeof(text_buf));
    sprintf(text_buf, "%02d:%02d", t.hour, t.min);

    add_text_layer(p_window, &g_layer_id_time, (char*)text_buf, &frame, GAlignLeft, U_ASCII_ARIAL_14, GColorWhite);
}

P_Window init_btc_window()
{

    static P_Window p_window;
    P_Layer layer_background = NULL;   
    p_window = app_window_create();
    if (NULL == p_window)
    {
        return NULL;
    }



    /*加入你的代码 begin*/    
    /*创建背景图层*/
    layer_background = get_layer();

    /*添加背景图层到窗口*/
    app_window_add_layer(p_window, layer_background);

    /* 添加时间栏 */
    add_time_bar(p_window);
 
    /*添加数据提示信息*/
    GRect frame_zzes = {{0,34}, {16, 128}};
    add_text_layer(p_window, &g_layer_id_zzes, "治电科技", &frame_zzes, GAlignBottom, U_ASCII_ARIAL_16, GColorWhite);
        
    /*添加温度数据*/
    GRect frame_temdata = {{25, 62}, {16, 50}};
    add_text_layer(p_window, &g_layer_id_temdata, "waiting", &frame_temdata, GAlignCenter, U_ASCII_ARIAL_14, GColorWhite);
    
    /*添加湿度数据*/
    GRect frame_humdata = {{25, 83}, {16, 50}};
    add_text_layer(p_window, &g_layer_id_humdata, "waiting", &frame_humdata, GAlignCenter, U_ASCII_ARIAL_14, GColorWhite);
    
    /*添加窝内数据*/
    GRect frame_indoordata = {{25, 103}, {16, 50}};
    add_text_layer(p_window, &g_layer_id_indoordata, "waiting", &frame_indoordata, GAlignCenter, U_ASCII_ARIAL_14, GColorWhite);

    return p_window;

}

void data_comm_result_callback(enum ECommResult result, uint32_t comm_id, void *context)
{

    /*如果上一次请求WEB通讯失败，并且通讯ID相同，则重新发送*/
    if ((result == ECommResultFail) && (comm_id == g_comm_id_web))
    {
        data_request_web();
    }
    
} 

static void web_recv_callback(const uint8_t *buff, uint16_t size)
{
    char stock_gid[10];
    char stock_gid2[10];
    char stock_gid3[10];

    char i;

    maibu_get_json_str(buff,"indoor", stock_gid, 10);//过滤
    maibu_get_json_str(buff,"tem", stock_gid2, 10);
    maibu_get_json_str(buff,"hum", stock_gid3, 10);
    for (i=0;i<10;i++)
    {
    if (stock_gid[i]=='}')
        {
            stock_gid[i]=0;
        }
    }
    for (i=0;i<10;i++)
    {
    if (stock_gid2[i]=='}')
        {
            stock_gid2[i]=0;
        }
    }
    for (i=0;i<10;i++)
    {
    if (stock_gid3[i]=='}')
        {
            stock_gid3[i]=0;
        }
    }
    /*添加数据*/
    GRect frame_indoordata = {{25, 103}, {16, 50}};
    add_text_layer(h_window, &g_layer_id_indoordata, stock_gid, &frame_indoordata, GAlignCenter, U_ASCII_ARIAL_14, GColorWhite);
    GRect frame_temdata = {{25, 62}, {16, 50}};
    add_text_layer(h_window, &g_layer_id_temdata, stock_gid2,&frame_temdata, GAlignCenter,U_ASCII_ARIAL_14,GColorWhite);
    GRect frame_humdata = {{25, 83}, {16, 50}};
    add_text_layer(h_window, &g_layer_id_humdata, stock_gid3,&frame_humdata, GAlignCenter,U_ASCII_ARIAL_14,GColorWhite);
    app_window_update(h_window);
}

static void watch_time_change_callback(enum SysEventType type, void *context)
{
    /*时间更改，分变化*/
    if (type == SysEventTypeTimeChange)
    {
        uint8_t text_buf[40];
        struct date_time t;
        app_service_get_datetime(&t);

        memset(text_buf, 0, sizeof(text_buf));
        sprintf((char *)text_buf, "%s", (char *)&weekday[t.wday][0]);
        sprintf(&text_buf[6], "%02d-%02d", t.mon, t.mday);

        GRect frame;
        frame.origin.x = DATE_TEXT_POS_X;
        frame.origin.y = DATE_TEXT_POS_Y;
        frame.size.h   = DATE_TEXT_SIZE_H;
        frame.size.w   = DATE_TEXT_SIZE_W;

        add_text_layer(h_window, &g_layer_id_date, (char*)text_buf, &frame, GAlignLeft, U_ASCII_ARIAL_14, GColorWhite);

        frame.origin.x = TIME_TEXT_POS_X;
        frame.origin.y = TIME_TEXT_POS_Y;
        frame.size.h   = TIME_TEXT_SIZE_H;
        frame.size.w   = TIME_TEXT_SIZE_W;

        memset(text_buf, 0, sizeof(text_buf));
        sprintf(text_buf, "%02d:%02d", t.hour, t.min);

        add_text_layer(h_window, &g_layer_id_time, (char*)text_buf, &frame, GAlignLeft, U_ASCII_ARIAL_14, GColorWhite);

        app_window_update(h_window);
    }
}

static void data_timer_callback(date_time_t tick_time, uint32_t millis, void *context)
{
    data_request_web();
}

int main()
{
    //simulator_init();
    /*创建消息列表窗口*/
    h_window = init_btc_window(); 

    //订阅时间改变事件
    maibu_service_sys_event_subscribe(watch_time_change_callback);
    
    /*放入窗口栈显示*/
    g_window_id = app_window_stack_push(h_window);

    data_request_web();

    /*注册通讯结果回调*/
    maibu_comm_register_result_callback(data_comm_result_callback);

    //注册网络请求回调函数
    maibu_comm_register_web_callback(web_recv_callback);

    //每隔10s更新数据
    app_window_timer_subscribe(h_window, 10000, data_timer_callback, (void *)h_window);
    //simulator_wait();
    return 0;

}

