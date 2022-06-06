import tensorflow as tf

tf.compat.v1.disable_eager_execution()
# Batch of input and target output (1x1 matrices)
x = tf.compat.v1.placeholder(tf.float32, shape=[None, 1, 1], name='input')
y = tf.compat.v1.placeholder(tf.float32, shape=[None, 1, 1], name='target')

# Trivial linear model
y_ = tf.identity(tf.compat.v1.layers.dense(x, 1), name='output')

# Optimize loss
loss = tf.reduce_mean(tf.square(y_ - y), name='loss')
optimizer = tf.compat.v1.train.GradientDescentOptimizer(learning_rate=0.01)
train_op = optimizer.minimize(loss, name='train')

init = tf.compat.v1.global_variables_initializer()

# tf.train.Saver.__init__ adds operations to the graph to save
# and restore variables.
saver_def = tf.compat.v1.train.Saver().as_saver_def()

print('Run this operation to initialize variables     : ', init.name)
print('Run this operation for a train step            : ', train_op.name)
print('Feed this tensor to set the checkpoint filename: ', saver_def.filename_tensor_name)
print('Run this operation to save a checkpoint        : ', saver_def.save_tensor_name)
print('Run this operation to restore a checkpoint     : ', saver_def.restore_op_name)

# Write the graph out to a file.
with open('graph.pb', 'wb') as f:
  f.write(tf.compat.v1.get_default_graph().as_graph_def().SerializeToString())