# S2客户端插件

Actions Workflow Visual Studio 2022环境中对中文函数处理相对严格，导致编译不通过；暂时未找到好的解决办法，临时处理重命名中文函数。

### 插件使用

```shell
# 客户端插件
# (客户端插件关闭绑定IP fixIp())
# 客户端加载Fd.dll

# 服务端插件
# 插件上传
# libfd_monitor.so -> /home/neople/monitor
# libfd.so -> /home/neople/game

# run文件修改

# 服务器名称
SERVER_NAME="siroco"

# ...
# df_monitor_r
LD_PRELOAD="./libfd_monitor.so" ./df_monitor_r mnt_${SERVER_NAME} start &

# ...
# df_game_r
LD_PRELOAD="./libfd.so" ./df_game_r "${SERVER_NAME}11" start &

```

### 其他资源

- [Cloudflare](https://developers.cloudflare.com/warp-client/get-started/windows/)
- [Visual Studio 2022](https://visualstudio.microsoft.com/zh-hans/downloads/)
