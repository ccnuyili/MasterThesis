# -*- coding:UTF-8 -*-
import numpy as np
import matplotlib.pyplot as plt

y=[2,	97,	677,743,1017,1110,746,395,156,	28,	10]
x=np.arange(1,12,1)
width=0.9
plt.bar(x,y,width,color='g',alpha=0.6,align='center')
plt.xticks(range(1, 12,1))
plt.axis([0, 12, 0, 1200]);  # 坐标刻度范围
plt.grid(True)
plt.xlabel('Number of active time points')
plt.ylabel('Number of proteins')
for x1,y1 in zip(x,y):
    plt.text(x1, y1-0.08, '%d' % y1, ha='center', va= 'bottom')
# plt.text(10,34,"text"); # 在x,y处放置文本text
plt.show();




