# Lvgl 模拟器（基于SDL2）

## 依赖库

### SDL2
Windows:  
本仓库内置 Windows 平台的SDL2库，直接使用 cmake 编译即可

Linux:  
需要安装 SDL2，以下是不同发行版的安装方法：
- Ubuntu/Debian:  
    ```
    sudo apt install libsdl2-dev
    ```

- Red Hat-based systems (including Fedora)
    ```
    sudo dnf install SDL2-devel
    ```

- Gentoo
    ```
    sudo emerge libsdl2
    ```
其他系统或编译安装请看[Installing SDL](https://wiki.libsdl.org/SDL2/Installation)
