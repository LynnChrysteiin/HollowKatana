# HollowKatana
一个 PVE 游戏的 Demo， 游戏中有一个完整的场景，玩家可以操作武士零与黄蜂女进行对抗。
- 此游戏完全使用 <b>C++</b> 语言实现，使用 <b>[EasyX](https://easyx.cn/)</b> 进行渲染。
- [EasyX](https://easyx.cn/) 基于 <b>Windows</b> 平台，提供了简单易用的 2D 图形和音频支持，适合于快速开发小型游戏项目。
- 使用<b>面向对象编程（OOP）</b>来设计角色、场景和道具类，便于维护和扩展。
- 通过<b>接口与实现分离</b>的设计，确保功能定义与具体实现解耦，增强了项目的灵活性和可维护性。
- 游戏实现了简单的物理引擎，用于处理角色的移动、跳跃和攻击受击、碰撞检测。
- 设计了<b>单例模式（Singleton Pattern）</b>的工厂方法来实现角色对象和动画图集、音频等资源的管理。
- 设计了子弹时间的逻辑以及后处理效果，使得游戏中时间流速逐渐放缓同时画面慢慢黯淡。
- 使用<b>有限状态机（LSM）</b>设计了 玩家的状态切换和 AI 敌人黄蜂女的行为逻辑，并且敌人在生命值过低时具有不同的行为。

> ### 玩家状态机节点 [```player_state_nodes.h```](player_state_nodes.h) | [```player_state_nodes.cpp```](player_state_nodes.cpp)
> ![image](https://github.com/user-attachments/assets/ed94e717-391a-4682-9177-a7895bd97f80)

> ### 敌人状态机节点 [```enemy_state_nodes.h```](enemy_state_nodes.h) | [```enemy_state_nodes.cpp```](enemy_state_nodes.cpp)
> ![image](https://github.com/user-attachments/assets/32d6d0bb-4e46-44c6-9855-1f1f74922c7a)

---
LynnChrysteiin | Sept 15, 2024

致谢与参考：[Voidmatrix](https://github.com/VoidmatrixHeathcliff)
