# tensorflow的一些API

tf.get_varialble()和tf.Variable()：

前者可以用于共享变量，会优先返回已创建的同名变量，后者调用时每次都会返回一个新的变量。采用tf.variable_scope()给变量指定命名空间，当其reuse参数为True时，会共享同一作用域内的同名变量。

```python
with tf.variable_scope("one"): 
    a = tf.get_variable("v", [1]) #a.name == "one/v:0" 
with tf.variable_scope("one"): 
    b = tf.get_variable("v", [1]) #创建两个名字一样的变量会报错 ValueError: Variable one/v already exists  
with tf.variable_scope("one", reuse = True): #注意reuse的作用。 
	c = tf.get_variable("v", [1]) #c.name == "one/v:0" 成功共享，因为设置了reuse 
assert a==c #Assertion is true, they refer to the same object.
```
tf.placeholder()：

生成占位符。占位符是输入数据的地方。譬如：

```python
x = tf.placeholder(tf.float32,[2,2])
y = tf.identify(x)
x_vals = np.random(2,2)
sess.run(y, feed_dict={x: x_vals})
```

tf.reduce_sum(input_tensor, reduction_indices=None, keep_dims=False, name=None)

压缩求和。可以按行、列分别求和、总体求和、保留原维度等。

```python
# 'x' is [[1, 1, 1]]
#         [1, 1, 1]]
tf.reduce_sum(x) ==> 6
tf.reduce_sum(x, 0) ==> [2, 2, 2]
tf.reduce_sum(x, 1) ==> [3, 3]
tf.reduce_sum(x, 1, keep_dims=True) ==> [[3], [3]]
tf.reduce_sum(x, [0, 1]) ==> 6
```

tf.reduce_max()：求取各个维度上的最大值。

tf.reduce_min()：求取各维度上的最小值。

tf.reduce_mean()：求均值。

tf.data.Iterator.from_string_handle():

获取数据的迭代器。

tf.nn.embedding_lookup（tensor, id）：

选取tensor中id处的元素；如下例子为读取c中索引为1和3处的元素。

```python
c = np.random.random([10,1])
b = tf.nn.embedding_lookup(c, [1, 3])
with tf.Session() as sess:
	sess.run(tf.initialize_all_variables())
	print sess.run(b)
	print c
```

tf.nn.dropout(x, keep_prob, noise_shape=None, seed=None, name=None)：

防止过拟合，一般用在全连接层。其中keep_prob要定义为占位符，x为上层输出结果。drop_out的作用是使得所有神经元，每次迭代中都有keep_prob的几率不更新，以防止过拟合发生，当keep_prob为1时，用于test。

tf.expand_dims(input, axis=None, name=None, dim=None)：

在第axis处扩展一个维度（可以理解为增加一层封装）。

譬如：将含两个元素的一维数组t转化为一个含一个元素的二维数组，第二维中包含两个元素。

[0, 0] => [[0, 0]]

```python
# 't' is a tensor of shape [2]
shape(expand_dims(t, 0)) ==> [1, 2]
shape(expand_dims(t, 1)) ==> [2, 1]
shape(expand_dims(t, -1)) ==> [2, 1]
# 't2' is a tensor of shape [2, 3, 5]
shape(expand_dims(t2, 0)) ==> [1, 2, 3, 5]
shape(expand_dims(t2, 2)) ==> [2, 3, 1, 5]
shape(expand_dims(t2, 3)) ==> [2, 3, 5, 1]
```
tf.squeeze(input, squeeze_dims=None, name=None)：

这行tf.expand_dims的反向操作，即将某一维度去除，将那一维的向量（或理解为数组）转化为元素；也可以指定去除哪一维。

[[0, 0]] => [0, 0]
```python
# 't' is a tensor of shape [1, 2, 1, 3, 1, 1]
shape(squeeze(t)) ==> [2, 3]
#Or, to remove specific size 1 dimensions:
# 't' is a tensor of shape [1, 2, 1, 3, 1, 1]
shape(squeeze(t, [2, 4])) ==> [1, 2, 3, 1]
```

tf.slice(input, begin, size, name=None):

从begin处开始切片，切片的个数为size中包含的个数，切片结果的形状为size的形状。

```python
sess = tf.Session()
a = tf.constant([[1, 1, 1],[2, 2, 2], [3, 3, 3]])
result = tf.slice(a, [1 ,0], [2, 3])
print(sess.run(result))
#'result' is a tensor:
#[[2 2 2]
# [3 3 3]]
```

x.shape.as_list():

获取某个张量的形状，以list的形式输出

