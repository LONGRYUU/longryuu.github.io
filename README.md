# 机器学习笔记
this is created for marking down some notes during study

## 算法

### 梯度下降
1、h(假设)：输出函数，即通过训练得到的一个函数结果。可以接收输入，获得输出。 

2、批量梯度下降（递归），随机梯度下降（循环）。

### 局部加权线性回归
1、对每个点进行拟合时，对其附近的点赋予高的权值，较远的点赋予低的权值。每一个点需要对所有数据拟合一次，开销较大。


## 概念

属性——特征，示例——样本——特征向量。

属性空间/样本空间/输入空间：属性张成的空间，在该空间内可以取得所有样本的值，换言之，每个样本对应该空间中的一个点，维度为属性的个数。

假设空间：所有假设的集合，即可能的模型或者学习结果的集合，（针对西瓜问题）可以表现为对属性取不同值进行搭配的集合。

版本空间：针对具体训练集的假设集合，这里的假设即根据训练集可以得到预期结果的模型，是假设空间的子集。

标记：关于示例的结果的信息（可以理解为样本处理的结果），被标记的示例成为样例，所有标记的集合称为标记空间或输出空间。

假设：从数据中会获得一个模型，模型对应了某种规律，这就是假设，规律本身称作真相或者真实。

分类：结果是离散的。 回归：结果是连续的。

泛化：模型适用于新样本的能力。

精度=1-错误率。 错误率=错误样本数/总样本数。

查准率=TP/(TP+FP),查全率=TP/(TP+FN)。

F1度量=2*P*R/（P+R），其拥有更为一般的形式，当参数β大于1，使查全率更重要；当其小于1，使查准率更重要。

P-R图与ROC图。

ROC相关：真正例率TPR=TP/(TP+FN)，假正例率FPR=FP/(TN+FP)

损失与AUC：设损失为l，则AUC=1-l,其中AUC为ROC曲线下面积，l即为ROC曲线上的面积

非均等代价：为不同错误赋予不同的代价（cost）。

代价敏感错误率：在错误率的基础上，给不同错误发生的次数乘以代价权值。

## 模型评估

留出法：直接将数据集划分为两个互斥的集合。

交叉验证法：将数据集划分为k个互斥子集，每次选择k-1个作为训练集，余下的作为测试集，进行k次训练和测试，取平均结果

自助法：每次从含有m个样本的数据集中拷贝一个样本，重复m次，得到一个训练集将（依概率来看）包含约2/3的样本，剩余样本作为测试集。一半用于数据集较小时，数据充足时一般使用前两种办法。
