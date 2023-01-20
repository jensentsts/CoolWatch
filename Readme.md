# External Includes
- jsoncpp
- Arduino-FT6336U
- LVGL
- TFT-eSPI
Gratefully thanks for these open-source projects.
Links will be added later.

# 开发中
下面对开发过程中的一些格式规范做记录。个人容易把开发中的一些问题想复杂，然后越写越复杂，越写越超出个人能力，只好一点一点来。

# 资源格式
许多类都带有`resource`用以存储和访问资源。
`package_name`作为资源标识符，用于访问各个资源。
由Json::Value组成的基本类型，下面将以不规范的json的形式给出。

## 基本资源
基本资源不带有`package_name`。除基本资源外，所有资源都需要带有`package_name`

### Graph
```json
{
    "width" : [Int],
    "height" : [Int],
    "graph" : [uint16_t*] // 指向存储图片的const变量
}
```

### AppPackageData
```json
{
    "package_name" : [String],
    "app_title" : [String],
    "icon" : [Graph],
    "app_pointer" : [AppBase*] // 指向包所对应的App
}
```

## CoolWigets

### CoolWidget
```json
{
    "package_name" : [String]
}
```

### Card
```json
{
    "package_name" : [String],
    "app_title" : [String],
    "app_icon" : [Graph],
    "container" : [String or lv_obj_t*] // container是卡片标题下方的正文部分容器
}
```

### Desktop_AppIcon
```json
{
    "package_name" : [String],
    "app_package" : [AppPackageData]
}
```

## AppBase
同`AppPackageData`


## Interface

### Desktop
```json
{
    "package_name" : [String],
    "apps" : [ // 此数组将从 app_package_mgr 中获取
        [AppPackageData],
        [AppPackageData],
        ...
    ],
    "transfer" : { // 用于切换界面
        [lv_dir_t] : [String, package_name]
    }
}
```

## Mgr

### AppPackageMgr
```json
[
    [AppPackageData],
    [AppPackageData],
    ...
]
```

### ResourceMgr
```json
{
    "SysInfo" : {
        "Name" : [String],
        "Version" : [String]
    },
    "App" : {
        "Settings" : {
            "icon" : [Pointer]
        }
    },
    "Tasks" : {
        
    },
    "Interface" : {
        "Desktop" : {
            "background_img" : [Pointer]
        }
    },
    "Mgr" : {

    }
}
```


