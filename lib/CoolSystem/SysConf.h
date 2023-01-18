/**
 * @file SysConf.h
 * @author Jensentsts (jensentsts@163.com)
 * @brief 系统设置
 * @version 1.0.0
 * @date 2023-01-18
 * 
 * @copyright CC4.0 BY-NC-SA
 * 
 */

#ifndef __SysConf_h
#define __SysConf_h

// WIDTH & HEIGHT 的定义在 hardware.h 末尾处
//////////////////////////////////////////////////////////////
// 桌面背景图 bgimg
#define BGIMG_WIDTH 240
#define BGIMG_HEIGHT 280
//////////////////////////////////////////////////////////////
// App图标设置
#define APP_ICON_WIDTH 256
#define APP_ICON_HEIGHT 256
//////////////////////////////////////////////////////////////
// 一般图标设置
#define ICON_WIDTH 200
#define ICON_HEIGHT 200
//////////////////////////////////////////////////////////////
// 无图像等效替换字符
#define NO_IMG_INFO ":("
//////////////////////////////////////////////////////////////
// Card 卡片系统设置
#define CARD_WIDTH 200
#define CARD_HEIGHT 140
#define CARD_RADIUS 12
#define CARD_BGCOLOR 0xFFFFFF           // bgcolor
#define CARD_TITLE_X_OFFSET 6           // 标题整体偏移量
#define CARD_TITLE_Y_OFFSET 6
#define CARD_TITLE_WIDTH (CARD_WIDTH - CARD_TITLE_X_OFFSET * 2)
#define CARD_TITLE_HEIGHT 12
#define CARD_TITLE_ITEMS_PADDING 6      // 标题容器内部对象之间的间隔
//////////////////////////////////////////////////////////////

#endif // __SysConf_h
