#pragma once

#include <string>
#include "lvgl.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "lvgl_app_global_types.hpp"

class LvglApp
{
public:
    enum class Type {
        Normal,
        NoGUI,     // 暂不支持
        FullScreen // 暂不支持
    };

    enum class RunState {
        Run,
        WaitingForStop,
        Stop
    };

    struct AppProperty {
        std::string name; // 应用的名字
        const Type type;
        lv_obj_t *main_page;
        void *argument;
    };

private:
    AppProperty app;
    const uint16_t _stack_depth; // 栈大小，单位：word (4 bytes)
    const uint16_t _priority;    // FreeRTOS 优先级，正常优先级是3，值越高优先级越高。范围：[0, configMAX_PRIORITIES]
    RunState _run_state;
    SemaphoreHandle_t _sem;

    void MutexLock()
    {
        xSemaphoreTakeRecursive(_sem, portMAX_DELAY);
    }

    void MutexUnlock()
    {
        xSemaphoreGiveRecursive(_sem);
    }

public:
    /**
     * @brief 判断程序的运行状态，如果返回 false，需要尽快结束线程
     * @note 类似于 ros::ok()
     *
     * @return true 程序正常运行，返回true
     * @return false 程序被外部关闭，则返回 false
     */
    bool ok()
    {
        MutexLock();
        auto state = _run_state;
        MutexUnlock();

        switch (state) {
        case RunState::Run:
            return true;
            break;

        default:
            return false;
            break;
        }
    }

    virtual int Run()
    {
        return 0;
    }

    virtual int OnLaunch()
    {
        return 0;
    }

    virtual int OnExit()
    {
        return 0;
    }

    virtual int OnSwitchToBackground()
    {
        return 0;
    }

    virtual int OnSwitchToForeground()
    {
        return 0;
    }

    virtual int Init()
    {
        return 0;
    }

    LvglApp(std::string app_name = "Untitled",
            Type app_type        = Type::Normal,
            void *argument       = nullptr,
            uint16_t stack_depth = 512,
            uint16_t priority    = 3)
        : app{app_name, app_type, nullptr, argument}, _stack_depth(stack_depth), _priority(priority)
    {
        _sem = xSemaphoreCreateRecursiveMutex();
    }

    ~LvglApp()
    {
        vSemaphoreDelete(_sem);
    }

    uint16_t GetStackDepth() const
    {
        return _stack_depth;
    }

    uint16_t GetPriority() const
    {
        return _priority;
    }

    AppProperty App()
    {
        MutexLock();
        auto result = app;
        MutexUnlock();
        return result;
    }

    void SetAppMainPage(lv_obj_t *main_page)
    {
        MutexLock();
        app.main_page = main_page;
        MutexUnlock();
    }

    void SetAppArgument(void *argument)
    {
        MutexLock();
        app.argument = argument;
        MutexUnlock();
    }

    void SetAppName(std::string name)
    {
        MutexLock();
        app.name = name;
        MutexUnlock();
    }
};
