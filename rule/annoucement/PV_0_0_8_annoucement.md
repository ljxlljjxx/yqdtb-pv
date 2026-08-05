### 元气打腿版 0.0.8 更新公告 Power Violence Edition 0.0.8 annoucement

概念修改:
1. 攻击技能:
   可以对初始状态下的出元气者<span style="border-bottom: 3px double;">或出**NUS**</span>者造成伤害的技能。
2. <span style="border-bottom: 3px double;">**RS**,**NS**</span>:
   > 这里讲的除特殊说明外, 均为底层实现。
   * 定义:
     + 第一指向对象(the $1^{st}$ target)
     + 第二指向对象(the $2^{nd}$ target)
     + 第三指向对象(the $3^{rd}$ target)
     + 第四指向对象(the $4^{th}$ target)
     + 第五指向对象(the $5^{th}$ target)
     + 第六指向对象(the $6^{th}$ target)
     + 第七指向对象(the $7^{th}$ target)
     + 第八指向对象(the $8^{th}$ target)
     + 第九指向对象(the $9^{th}$ target)
     + 第十指向对象(the $10^{th}$ target)
     + 第十一指向对象(the $11^{th}$ target)
     + 第十二指向对象(the $12^{th}$ target)
     + 第十三指向对象(the $13^{th}$ target)
     + 第十四指向对象(the $14^{th}$ target)
     + 第十五指向对象(the $15^{th}$ target)
     + 第十六指向对象(the $16^{th}$ target)
     + 第十七指向对象(the $17^{th}$ target)
     + 第十八指向对象(the $18^{th}$ target)
     + 第十九指向对象(the $19^{th}$ target)
     + 第二十指向对象(the $20^{th}$ target)
     + 第二十一指向对象(the $21^{st}$ target)
     + 第二十二指向对象(the $22^{nd}$ target)
     + 第二十三指向对象(the $23^{rd}$ target)
     + 第二十四指向对象(the $24^{th}$ target)
     + 第二十五指向对象(the $25^{th}$ target)
     + 第二十六指向对象(the $26^{th}$ target)
     + 第二十七指向对象(the $27^{th}$ target)
     + 第二十八指向对象(the $28^{th}$ target)
     + 第二十九指向对象(the $29^{th}$ target)
     + 第三十指向对象(the $30^{th}$ target)
   * 技能种类:
      1. 非指向性技能(*Non-restricted Skill, **abbr. NS***):
         + 其第一指向对象~第三十指向对象必须为0(floor)。
         + 对于**NS**来说, 不可说指向某一玩家。表面上看, 该类型技能没有指向对象。
      2. 单指向性技能(*Single Restricted Skill, **abbr. SRS***):
         + 其第二指向对象~第三十指向对象必须为0(floor); 其第一指向对象可为0也可不为。
         + 对于**SRS**来说, 指向某一玩家取决于第一指向对象。表面上看, 该类型技能只有一个指向对象。
      3. 第二指向对象(*Dual Restricted Skill, **abbr. DRS***):
         + 其第三指向对象~第三十指向对象必须为0; 其第一指向对象、第二指向对象可为0也可不为。
         + 对于**DRS**来说, 指向某一或二位玩家取决于第一指向对象和第二指向对象。表面上看, 该类型技能只有两个指向对象。
      4. 第三指向对象(*Triple Restricted Skill, **abbr. TRS***):
         + 其第四指向对象~第三十指向对象必须为0; 其第一指向对象~第三指向对象可为0也可不为。
         + 对于**TRS**来说, 指向某一或二或三位玩家取决于第一指向对象、第二指向对象和第三指向对象。表面上看, 该类型技能只有三个指向对象。
      5. 四指向性技能(*Quadruple Restricted Skill, **abbr. QRS***):
         + 其第五指向对象~第三十指向对象必须为0; 其第一指向对象~第四指向对象可为0也可不为。
         + 对于**QRS**来说, 指向某一或二或三或四位玩家取决于第一指向对象、第二指向对象、第三指向对象和第四指向对象。表面上看, 该类型技能只有四个指向对象。
      6. 更多指向性技能:
         + 对于n指向性技能($n \in\lbrace 1,2,3,...,30\rbrace$), 其第m指向对象($n<m\leq 30,m\in\Z$)必须为0; 其第k指向对象($0<k\leq n, k\in\Z$)可为0也可不为。
         + 对于n指向性技能($n \in\lbrace 1,2,3,...,30\rbrace$)来说, 指向某m($0\leq m\leq n, m\in\Z$)位玩家取决于前m个指向对象。表面上看, 该类型技能只有n个指向对象。
3. 技能修改:
   1. 每个技能有编号(Serial Number)、名称(Name)、动作(Movement)、条件(Precondition)、效果(Effect)、性质(Type)。
   2. 编号必须为$(0,2^{13})$中的自然数。
   3. 名称有4个: 英文名(English name), 缩写(Abbreviation), 中文名(Chinese name), 别称(Alias)。每个小于128字节。
   4. 动作有2个, 分别为中文动作及英文翻译。每个小于2048字节(2 KiB)。
   5. 条件暂不规定形式, 但总字节数不得超过1024(1 KiB)。
   6. 效果有2个, 分别为中文动作及英文翻译。每个小于5120字节(5 KiB)。
   7. 性质暂不规定形式, 但总字节数不得超过128。
   8. 每位玩家一回合只能主动使用一个技能。
4. 储存方式修改:
   1. <span style="border-bottom: 3px double;">每位玩家每回合有1KiB空间储存信息。打腿版不保存256回合及之前的玩家信息。</span>打腿版的出错判定不能依靠256回合及之前的状态或技能等。
   2. 回合数默认会小于最多玩家数的平方, 即$回合数<(2^8)^2=65535$。
   3. 玩家一回合的信息分为以下四个板块进行储存:
      * 玩家基础信息(player): 256B。
      * 召唤物信息(scapegoat): 256B。
      * 状态(state): 480B。
      * 使用技能(skill): 32B。
---
| 6        | 31       | result   |
|:--------:|:--------:|:--------:|
| Approved | Approved | approved |
---
$$
2025年12月26日
Dec. 26^{th}, 2025
$$
