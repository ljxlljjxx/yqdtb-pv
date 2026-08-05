### 元气打腿版 0.0.13 更新公告 Power Violence Edition 0.0.13 annoucement

1. 打断双腿动作:
   * 双手握实心拳,分别向指向目标的大腿中部快速反复做锤击动作。若对方没有大腿, 也可以向指向目标的其他部位快速反复做锤击动作。做该动作时, 双手手肘均不能位于肩膀上方。Make a fist with both hands and quickly repeat the hammering motion towards the middle of the target's thigh. If the opponent doesn't have a thigh, you can also perform the hammering motion towards other parts of the target quickly and repeatedly. During this action, the elbows of both hands must not be above the shoulders.
2. 伤害:
   * 伤害由以下部分组成: 造成者(1B), 受伤害者(1B), 伤害类型(2B), 伤害数值(16B), 造成伤害的技能(2B)
   * 伤害具有指向性。伤害在伤害表中存储, 在抵伤环节计算。
   * 伤害数值范围同命数范围。
3. 获胜者:
   1. 当游戏结束时, 若仍幸存1位玩家, 则该名玩家为获胜者。
   2. 当游戏结束时, 若无玩家, 视为平局, 则不存在获胜者。
   3. 若为组队制, 则场上的人均为同一条队伍的成员, 则该队全员为获胜者。
   > 以上内容不考虑地板。
4. 玩家:
   1. 表面上看, 凡参与游戏拥有编号的均可视为玩家。狭义上讲, 玩家应该为人类。
   2. 底层上把地板视为玩家, 表层上不这么看。若为标注为底层, 则默认地板不属于玩家。
5. 增加和减少:
   1. 增加指某个数值在某一时间点大于在其之前的另一时间点。
   2. 减少指某个数值在某一时间点小于在其之前的另一时间点。
6. 一个技能必须拥有编号、名称、动作、效果和性质。
7. 打腿版基本原则第1条改为:
   * 元气打腿版为纯运气游戏。即若1人对阵n人时, 无论n个人出什么技能, 必须存在至少一种方案保证**该人**在有限回合内取得胜利。PV(Power Violence Edition) is purely a game of chance. That is, when one person faces n people, regardless of the skills each person uses and the value of n, there must exist at least one solution to ensure victory **of this player** within a limited number of rounds.
8. 玩家的名字:
   1. 玩家的名字存储在名字列表中。
   2. 玩家的名字不得大于等于128字节。
   3. 玩家不可以在游戏中途改名。
   4. 玩家的名字为必须, 初始默认为该玩家编号, 且名字不可重复。名字不能是纯数字字符串, 且不能为“地板”“场景”“floor”。
   5. 玩家的名字和计算过程无关。
---
| 6        | 31       | result   |
|:--------:|:--------:|:--------:|
| Approved | Approved | approved |
---
$$
2026年1月9日
Dec. 9^{th}, 2026
$$
