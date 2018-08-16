## tensorflow 应用的简单构建过程

tf.Graph()：将代码块自动整合成为一个整体。对于tensorflow来说，运算过程是数据从输入端流过一个个节点最后输出的过程。在节点处计算而在边上流动，节点和边组成了graph。

tf.session()：新建对话，session中包含了Tensor计算的环境。

tf.palceholder()：占位符，大小不定的一些参数。

tf.Variables()：变量声明。变量必须调用初始化操作后才能使用，一次性可以初始化所有变量。

### 定义模型和损失函数

计算每个分类的概率值（采用线性模型）：

```python
y = tf.nn.softmax(tf.matmul(x,W) + b)
```

定义损失函数为交叉熵：

```python
cross_entropy = -tf.reduce_sum(y_*tf.log(y))
```

### 训练模型（指定优化器）

定义一次迭代中的处理：

```python
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
```

反复进行迭代：

```python
for i in range(1000):
  batch = mnist.train.next_batch(50)
  train_step.run(feed_dict={x: batch[0], y_: batch[1]})
```

### 评估模型

将预测值与实际值比对，得到相等的数量。

```python
correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
```

## 神经网络的构建

### 权重初始化

定义W和b

```python
def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)
```

### 卷积和池化

```python
def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')
```

做每一层卷积时，定义该层的权重W和偏置b，然后调用卷积和池化操作。

tf.reshape()可以用于调整张量的维度。

tf.nn.relu用于做激活函数，激活函数在卷积和池化之间调用。

上一层池化后的输出作为下一层的输入。

### 全连接层

在全连接层需要定义该层的权重和偏置值，但无需再进行卷积，直接将输入与W作点积即可。需要指出，在该层会将张量展开成一维数组，然后与W做点积。

tf.matmul()用于张量间的点积计算。

### Dropout

防止过拟合，在输出层前增加Dropout。采用一个占位符来代表神经元输出在dropout层不变的概率。 

调用tf.nn.dropout()

### 输出层

同样需要定义该层的权重和偏置值。将全连接层的输出与W做点积得到最终输出结果，故b以及输出结果的维度应当与y的维度一致（譬如y中分类的个数）。

```python
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)
```

以上步骤对应与上一节中模型定义的部分。