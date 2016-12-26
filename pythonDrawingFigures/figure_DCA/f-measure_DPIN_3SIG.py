# -*- coding:UTF-8 -*-
import numpy as np
import matplotlib.pyplot as plt

sn=[0.690349,
0.37,
0.598712,
0.86798,
0.805714,
0.906815,
0.526427,

0.355072,
0.783784,
0.644643,

]

sp=[0.581921,
0.51,
0.330961,
0.362104,
0.333728,
0.222147,
0.468927,

0.475728,
0.263763,
0.401557,
]

f=[0.631514,
0.43,
0.42628,
0.511021,
0.471967,
0.356869,
0.496016,

0.406639,
0.394699,
0.494859,


]


sn_sp=[1.27227,
0.88,
0.929673,
1.230084,
1.139442,
1.128962,
0.995354,

0.8308,
1.047547,
1.0462,


]


plt.figure(1);
N=10
ind=np.arange(1,N+1,1)
width=0.9
plt.bar(ind,sn,width,color='g',label='Sn',alpha=0.8,align='center')
plt.bar(ind,sp,width,color='y',bottom=sn,label='Sp',alpha=0.7,align='center')
plt.bar(ind,f,width,color='r',bottom=sn_sp,label='f-measure',alpha=0.8,align='center')
plt.xticks(ind,('DCA','DPC','TS-OCD','CAMSE','ClusterONE','CoreAttach','CPM','MCODE','SPICI','COACH'), rotation=20 )
plt.title('Comparision on dynamic PPI network (DIP)')
plt.axis([0, N+1, 0, 2.0]);  # 坐标刻度范围
plt.grid(True)
plt.legend(loc='upper right', frameon=True)  # 图例

for x1,y1 in zip(ind,sn):
    plt.text(x1, y1-0.08, '%.3f' % y1, ha='center', va= 'bottom')

i=0
for x2,y2 in zip(ind,sp):
    plt.text(x2, y2-0.08+sn[i], '%.3f' % y2, ha='center', va= 'bottom')
    i+=1
i=0
for x3,y3 in zip(ind,f):
    plt.text(x3, y3-0.08+sn_sp[i], '%.3f' % y3, ha='center', va= 'bottom')
    i+=1
# plt.text(10,34,"text"); # 在x,y处放置文本text
plt.show();




