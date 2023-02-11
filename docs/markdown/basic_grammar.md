本文主要介绍Markdown中的基本语法。

## 1.Markdown标题

几级标题对应几个 `#`，共六级标题。

```
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
```

![title](photos\title.png)

## 2.Markdown文本

+ 斜体文本：可以在需要标注为斜体文本前及斜体文本结尾，输入一个星号`*`或者一个下划线 `_` ；
+ 粗体文本：可以在需要标注为粗体文本前及粗体文本结尾，输入两个星号 `**` 或者两个下划线  `__`；
+ 粗斜体文本：可以在需要标注为粗斜体文本前及粗斜体文本结尾，输入三个星号 `***` 或者三个下划线 `___`；
+ 高亮文本：可以在需要标注为高亮文本前及高亮文本结尾，输入两个 等号` ==`；

```
*斜体文本*
_斜体文本_

**粗体文本**
__粗体文本__

***粗斜体文本***
___粗斜体文本___

==高亮文本==
```

![text](photos\text.png)

## 3.Markdown列表

+ 有序列表：使用星号(`*`)、加号(`+`)或是减号(`-`)

+ 有序列表：用数字加上`.`

  ```
  * 无序列表1
  + 无序列表2
  - 无序列表3
  
  1. 有序列表1
  2. 有序列表2
  3. 有序列表3
  ```

  ![list](photos\list.png)

  

可以使用缩进控制列表层级

  ```
  * 无序列表1
  	* 无序列表1.1
  * 无序列标2
  	* 无序列表2.1
  ```

  ![level_list](photos\level_list.png)

在`-`后加上`[]`或`[x]`表示完成或未完成的列表。

```
- [ ] a task list item
- [ ] list syntax required
- [ ] normal **formatting**, @mentions, #1234 refs
- [ ] incomplete
- [x] completed
```

- [ ] a task list item
- [ ] list syntax required
- [ ] normal **formatting**, @mentions, #1234 refs
- [ ] incomplete
- [x] completed

## 4.Markdown表格

+ 使用 `|`分割不同的单元格

+ 使用 `-`分割表头和其他行

+ 对齐方式：

    + `:-` :内容左对齐

    + `-:` :内容右对齐

    + `:-:` :内容居中对齐
```
|学号|总分|排名|
|:---|:---:|---:|
|0101|100|1|
|0102|99|3|
|0103|98|10|
```

|学号|总分|排名|
|:---|:---:|---:|
|0101|100|1|
|0102|99|3|
|0103|98|10|

## 5.Markdown链接

```
[链接名字](链接地址) #将文本设为超链接

<链接地址> #将链接直接设为超链接
```

[my wiki](https://camlthx.github.io)

<https://camlthx.github.io>

## 6.Markdwon图片

```
![图片名字](图片链接)
```

图片链接可以使用本地图片或者url链接都可以

## 7.Markdown代码块

使用` ``` `引用起来，可以选择语言。

```
​```cpp(这里可以选择语言)

​```

或

​```

​```
```

也可以在行内使用`` `引用代码 。



## 8.Markdown引用

在 `>` 后写文字即可。也可以用多个 `>` 进行嵌套

```
> 引用1
> 引用2
> 引用3

> 引用1
>> 引用2
>>> 引用3
```

> 引用1
> 引用2
> 引用3

> 引用1
> > 引用2
> >
> > > 引用3

## 9.Markdown分割线

~~不排斥你用一些奇奇怪怪的分割线~~

可以用三个 `_` 或者 `*`来建立一个分割线

```
---

***
```

## 10.Markdown删除线

用 `~~`引用文字即可

```
~~被删除的文本~~
```

~~被删除的文本~~

## 11.Markdown下划线

用 `<u>` 和 `</u>` 引用文字

```
<u>下划线</u>
```

<u>下划线</u>

## 12.Markdown脚注

```
You can create footnotes like this[^footnote].

[^footnote]: Here is the *text* of the **footnote**.
```

的效果：

You can create footnotes like this[^footnote].

[^footnote]: Here is the *text* of the **footnote**.

## 13.Markdown Emojis

使用一下语法召唤emojis

```markdown
:name:
```

