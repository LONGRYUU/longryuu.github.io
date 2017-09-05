# 机器学习笔记
this is created for marking down some notes during study

# 算法

### 梯度下降
1、h(假设)：输出函数，即通过训练得到的一个函数结果。可以接收输入，获得输出。 

2、批量梯度下降（递归），随机梯度下降（循环）。

### 局部加权线性回归
1、对每个点进行拟合时，对其附近的点赋予高的权值，较远的点赋予低的权值。每一个点需要对所有数据拟合一次，开销较大。


# 概念

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

代价曲线：由多段直线构成，每一条直线对应ROC图上的一个点，曲线下的面积是期望的总体代价；线段由（0，FPR）到（1，FNR）。


# 模型评估

留出法：直接将数据集划分为两个互斥的集合。

交叉验证法：将数据集划分为k个互斥子集，每次选择k-1个作为训练集，余下的作为测试集，进行k次训练和测试，取平均结果

自助法：每次从含有m个样本的数据集中拷贝一个样本，重复m次，得到一个训练集将（依概率来看）包含约2/3的样本，剩余样本作为测试集。一半用于数据集较小时，数据充足时一般使用前两种办法。


# 线性模型

## 线性回归

求一组参数，向量w，和参数b，构成直线，使得所有样本点到直线的距离之和最短。
可以采用最小二乘法，对w和b分别求偏导，使得结果为0.

## 对数几率函数

对于处理二分类时，为了使得函数连续可微而构造的函数。

对数几率：ln[y/(1-y)],其中的y/(1-y)称为几率。

## 线性判别分析

在二分类问题上，将样例投影到一条直线，使得同类样例尽可能接近，异类样例尽可能远离。即要使得同类样例投影点的协方差尽可能小，而使得异类样例投影点的类中心距离尽可能大。

## 多分类问题的求解策略

拆解成若干个二分类问题。拆解的策略有一对一，一对其余，多对多。

一对一分类：将N个预期的分类结果两两配对得到(N-1)N/2个分类器，每次分别将样本提交给各个分类器得到分类结果，得到的(N-1)N/2个结果中，类别最多的即为所求分类。

一对其余：需要N个分类器，每个分类器的正类为N个类别中的一个（各不相同），其余类别作为反类；则当N个分类器中，仅有一个结果为正类，则取该正类作为最终分类结果，而若有多个预测为正类，则需要另外考虑置信度。

多对多：每次将若干的划分为正类，其余的划分为反类，不可随意选取。

纠错输出码：类别越多，编码越长，纠错能力越强。如果类别和编码长度一定，需要使得不同类别的编码差异越大，从而使得纠错能力越强

编码：对N个类别进行M次划分，每次划分将一部分划分为正类，一部分划分为反类，产生M个训练集以得到M个分类器。

解码：M个分类器分别对样本进行测试，所得预测标记组成一个编码，将该编码与各个类别各自的编码进行比较，差别最小的即为所求类别。

## 类别不平衡问题

分类任务中，训练样例数的差别很大，或者在进行多分类拆分时，得到的类别数量不平衡。

再缩放法：对于几率y/(1-y)，给它乘以比例（反例数/正例数），构成新的几率，当该值大于1则为正例。局限：训练集样本难以和真实样本毫无偏差。

欠采样法：去除一些示例使得正反例的数目接近。

过采样法：增加一些示例使得正反例数目接近。

阈值移动：将再缩放嵌入决策中。

# 决策树

根结点包含样本全集，每个结点包含的样本集合根据属性测试结果被划分到子结点中；叶结点对应决策结果，其余各个结点对应一个属性测试。

## 划分选择

结点纯度越来越高意味着结点包含的样本尽可能属同一类别。

### ID3决策树

纯度判断：用当前集合D和分类属性a计算信息增益，增益越大越好，问题在于该算法对于取值数目多的属性有偏好。

信息增益的计算：用当前总集合D的信息熵，减去所选属性的各个取值对应的子集 D^v 的信息熵，每个子集信息熵权重为|D^v|/|D|

