### 元气打腿版 0.0.3 更新公告 Power Violence Edition 0.0.3 annoucement


概念定义 Concept Definition:
1. 出错(*Using the Wrong Skills, **abbr. UWS***):
* 有下列两种情况之一的, 视作出错。
1. 使用规则未规定的技能(Using undefined skills)。
2. 使用未满足使用条件的技能(Using skills that do not meet the usage conditions)。
* 出错应当视为当回合什么也没出, 且放弃游戏。
2. 什么也没出(*Not Using Skills, **abbr. NUS***):
* 其应当被视为0号技能(zeroth skill, $0^{th}$ skill)。该技能属于其他技能。该技能不能被主动使用。
3. 地板(*floor*):
* 其应当被视为0号玩家(zeroth player, $0^{th}$ player)。
4. 指向性技能(*Restricted Skill, **abbr. RS***):
* 其具有指向性, 指向的对象必须为玩家, 必须指向2个对象。
* 有些指向性技能的其中一个指向对象必须为地板。这类技能被称为单指向性技能(Single Restricted Skill, **abbr. SRS**), 否则为双指向性技能(Dual Restricted Skill, **abbr. DRS**)。
* 若两个对象都是地板, 则称**对地**(towards the ground, **abbr. TG**)。
* 若其中一个对象为地板, 可以称其单独指向另一个玩家(若该技能为**SRS**, 则可称其指向该玩家)。
* 若两个对象相同, 可以称其全部指向这个玩家。
* 若其中一个对象为地板, 另一个对象为自己, 可以称其单独对自己(若该技能为**SRS**, 则可称其对自己)。
* 若两个对象相同且都为自己, 可以称其完全对自己。
5. 非指向性技能(*Non-restricted Skill, **abbr. NS***):
* 不具有指向性, 即指向两个地板。
---
技能简称 Skill Abbreviation:
| Serial Number | English name     | Abbreviation | Chinese name |
|--------------:|:----------------:|:------------:|:------------:|
| 0             | not using skills | NUS          | 什么也没出     |
| 1             | break one's leg  | BOG          | 打断双腿      |
| 2             | power            | P            | 元气         |
---
概念简称 Concept Abbreviation:
1. 攻击技能: **AS**
2. 增加元气技能: **INS**
3. 防御技能: **DS**
4. 其他技能: **OS**
5. 初始状态: **IS**
* 简称应当大写, 最好加粗或添加下划线。
---
技能属性 Skill Attributes:
| Serial Number | Abbreviation | Attributes  |
|--------------:|:------------:|:-----------:|
| 0             | NUS          | NS, OS      |
| 1             | BOG          | SRS, AS     |
| 2             | P            | NS, INS     |
---
打腿版函数 Functions:
1. $\max(...)$:
* 表示在很多数中取最大值。先比较实数部分, 再比较虚数部分。
* 即: $如果\exists r\in\Complex, \forall a_i(i=1, 2, ..., n)\in\Complex, \Re(a_i)\leq\Re(r), 且\forall a_i(i=1, 2, ..., n, \Re(a_i)=\Re(r)), \Im(a_i)\leq\Im(r), 且\exists a_i = r, 则max(a_1, a_2, ..., a_n) = r$。
2. $\min(...)$:
* 表示在很多数中取最小值。先比较实数部分, 再比较虚数部分。
---
打腿版一人信息储存方式 Storage Method:
<table border="2">
<tr>
<th colspan="2">元气数(32B)</th>
<th colspan="1">命数(16B)</th>
<th colspan="1">命数上限(16B)</th>
</tr>
<tr>
<th colspan="1">召唤物状态(16B)</th>
<th colspan="1">召唤物一位(16B)</th>
<th colspan="1">召唤物二位(16B)</th>
<th colspan="1">召唤物三位(16B)</th>
</tr>
<tr>
<th colspan="1">召唤物四位(16B)</th>
<th colspan="1">召唤物五位(16B)</th>
<th colspan="2">指向性状态(32B)</th>
</tr>
<tr>
<th colspan="4">编号(1B) + 非指向性状态(63B)</th>
</tr>
</table>

---
其他规定 Other Rules:
1. 玩家数 $\in\N^*$
2. 技能数 $\in\N^*$
3. 名称字节数 $\in\N^*$
4. 状态数 $\in\N$
---
| 6        | 31       | result   |
|:--------:|:--------:|:--------:|
| Approved | Approved | approved |
---
$$
2025年11月24日
Nov. 24^{th}, 2025
$$
