# -*- coding:UTF-8 -*-
import numpy as np
import matplotlib.pyplot as plt

plt.figure(1);
x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
     32, 33, 34, 35, 36]
y1 = [94, 92, 99, 96, 96, 93, 94, 100, 97, 100, 101, 99, 92, 95, 93, 99, 95, 94, 99, 98, 101, 105, 98, 93, 95, 93, 102,
      99, 100, 102, 92, 93, 100, 101, 102, 101]
y2 = [94, 87, 103, 96, 101, 94, 86, 91, 79, 95, 104, 94, 94, 90, 98, 98, 96, 97, 94, 85, 93, 99, 93, 96, 96, 90, 97, 96,
      97, 100, 99, 78, 94, 93, 102, 93]
y3 = [53, 54, 51, 47, 49, 48, 45, 52, 43, 44, 48, 47, 51, 55, 46, 50, 50, 50, 47, 46, 49, 47, 44, 51, 47, 50, 49, 50,
      52, 52, 50, 44, 48, 46, 48, 49]

line1 = plt.plot(x, y1, label='tepin', color='blue', linewidth=0.2, marker='4', mew=3, linestyle='--');
line2 = plt.plot(x, y2, label='wdpin', color='red', linewidth=1.0, marker='4', mew=3);
line3 = plt.plot(x, y3, label='hello', color='green', linewidth=1.0, marker='4', mew=3);

plt.xlabel('overlapping score')
plt.ylabel('num of mkc')
plt.axis([1, 36, 0, 110]) # 坐标刻度范围
plt.xticks(range(1, 37, 4))  # x字 min,max+1,间隔
plt.yticks(range(0, 111, 10))  # y坐标数字 min,max+1,间隔
plt.title('match')
plt.grid(True)
plt.legend(loc='lower right', frameon=True)  # 图例
plt.text(10, 34, "text")  # 在x,y处放置文本text
plt.annotate('local max', xy=(2, 10), xytext=(20, 50),  # 箭头注释
             arrowprops=dict(facecolor='black', shrink=0.2),
             )
plt.show();

plt.figure(2);
plt.subplot(311)
line1 = plt.plot(x, y1, label='tepin', color='blue', linewidth=0.2, marker='4', mew=3, linestyle='--')
plt.xlabel('overlapping score')
plt.ylabel('num of mkc')
plt.axis([1, 36, 0, 110])  # 坐标刻度范围
plt.xticks(range(1, 37, 4)) # x字 min,max+1,间隔
plt.yticks(range(0, 111, 10))  # y坐标数字 min,max+1,间隔
plt.title('match')
plt.grid(True)
plt.legend(loc='lower right', frameon=True)  # 图例
# plt.text(10,34,"text"); # 在x,y处放置文本text

plt.subplot(312)
line2 = plt.plot(x, y2, label='wdpin', color='red', linewidth=1.0, marker='4', mew=3);
plt.xlabel('overlapping score');
plt.ylabel('num of mkc');
plt.axis([1, 36, 0, 110]);  # 坐标刻度范围
plt.xticks(range(1, 37, 4));  # x字 min,max+1,间隔
plt.yticks(range(0, 111, 10));  # y坐标数字 min,max+1,间隔
plt.title('match');
plt.grid(True);
plt.legend(loc='lower right', frameon=True)  # 图例
# plt.text(10,34,"text"); # 在x,y处放置文本text

plt.subplot(313)
line3 = plt.plot(x, y3, label='hello', color='green', linewidth=1.0, marker='4', mew=3);
plt.xlabel('overlapping score');
plt.ylabel('num of mkc');
plt.axis([1, 36, 0, 110]);  # 坐标刻度范围
plt.xticks(range(1, 37, 4));  # x字 min,max+1,间隔
plt.yticks(range(0, 111, 10));  # y坐标数字 min,max+1,间隔
plt.title('match');
plt.grid(True);
plt.legend(loc='lower right', frameon=True)  # 图例
plt.text(10, 74, "texthae");  # 在x,y处放置文本text
plt.annotate("",
             xy=(5, 12), xycoords='data',
             xytext=(20, 90), textcoords='data',
             arrowprops=dict(arrowstyle="->",
                             connectionstyle="arc3"),
             )

plt.show();

"""
linestyle or ls  
	[ ’-’ | ’--’ | ’-.’ | ’:’ | ’steps’ | ...]  连接点的线条样式
marker
	[ ’+’ | ’,’ | ’.’ | ’1’ | ’2’ | ’3’ | ’4’ ]  点的样式
others that control the line style or marker:
	'.'	point marker
	','	pixel marker
	'o'	circle marker
	'v'	triangle_down marker
	'^'	triangle_up marker
	'<'	triangle_left marker
	'>'	triangle_right marker
	'1'	tri_down marker
	'2'	tri_up marker
	'3'	tri_left marker
	'4'	tri_right marker
	's'	square marker
	'p'	pentagon marker
	'*'	star marker
	'h'	hexagon1 marker
	'H'	hexagon2 marker
	'+'	plus marker
	'x'	x marker
	'D'	diamond marker
	'd'	thin_diamond marker
	'|'	vline marker
	'_'	hline marker
markeredgecolor or mec
	any matplotlib color
markeredgewidth or mew
	float value in points
markerfacecolor or mfc
	any matplotlib color
markersize or ms
	float
locations are  图例位置
	center left
	center right
	upper center
	upper left
	lower center
	right
	upper right
	lower left
	lower right
	best
	center 
character   color
	‘b’	blue
	‘g’	green
	‘r’	red
	‘c’	cyan
	‘m’	magenta
	‘y’	yellow
	‘k’	black
	‘w’	white
	...
"""
