# -*- coding:UTF-8 -*-
import numpy as np
import matplotlib.pyplot as plt

x=np.arange(0.2,1.1,0.1)
mcl_tepin= [47.5070555,27.18720602,18.53245532,12.13546566,8.278457197,2.822201317,2.069614299,1.69332079,1.69332079]
mcl_dpin = [37.06491063,21.44873001,15.05174036,9.783631232,5.45625588,2.257761054,1.599247413,1.128880527,1.128880527]
mcl_spin = [31.88,19.9,15.05,10.16,5.83,2.35,1.975,1.88,1.88]
mcl_wspin=[41.20413923,27.2812794,21.44873001,16.9332079,12.69990593,7.996237065,5.832549389,5.174035748,5.079962371]
mcl_wdpin=[40.0752587,26.15239887,18.81467545,13.07619944,8.466603951,3.762935089,2.634054563,2.257761054,2.257761054]
mcl_wtepin=[53.43367827,33.39604892,22.2953904,15.14581373,10.81843838,4.703668862,3.668861712,3.010348071,3.010348071]

camse_spin=[38.94637817,23.23612418,14.39322672,8.560677328,4.703668862,1.599247413,0.376293509,0.094073377,0]
camse_tepin=[49.48259643,25.68203198,17.40357479,10.63029163,6.773283161,2.634054563,1.975540922,1.505174036,1.505174036]
camse_dpin=[41.20413923,22.67168391,16.83913452,11.94731891,7.431796802,3.668861712,2.539981185,1.787394167,1.787394167]
camse_wspin=[45.81373471,30.29162747,22.48353716,16.36876764,8.560677328,3.668861712,1.975540922,1.03480715,1.03480715]
camse_wdpin=[42.23894638,26.434619,17.96801505,13.17027281,6.867356538,3.480714958,2.539981185,1.975540922,1.975540922]
camse_wtepin=[60.86547507,36.12417686,24.64722484,16.46284102,9.219190969,3.951081844,2.916274694,2.634054563,2.634054563]

clusterone_spin=[24.17685795,	16.46284102,	12.32361242,	7.80809031,	5.079962371,	2.445907808,	1.69332079,	1.411100659,	1.411100659]
clusterone_dpin=[37.72342427,	23.61241769,	17.21542803,	11.66509878,	7.996237065,	2.72812794,	1.505174036,	1.03480715,	1.03480715]
clusterone_tepin=[48.73000941,	28.59830668,	20.50799624,	13.82878645,	9.125117592,	3.38664158,	1.975540922,	1.69332079,	1.69332079]



plt.figure(1)
line1 = plt.plot(x, mcl_tepin, label='MCL_TEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, mcl_dpin, label='MCL_DPIN', color='blue', linewidth=1.5, marker='v', mew=2,mec='blue');
line3 = plt.plot(x, mcl_spin, label='MCL_SPIN', color='green', linewidth=1.5, marker='>', mew=2,mec='green');

plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 50]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 50,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();
"""

plt.figure(2)
line1 = plt.plot(x, camse_tepin, label='CAMSE_TEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, camse_dpin, label='CAMSE_DPIN', color='blue', linewidth=1.5, marker='v', mew=2,mec='blue');
line3 = plt.plot(x, camse_spin, label='CAMSE_SPIN', color='green', linewidth=1.5, marker='>', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 55]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 55,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();


plt.figure(3)
line1 = plt.plot(x, clusterone_tepin, label='ClusterONE_TEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, clusterone_dpin, label='ClusterONE_DPIN', color='blue', linewidth=1.5, marker='v', mew=2,mec='blue');
line3 = plt.plot(x, clusterone_spin, label='ClusterONE_SPIN', color='green', linewidth=1.5, marker='>', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 55]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 55,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();
"""

plt.figure(4)
line1 = plt.plot(x, mcl_wtepin, label='MCL_WTEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, mcl_wdpin, label='MCL_WDPIN', color='blue', linewidth=1.5, marker='v', mew=2,mec='blue');
line3 = plt.plot(x, mcl_wspin, label='MCL_WSPIN', color='green', linewidth=1.5, marker='>', mew=2,mec='green');

plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 55]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 55,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();
"""
plt.figure(5)
line1 = plt.plot(x, camse_wtepin, label='CAMSE_WTEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, camse_wdpin, label='CAMSE_WDPIN', color='blue', linewidth=1.5, marker='v', mew=2,mec='blue');
line3 = plt.plot(x, camse_wspin, label='CAMSE_WSPIN', color='green', linewidth=1.5, marker='>', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 65]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 65,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();
"""

plt.figure(6)
line1 = plt.plot(x, mcl_wtepin, label='MCL_WTEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, mcl_tepin, label='MCL_TEPIN', color='green', linewidth=1.5, marker='v', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 55]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 55,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();

plt.figure(7)
line1 = plt.plot(x, mcl_wdpin, label='MCL_WDPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, mcl_dpin, label='MCL_DPIN',color='green', linewidth=1.5, marker='v', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 45]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 45,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();

plt.figure(8)
line3 = plt.plot(x, mcl_wspin, label='MCL_WSPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line4 = plt.plot(x, mcl_spin, label='MCL_SPIN', color='green', linewidth=1.5, marker='v', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 45]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 45,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();

plt.figure(9)
line1 = plt.plot(x, camse_wtepin, label='CAMSE_WTEPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, camse_tepin, label='CAMSE_TEPIN', color='green', linewidth=1.5, marker='v', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 65]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 65,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();

plt.figure(10)
line1 = plt.plot(x, camse_wdpin, label='CAMSE_WDPIN',color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line2 = plt.plot(x, camse_dpin, label='CAMSE_DPIN', color='green', linewidth=1.5, marker='v', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 45]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 45,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
plt.show();

plt.figure(11)
line1 = plt.plot(x, camse_wspin, label='CAMSE_WSPIN', color='red', linewidth=1.5, marker='o', mew=2,mec='red');
line3 = plt.plot(x, camse_spin, label='CAMSE_SPIN', color='green', linewidth=1.5, marker='v', mew=2,mec='green');
plt.xlabel('Overlapping score threshold')
plt.ylabel('Percent of MKC')
plt.axis([0.2, 1.0, 0, 50]) # 坐标刻度范围
plt.xticks(np.arange(0.2, 1.1, 0.1))  # x字 min,max+1,间隔
plt.yticks(range(0, 50,5))  # y坐标数字 min,max+1,间隔
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例
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