增益率：针对上述问题的一个解决方案，将信息增益除以一个“固有值”，属性的取值数目越多，往往固有值越大，固有值直观上与上述权重有关。但该准则又对取值数目较少的属性有偏好。

启发式：先选取信息增益高于平均水平的属性，再从中选择增益率最高的。

### CART决策树

基尼值：Gini(D)反映了从数据集D中随机抽取两个样本，其类别标记不一样的概率。Gini(D)越小，数据集D的纯度越高。

属性的基尼指数：属性的各个取值对应的子集D^v对应的基尼值乘以其对应权重（同信息熵权重）所得结果之和。最优属性为候选属性中，基尼指数最小的那个。

## 剪枝

预剪枝：开销小，降低过拟合风险，但是增大了欠拟合的风险。

后剪枝：开销比较大，欠拟合风险很小，泛化性能往往优于预剪枝。

## 连续值与缺失值的处理

关键在于运用信息增益，对信息增益Gain(D,a)进行修改和推广。

连续值：对于样本中n个值，取n-1个划分点，每个划分点取值为属性相邻取值之间【a(i),a(i+1))。然后分别计算各个划分点进行二分后所得的信息增益，取信息增益最大的划分点作为划分方式；连续属性在划分后，在其后代结点中任可以对该连续属性进行划分。

缺失值：需要取出一个属性值完整的子集D'，以该集合计算信息增益进行划分；每个样本拥有一个权值w，划分时，属性值已知的样本保留该权值，若划分时属性值未知，放入该划分的所有子节点中，并将其权值w乘以一个当前属性值对应集合Dv所占D'的比例。即让一个样本以不同概率划分到各个子结点，概率即为各个属性值的比例。

有缺失值的信息增益计算：Gain(D,a)=ρ*Gain(D',a)，其中ρ为|D'|/|D|，即各属性完整的样本数量占总数量的比例。

多变量决策树：在进行划分时，不是看单一的某个属性值，而是将各个属性值对应的权值相加，看结果是否大于或小于某个值，得到的图像边界将是斜线。

# 神经网络

神经元：神经网络中简单的单元，最基本的成分。

感知机学习：通过输出调整权重，△wi为实际标记y减去输出,乘以学习率和xi。仅有输入和输出两层神经元；只有输出层神经元进行激活函数处理，即只拥有一层功能神经元，学习能力非常有限。

多层功能神经元：输出层和输入层之间的神经元被称为隐层或隐含层，包含隐层即为多层网络；隐层神经元和输出神经元都是功能神经元；用于解决非线性可分问题。

## 误差逆传播（BP神经网络）

BP算法：基于梯度下降策略，以目标的负梯度方向对参数进行调整，对于训练集中的样例一个个进行训练并更新参数。

累计BP算法：将训练集中所有样例均读取一遍后才对参数进行更新，一半来说，在累计误差下降到一定程度之后，进一步下降会特别缓慢，尤其是在训练集较大时，此时应该使用标准BP算法。

BP神经网络由于过强的学习能力容易遭遇过拟合，可以采用早停法和正则化两种策略。

早停法：将数据分为数据集和验证集，训练集用来计算梯度、更新权值和阈值，验证集用来计算误差，如果训练集误差降低但是验证集误差上升，则停止训练，返回具有最小验证集误差的连接权和阈值。</br>
正则化：在误差目标函数中增加一个用于描述网络复杂度的部分。</br>

## 全局最小和局部极小

跳出局部极小的策略：</br>
1、以多组不同参数值初始化多个神经网络，取其中误差最小的解作为最终参数。</br>
2、模拟退火：每一步以一定概率接受比当前解更差的结果。</br>
3、随机梯度下降：在计算梯度时加入随机因素，即便陷入局部极小点，计算出的梯度仍然可能不为0，有机会跳出局部极小。

## 其余常见神经网络

RBF网络

ART网络

SOM网络

级联相关网络

Elman网络

Boltzmann机

## 深度学习

